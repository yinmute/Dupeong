//
//  main.cpp
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#include <iostream>
#include "SDL.h"
#include "Game.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "Test";
    std::cout << "catdog";
    
    Game game;
    bool success = game.Initialize();
    
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
