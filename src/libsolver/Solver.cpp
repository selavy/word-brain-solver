//
// Created by peter on 4/5/15.
//

#include "Solver.h"
#include "Logger.h"

Solver::Solver( std::unique_ptr<Board> board, std::unique_ptr<Dictionary> dictionary, std::vector<int> wordLengths )
        : board_(std::move(board)) , dictionary_(std::move(dictionary)) , wordLengths_(std::move(wordLengths)) , x_(0) , y_(0) , word_()
{ }


void Solver::solve() {
    Logger::instance().log("[Solver::solve] begin");
    Logger::instance().log("[Solver::solve] end");
}
