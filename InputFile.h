#ifndef InputFileH
#define InputFileH

#include <fstream>

class InputFile {
    public:
        InputFile(const std::string& name);
        ~InputFile();
        std::istream& stream();
    private:
        InputFile(const InputFile&);
        InputFile& operator=(const InputFile&);
    private:
        std::ifstream file;
};

#endif
