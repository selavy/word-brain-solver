//
// Created by peter on 3/28/15.
//

#ifndef WORD_BRAIN_SOLVER_BOARD_H
#define WORD_BRAIN_SOLVER_BOARD_H


#include <stddef.h>
#include <ostream>
#include <vector>
#include "Tile.h"

class Board {
public:
    typedef std::vector<Tile> Row;
    typedef Row Column;

public:
    Board();
    explicit Board(std::size_t size);
    ~Board();

    Row const& getRow(int row) const;
    Tile const& getTile(int row, int col) const;
    void setTile(int row, int col, char val);
    void print(std::ostream& os);

private:
    std::size_t size_;
    std::vector< Row > board_;
};


#endif //WORD_BRAIN_SOLVER_BOARD_H
