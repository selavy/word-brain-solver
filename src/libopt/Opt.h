//
// Created by peter on 4/14/15.
//

#ifndef WORD_BRAIN_SOLVER_OPT_H
#define WORD_BRAIN_SOLVER_OPT_H

#include <string>

class Opt {
public:
    Opt(int argc, char **argv);
    ~Opt() {}

    const std::string& boardFile() const { return boardFile_; }
    const std::string& dictionaryFile() const { return dictionaryFile_; }

private:
    std::string boardFile_;
    std::string dictionaryFile_;
};


#endif //WORD_BRAIN_SOLVER_OPT_H
