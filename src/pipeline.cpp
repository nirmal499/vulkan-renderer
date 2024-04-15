#include <pipeline/pipeline.hpp>
#include <iostream>

Pipeline::Pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
    this->create_graphics_pipeline(vertex_file_path, fragment_file_path);
}

std::vector<char> Pipeline::read_file(const std::string& file_path)
{
    std::ifstream infile{file_path, std::ios::ate | std::ios::binary };
    if(!infile.is_open())
    {
        throw std::runtime_error("Failed to open file " + file_path);
    }

    size_t file_size = static_cast<size_t>(infile.tellg());
    std::vector<char> buffer(file_size); /* It will resize the buffer for the provided file_size */

    infile.seekg(0); /* seek to beginning of the file */
    infile.read(buffer.data(), file_size);

    infile.close();
    return buffer;
}

void Pipeline::create_graphics_pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
    auto vert_code = Pipeline::read_file(vertex_file_path);
    auto frag_code = Pipeline::read_file(fragment_file_path);

    std::cout << "Vertex shader code size : " << vert_code.size() << "\n";
    std::cout << "Fragment shader code size : " << frag_code.size() << "\n";
}