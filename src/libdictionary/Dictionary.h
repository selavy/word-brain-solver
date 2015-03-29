//
// Created by peter on 3/29/15.
//

#ifndef WORD_BRAIN_SOLVER_DICTIONARY_H
#define WORD_BRAIN_SOLVER_DICTIONARY_H

#include <string>

class Dictionary {
public:
    Dictionary() {}
    virtual ~Dictionary() {}
    virtual bool check(const std::string& word) const=0;
};


#endif //WORD_BRAIN_SOLVER_DICTIONARY_H
