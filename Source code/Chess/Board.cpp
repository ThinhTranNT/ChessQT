#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"

Board::Board()
{
	gameStatus = GameStatus::ACTIVE;
	this->chessBoard.resize(8);
	for (int i = 0; i < 8; i++)
	{
		this->chessBoard[i].resize(8);
	}

    for (int i = 0; i < 8; i++)
    {
        this->chessBoard[1][i] = new Spot('2', 'a' + i, new Pawn('2', 'a' + i, true));
        this->chessBoard[6][i] = new Spot('7', 'a' + i, new Pawn('7', 'a' + i, false));
    }

    this->chessBoard[0][0] = new Spot('1', 'a', new Rook('1', 'a', true));
    this->chessBoard[0][7] = new Spot('1', 'h', new Rook('1', 'h', true));
    this->chessBoard[7][0] = new Spot('8', 'a', new Rook('8', 'a', false));
    this->chessBoard[7][7] = new Spot('8', 'h', new Rook('8', 'h', false));

    this->chessBoard[0][1] = new Spot('1', 'b', new Knight('1', 'b', true));
    this->chessBoard[0][6] = new Spot('1', 'g', new Knight('1', 'g', true));
    this->chessBoard[7][1] = new Spot('8', 'b', new Knight('8', 'b', false));
    this->chessBoard[7][6] = new Spot('8', 'g', new Knight('8', 'g', false));

    this->chessBoard[0][2] = new Spot('1', 'c', new Bishop('1', 'c', true));
    this->chessBoard[0][5] = new Spot('1', 'f', new Bishop('1', 'f', true));
    this->chessBoard[7][2] = new Spot('8', 'c', new Bishop('8', 'c', false));
    this->chessBoard[7][5] = new Spot('8', 'f', new Bishop('8', 'f', false));

    this->chessBoard[0][3] = new Spot('1', 'd', new Queen('1', 'd', true));
    this->chessBoard[0][4] = new Spot('1', 'e', new King('1', 'e', true));
    this->chessBoard[7][3] = new Spot('8', 'd', new Queen('8', 'd', false));
    this->chessBoard[7][4] = new Spot('8', 'e', new King('8', 'e', false));

    for (int i = 2; i <= 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->chessBoard[i][j] = new Spot('1' + i, 'a' + j, nullptr);
        }
    }

}

Board::Board(const Board& board)
{
	this->gameStatus = board.getGameStatus();
	this->chessBoard.resize(8);
	for (int i = 0; i < 8; i++)
	{
		this->chessBoard[i].resize(8);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->chessBoard[i][j] = new Spot(*(board.chessBoard[i][j]));
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
            if(this->chessBoard[i][j] != nullptr)
            {
                if(this->chessBoard[i][j] != nullptr)
                {
                    delete this->chessBoard[i][j];
                }
            }
            this->chessBoard[i][j] = nullptr;
		}
	}
}

void Board::deletePieces()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(!this->chessBoard[i][j]->isEmpty())
            {
                delete this->chessBoard[i][j]->getPiece();
                this->chessBoard[i][j]->setPiece(nullptr);
            }
        }
    }
}

Spot* Board::findPositionOfKing(bool PieceColor)
{
    bool breakFlag = false;
    for (int iRow = 0; iRow < 8; iRow++)
    {
        for (int iCol = 0; iCol < 8; iCol++)
        {
            if (this->getChessBoard()[iRow][iCol]->isEmpty())
            {
                continue;
            }
            if (!this->getChessBoard()[iRow][iCol]->getPiece()->getIsWhite() == PieceColor)
            {
                continue;
            }
            if (this->getChessBoard()[iRow][iCol]->getPiece()->getClassName() == "King")
            {
                return this->getChessBoard()[iRow][iCol];
                breakFlag = true;
                break;
            }
        }

        if (breakFlag) break;
    }

    return nullptr;
}

bool Board::isInCheck(bool PieceColor)
{
    Spot* spotKing = findPositionOfKing(PieceColor);
    int iKingRow = spotKing->getX() - '1';
    int iKingCol = spotKing->getY() - 'a';
	


	// Run through the opponent's pieces and see if any can take the king

    std::vector<Spot*> virtualSpots;
    int virtualRow = 0;
    int virtualCol = 0;
    Piece* enemy = nullptr;

    for (int iRow = 0; iRow < 8; iRow++)
    {
        for (int iCol = 0; iCol < 8; iCol++)
        {
            enemy = this->getChessBoard()[iRow][iCol]->getPiece();
            if (enemy == nullptr)
            {
                continue;
            }

            if (enemy->getIsWhite() == PieceColor)
            {
                continue;
            }

            virtualSpots = enemy->getVirtualSpots(this);

            for (int i = 0; i < (int)(virtualSpots.size()); i++)
            {
                virtualRow = virtualSpots[i]->getX() - '1';
                virtualCol = virtualSpots[i]->getY() - 'a';
                if (virtualRow != iKingRow || virtualCol  != iKingCol)
                {
                    continue;
                }

                if (enemy->getIsWhite() == 1)
                {
                    this->setGameStatus(GameStatus::CHECK_BLACK_KING);
                }
                else
                {
                    this->setGameStatus(GameStatus::CHECK_WHITE_KING);
                }
                return true; // if the oppent's pieces can take the king by spot x, y
            }
		}
	}
	this->setGameStatus(GameStatus::ACTIVE);
	
	return false;
}

std::vector<std::vector<Spot*>> Board::getChessBoard() const
{
	return this->chessBoard;
}

GameStatus Board::getGameStatus() const
{
	return gameStatus;
}

void Board::setGameStatus(GameStatus gameStatus)
{
	this->gameStatus = gameStatus;
}

bool Board::isCheckMate(bool PieceColor) {
    // after moving, check enemy's validSpot
    std::vector<Spot*> validSpots;

    Piece*  enemy = nullptr;
    bool checkMate = true;

    for (int iRow = 0; iRow < 8; iRow++)
    {
        for (int iCol = 0; iCol < 8; iCol++)
        {
            enemy = this->getChessBoard()[iRow][iCol]->getPiece();
            if (enemy == nullptr)
            {
                continue;
            }
            if (enemy->getIsWhite() == PieceColor)
            {
                continue;
            }
            validSpots = enemy->getValidSpots(this);
            int n = validSpots.size();
            if (n > 0) {
                checkMate = false;
                break;
            }
        }
    }

    if (checkMate == true && isInCheck(!PieceColor)) {
        if (PieceColor == 1)
        {
            this->setGameStatus(GameStatus::WHITE_WIN);
        }
        else
        {
            this->setGameStatus(GameStatus::BLACK_WIN);
        }
        return true;
    }
    else if (checkMate == true) {
        this->setGameStatus(GameStatus::DRAW);
    }
    else {
        this->setGameStatus(GameStatus::ACTIVE);
    }
    return false;
}

GameStatus Board::checkGameStatus(bool PieceColor) {
    isCheckMate(PieceColor);
    return gameStatus;
}
