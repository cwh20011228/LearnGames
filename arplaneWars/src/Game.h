#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <memory>
#include <iostream>
#include "Scene.h"
#include "SceneMain.h"

class Game
{
public:
    Game();
    Game(int width, int height);
    ~Game();
    void run(); // 主循环
    void init();
    void clean();
    void changeScene(std::shared_ptr<Scene> scene);

    void handleEvent(SDL_Event* event);
    void update();
    void render();

private:
    bool mIsRunning{true};
    std::shared_ptr<Scene> mCurrentScene;
    SDL_Window *mWindow{nullptr};
    SDL_Renderer *mRenderer{nullptr};
    int mWidth{600};
    int mHeight{800};
};

#endif