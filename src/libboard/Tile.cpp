//
// Created by peter on 3/28/15.
//

#include "Tile.h"

Tile::Tile() : val_(EMPTY) {
}

Tile::Tile(char val) {
    setValue(val);
}

bool Tile::isEmpty() const {
    return val_ == EMPTY;
}

bool Tile::isUsed() const {
    return val_ == USED;
}

bool Tile::isActive() const {
    return !(isEmpty() || isUsed());
}

void Tile::print(std::ostream &os) {
    os << (isEmpty() ? ' ' : val_);
}

std::ostream& operator<<(std::ostream &os, Tile tile) {
    tile.print(os);
    return os;
}

char Tile::getValue() const {
    return val_;
}

void Tile::setValue(char val) {
    if (val >= 'A' && val <= 'Z') {
        val_ = val;
    } else if (val >= 'a' && val <= 'z') {
        val_ = val - ('a' - 'A');
    } else {
        val_ = EMPTY;
    }
}

void Tile::setEmpty() {
    val_ = EMPTY;
}

void Tile::setUsed() {
    val_ = USED;
}
