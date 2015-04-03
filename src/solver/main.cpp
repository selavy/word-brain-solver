//
// Created by peter on 3/31/15.
//

#include <iostream>
#include <sstream>
#include <memory>
#include <Timer.h>
#include <Board.h>
#include <FileReader.h>
#include <UnixDictionary.h>
#include <Logger.h>
#include <boost/program_options.hpp>

int main(int argc, char **argv) {
    Timer timer;
    timer.start();
    std::unique_ptr<Reader> reader = std::unique_ptr<Reader>(new FileReader("input.board"));
    std::unique_ptr<Dictionary> dictionary = std::unique_ptr<Dictionary>(new UnixDictionary());

    Logger::instance().log("Loaded modules in: ", timer.elapsedNs(), " nanoseconds.\n");

    return 0;
}

