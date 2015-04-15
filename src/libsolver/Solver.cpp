//
// Created by peter on 4/5/15.
//

#include "Solver.h"
#include "Logger.h"

Solver::Solver(const std::unique_ptr<Board>& board, const std::unique_ptr<Dictionary>& dictionary, const std::vector<int>& wordLengths)
        : board_(board), dictionary_(dictionary), wordLengths_(wordLengths), queue_()
{ }


void Solver::solve() {
    Logger::instance().log("[Solver::solve] begin");
    // initialize with beginning states
    std::vector<std::string> blank;
    for (int x = 0; x < board_->dim(); ++x) {
        for (int y = 0; y < board_->dim(); ++y) {
            std::unique_ptr<State> state(new State(board_, blank, x, y));
            queue_.push_back(std::move(state));
        }
    }

   for (auto& it : queue_) {
       std::cout << *it << std::endl;
   }

    Logger::instance().log("[Solver::solve] end");
}
