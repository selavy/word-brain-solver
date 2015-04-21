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

Tile const & Board::getTile(int row, int col) const {
    assert(row < size_ && row >= 0);
    assert(col < size_ && col >= 0);
    return board_[col][row];
}

void Board::setTile(int row, int col, char val) {
    board_[col][row].setValue(val);
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

void Board::useTile(int row, int col) {
    getTile(row, col).setUsed();
}

void Board::setTileToEmpty(int row, int col) {
    getTile(row, col).setEmpty();
}

Board::Board(Board &&board)
        : size_(board.size_)
        , board_(std::move(board_))
{ }

Board::Board(const Board &board)
    : size_(board.size_)
    , board_(board.board_)
{ }

int Board::dim() const { return static_cast<int>(board_.size()); }

Tile &Board::getTile(int row, int col) {
    return board_[col][row];
}
