//
// Created by peter on 4/14/15.
//

#include "State.h"

State::State(const std::shared_ptr<Board>& board, const std::vector<std::string>& wordsCompleted, int curX, int curY)
        : board_(new Board(*board))
        , wordsCompleted_(wordsCompleted)
        , x_(curX)
        , y_(curY)
{}
