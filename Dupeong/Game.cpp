//
//  Game.cpp
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#include "Game.h"
#include <iostream>

using namespace std;

const int thickness = 15;
const float paddleH = 100.0f;
const float offset = 3.0f;
const float speedMultiplier = 0.75f;
const float bounceTimes = 3;

// Update paddle position based on direction
void updatePaddlePosition(Vector2& paddlePosition, int paddleDirection, float deltaTime) {
    if (paddleDirection != 0) {
        paddlePosition.y += paddleDirection * 600.0f * deltaTime;
        // Make sure paddle doesn't move off screen
        if (paddlePosition.y < (paddleH/2.0f + thickness)) {
            paddlePosition.y = paddleH/2.0f + thickness;
        }
        else if (paddlePosition.y > (768.0f - paddleH/2.0f - thickness)) {
            paddlePosition.y = 768.0f - paddleH/2.0f - thickness;
        }
    }
}


Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mPaddleDir(0)
{
    
}

bool Game::Initialize() {
    // Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    // Create an SDL Window
    mWindow = SDL_CreateWindow(
                           "Dupeong", // Window title
                           100, // Top left x-coordinate of window
                           100, // Top left y-coordinate of window
                           1024, // Width of window
                           768, // Height of window
                           0 // Flags (0 for no flags set))
                           );
    
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    
    // Create SDL renderer
    mRenderer = SDL_CreateRenderer(
                                   mWindow, // Window to create renderer for
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s ", SDL_GetError);
        return false;
    }
    
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f/2.0f;
    mSecondPaddlePos.x = 1014.0f - thickness;
    mSecondPaddlePos.y = 768.0f/2.0f;
    mBallPos.x = 1024.0f/2.0f;
    mBallPos.y = 768.0f/2.0f;
    mBallVel.x = -200.0f * speedMultiplier;
    mBallVel.y = 235.0f * speedMultiplier;
    
    Ball ball1 = {
        mBallPos.x,
        mBallPos.y,
        mBallVel.x,
        mBallVel.y,
        0,
    };
    mBalls.push_back(ball1);
    
    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
                // If we get an SDL_QUIT event, end loop
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
    
    // Update paddle direction based on W/S keys
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
    }
    
    // Update second paddle direction based on I/K keys
    mSecondPaddleDir = 0;
    if (state[SDL_SCANCODE_I]) {
        mSecondPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_K]) {
        mSecondPaddleDir += 1;
    }
    
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    
    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();
    
    // Update first paddle position
    updatePaddlePosition(mPaddlePos, mPaddleDir, deltaTime);
    // Update second paddle position
    updatePaddlePosition(mSecondPaddlePos, mSecondPaddleDir, deltaTime);

    // Flag to add new ball if needed
    bool addNewBall = false;
    // Save veolicty for a new ball
    float velX = 0;
    float velY = 0;
    
    // Update balls position based on ball velocity
    for(auto& ball: mBalls) {
        // Update ball position based on ball velocity
        ball.position.x += ball.velocity.x * deltaTime;
        ball.position.y += ball.velocity.y * deltaTime;
                
        // Bounce if needed
        // Did we intersect with the paddle?
        float diff = mPaddlePos.y - ball.position.y;
        float diffSecond = mSecondPaddlePos.y - ball.position.y;
        // Take absolute value of difference
        diff = (diff > 0.0f) ? diff : -diff;
        diffSecond = (diffSecond > 0.0f) ? diffSecond : -diffSecond;
        if (
            // Our y-difference is small enough
            diff <= paddleH / 2.0f &&
            // We are in the correct x-position
            ball.position.x < (10.0f + thickness*1.5 - offset) && ball.position.x > (5.0f + thickness*1.5 - offset) &&
            // The ball is moving to the left
            ball.velocity.x < 0.0f) {
            ball.velocity.x *= -1.0f;
            ball.numberOfBounces += 1;
        }
        // Did the ball go off the screen? (if so, end game)
        else if (ball.position.x <= 0.0f) {
            mIsRunning = false;
            cout << "Right player won the game!" << endl;
        }
		cout << mSecondPaddlePos.y << " " << ball.position.y << " " << diffSecond << " " << paddleH / 2.0f << " " << ball.position.x << endl;
        if (
            // Our y-difference is small enough
            diffSecond <= paddleH / 2.0f &&
            // We are in the correct x-position
            ball.position.x < (1019.0f - thickness/2 + offset) && ball.position.x > (1014.0f - thickness*1.5 + offset) &&
            // The ball is moving to the right
            ball.velocity.x > 0.0f) {
            ball.velocity.x *= -1.0f;
            ball.numberOfBounces += 1;
        }
        else if (ball.position.x >= 1024.f) {
            mIsRunning = false;
            cout << "Left player won the game!" << endl;
        }
        
        // Did the ball collide with the top wall?
        if (ball.position.y <= (thickness * 1.5 - offset) && ball.velocity.y < 0.0f) {
            ball.velocity.y *= -1;
        }
        
        // Did the ball collide with the bottom wall?
        else if (ball.position.y >= (768 - thickness * 1.5 + offset) &&  ball.velocity.y > 0.0f) {
            ball.velocity.y *= -1;
        }
        // Each 10 bounces off the paddle - spawn a new ball in opposite direction
        if (ball.numberOfBounces == bounceTimes) {
            addNewBall = true;
            ball.numberOfBounces = 0;
            velX = ball.velocity.x;
            velY = ball.velocity.y;
        }
    }
    
    // Adding a new ball if flag was set
    if (addNewBall) {
        Ball newBall = {
            mBallPos.x,
            mBallPos.y,
            velX,
            -velY,
            0,
        };
        mBalls.push_back(newBall);
        velX = 0;
        velY = 0;
        addNewBall = false;
    }
    
}

void Game::GenerateOutput() {
    // Set draw color to blue
    SDL_SetRenderDrawColor(
                           mRenderer,
                           168,
                           168,
                           168,
                           255);
    // Clear back buffer
    SDL_RenderClear(mRenderer);
    
    // Draw walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    
    // Draw top wall
    SDL_Rect wall{
        0, // Top left x
        0, // Top left y
        1024, // Width
        thickness // Height
    };
    SDL_RenderFillRect(mRenderer, &wall);
    
    // Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    
    // Draw paddle
    SDL_Rect paddle {
        static_cast<int>(mPaddlePos.x),
        static_cast<int>(mPaddlePos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    
    // Draw second paddle
    SDL_Rect secondPaddle {
        static_cast<int>(mSecondPaddlePos.x),
        static_cast<int>(mSecondPaddlePos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &secondPaddle);
    
    // Draw balls
    for(const auto& ball: mBalls) {
            SDL_Rect ballToDraw{
            static_cast<int>(ball.position.x - thickness/2),
            static_cast<int>(ball.position.y - thickness/2),
            thickness,
            thickness,
        };
        SDL_RenderFillRect(mRenderer, &ballToDraw);
    }
    
    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
    
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

