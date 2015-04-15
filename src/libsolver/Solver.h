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
    Solver(std::unique_ptr<Board> board, std::unique_ptr<Dictionary> dictionary, std::vector<int> wordLengths);
    ~Solver() {}

    void solve();

private:
    std::unique_ptr<Board> board_;
    std::unique_ptr<Dictionary> dictionary_;
    std::vector<std::string> foundWords_;
    std::vector<int> wordLengths_;

    int x_;
    int y_;
    std::string word_;
};


#endif //WORD_BRAIN_SOLVER_SOLVER_H
