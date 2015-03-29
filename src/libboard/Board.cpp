//
// Created by peter on 3/28/15.
//

#include <assert.h>
#include <algorithm>
#include "Board.h"

Board::Board() : size_(0), board_() {
}

Board::Board(std::size_t size) : size_(size), board_() {
    for (std::size_t i = 0; i < size_; ++i) {
        board_.push_back(Row(size_));
    }
}

Board::~Board() { }

Board::Row const & Board::getRow(int row) const {
    assert(row < size_ && row >= 0);
    return board_[row];
}

Tile const & Board::getTile(int row, int col) const {
    assert(row < size_ && row >= 0);
    assert(col < size_ && col >= 0);
    return board_[row][col];
}

void Board::setTile(int row, int col, char val) {
    board_[row][col].setValue(val);
}

void Board::print(std::ostream &os) const {
    std::string rowDelim("");
    rowDelim.push_back('-');
    for (int i=0; i < size_; ++i) {
        rowDelim.push_back('-');
        rowDelim.push_back('-');
    }
    os << rowDelim << '\n';
    std::for_each(board_.begin(), board_.end(), [&os, &rowDelim](Row const& row) {
        os << '|';
        std::for_each(row.begin(), row.end(), [&os, &rowDelim](Tile const& tile) {
            os << tile << '|'; }
        );
        os << '\n' << rowDelim << '\n';
    }
    );
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    board.print(os);
    return os;
}
