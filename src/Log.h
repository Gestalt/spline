#ifndef LogH
#define LogH

#include <sstream>
#include "Defs.h"

namespace app {

class OutputFile;

class Logger {
    public:
        enum LogLevel {
            log = 0,
            verbose
        };

        static Logger* instance();

        static int logLevel;
        void setLevel(LogLevel level);

        void message(const std::string& str) const;
    private:
        Logger();
        Logger(const Logger&);
        Logger& operator=(const Logger&);
    private:
        sp::shared_ptr<OutputFile> logFile;
};

template <int Level>
class LogMessage {
    public:
        ~LogMessage() {
            if (Level <= Logger::logLevel) {
                Logger::instance()->message(stream.str());
            }
        }
        template <class M>
        LogMessage& operator<<(const M& message) {
            stream << message;
            return *this;
        }
    private:
        std::ostringstream stream;
};

typedef LogMessage<Logger::log> log;
typedef LogMessage<Logger::verbose> verbose;

}
#endif

