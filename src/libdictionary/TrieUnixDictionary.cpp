//
// Created by peter on 4/26/15.
//

#include "TrieUnixDictionary.h"
#include <Timer.h>
#include <Logger.h>

TrieUnixDictionary::TrieUnixDictionary(std::size_t maxSize) : trie_('\0') {
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

TrieUnixDictionary::TrieUnixDictionary(std::vector<int>& wordLengths) : trie_('\0') {
    auto tfunc = [&wordLengths](const std::string& word) {
        return std::find(wordLengths.begin(), wordLengths.end(), static_cast<int>(word.length())) == wordLengths.end();
    };
    load(tfunc);
}

TrieUnixDictionary::~TrieUnixDictionary() { }

bool TrieUnixDictionary::check(const std::string& word) const {
    //return trie_.find(word.c_str()) == trie_.end();
    return trie_.hasKey(word.c_str());
}

template <typename T>
void TrieUnixDictionary::load(T verify) {
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
            trie_.insert(word.c_str(), "");
        }
    }
    in.close();

    Logger::instance().log("Loading dictionary took: ", timer.elapsedNs(), " nanoseconds.");
    Logger::instance().log("Dictionary has: ", trie_.size(), " items.");
}

bool TrieUnixDictionary::isPrefix(const std::string &word) const {
    return trie_.find(word.c_str()) != trie_.end();
}

