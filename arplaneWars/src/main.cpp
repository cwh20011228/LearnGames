#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"

int main(int, char **)
{
    std::shared_ptr<Game> mGame = std::make_shared<Game>();
    mGame->init();
    mGame->run();

    return 0;
}