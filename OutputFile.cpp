#include <sstream>
#include "OutputFile.h"

OutputFile::OutputFile(const std::string& name) {
    file.open(name.c_str(), std::ofstream::out);
    if (!file.is_open()) {
        std::stringstream err;
        err << "Failed to open output file: "
            << name.c_str();
        throw std::runtime_error(err.str());
    }
}

OutputFile::~OutputFile() {
    if (file.is_open()) {
        file.close();
    }
}

std::ofstream& OutputFile::stream() {
    return file;
}
