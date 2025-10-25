#pragma once

int getDirFileNames(const std::string, std::vector<std::string>&);

// Primarily for loading shaders, however does arbitrarily load files
std::vector<char> readFile(const std::string&);
