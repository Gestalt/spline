#include "OutputFile.h"

OutputFile::OutputFile(const std::string& name) {
    file.open(name.c_str(), std::ofstream::out);
    if (!file.is_open()) {
        throw std::exception();
    }
}

OutputFile::~OutputFile() {
    if (file.is_open()) {
        file.close();
    }
}

std::ostream& OutputFile::stream() {
    return file;
}
