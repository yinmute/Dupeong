//
//  Game.h
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#pragma once
#include "SDL.h"

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
    
    // Game should continue to run
    bool mIsRunning;
    
    
};
