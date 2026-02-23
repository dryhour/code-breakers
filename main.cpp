#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

const std::string filename = "textfile.txt";

std::string readFile() {
    std::string content;
    std::ifstream file(filename);

    std::getline(file, content);

    return content;
}

void appendFile(std::string& text) {
    std::ofstream file(filename, std::ios::app);
    file << text;
}

void overwriteFile(std::string& text) {
    std::ofstream file(filename);
    file << text;
}

int main() {
    return 0;
}