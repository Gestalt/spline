#ifndef OutputFileH
#define OutputFileH

#include <fstream>

class OutputFile {
    public:
        OutputFile(const std::string& name);
        ~OutputFile();
        std::ostream& stream();
    private:
        OutputFile(const OutputFile&);
        OutputFile& operator=(const OutputFile&);
    private:
        std::ofstream file;
};

#endif

