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

    template <typename First, typename... Rest>
    void log(First param1, Rest...param) {
        ss_ << param1;
        log(param...);
    }

private:
    Logger();
    void log() {
        boost::local_time::local_date_time ldt(boost::local_time::local_microsec_clock::local_time(tz_));
        std::cout << ldt << " - " << ss_.str() << std::endl;
        ss_.str("");
    }

private:
    std::stringstream ss_;
    boost::local_time::time_zone_ptr tz_;
    boost::local_time::local_time_facet* output_facet_;
    boost::local_time::local_time_input_facet* input_facet_;
};

#endif // LOG_H_
