//
// Created by peter on 3/28/15.
//

#ifndef WORD_BRAIN_SOLVER_BOARD_H
#define WORD_BRAIN_SOLVER_BOARD_H


#include <stddef.h>
#include <ostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Tile.h"

class Board {
public:
    typedef std::vector<Tile> Row;
    typedef Row Column;
    static const char EMPTY = 0;
    static const char USED = -1;

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

    void setTileToEmpty(int row, int col);

    void print(std::ostream& os) const;

    int dim() const;

private:
    std::size_t size_;
    std::vector<Row> board_;

private: // methods
    Tile& getTile(int row, int col);
};

typedef std::unique_ptr<Board> BoardPtr;

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif //WORD_BRAIN_SOLVER_BOARD_H
