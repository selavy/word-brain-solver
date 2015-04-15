//
// Created by peter on 4/7/15.
//

#ifndef WORD_BRAIN_SOLVER_MOVE_H
#define WORD_BRAIN_SOLVER_MOVE_H


class Move {
public:
    Move(int fromRow, int fromCol, char fromVal, int toRow, int toCol, char toVal);
    ~Move() {}

    void apply(Board& board);
    void undo(Board& board);

private:
    char fromVal_;
    char toVal_;
    int fromRow_;
    int fromCol_;
    int toRow_;
    int toCol_;
};


#endif //WORD_BRAIN_SOLVER_MOVE_H
