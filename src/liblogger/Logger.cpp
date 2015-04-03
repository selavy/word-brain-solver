#include "Logger.h"
#include <iostream>

//
// (plesslie)
// posix_time_zone is just parsing the "-XX" portion and subtracting that from UTC meaning
// that it isn't adjusting for daylight savings time.  not sure how to fix that, and I don't
// really care for now.
//
Logger::Logger() : ss_(), tz_(new boost::local_time::posix_time_zone("CST-05")), output_facet_(new boost::local_time::local_time_facet()), input_facet_(new boost::local_time::local_time_input_facet())  {
	ss_.imbue(std::locale(std::locale::classic(), output_facet_));
	ss_.imbue(std::locale(ss_.getloc(), input_facet_));
	output_facet_->format(boost::local_time::local_time_facet::iso_time_format_extended_specifier);
}

Logger::~Logger() {
	delete output_facet_;
	delete input_facet_;
}

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
