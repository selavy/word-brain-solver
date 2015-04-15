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
    State(const std::unique_ptr<Board>& board, const std::vector<std::string>& wordsCompleted, const std::string& currentWord, int curX, int curY);

    State(const State& rhs) : board_(new Board(*rhs.board_)), wordsCompleted_(rhs.wordsCompleted_), currentWord_(rhs.currentWord_), x_(rhs.x_), y_(rhs.y_) {}

    State(State&& rhs) : board_(std::move(rhs.board_)), wordsCompleted_(std::move(rhs.wordsCompleted_)), currentWord_(std::move(rhs.currentWord_)), x_(rhs.x_), y_(rhs.y_) {}

    const std::unique_ptr<Board> & getBoard() const;

    const std::vector<std::string> & getWordsCompleted() const;

    const std::string & getCurrentWord() const;

    int getX() const;

    int getY() const;

    void print(std::ostream& os) const;

private:
    std::unique_ptr<Board> board_;
    std::vector<std::string> wordsCompleted_;
    std::string currentWord_;
    int x_;
    int y_;
};

std::ostream& operator<<(std::ostream& os, const State& state);

#endif //WORD_BRAIN_SOLVER_STATE_H
