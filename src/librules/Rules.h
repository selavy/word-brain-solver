//
// Created by peter on 3/31/15.
//

#ifndef WORD_BRAIN_SOLVER_RULES_H
#define WORD_BRAIN_SOLVER_RULES_H

#include <Board.h>
#include <Dictionary.h>

class Rules {
public:
    Rules(const std::unique_ptr<Board>& board, const std::unique_ptr<Dictionary>& dictionary);
    ~Rules() {}

    void onAfterMove();

};


#endif //WORD_BRAIN_SOLVER_RULES_H
