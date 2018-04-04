#include <sstream>
#include "OutputFile.h"

app::OutputFile::OutputFile(const std::string& name) {
    file.open(name.c_str(), std::ofstream::out);
    if (!file.is_open()) {
        std::stringstream err;
        err << "Failed to open output file: "
            << name.c_str();
        throw std::runtime_error(err.str());
    }
}

app::OutputFile::~OutputFile() {
    if (file.is_open()) {
        file.close();
    }
}

std::ofstream& app::OutputFile::stream() {
    return file;
}
