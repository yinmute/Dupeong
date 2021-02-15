//
//  main.cpp
//  Dupeong
//
//  Created by Nesiolovskiy, Artem on 1/30/21.
//

#include "SDL.h"
#include "Game.h"

int main(int argc, char * argv[]) {
    Game game;
    bool success = game.Initialize();
    
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
