cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main)

find_package(Vulkan REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(main 
    main.cpp

    src/first_app.cpp
    src/window.cpp
    src/pipeline.cpp
)

target_include_directories(main
    
    # PRIVATE external/glfw/include # No need cause it is getting included automatically when we are linking to it
    PRIVATE external/glm

    PRIVATE src/include
)

target_link_libraries(main
    PRIVATE glfw
    PRIVATE Vulkan::Vulkan
)