//
// Created by peter on 3/29/15.
//

#ifndef WORD_BRAIN_SOLVER_UNIXDICTIONARY_H
#define WORD_BRAIN_SOLVER_UNIXDICTIONARY_H

#include <unordered_set>
#include <vector>
#include "Dictionary.h"

class UnixDictionary : public Dictionary {
public:
    explicit UnixDictionary(std::size_t maxSize=0);

    explicit UnixDictionary(const std::vector<int>& wordLengths);

    virtual ~UnixDictionary();

    virtual bool check(const std::string& word) const;

    virtual bool isPrefix(const std::string& word) const;

private:
    std::unordered_set<std::string> dict_;

private: // methods
    template <typename T>
    void load(T verify);
};


#endif //WORD_BRAIN_SOLVER_UNIXDICTIONARY_H
