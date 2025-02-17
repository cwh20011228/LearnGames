#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <iostream>
#include "Scene.h"
#include "SceneMain.h"

class Game
{
private:
    Game();
    Game(int width, int height);

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    ~Game();
    void run(); // 主循环
    void init();
    void clean();
    void changeScene(std::shared_ptr<Scene> scene);

    void handleEvent(SDL_Event* event);
    void update();
    void render();

    static Game& getInstance();
    SDL_Window* getWindow() const;
    SDL_Renderer* getRender() const;
    int getWidth() const;
    int getHeight() const;

private:
    bool mIsRunning{true};
    std::shared_ptr<Scene> mCurrentScene;
    SDL_Window *mWindow{nullptr};
    SDL_Renderer *mRenderer{nullptr};
    int mWidth{600};
    int mHeight{800};
};

#endif