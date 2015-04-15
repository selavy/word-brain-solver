//
// Created by peter on 4/14/15.
//

#ifndef WORD_BRAIN_SOLVER_STATE_H
#define WORD_BRAIN_SOLVER_STATE_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include "Board.h"

class State {
public:
    State(const std::unique_ptr<Board>& board, const std::vector<std::string>& wordsCompleted, int curX, int curY);

    const std::unique_ptr<Board> & getBoard() const;

    const std::vector<std::string> & getWordsCompleted() const;

    int getX() const;

    int getY() const;

    void print(std::ostream& os) const;

private:
    std::unique_ptr<Board> board_;
    std::vector<std::string> wordsCompleted_;
    int x_;
    int y_;
};

std::ostream& operator<<(std::ostream& os, const State& state);

#endif //WORD_BRAIN_SOLVER_STATE_H
