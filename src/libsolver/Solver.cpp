//
// Created by peter on 4/5/15.
//

#include "Solver.h"

Solver::Solver(
        std::unique_ptr<Board> board,
        std::unique_ptr<Dictionary> dictionary)
        : board_(std::move(board)),
          dictionary_(std::move(dictionary)) { }


