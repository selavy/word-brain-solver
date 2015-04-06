//
// Created by peter on 3/28/15.
//

#ifndef WORD_BRAIN_SOLVER_READER_H
#define WORD_BRAIN_SOLVER_READER_H

#include "Board.h"
#include <memory>

class Reader {
public:
    Reader() {}
    virtual ~Reader() {}
    virtual std::shared_ptr<Board> getBoard()=0;
    virtual std::vector<int> getWordLengths()=0;
};

#endif //WORD_BRAIN_SOLVER_READER_H
