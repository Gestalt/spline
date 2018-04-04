#include <iostream>
#include <sstream>
#include "Log.h"
#include "OutputFile.h"

static const std::string kLogFileName = std::string("log.txt");

int app::Logger::logLevel = app::Logger::log;

app::Logger::Logger()
    : logFile(sp::shared_ptr<OutputFile>()) {
        logFile = sp::make_shared<OutputFile>(kLogFileName);
}

app::Logger* app::Logger::instance() {
    static Logger logger;
    return &logger;
}

void app::Logger::setLevel(Logger::LogLevel level) {
    Logger::logLevel = level;
}

void app::Logger::message(const std::string& str) const {
    std::ofstream& stream = logFile->stream();
    stream << str << std::endl;

    std::cout << str << std::endl;
}
