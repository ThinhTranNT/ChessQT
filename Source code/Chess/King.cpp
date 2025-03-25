#include "King.h"
#include <vector>
#include <cmath>
Piece* King::bootstrapObject = Piece::addSample(new King());

King::King() : Piece()
{}

King::King(bool isWhite) : Piece(isWhite)
{}

King::King(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

King::~King()
{}


std::vector<Spot*> King::getValidSpots(Board* board) const
{
    std::vector<Spot*> validSpots;
    bool check = this->isWhite ? true : false;
    std::vector<Spot*> virtualSpots;
    int X = int(this->x - '1');
    int Y = this->y - 'a';
    virtualSpots = board->getChessBoard()[X][Y]->getPiece()->getVirtualSpots(board);
    int n = virtualSpots.size();
    int kt = 0;
    if (board->isInCheck(check))
    {
        kt = 1;
    }

    Piece* temp = board->getChessBoard()[X][Y]->getPiece();
    board->getChessBoard()[X][Y]->setPiece(nullptr);

    for (int i = 0; i < n; i++) {
        if (virtualSpots[i]->getY() - board->getChessBoard()[X][Y]->getY() == 2)
        {
            if (kt == 1)
            {
                continue;
            }
            int m = validSpots.size();
            if (m == 0)
            {
                continue;
            }
            if (validSpots[m - 1]->getY() - board->getChessBoard()[X][Y]->getY() != +1)
            {
                continue;
            }
        }
        if (virtualSpots[i]->getY() - board->getChessBoard()[X][Y]->getY() == -2)
        {
            if (kt == 1)
            {
                continue;
            }
            int m = validSpots.size();
            if (m == 0) {
                continue;
            }
            if (validSpots[m - 1]->getY() - board->getChessBoard()[X][Y]->getY() != -1) {
                continue;
            }
        }

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

std::vector<Spot*> King::getVirtualSpots(Board* board) const
{
    std::vector<Spot*> virtualSpots;
    int d = 1;
    int X = int(this->x - '1');
    int Y = this->y - 'a';

    //int c = 2; // castling

    if (X + d >= 0 && X + d <= 7) {
        if ((board->getChessBoard()[X + d][Y]->isEmpty() || board->getChessBoard()[X + d][Y]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][Y]);
        }
    }
    if (X - d >= 0 && X - d <= 7)
    {
        if ((board->getChessBoard()[X - d][Y]->isEmpty() || board->getChessBoard()[X - d][Y]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X - d][Y]);
        }
    }
    if (Y + d >= 0 && Y + d <= 7) {
        if ((board->getChessBoard()[X][Y + d]->isEmpty() || board->getChessBoard()[X][Y + d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X][Y + d]);
            if (!this->isMoved && board->getChessBoard()[X][Y + 2 * d]->isEmpty() && !board->getChessBoard()[X][Y + 3 * d]->isEmpty())
            {
                if (board->getChessBoard()[X][Y + 3 * d]->getPiece()->getClassName() == "Rook" && !board->getChessBoard()[X][Y + 3 * d]->getPiece()->getIsMoved())
                {
                    virtualSpots.push_back(board->getChessBoard()[X][Y + 2 * d]);
                }
            }
        }
    }
    if (Y - d >= 0 && Y - d <= 7) {
        if ((board->getChessBoard()[X][Y - d]->isEmpty() || board->getChessBoard()[X][Y - d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X][Y - d]);
            if (!this->isMoved && board->getChessBoard()[X][Y - 2 * d]->isEmpty() && board->getChessBoard()[X][Y - 3 * d]->isEmpty() && !board->getChessBoard()[X][Y - 4 * d]->isEmpty())
            {
                if (board->getChessBoard()[X][Y - 4 * d]->getPiece()->getClassName() == "Rook" && !board->getChessBoard()[X][Y - 4 * d]->getPiece()->getIsMoved())
                {
                    virtualSpots.push_back(board->getChessBoard()[X][Y - 2 * d]);
                }
            }
        }
    }
    if (X + d >= 0 && X + d <= 7 && Y + d >= 0 && Y + d <= 7) {
        if ((board->getChessBoard()[X + d][Y + d]->isEmpty() || board->getChessBoard()[X + d][Y + d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][Y + d]);
        }
    }
    if (X + d >= 0 && X + d <= 7 && Y - d >= 0 && Y - d <= 7) {
        if ((board->getChessBoard()[X + d][Y - d]->isEmpty() || board->getChessBoard()[X + d][Y - d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X + d][Y - d]);
        }
    }
    if (X - d >= 0 && X - d <= 7 && Y + d >= 0 && Y + d <= 7) {
        if ((board->getChessBoard()[X - d][Y + d]->isEmpty() || board->getChessBoard()[X - d][Y + d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X - d][Y + d]);
        }
    }
    if (X - d >= 0 && X - d <= 7 && Y - d >= 0 && Y - d <= 7) {
        if ((board->getChessBoard()[X - d][Y - d]->isEmpty() || board->getChessBoard()[X - d][Y - d]->getPiece()->getIsWhite() != this->isWhite))
        {
            virtualSpots.push_back(board->getChessBoard()[X - d][Y - d]);
        }
    }


    return virtualSpots;
}
QTableWidgetItem* King::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WKing.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BKing.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}
std::string King::getClassName() const
{
    return "King";
}

Piece* King::clone() const
{
    return new King(this->x, this->y, this->isWhite);
}
