//
// Created by peter on 4/5/15.
//

#ifndef WORD_BRAIN_SOLVER_SOLVER_H
#define WORD_BRAIN_SOLVER_SOLVER_H

#include <memory>
#include <queue>
#include <list>
#include "Dictionary.h"
#include "Board.h"
#include "State.h"

class Solver {
public:
    Solver(const BoardPtr& board, const DictionaryPtr& dictionary, const std::vector<int>& wordLengths);

    ~Solver() {}

    void solve();

private: // types
    typedef std::unique_ptr<State> StatePtr;

private: // members
    const BoardPtr& board_;
    const DictionaryPtr& dictionary_;
    const std::vector<int>& wordLengths_;
    std::list<StatePtr> queue_;

private: // methods
    void initializeQueue();
    void printQueue();
};


#endif //WORD_BRAIN_SOLVER_SOLVER_H
