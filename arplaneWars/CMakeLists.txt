# 标题
cmake_minimum_required(VERSION 3.5.0)
project(airplaneWars VERSION 0.1.0 LANGUAGES C CXX)

# 启用编译命令导出
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 当使用 gcc 或 clang 编译器时, 设置输入代码的编码格式为 utf-8
add_compile_options("$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-finput-charset=UTF-8>")
# 当使用 MSVC 编译器时, 设置输入代码的编码格式为 utf-8
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# 设置目标名称 
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并处理预设的SDL2库
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# 编译可执行文件
add_executable(${TARGET} 
                "src/main.cpp"
                "src/Scene.cpp"
                "src/Game.cpp"
                "src/SceneMain.cpp"
                "src/SceneStart.cpp"
                "src/SceneEnd.cpp")

# 链接库
target_link_libraries(${TARGET}
                        ${SDL2_LIBRARIES}
                        SDL2_image::SDL2_image
                        SDL2_mixer::SDL2_mixer
                        SDL2_ttf::SDL2_ttf
                        )


# if(WIN32)
# include_directories("E:/Library/SDL2/include") # 头文件的路径
# link_directories("E:/Library/SDL2/lib/x64") # 链接库的路径
# elseif(UNIX)
# include_directories(/usr/include/SDL2)
# link_directories(/usr/lib/x86_64-linux-gnu)
# elseif(APPLE)
# include_directories(/usr/local/include/SDL2)
# link_directories(/usr/local/lib)
# endif()