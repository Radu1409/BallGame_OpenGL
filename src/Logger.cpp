// Logger.cpp
#include <iostream>
#include <ctime>
#include "Logger.h"

Logger::Logger() {
    // Constructorul poate rămâne neschimbat
}

Logger::~Logger() {
    // Destructorul poate rămâne neschimbat
}


Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}
//Logger* Logger::getInstance() {
//    static Logger instance;
//    return &instance;
//}

std::string Logger::getCurrentTime() {
    // Obține timpul curent
    std::time_t now = std::time(nullptr);

    // Formatează timpul curent într-un șir de caractere
    char buffer[80];
    std::tm timeInfo;
    localtime_s(&timeInfo, &now);
    std::strftime(buffer, sizeof(buffer), "[%d %b %Y %H:%M:%S] ", &timeInfo);

    return std::string(buffer);
}

void Logger::log(const std::string& message, LogLevel level) {
    std::string prefix;
    std::string colorCode;

    switch (level) {
        case LogLevel::INFO:
            prefix = "INFO";
            colorCode = "\x1B[32m"; // Culoare verde
            break;
        case LogLevel::WARNING:
            prefix = "WARNING";
            colorCode = "\x1B[33m"; // Culoare galben
            break;
        case LogLevel::ERROR:
            prefix = "ERROR";
            colorCode = "\x1B[31m"; // Culoare roșu
            break;
    }

    std::string logMessage = getCurrentTime() + "[" + colorCode + prefix + "\x1B[0m" + "] " + message; // Resetare la culoarea implicită

    // Afișează direct în consolă
    std::cout << logMessage << std::endl;
}

void Logger::info(const std::string& message) {
    log(message, LogLevel::INFO);
}

void Logger::warning(const std::string& message) {
    log(message, LogLevel::WARNING);
}

void Logger::error(const std::string& message) {
    log(message, LogLevel::ERROR);
}

