#include "Knight.h"
#include <vector>
#include <cmath>

Piece* Knight::bootstrapObject = Piece::addSample(new Knight());

Knight::Knight() : Piece()
{}

Knight::Knight(bool isWhite) : Piece(isWhite)
{}

Knight::Knight(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

Knight::~Knight()
{}


std::vector<Spot*> Knight::getValidSpots(Board* board) const
{
    std::vector<Spot*> validSpots;
    bool check = this->isWhite ? true : false;
    std::vector<Spot*> virtualSpots;
    int X = int(this->x - '1');
    int Y = this->y - 'a';
    virtualSpots = board->getChessBoard()[X][Y]->getPiece()->getVirtualSpots(board);
    int n = virtualSpots.size();

    Piece* temp = board->getChessBoard()[X][Y]->getPiece();
    board->getChessBoard()[X][Y]->setPiece(nullptr);

    for (int i = 0; i < n; i++) {
        Piece* tmpIdx = virtualSpots[i]->getPiece();
        virtualSpots[i]->setPiece(temp);
        if (!board->isInCheck(check)) {
            validSpots.push_back(virtualSpots[i]);
            virtualSpots[i]->setPiece(tmpIdx);
            continue;
        }
        virtualSpots[i]->setPiece(tmpIdx);
    }

    board->getChessBoard()[X][Y]->setPiece(temp);

    return validSpots;
}

std::vector<Spot*> Knight::getVirtualSpots(Board* board) const
{
	std::vector<Spot*> virtualSpots;
	int X = int(this->x - '1');
	int Y = this->y - 'a';

    if (X - 2 >= 0 && Y - 1 >= 0) {
        if (board->getChessBoard()[X - 2][Y - 1]->isEmpty() || board->getChessBoard()[X - 2][Y - 1]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X - 2][Y - 1]);
        }
    }
    if (X - 1 >= 0 && Y - 2 >= 0)
    {
        if (board->getChessBoard()[X - 1][Y - 2]->isEmpty() || board->getChessBoard()[X - 1][Y - 2]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X - 1][Y - 2]);
        }
    }
    if (X - 2 >= 0 && Y + 1 <= 7)
    {
        if (board->getChessBoard()[X - 2][Y + 1]->isEmpty() || board->getChessBoard()[X - 2][Y + 1]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X - 2][Y + 1]);
        }
    }
    if (X - 1 >= 0 && Y + 2 <= 7)
    {
        if (board->getChessBoard()[X - 1][Y + 2]->isEmpty() || board->getChessBoard()[X - 1][Y + 2]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X - 1][Y + 2]);
        }
    }
    if (X + 1 <= 7 && Y - 2 >= 0)
    {
        if (board->getChessBoard()[X + 1][Y - 2]->isEmpty() || board->getChessBoard()[X + 1][Y - 2]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X + 1][Y - 2]);
        }
    }
    if (X + 2 <= 7 && Y - 1 >= 0) {
        if (board->getChessBoard()[X + 2][Y - 1]->isEmpty() || board->getChessBoard()[X + 2][Y - 1]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X + 2][Y - 1]);
        }
    }
    if (X + 1 <= 7 && Y + 2 <= 7)
    {
        if (board->getChessBoard()[X + 1][Y + 2]->isEmpty() || board->getChessBoard()[X + 1][Y + 2]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X + 1][Y + 2]);
        }
    }
    if (X + 2 <= 7 && Y + 1 <= 7)
    {
        if (board->getChessBoard()[X + 2][Y + 1]->isEmpty() || board->getChessBoard()[X + 2][Y + 1]->getPiece()->getIsWhite() != this->isWhite)
        {
            virtualSpots.push_back(board->getChessBoard()[X + 2][Y + 1]);
        }
    }


	return virtualSpots;
}

QTableWidgetItem* Knight::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WKnight.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BKnight.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}

std::string Knight::getClassName() const
{
	return "Knight";
}

Piece* Knight::clone() const
{
	return new Knight(this->x, this->y, this->isWhite);
}





