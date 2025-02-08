#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int, char **)
{
    std::cout << "hello world 你好" << std::endl;
    SDL_Log("SDL version:%d.%d.%d",SDL_MAJOR_VERSION,SDL_MINOR_VERSION,SDL_PATCHLEVEL);

    // 1. SDL初始化
    if(SDL_Init(SDL_INIT_EVERYTHING ) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"无法初始化 SDL: %s",SDL_GetError());
        return 1;
    }
    // 1.1. 创建窗口
    SDL_Window* window = SDL_CreateWindow("SDL Example", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    // 1.2. 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "渲染器创建失败: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    std::cout<< "SDL_GetNumRenderDrivers = " << SDL_GetNumRenderDrivers() << std::endl;
    SDL_RendererInfo info;
    std::cout << "SDL_GetRenderDriverInfo = " << SDL_GetRenderDriverInfo(-1,&info)<<std::endl;


    // 2. SDL_image初始化
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG ) == 0){
        std::cerr<<"IMG_Init Error:"<<IMG_GetError()<<std::endl;
        return 1;
    }
    // 加载图片
    SDL_Texture *image = IMG_LoadTexture(renderer,"./assets/image/bg.png");


    // 3. SDL_mixer初始化（音频）
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0){
        std::cerr<<"Mix_openAudio Error:"<<Mix_GetError()<<std::endl;
        return 1;
    }
    // 读取音乐
    Mix_Music *music = Mix_LoadMUS("assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    // 播放音乐
    if(!music){
        std::cerr << "加载音乐失败：" << Mix_GetError() <<std::endl;
        Mix_CloseAudio();
        return 1;
    }
    Mix_PlayMusic(music,-1);


    // 4. SDL_ttf初始化（字体）
    if(TTF_Init() == -1){
        std::cerr<<"TTF_Init Error:"<<TTF_GetError()<<std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf",24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }   
    // 渲染字体
    SDL_Color color = {255,255,255};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font,"Hello SDL!",color);
    SDL_Texture *ttfTexture = SDL_CreateTextureFromSurface(renderer,surface);

    bool running = true;
    SDL_Event event;
    while(running){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                break;
            }

            //  设置渲染颜色（背景颜色）
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            //  渲染器清屏
            SDL_RenderClear(renderer);

            //  渲染器设置颜色
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            //  画一个长方形
            SDL_Rect rect{100,100,300,400};
            SDL_RenderFillRect(renderer,&rect);
            
            //  画图片
            SDL_Rect rect1{200,200,300,400};
            SDL_RenderCopy(renderer,image,NULL,&rect1);

            // 画字体
            SDL_Rect rect2{300,300,surface->w,surface->h};
            SDL_RenderCopy(renderer,ttfTexture,NULL,&rect2);

            //  更新屏幕内容
            SDL_RenderPresent(renderer);
        }
    }

    // 销毁图片资源
    SDL_DestroyTexture(image);
    IMG_Quit();     // 关闭SDL_image

    // 清理音乐资源
    Mix_FreeMusic(music);
    Mix_CloseAudio();   
    Mix_Quit();
    
    // 清理字体资源
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(ttfTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // 销毁渲染器
    SDL_DestroyRenderer(renderer);
    // 销毁窗口
    SDL_DestroyWindow(window);
    // 退出SDL
    SDL_Quit();

    return 0;
}