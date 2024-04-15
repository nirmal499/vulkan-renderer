#pragma once

#include <types/types.hpp>

class Pipeline
{
    public:
        Pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path);

    private:
        static std::vector<char> read_file(const std::string& file_path);
        void create_graphics_pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path);
};