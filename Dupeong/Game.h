//
//  Game.h
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#pragma once
#include "SDL.h"
#include <vector>


struct Vector2 {
    float x;
    float y;
};

struct Ball {
    Vector2 position;
    Vector2 velocity;
    int numberOfBounces;
};

class Game {
    
public:
    Game();
    
    // Initialize the game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shut down the game
    void Shutdown();
    
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    // Window created by SDL
    SDL_Window* mWindow;
    // SDL Renderer
    SDL_Renderer* mRenderer;
    // Number of ticks since start of the game
    Uint32 mTicksCount;
    // Game should continue to run
    bool mIsRunning;
    
    // Pong specific
    // Direction of paddle
    int mPaddleDir;
    // Directon of the second paddle
    int mSecondPaddleDir;
    // Position of the paddle
    Vector2 mPaddlePos;
    // Position of the second paddle
    Vector2 mSecondPaddlePos;
    // Position of the ball
    Vector2 mBallPos;
    // Velocity of the ball
    Vector2 mBallVel;
    // Array of balls
    std::vector<Ball> balls;
};
