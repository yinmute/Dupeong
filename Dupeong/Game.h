//
//  Game.h
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#pragma once
#include "SDL.h"


struct Vector2 {
    float x;
    float y;
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
    // Game should continue to run
    bool mIsRunning;
    
    // Pong specific
    // Position of the paddle
    Vector2 mPaddlePos;
    // Position of the ball
    Vector2 mBallPos;    
};
