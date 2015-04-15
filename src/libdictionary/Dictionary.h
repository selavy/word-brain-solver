//
// Created by peter on 3/29/15.
//

#ifndef WORD_BRAIN_SOLVER_DICTIONARY_H
#define WORD_BRAIN_SOLVER_DICTIONARY_H

#include <string>
#include <vector>
#include <memory>

class Dictionary {
public:
    explicit Dictionary(std::size_t maxSize=0) {}
    explicit Dictionary(std::vector<int>& wordLengths) {}
    virtual ~Dictionary() {}
    virtual bool check(const std::string& word) const=0;
};

typedef std::unique_ptr<Dictionary> DictionaryPtr;


#endif //WORD_BRAIN_SOLVER_DICTIONARY_H
