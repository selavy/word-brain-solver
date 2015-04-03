#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include "boost/date_time/local_time/local_time.hpp"

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
        //std::time_t t = std::time(NULL);
        //char mbstr[100];
        //if (std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) {
        //    std::cout << mbstr << " - " << ss_.str() << std::endl;
        //} else {
        //    std::cout << ss_.str() << std::endl;
        //}
        boost::local_time::local_date_time ldt(boost::local_time::local_microsec_clock::local_time(tz_));
        std::cout << ldt << " - " << ss_.str() << std::endl;
    }
    Logger();
    std::stringstream ss_;
    boost::local_time::time_zone_ptr tz_;
    boost::local_time::local_time_facet* output_facet_;
    boost::local_time::local_time_input_facet* input_facet_;
};

#endif // LOG_H_
