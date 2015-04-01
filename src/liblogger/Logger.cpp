#include "Logger.h"
#include <iostream>

Logger::Logger() {}

Logger::~Logger() {}

Logger& Logger::instance() {
	static Logger logger;
	return logger;
}

void Logger::log(const std::string& stmt) {
	std::cout << stmt << std::endl;
}

void Logger::log(const std::stringstream& ss) {
	log(ss.str());
}
