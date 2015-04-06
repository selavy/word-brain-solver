//
// Created by peter on 4/5/15.
//

#include "Solver.h"

Solver::Solver(
        std::shared_ptr<Board> board,
        std::unique_ptr<Dictionary> dictionary)
        : board_(board),
          dictionary_(std::move(dictionary)) { }


