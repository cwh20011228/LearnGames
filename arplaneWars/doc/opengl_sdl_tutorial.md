# OpenGL, C++ and SDL Tutorial

This tutorial will guide you through setting up and using OpenGL with C++ and SDL.

## 1. Setup

### 1.1 Install Dependencies
- SDL2
- SDL2_image
- SDL2_ttf
- GLEW (OpenGL Extension Wrangler Library)

### 1.2 CMake Configuration
Create a CMakeLists.txt file with the following content:

```cmake
cmake_minimum_required(VERSION 3.10)
project(OpenGL_SDL_Example)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(main main.cpp)

target_link_libraries(main ${SDL2_LIBRARIES})
target_link_libraries(main ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(main ${SDL2_TTF_LIBRARIES})
target_link_libraries(main ${OPENGL_LIBRARIES})
```

## 2. Basic Structure

### 2.1 Main.cpp
```cpp
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "OpenGL with SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    // Create OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "OpenGL context could not be created! Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return 1;
    }

    // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

## 3. Drawing a Triangle

### 3.1 Vertex Shader
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
```

### 3.2 Fragment Shader
```glsl
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
```

### 3.3 Main Program Updates
Add shader compilation and triangle drawing code to the main program.

## 4. Text Rendering with SDL_ttf

### 4.1 Initialize TTF
```cpp
if (TTF_Init() == -1) {
    std::cerr << "TTF could not initialize! Error: " << TTF_GetError() << std::endl;
    return 1;
}
```

### 4.2 Load Font and Render Text
```cpp
TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
SDL_Color color = {255, 255, 255};
SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello World!", color);
```

## 5. Cleanup
Remember to properly clean up all resources when closing the application.

## 6. Next Steps
- Add texture support
- Implement 3D transformations
- Add lighting
- Create a simple game

This tutorial provides the basic setup for using OpenGL with C++ and SDL. You can expand upon this foundation to create more complex applications.
