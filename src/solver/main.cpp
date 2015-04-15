//
// Created by peter on 3/31/15.
//

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>
#include <Timer.h>
#include <Board.h>
#include <FileReader.h>
#include <UnixDictionary.h>
#include <Logger.h>
#include <Solver.h>
#include <Opt.h>

template <typename T>
void logVector(const std::vector<T>& vec) {
    for (const auto& it : vec) {
        Logger::instance().log(it, '\n');
    }
}

int main(int argc, char **argv) {
    Opt opt(argc, argv);

    std::string dictionaryFile(opt.dictionaryFile());
    std::string boardFile(opt.boardFile());

    Timer timer;
    timer.start();
    std::unique_ptr<Reader> reader = std::unique_ptr<Reader>(new FileReader(boardFile.c_str()));
    std::unique_ptr<Board> board(reader->getBoard());
    std::vector<int> wordLengths = reader->getWordLengths();
    reader.reset();

    int maxWordLength = *(std::max_element(wordLengths.begin(), wordLengths.end()));
    Logger::instance().log("Max word length: ", maxWordLength);
    std::unique_ptr<Dictionary> dictionary = std::unique_ptr<Dictionary>(new UnixDictionary(maxWordLength));
    Logger::instance().log("Loaded modules in: ", timer.elapsedNs(), " nanoseconds.\n");
    Logger::instance().log("Board: \n", *board);
    Logger::instance().log("Word lengths...");
    logVector(wordLengths);
    Solver solver(std::move(board), std::move(dictionary), std::move(wordLengths));
    return 0;
}

