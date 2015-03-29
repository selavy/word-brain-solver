//
// Created by peter on 3/28/15.
//
#include <iostream>
#include <memory>
#include <FileReader.h>
#include <Board.h>

int main(int argc, char **argv) {
    std::unique_ptr<Reader> reader(new FileReader("test.board"));
    Board board = reader->getBoard();
    std::cout << board << std::endl;
    return 0;
}
