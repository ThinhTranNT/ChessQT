#include "Pawn.h"
#include <vector>
#include "Move.h"

Piece* Pawn::bootstrapObject = Piece::addSample(new Pawn());

Pawn::Pawn() : Piece()
{}

Pawn::Pawn(bool isWhite) : Piece(isWhite)
{}

Pawn::Pawn(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

Pawn::~Pawn()
{}


std::vector<Spot*> Pawn::getValidSpots(Board* board) const
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

std::vector<Spot*> Pawn::getVirtualSpots(Board* board) const
{
        int d = 1; //neu la quan trang thi khi piece di chuyen, x va y tang
    if (!this->isWhite)
    {
        d = -1; //nguoc lai
    }

    std::vector<Spot*> virtualSpots;
    int X = int(this->x - '1');
    int Y = this->y - 'a';

    if (X + d >= 0 && X + d < 8 && board->getChessBoard()[X + d][Y]->isEmpty())
    {
        virtualSpots.push_back(board->getChessBoard()[X + d][Y]);
    }

    if (!this->isMoved)
    {
        if (board->getChessBoard()[X + 2 * d][Y]->isEmpty() && board->getChessBoard()[X + d][Y]->isEmpty())
        {
            virtualSpots.push_back(board->getChessBoard()[X + 2 * d][Y]);
        }
    }

    if (X + d >= 0 && X + d < 8 && Y + d < 8 && Y + d >= 0 && !board->getChessBoard()[X + d][Y + d]->isEmpty())
    {
        if (this->isEnemy(board->getChessBoard()[X + d][Y + d]->getPiece()))
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][Y + d]);
        }
    }
    if (X + d >= 0 && X + d < 8 && Y - d >= 0 && Y - d < 8 && !board->getChessBoard()[X + d][Y - d]->isEmpty())
    {
        if (this->isEnemy(board->getChessBoard()[X + d][Y - d]->getPiece()))
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][Y - d]);
        }
    }

    if (X == (7 + d) / 2)
    {
        if (Move::lastMove->getNamePieceMove() != "Pawn")
        {
            return virtualSpots;
        }

        if (Move::lastMove->getSpotEnd()->getY() != this->y + 1 && Move::lastMove->getSpotEnd()->getY() != this->y - 1)
        {
            return virtualSpots;
        }

        int enemyY = Move::lastMove->getSpotEnd()->getY() - 'a';

        if (Move::lastMove->getSpotEnd()->getX() - Move::lastMove->getSpotStart()->getX() == -2*d)
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][enemyY]);
        }
    }

    return virtualSpots;
}

QTableWidgetItem* Pawn::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WPawn.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BPawn.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}

std::string Pawn::getClassName() const
{
    return "Pawn";
}

Piece* Pawn::clone() const
{
    return new Pawn(this->x, this->y, this->isWhite);
}
