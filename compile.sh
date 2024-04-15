#! /usr/bin/bash

glslc_PATH="/home/nbaskey/my_opt/glslc/install/bin"

${glslc_PATH}/glslc shaders/simple_shader.vert -o shaders/SPIRV/simple_shader.vert.spv
${glslc_PATH}/glslc shaders/simple_shader.frag -o shaders/SPIRV/simple_shader.frag.spv