#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene
{
public:
    Scene();
    ~Scene();
    virtual void init();
    virtual void handleEvent(SDL_Event* event);
    virtual void update();
    virtual void render();
    virtual void clean();
};

#endif