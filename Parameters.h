#ifndef ParametersH
#define ParametersH

#include <vector>
#include <string>

class Parameters {
    public:
        Parameters();

        bool getVerbose() const;
        const std::string& getSource() const;
        const std::string& getDestination() const;
        const std::string& getOutput() const;
        const std::string& getSpline() const;

        const std::string parse(int argc, char** argv);

        const std::string readFlag(const std::string& longOption, const std::string& shortOption = "") const;
        const std::string readPair(const std::string& longOption, const std::string& shortOption = "") const;
    private:
        std::vector<std::string> params;
        std::string source;
        std::string destination;
        std::string output;
        std::string spline;
        bool verbose;
};

#endif

