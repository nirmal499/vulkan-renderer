#pragma once

#include <window/window.hpp>
#include <pipeline/pipeline.hpp>

#define SHADER_PATH "/home/nbaskey/Desktop/nirmal/projects/vulkan_renderer/shaders/SPIRV/"

class FirstApp
{
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        
        void run();
    private:
        Window m_window{WIDTH, HEIGHT, "Learning VULKAN"};
        Pipeline m_pipeline{SHADER_PATH "simple_shader.vert.spv", SHADER_PATH "simple_shader.frag.spv"};
};