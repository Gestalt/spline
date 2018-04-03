#include <sstream>
#include "InputFile.h"

InputFile::InputFile(const std::string& name) {
    file.open(name.c_str(), std::ifstream::in);
    if (!file.is_open()) {
        std::stringstream err;
        err << "Failed to open input file: "
            << name.c_str();
        throw std::runtime_error(err.str());
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
