#include "shared.h"
#include <fstream>

int getDirFileNames(const std::string dir, std::vector<std::string>& files) {
    for (const auto& entry : std::filesystem::directory_iterator(dir))
        files.emplace_back(entry.path().filename().string());

    return 1;
}

std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    std::vector<char> buffer(file.tellg());

    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    file.close();

    return buffer;
}
