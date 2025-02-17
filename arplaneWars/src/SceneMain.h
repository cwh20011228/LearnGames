#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include <memory>
#include "Scene.h"
#include "object.h"

class Game;

class SceneMain : public Scene
{
public:
    SceneMain();
    ~SceneMain();

    void init() override;
    void handleEvent(SDL_Event* event) override;
    void update() override;
    void render() override;
    void clean() override;

private:
    std::shared_ptr<Player> mPlayer;
    Game& mGame;
};
#endif