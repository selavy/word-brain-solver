//
// Created by peter on 3/28/15.
//

#ifndef WORD_BRAIN_SOLVER_TILE_H
#define WORD_BRAIN_SOLVER_TILE_H


#include <ostream>

class Tile {
public:
    Tile();

    explicit Tile(char val);

    ~Tile() { }

    bool isEmpty() const;

    bool isUsed() const;

    void print(std::ostream& os);

    char getValue() const;

    void setValue(char val);

    void setEmpty();

    void setUsed();

private:
    static const char EMPTY = ' ';
    static const char USED = '_';
    char val_;
};

std::ostream& operator<<(std::ostream& os, Tile tile);

#endif //WORD_BRAIN_SOLVER_TILE_H
