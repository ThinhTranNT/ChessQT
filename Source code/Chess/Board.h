#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "Spot.h"

enum class GameStatus
{	

	ACTIVE, // trạng thái bình thường
	BLACK_WIN,
	WHITE_WIN,
	DRAW,
	CHECK_BLACK_KING, // vua đen bị chiếu
	CHECK_WHITE_KING, // vua trắng bị chiếu
	
};

class Board {
private:
	std::vector<std::vector<Spot*>> chessBoard;

	// thuộc tính trạng thái hiện tại của bàn cờ (kiểu enum)
	GameStatus gameStatus;
	
public:
	Board();
	Board(const Board& board);
	~Board();

    void deletePieces();
	std::vector<std::vector<Spot*>> getChessBoard() const;
	GameStatus getGameStatus() const;
	void setGameStatus(GameStatus gameStatus);
    Spot* findPositionOfKing(bool PieceColor);
	bool isInCheck(bool PieceColor);
    bool isCheckMate(bool PieceColor);
    GameStatus checkGameStatus(bool PieceColor);

};

#endif //BOARD_H_
