//
// Created by peter on 4/5/15.
//

#ifndef WORD_BRAIN_SOLVER_SOLVER_H
#define WORD_BRAIN_SOLVER_SOLVER_H

#include <memory>
#include "Dictionary.h"
#include "Board.h"

class Solver {
public:
    Solver(std::shared_ptr<Board> board, std::unique_ptr<Dictionary> dictionary);
    ~Solver() {}

private:
    std::shared_ptr<Board> board_;
    std::unique_ptr<Dictionary> dictionary_;
};


#endif //WORD_BRAIN_SOLVER_SOLVER_H
