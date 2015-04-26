//
// Created by peter on 4/5/15.
//

#include "Solver.h"
#include "Logger.h"
#include <cstddef>
#include <unordered_set>

//#define EXTRA_LOGGING

Solver::Solver(const BoardPtr& board, const DictionaryPtr& dictionary, const std::vector<int>& wordLengths)
        : board_(board), dictionary_(dictionary), wordLengths_(wordLengths), queue_()
{ }


void Solver::solve() {
    Logger::instance().log("[Solver::solve] begin");

    initializeQueue();
    #ifdef EXTRA_LOGGING
    printQueue();
    #endif

    int64_t safetyCounter = 0;
    int64_t MAX_LOOPS = 5000000000LL;
    std::unordered_set<std::string> finalWordsFound;

    // TODO (plesslie); if we make the queue multithreaded safe
    // we can process states in different threads
    while (!queue_.empty() && safetyCounter < MAX_LOOPS) {
        #ifdef EXTRA_LOGGING
        Logger::instance().log("----- BEGIN ONE ITERATION -----");
        #endif
        const StatePtr& state = queue_.front();
        #ifdef EXTRA_LOGGING
        Logger::instance().log("### POPPED STATE ###");
        Logger::instance().log(*state);
        Logger::instance().log("### END POPPED STATE ###");
        #endif

        std::string word = state->getCurrentWord();
        const BoardPtr& board = state->getBoard();
        std::vector<std::string> wordsCompleted(state->getWordsCompleted());
        int currX = state->getX();
        int currY = state->getY();
        int dim = board->dim();
        const Tile& tile = const_cast<const Board&>(*board).getTile(currX, currY);

        word += ::tolower(tile.getValue());
        #ifdef EXTRA_LOGGING
        Logger::instance().log("Checking word: ", word);
        #endif
        bool foundWord = dictionary_->check(word);
        if (foundWord) {
            int counter = 0;
            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) {
                    if (const_cast<const Board&>(*board).getTile(i, j).isActive()) { ++counter; }
                }
            }
            if (counter <= 1) {
//                #ifdef EXTRA_LOGGING
                Logger::instance().log("Finished state:\n", *state);
//                #endif
                for (auto& w: wordsCompleted) {
                    finalWordsFound.insert(w);
                }
//                finalWordsFound = wordsCompleted;
//                finalWordsFound.push_back(word);
                finalWordsFound.insert(word);
                queue_.pop_front();
                ++safetyCounter;
                continue;
                //break;
            }
            #ifdef EXTRA_LOGGING
            Logger::instance().log("Found word: ", word);
            #endif
        }


        std::vector<std::pair<int, int> > nextMoves(std::move(generateMoves(currX, currY, dim)));

        #ifdef EXTRA_LOGGING
        {
            Logger::instance().log("...generated moves...");
            for (auto &it: nextMoves) {
                Logger::instance().log("(", it.first, ",", it.second, ")");
            }
            Logger::instance().log("...end generated moves...");
        }
        #endif

        BoardPtr newBoard = BoardPtr(new Board(*board));
        newBoard->useTile(currX, currY);
        simplifyBoard(newBoard);

        #ifdef EXTRA_LOGGING
        Logger::instance().log("After simplify:\n", *newBoard);
        #endif

        if (dictionary_->isPrefix(word)) {
            for (auto &move : nextMoves) {
                if (const_cast<const Board &>(*newBoard).getTile(move.first, move.second).isActive()) {
                    StatePtr newState(new State(newBoard, wordsCompleted, word, move.first, move.second));
                #ifdef EXTRA_LOGGING
                Logger::instance().log("Adding state:\n", *newState);
                #endif
                    queue_.push_back(std::move(newState));
                }
            #ifdef EXTRA_LOGGING
            else {
                Logger::instance().log("Skipping square (", move.first, ",", move.second, ")");
            }
            #endif
            }
        }

        if (foundWord) {
            // create states using the word we found
            std::vector<std::string> wordsCompletedWithNew(wordsCompleted);
            wordsCompletedWithNew.push_back(word);
            for (int x = dim - 1; x >= 0; --x) {
                for (int y = 0; y < dim; ++y) {
                    if (const_cast<const Board&>(*newBoard).getTile(x, y).isUsed()) {
                        newBoard->setTileToEmpty(x, y);
                    }
                }
            }
            simplifyBoard(newBoard);
            #ifdef EXTRA_LOGGING
            Logger::instance().log("After adding word (", word, ") and simplify:\n", *newBoard);
            #endif

            std::vector<std::pair<int, int> > startingMoves(std::move(generateStartingMoves(dim)));
            std::string newWord;
            if (dictionary_->isPrefix(newWord)) {
                for (auto &move : startingMoves) {
                    if (const_cast<const Board &>(*newBoard).getTile(move.first, move.second).isActive()) {
                        StatePtr newState(new State(newBoard, wordsCompletedWithNew, newWord, move.first, move.second));
                    #ifdef EXTRA_LOGGING
                    Logger::instance().log("Adding state:\n", *newState);
                    #endif
                        queue_.push_back(std::move(newState));
                    }
                }
            }
        }

        queue_.pop_front();
        ++safetyCounter;
        #ifdef EXTRA_LOGGING
        Logger::instance().log("----- END ITERATION(", safetyCounter, ") -----");
        #endif
    }

    if (queue_.empty()) {
        Logger::instance().log("Unable to find solution!");
        for (auto& it : finalWordsFound) {
            Logger::instance().log(it);
        }
    } else if (safetyCounter > MAX_LOOPS) {
        Logger::instance().log("Not enough iterations");
    } else {
        Logger::instance().log("FINISHED");
        Logger::instance().log("words: ");
        for (auto& it : finalWordsFound) {
            Logger::instance().log(it);
        }
    }

    Logger::instance().log("[Solver::solve] end");
}

void Solver::simplifyBoard(BoardPtr& board) {
    int dim = board->dim();
    for (int x = (dim - 1); x >= 0; --x) {
        for (int y = (dim -1); y >= 0; --y) {
            if (const_cast<const Board&>(*board).getTile(x, y).isEmpty()) {
                char val = -1;
                // check if any tiles above to drop down
                for (int i = y; i >= 0; --i) {
                    if (!const_cast<const Board&>(*board).getTile(x, i).isEmpty()) {
                        val = const_cast<const Board&>(*board).getTile(x, i).getValue();
                        board->setTileToEmpty(x, i);
                        break;
                    }
                }

                if (val == -1) {
                    board->setTileToEmpty(x, y);
                } else {
                    board->setTile(x, y, val);
                }
            }
        }
    }
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
    Logger::instance().log("=== QUEUE ===\n\n");
    for (auto& it : queue_) {
        Logger::instance().log(*it);
    }
    Logger::instance().log("=== \\QUEUE\\ ===\n\n");
}

std::vector<std::pair<int, int> > Solver::generateMoves(int currX, int currY, int dim) {
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
    return nextMoves;
}

std::vector<std::pair<int, int> > Solver::generateStartingMoves(int dim) {
    std::vector<std::pair<int, int> > ret;
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            ret.emplace_back(i, j);
        }
    }
    return ret;
}
