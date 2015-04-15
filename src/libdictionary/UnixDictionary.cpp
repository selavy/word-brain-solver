//
// Created by peter on 3/29/15.
//

#include "UnixDictionary.h"
#include <fstream>
#include <sstream>
#include <Logger.h>
#include <Timer.h>

UnixDictionary::UnixDictionary(std::size_t maxSize) {
    if (maxSize == 0) {
        auto tfunc = [](const std::string& word) { return false; };
        load(tfunc);
    } else {
        auto tfunc = [maxSize](const std::string &word) {
            return word.length() > maxSize;
        };
        load(tfunc);
    }
}

UnixDictionary::UnixDictionary(const std::vector<int>& wordLengths) {
    auto tfunc = [&wordLengths](const std::string& word) {
        return std::find(wordLengths.begin(), wordLengths.end(), static_cast<int>(word.length())) == wordLengths.end();
    };
    load(tfunc);
}

template <typename T>
void UnixDictionary::load(T verify) {
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
        if (verify(word)) {
            continue;
        } else if (word.find('\'') != std::string::npos) {
            continue;
        } else {
            dict_.insert(word);
        }
    }
    in.close();

    Logger::instance().log("Loading dictionary took: ", timer.elapsedNs(), " nanoseconds.");
    Logger::instance().log("Dictionary has: ", dict_.size(), " items.");
}

UnixDictionary::~UnixDictionary() { }

bool UnixDictionary::check(const std::string &word) const {
    return dict_.find(word) != dict_.end();
}
