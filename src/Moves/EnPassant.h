#pragma once
#include "Capture.h"
#include "../Pieces/Pawn.h"

class EnPassant : public Capture
{
public:
    EnPassant(const Square& source, std::shared_ptr<Pawn> pawnToMove, std::shared_ptr<Pawn> pawnToCapture) :
        Capture(source, {source.col + 1, source.row + 1}, pawnToMove, pawnToCapture)
    {}

    bool checkValidity(ChessGame& game) const override;

    bool execute(ChessGame& game) const override;
    void undo(ChessGame& game) const override;

};

