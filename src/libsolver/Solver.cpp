//
// Created by peter on 4/5/15.
//

#include "Solver.h"
#include "Logger.h"

Solver::Solver(const BoardPtr& board, const DictionaryPtr& dictionary, const std::vector<int>& wordLengths)
        : board_(board), dictionary_(dictionary), wordLengths_(wordLengths), queue_()
{ }


void Solver::solve() {
    Logger::instance().log("[Solver::solve] begin");

    initializeQueue();
    printQueue();

    int safetyCounter = 0;

    while (!queue_.empty() && safetyCounter < 10) {
        const StatePtr& state = queue_.front();

        std::string word = state->getCurrentWord();
        const BoardPtr& board = state->getBoard();
        std::vector<std::string> wordsCompleted(state->getWordsCompleted());
        int currX = state->getX();
        int currY = state->getY();
        int dim = board->dim();
        const Tile& tile = const_cast<const Board&>(*board).getTile(currX, currY);
        word += tile.getValue();

        bool foundWord = dictionary_->check(word);
        if (foundWord) { Logger::instance().log("Found word: ", word); }

        std::vector<std::pair<int, int> > nextMoves;
        if (currX > 0) {
            if (currY > 0) {
                nextMoves.emplace_back(currX-1, currY-1);
            }
            if (currY < (dim - 1)) {
                nextMoves.emplace_back(currX-1, currY+1);
            }
            nextMoves.emplace_back(currX-1, currY);
        }
        if (currX < (dim - 1)) {
            if (currY > 0) {
                nextMoves.emplace_back(currX+1, currY-1);
            }
            if (currY < (dim - 1)) {
                nextMoves.emplace_back(currX+1, currY+1);
            }
            nextMoves.emplace_back(currX+1, currY);
        }
        if (currY > 0) {
           nextMoves.emplace_back(currX, currY-1);
        }
        if (currY < (dim - 1)) {
           nextMoves.emplace_back(currX, currY+1);
        }

        BoardPtr newBoard = BoardPtr(new Board(*board));
        newBoard->useTile(currX, currY);

        if (foundWord) {
            // create states using the word we found
            std::vector<std::string> wordsCompletedWithNew(wordsCompleted);
            wordsCompletedWithNew.push_back(word);
            BoardPtr anotherBoard(new Board(*newBoard));
            for (int x = dim - 1; x >= 0; --x) {
                for (int y = 0; y < dim; ++y) {
                    if (const_cast<const Board&>(*anotherBoard).getTile(x, y).isUsed() || const_cast<const Board&>(*anotherBoard).getTile(x, y).isEmpty()) {
                        char val = -1;
                        for (int i = y; i < (dim - 1); ++i) {
                            if (!const_cast<const Board&>(*anotherBoard).getTile(x, i).isEmpty()) {
                                val = const_cast<const Board&>(*anotherBoard).getTile(x, i).getValue();
                                anotherBoard->setTileToEmpty(x, i);
                                break;
                            }
                        }

                        if (val == -1) {
                            anotherBoard->setTileToEmpty(x, y);
                        } else {
                            anotherBoard->setTile(x, y, val);
                        }
                    }
                }
            }
            std::string newWord;

            for (auto& move : nextMoves) {
                queue_.push_back(StatePtr(new State(anotherBoard, wordsCompletedWithNew, newWord, move.first, move.second)));
            }
        }

//        for (auto& move : nextMoves) {
 //       }

        queue_.pop_front();
        ++safetyCounter;
    }

    Logger::instance().log("[Solver::solve] end");
}

void Solver::initializeQueue() {
    // initialize with beginning states
    std::vector<std::string> blank;
    std::string blankWord;
    for (int x = 0; x < board_->dim(); ++x) {
        for (int y = 0; y < board_->dim(); ++y) {
            StatePtr state(new State(board_, blank, blankWord, x, y));
            queue_.push_back(std::move(state));
        }
    }
}

void Solver::printQueue() {
    std::cout << "=== QUEUE ===" << "\n\n";
    for (auto& it : queue_) {
        std::cout << *it << std::endl;
    }
    std::cout << "=== \\QUEUE\\ ===" << "\n\n";
}
