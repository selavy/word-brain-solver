//
// Created by peter on 4/14/15.
//

#include "Opt.h"
#include "Logger.h"
#include <boost/program_options.hpp>
#include <cstdlib>

Opt::Opt(int argc, char **argv)
: boardFile_("input.board")
, dictionaryFile_("")
{
        boost::program_options::options_description desc("Options");
        desc.add_options()
                ("help", "Print help message.")
                ("dict", boost::program_options::value<std::string>(), "Specify dictionary file to use.")
                ("board", boost::program_options::value<std::string>(), "Specify board input file to use.");

        boost::program_options::variables_map vm;
        try {
                boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
                if (vm.count("help")) {
                        Logger::instance().log(desc, '\n');
                        std::exit(1);
                }
                boost::program_options::notify(vm);
        } catch (boost::program_options::error &ex) {
                Logger::instance().log("ERROR: ", ex.what(), '\n');
                Logger::instance().log(desc, '\n');
                std::exit(1);
        }

        if (vm.count("dict")) { dictionaryFile_ = vm["dict"].as<std::string>(); }
        if (vm.count("board")) { boardFile_ = vm["board"].as<std::string>(); }
}
