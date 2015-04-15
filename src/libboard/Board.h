//
// Created by peter on 3/28/15.
//

#ifndef WORD_BRAIN_SOLVER_BOARD_H
#define WORD_BRAIN_SOLVER_BOARD_H


#include <stddef.h>
#include <ostream>
#include <vector>
#include <algorithm>
#include "Tile.h"

class Board {
public:
    typedef std::vector<Tile> Row;
    typedef Row Column;
    static const char EMPTY = 0;

public:
    Board();
    explicit Board(std::size_t size);
    ~Board();

    Board(const Board& board);
    Board(Board&& board);

    Row const& getRow(int row) const;
    Tile const& getTile(int row, int col) const;
    void setTile(int row, int col, char val);
    void useTile(int row, int col);
    void print(std::ostream& os) const;
    const std::vector<int>& getWordLengths() { return wordLengths_; }
    int getMaxWordLength() const { return *(std::max_element(wordLengths_.begin(), wordLengths_.end())); }
    void addWordLength(int l) { wordLengths_.push_back(l); }

private:
    std::size_t size_;
    std::vector<Row> board_;
    std::vector<int> wordLengths_;
};


std::ostream& operator<<(std::ostream& os, const Board& board);

#endif //WORD_BRAIN_SOLVER_BOARD_H
