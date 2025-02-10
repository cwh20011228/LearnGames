#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"

class SceneMain : public Scene
{
    SceneMain();
    ~SceneMain();

    void init() override;
    void handleEvent(SDL_Event* event) override;
    void update() override;
    void render() override;
    void clean() override;
};
#endif