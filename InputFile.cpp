#include "InputFile.h"

InputFile::InputFile(const std::string& name) {
    file.open(name.c_str(), std::ifstream::in);
    if (!file.is_open()) {
        throw std::exception();
    }
}

InputFile::~InputFile() {
    if (file.is_open()) {
        file.close();
    }
}

std::istream& InputFile::stream() {
    return file;
}
