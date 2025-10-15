#include "shared.h"
#include <filesystem>

int getDirFileNames(const std::string dir, std::vector<std::string>& files) {
    for (const auto& entry : std::filesystem::directory_iterator(dir))
        files.emplace_back(entry.path().filename().string());

    return 1;
}
