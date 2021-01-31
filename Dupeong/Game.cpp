//
//  Game.cpp
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#include "Game.h"


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
    
    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
    
}

void Game::UpdateGame() {
    while(true) {
        
    }
}

void Game::GenerateOutput() {
    
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

