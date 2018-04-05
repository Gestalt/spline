#include <sstream>
#include <iostream>
#include <algorithm>
#include "Parameters.h"

static const std::string kDefaultOutput = std::string("output.txt");

app::Parameters::Parameters()
    : params(std::vector<std::string>())
    , source(std::string())
    , destination(std::string())
    , output(std::string())
    , spline(std::string())
    , verbose(false) {
}

bool app::Parameters::getVerbose() const {
    return verbose;
}

const std::string& app::Parameters::getSource() const {
    return source;
}

const std::string& app::Parameters::getDestination() const {
    return destination;
}

const std::string& app::Parameters::getOutput() const {
    return output;
}

const std::string& app::Parameters::getSpline() const {
    return spline;
}

const std::string app::Parameters::parse(int argc, char** argv) {

    for (int i = 0; i < argc; i++) {
        std::stringstream ss;
        ss << argv[i];

        params.push_back(ss.str());
    };

    std::string help = readFlag("--help", "-h");
    if (!help.empty()) {
        return std::string("Spline application v.1.0");
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
        return std::string("Missing required argument: --source|-s");
    }

    destination = readPair("--destination", "-d");
    if (destination.empty()) {
        return std::string("Missing required argument: --destination|-d");
    }

    spline = readPair("--spline");
    if (spline.empty()) {
        return std::string("Missing required argument: --spline");
    }

    return std::string();
}

const std::string app::Parameters::readFlag(const std::string& longOption, const std::string& shortOption) const {
    std::string res;

    std::vector<std::string>::const_iterator it;

    it = std::find(params.begin(), params.end(), shortOption);

    if (it == params.end()) {
        it = std::find(params.begin(), params.end(), longOption);
    }

    if (it == params.end()) {
        return res;
    }

    res = *it;

    return res;
}

const std::string app::Parameters::readPair(const std::string& longOption, const std::string& shortOption) const {
    std::string res;

    std::vector<std::string>::const_iterator it;

    it = std::find(params.begin(), params.end(), shortOption);

    if (it == params.end()) {
        it = std::find(params.begin(), params.end(), longOption);
    }

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
