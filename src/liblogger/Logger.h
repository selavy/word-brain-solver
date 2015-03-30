#ifndef LOG_H_
#define LOG_H_

#include <string>

class Logger {
	public:
		~Logger();
		static Logger& instance();
		void log(const std::string& stmt);

	private:
		Logger();
};

#endif // LOG_H_
