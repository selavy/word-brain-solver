//
// Created by peter on 3/28/15.
//

#include <iostream>
#include "Board.h"
#include "Tile.h"

int main(int argc, char **argv) {
    Tile t;
    std::cout << "Value of t: " << t << std::endl;
    Tile c('C');
    std::cout << "Value of c: " << c << std::endl;

    Board board(4);
    std::cout << "Printing board:" << '\n';
    board.print(std::cout);

    board.setTile(2,3,'A');
    board.setTile(1,2, 'b');
    std::cout << "Printing board:" << '\n';
    board.print(std::cout);
    return 0;
}
