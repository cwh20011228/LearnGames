```cmake

# 标题
cmake_minimum_required(VERSION 3.5.0)
project(airplaneWars VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# 设置目标名称 
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并处理预设的SDL2库
find_package(SDL2 REQUIRED)

# 编译可执行文件
add_executable(${TARGET} hello.cpp)

# 链接库
target_link_libraries(${TARGET}
                        SDL2::SDL2
                        SDL2::SDL2main)


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
```
