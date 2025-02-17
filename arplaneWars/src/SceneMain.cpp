#include <SDL_image.h>
#include "SceneMain.h"
#include "Game.h"

SceneMain::SceneMain():mGame(Game::getInstance()){
    mPlayer = std::make_shared<Player>();
}

SceneMain::~SceneMain(){
}

void SceneMain::init(){
    mPlayer->texture = IMG_LoadTexture(mGame.getRender(),"assets/image/SpaceShip.png");
    SDL_QueryTexture(mPlayer->texture, nullptr, nullptr, &mPlayer->width, &mPlayer->height);
    mPlayer->width /= 4;
    mPlayer->height /= 4;
    mPlayer->position.x = mGame.getWidth() / 2  - mPlayer->width / 2 ;
    mPlayer->position.y = mGame.getHeight() - mPlayer->height - 15; 
    
}

void SceneMain::handleEvent(SDL_Event* event){
}

void SceneMain::update(){
}

void SceneMain::render(){
    SDL_Rect playerRect = {
        static_cast<int>(mPlayer->position.x),
        static_cast<int>(mPlayer->position.y),
        mPlayer->width,
        mPlayer->height
    };
    SDL_RenderCopy(mGame.getRender(),mPlayer->texture,nullptr,&playerRect);
}

void SceneMain::clean() {

}