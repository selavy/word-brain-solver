//
// Created by peter on 4/14/15.
//

#include "State.h"

State::State(const std::unique_ptr<Board>& board, const std::vector<std::string>& wordsCompleted, const std::string& currentWord, int curX, int curY)
        : board_(new Board(*board))
        , wordsCompleted_(wordsCompleted)
        , currentWord_(currentWord)
        , x_(curX)
        , y_(curY)
{}

const std::unique_ptr<Board> &State::getBoard() const { return board_; }

const std::vector<std::string> &State::getWordsCompleted() const { return wordsCompleted_; }

int State::getX() const { return x_; }

int State::getY() const { return y_; }

void State::print(std::ostream &os) const {
        os << "==== STATE ====\n";
        os << *board_;
        os << "Words Completed: ";
        for (auto& it : wordsCompleted_) {
                os << it << " ";
        }
        os << '\n';
        os << "x = " << x_ << ", y = " << y_ << '\n';
        os << "Current Word: " << currentWord_ << '\n';
        os << "==== \\STATE\\ ====";
        os << std::endl;
}

std::ostream& operator<<(std::ostream& os, const State& state) {
        state.print(os);
        return os;
}

const std::string &State::getCurrentWord() const { return currentWord_; }