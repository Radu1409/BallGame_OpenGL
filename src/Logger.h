// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance();

    void log(const std::string& message, LogLevel level = LogLevel::INFO);

    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    ~Logger();

    std::string getCurrentTime();
};

#endif // LOGGER_H