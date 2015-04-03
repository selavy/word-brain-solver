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
  boost::program_options::options_description desc("Options");
  desc.add_options()
    ("help", "Print help message.")
    ("dict", boost::program_options::value<std::string>(), "Specify dictionary file to use.")
    ("board", boost::program_options::value<std::string>(), "Specify board input file to use.")
    ;

  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
      return 0;
    }
    boost::program_options::notify(vm);
  } catch (boost::program_options::error& ex) {
    std::cerr << "ERROR: " << ex.what() << '\n';
    std::cerr << desc << '\n';
    return 1;
  }

  std::string dictionaryFile;
  std::string boardFile("input.board");

  if (vm.count("dict")) {
    dictionaryFile = vm["dict"].as<std::string>();
    Logger::instance().log("Using dictionary file: ", dictionaryFile);
  }

  if (vm.count("board")) {
    boardFile = vm["dict"].as<std::string>();
    Logger::instance().log("Using board file: ", boardFile);
  }

  Timer timer;
  timer.start();
  std::unique_ptr<Reader> reader = std::unique_ptr<Reader>(new FileReader(boardFile.c_str()));
  std::unique_ptr<Dictionary> dictionary = std::unique_ptr<Dictionary>(new UnixDictionary());

  Logger::instance().log("Loaded modules in: ", timer.elapsedNs(), " nanoseconds.\n");

  return 0;
}
