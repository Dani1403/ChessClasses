#include "Player.h"
#include "Moves/ChessMove.h"
#include "ChessBoard.h"
#include "ChessGame.h"


std::string Player::getMoveFromUser(std::istream& is) const
{
	displayExitGameInstructions();
	displayInstructionToMove();
	std::string input;
	is >> input;
	return input;
}


std::shared_ptr<Castle> Player::getCastle(const ChessGame& game, std::shared_ptr<ChessBoard> board, const Side side) const
{
	const Square kingPos = board->getKingPosition(game.getCurrentPlayer().getColor());
	const Square rookPos = { kingPos.row,  rookColForCastle(side) };
	std::shared_ptr<King> kingToMove = std::dynamic_pointer_cast<King>(board->getPieceAt(kingPos));
	std::shared_ptr<Rook> rookToMove = std::dynamic_pointer_cast<Rook>(board->getPieceAt(rookPos));
	if (!kingToMove || !rookToMove)
		throw InvalidMove(INVALID_CASTLE_PIECES);
	return std::make_shared<Castle>(kingPos, rookToMove->getSquare(), kingToMove, rookToMove, side);

}

std::shared_ptr<ChessPiece> Player::getPromotedPiece(Type type, Color color, Square square) const
{
	switch (type)
	{
		case Type::QUEEN:
			return std::make_shared<Queen>(Queen(color, square));
		case Type::ROOK:
			return std::make_shared<Rook>(Rook(color, square));
		case Type::BISHOP:
			return std::make_shared<Bishop>(Bishop(color, square));
		case Type::KNIGHT:
			return std::make_shared<Knight>(Knight(color, square));
	  default:
			throw InvalidMove(INVALID_PROMOTED_PIECE);
	}
}



std::shared_ptr<ChessMove> Player::getMove(const ChessGame& game) const
{
	const std::shared_ptr<ChessBoard> board = game.getChessBoard();
	const std::string input = getMoveFromUser(std::cin);

	// Exit
	if (input == EXIT_SYMBOL_LOWER || input == EXIT_SYMBOL_UPPER)
		throw ExitGame();

	// Castle
	if (input == CASTLE_KINGSIDE || input == CASTLE_QUEENSIDE)
	{
		const Side side = input == CASTLE_KINGSIDE ? Side::KING : Side::QUEEN;
		return getCastle(game, board, side);
	}

	Square source = algebraicToSquare(input.substr(0, 2));
	Square destination = algebraicToSquare(input.substr(input.length() - 2));
	std::shared_ptr<ChessPiece> pieceToMove = board->getPieceAt(source);
	if (!pieceToMove)
		throw InvalidMove(SOURCE_SQUARE_EMPTY);

	//Capture
	if (input.at(2) == CAPTURE_SYMBOL_UPPER ||
			input.at(2) == CAPTURE_SYMBOL_LOWER)
	{
		std::shared_ptr<ChessPiece> capturedPiece = board->getPieceAt(destination);
		return std::make_shared<Capture>(source, destination, pieceToMove, capturedPiece);
	}

	//Promotion
	if (input[2] == PROMOTION_SYMBOL)
	{
		std::shared_ptr<Pawn> pawnToPromote = std::dynamic_pointer_cast<Pawn>(pieceToMove);
		if (!pawnToPromote)
			throw InvalidMove(INVALID_PROMOTION_PIECE);
		const Type promotionType = charToType(input[3]);
		const Color color = pawnToPromote->getColor();
		std::shared_ptr<ChessPiece> promotedPiece = getPromotedPiece(promotionType, color, { rowForPawnPromotion(color), pawnToPromote->colForPromotion() });
		return std::make_shared<Promotion>(source, promotedPiece->getSquare(), pawnToPromote, promotedPiece);
	}

	// Regular
	return std::make_shared<ChessMove>(source, destination, pieceToMove);
}
