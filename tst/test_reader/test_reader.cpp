//
// Created by peter on 3/28/15.
//
#include <iostream>
#include <FileReader.h>
#include "Board.h"

int main(int argc, char **argv) {

    Reader* reader = new FileReader("test.board");
    std::cout << "test complete" << std::endl;
    Board board = reader->getBoard();
    board.print(std::cout);
    delete reader;
    return 0;
}
