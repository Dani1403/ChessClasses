#include "../ChessGame.h"
#include "Promotion.h"

/*
* Checks if a promotion move is valid
* Uses the checkValidity() function from the ChessMove class
* @param game : the game to check the move on
* @return true if the move is valid, otherwise an exception is raised
* @override the ChessMove::checkValidity() function
*/
bool Promotion::checkValidity(ChessGame& game) const
{
	return ChessMove::checkValidity(game);
}

/*
* Apply the move to the current game
* @param game : the game to apply the move to
* @return true if the move was applied, false otherwise
* @override the ChessMove::execute() function
*/
bool Promotion::execute(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getPieceToMove());
	board->addPiece(getNewPiece());
	return true;
}

/*
* Undo the move on the current game
* @param game : the game to undo the move on
* @override the ChessMove::undo() function
*/
void Promotion::undo(ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	board->removePiece(getNewPiece());
	board->addPiece(getPieceToMove());
}

/*
* @return a string describing the move
*	@override the ChessMove::moveDescription() function
*/
std::string Promotion::moveDescription() const
{
	return ChessMove::moveDescription() + "\n Promoted piece: " +
		getNewPiece()->pieceDescription();
}
