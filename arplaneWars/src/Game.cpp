#include "Game.h"

Game::Game(){
    mCurrentScene = std::make_shared<Scene>();
}

Game::Game(int width, int height)
        : mWidth(width)
        , mHeight(height){
    mCurrentScene = std::make_shared<Scene>();
}

Game& Game::getInstance(){
    static Game instance;
    return instance;
}

SDL_Window* Game::getWindow() const{
    return mWindow;
}

SDL_Renderer* Game::getRender() const{
    return mRenderer;
}

int Game::getWidth() const{
    return mWidth;
}

int Game::getHeight() const{
    return mHeight;
}

Game::~Game(){
    if (mCurrentScene){
        mCurrentScene->clean();
    }

    clean();
}

void Game::run(){
    while (mIsRunning){
        SDL_Event event;
        handleEvent(&event);
        
        update();

        render();        
    }
}

void Game::init(){
    // 1. SDL初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL无法初始化 SDL: %s\n", SDL_GetError());
        mIsRunning = false;
    }
    // 1.1. 创建窗口
    mWindow = SDL_CreateWindow("SDL_AirplaneWars",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "创建窗口失败: %s\n", SDL_GetError());
        mIsRunning = false;
    }

    // 1.2. 创建渲染器
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "渲染器创建失败: %s\n", SDL_GetError());
        mIsRunning = false;
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,"SDL_image初始化失败: %s\n",IMG_GetError());
        mIsRunning = false;
    }

    // 切换为初始场景
    changeScene(std::make_shared<SceneMain>());
}

void Game::clean(){
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::changeScene(std::shared_ptr<Scene> scene){
    if (mCurrentScene){
        mCurrentScene->clean();
    }

    if (scene){
        mCurrentScene = std::move(scene);
        mCurrentScene->init();
    }else{
        mCurrentScene.reset();
    }
}

void Game::handleEvent(SDL_Event* event){
    // SDL_PollEvent : 检查并获取事件
    while (SDL_PollEvent(event)){
        if (event->type == SDL_QUIT){
            mIsRunning = false;
        }
        mCurrentScene->handleEvent(event);
    }
}

void Game::update(){
    mCurrentScene->update();
}

void Game::render(){
    // 渲染器清屏
    SDL_RenderClear(mRenderer);

    mCurrentScene->render();

    // 更新屏幕内容
    SDL_RenderPresent(mRenderer);
}