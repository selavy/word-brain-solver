//
// Created by peter on 3/29/15.
//

#ifndef WORD_BRAIN_SOLVER_FILEREADER_H
#define WORD_BRAIN_SOLVER_FILEREADER_H

#include <fstream>
#include "Reader.h"

class FileReader : public Reader {
public:
    explicit FileReader(const std::string& filename);
    virtual ~FileReader();
    virtual Board getBoard();

private:
    std::ifstream in_;
};


#endif //WORD_BRAIN_SOLVER_FILEREADER_H
