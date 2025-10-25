
int getDirFileNames(const std::string dir, std::vector<std::string>& files);

// Primarily for loading shaders, however does arbitrarily load files
std::vector<char> readFile(const std::string&);
