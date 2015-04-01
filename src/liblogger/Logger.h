#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <sstream>
#include <iostream>

class Logger {
	public:
		~Logger();
		static Logger& instance();
		void log(const std::string& stmt);
		void log(const std::stringstream& ss);

        template <typename First, typename... Rest>
        void log(First param1, Rest...param) {
            ss_ << param1;
            log(param...);
        }

	private:
        void log() {
            std::cout << ss_.str() << std::endl;
            ss_.str("");
        }
		Logger();
		std::stringstream ss_;
};

#endif // LOG_H_
