//
// Created by peter on 4/7/15.
//

#include "Move.h"

Move::Move(int fromRow, int fromCol, char fromVal, int toRow, int toCol, char toVal)
        : fromVal_(fromVal)
        , toVal_(toVal)
        , fromVal_(fromVal)
        , fromRow_(fromRow)
        , fromCol_(fromCol)
        , toRow_(toRow)
        , toCol_(toCol)
{ }

void Move::apply(Board& board) {

}

void Move::undo(Board& board) {
        board.setTile(fromRow_);
}
