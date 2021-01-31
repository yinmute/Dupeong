//
//  Game.cpp
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#include "Game.h"

const int thickness = 15;

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
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
}

void Game::UpdateGame() {
    
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
    
    // Draw right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(mRenderer, &wall);
    
    // Draw paddle
    SDL_Rect paddle {
        static_cast<int>(m),
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

