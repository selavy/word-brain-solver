//
// Created by peter on 3/29/15.
//

#include "UnixDictionary.h"
#include <fstream>
#include <sstream>
#include <Logger.h>
#include <Timer.h>

UnixDictionary::UnixDictionary(std::size_t maxSize) {
    Timer timer;
    timer.start();

    std::ifstream in("/usr/share/dict/american-english", std::ios::in);
    if (!in.good()) {
            in.close();
	    in.open("/usr/share/dict/words", std::ios::in);
	    if (!in.good()) {
		    throw std::runtime_error("unabled to find dictionary at: /usr/share/dict/american-english");
	    }
    }
    std::string word;
    while (!in.eof()) {
        getline(in, word);
        if (maxSize != 0 && word.length() > maxSize) {
            continue;
        } else if (word.find('\'') != std::string::npos) {
            continue;
        } else {
            dict_.insert(word);
        }
    }
    in.close();

    std::stringstream ss;
    ss << "Loading dictionary took: " << timer.elapsedNs() << " nanoseconds.";
    Logger::instance().log(ss.str());
}

UnixDictionary::~UnixDictionary() { }

bool UnixDictionary::check(const std::string &word) const {
    return dict_.find(word) != dict_.end();
}
