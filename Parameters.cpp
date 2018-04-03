#include <sstream>
#include <iostream>
#include <algorithm>
#include "Parameters.h"

static const std::string kDefaultOutput = std::string("output.txt");

Parameters::Parameters(Helper helper_)
    : params(std::vector<std::string>())
    , source(std::string())
    , destination(std::string())
    , output(std::string())
    , spline(std::string())
    , verbose(false)
    , helper(helper_) {
}

bool Parameters::getVerbose() const {
    return verbose;
}

const std::string& Parameters::getSource() const {
    return source;
}

const std::string& Parameters::getDestination() const {
    return destination;
}

const std::string& Parameters::getOutput() const {
    return output;
}

const std::string& Parameters::getSpline() const {
    return spline;
}

bool Parameters::parse(int argc, char** argv) {

    for (int i = 0; i < argc; i++) {
        std::stringstream ss;
        ss << argv[i];

        params.push_back(ss.str());
        std::cout << "i=" << i << " arg=" << ss.str() << std::endl;
    };

    std::string help = readFlag("--help", "-h");
    if (!help.empty()) {
        printHelp();
    }

    output = readPair("--output", "-o");
    if (output.empty()) {
        output = kDefaultOutput;
    }

    std::string verbosity = readFlag("--verbose", "-v");
    if (!verbosity.empty()) {
        verbose = true;
    }

    source = readPair("--source", "-s");
    if (source.empty()) {
        throw std::exception();
    }

    destination = readPair("--destination", "-d");
    if (destination.empty()) {
        throw std::exception();
    }

    spline = readPair("--spline");
    if (spline.empty()) {
        throw std::exception();
    }

    return true;
}

const std::string Parameters::readFlag(const std::string& longOption, const std::string& shortOption) const {
    std::string res;
    std::string param = shortOption.empty() ? longOption : shortOption;

    if (param.empty()) {
        return res;
    }

    std::vector<std::string>::const_iterator it = std::find(params.begin(), params.end(), param);

    if (it == params.end()) {
        return res;
    }

    res = *it;

    return res;
}

const std::string Parameters::readPair(const std::string& longOption, const std::string& shortOption) const {
    std::string res;
    std::string param = shortOption.empty() ? longOption : shortOption;

    if (param.empty()) {
        return res;
    }

    std::vector<std::string>::const_iterator it = std::find(params.begin(), params.end(), param);

    if (it == params.end()) {
        return res;
    }

    ++it;

    if (it == params.end()) {
        return res;
    }
    res = *it;

    return res;
}

void Parameters::printHelp() const {
    if (helper) {
        helper();
    }
}
