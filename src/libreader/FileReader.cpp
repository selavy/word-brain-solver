//
// Created by peter on 3/29/15.
//

#include <stdexcept>
#include "FileReader.h"

FileReader::FileReader(const std::string &filename) : in_(filename.c_str(), std::ios::in), board_(), wordLengths_() {
    if (!in_.good()) {
        std::string err("unabled to open file: ");
        err += filename;
        throw std::runtime_error(err.c_str());
    }
    parse();
}

FileReader::~FileReader() {
    if (in_.is_open()) {
        in_.close();
    }
}

void FileReader::parse() {
    int c;
    std::vector< char > row;
    while (!in_.eof()) {
        c = in_.get();
        if (c == '\n') {
            break;
        } else if (c == ' ') {
            continue;
        } else {
            row.push_back(static_cast<char>(c));
        }
    }
    const std::size_t size = row.size();
    if (size < 2) {
        std::string err("invalid board size: ");
        err += static_cast<char>(size+'0');
        throw std::runtime_error(err.c_str());
    }
    board_.reset(new Board(size));
    for (int i = 0; i < size; ++i) {
        board_->setTile(0, i, row[i]);
    }

    for (int i = 1; i < size; ++i) {
        for (int col = 0; col < size; ++col) {
            if (in_.eof()) {
                throw std::runtime_error("malformed input file");
            }
            c = in_.get();
            if ((c < 'a' && c > 'z') || (c < 'A' && c > 'Z')) {
                std::string err("malformed input file, bad character: ");
                err += static_cast<char>(c);
                throw std::runtime_error(err.c_str());
            }
            board_->setTile(i, col, static_cast<char>(c));
            // swallow next character, which should either be a newline or space
            in_.get();
        }
    }

    while (!in_.eof() && (c = in_.get()) != '\n') {
        if (c >= '0' && c <= '9') {
//            board_->addWordLength(c - '0');
            wordLengths_.push_back(c - '0');
        }
    }

//    if (board_->getWordLengths().empty()) {
    if (wordLengths_.empty()) {
        throw std::runtime_error("malformed input file: no word lengths given");
    }
}

