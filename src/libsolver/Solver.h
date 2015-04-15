//
// Created by peter on 4/5/15.
//

#ifndef WORD_BRAIN_SOLVER_SOLVER_H
#define WORD_BRAIN_SOLVER_SOLVER_H

#include <memory>
#include <queue>
#include "Dictionary.h"
#include "Board.h"
#include "State.h"

class Solver {
public:
    Solver(const std::unique_ptr<Board>& board, const std::unique_ptr<Dictionary>& dictionary, const std::vector<int>& wordLengths);

    ~Solver() {}

    void solve();

private:
    const std::unique_ptr<Board>& board_;
    const std::unique_ptr<Dictionary>& dictionary_;
    const std::vector<int>& wordLengths_;
    std::vector<std::unique_ptr<State>> queue_;
};


#endif //WORD_BRAIN_SOLVER_SOLVER_H
