#include "Bishop.h"
#include <vector>

Piece* Bishop::bootstrapObject = Piece::addSample(new Bishop());

Bishop::Bishop() : Piece()
{}

Bishop::Bishop(bool isWhite) : Piece(isWhite)
{}

Bishop::Bishop(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

Bishop::~Bishop()
{}


std::vector<Spot*> Bishop::getValidSpots(Board* board) const
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

std::vector<Spot*> Bishop::getVirtualSpots(Board* board) const
{
    std::vector<Spot*> virtualSpots;
    int X = int(this->x - '1');
    int Y = this->y - 'a';

    int temp = 0;

    temp = Y;
    for (int i = X + 1; i < 8; ++i) {
        temp++;
        if (temp >= 8) {
            break;
        }
        if (board->getChessBoard()[i][temp]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
            continue;
        }
        if (board->getChessBoard()[i][temp]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
        }
        break;
    }
    temp = Y;
    for (int i = X + 1; i < 8; ++i) {
        temp--;
        if (temp < 0) {
            break;
        }
        if (board->getChessBoard()[i][temp]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
            continue;
        }
        if (board->getChessBoard()[i][temp]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
        }
        break;
    }

    temp = Y;
    for (int i = X - 1; i >= 0; --i) {
        temp++;
        if (temp >= 8) {
            break;
        }
        if (board->getChessBoard()[i][temp]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
            continue;
        }
        if (board->getChessBoard()[i][temp]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
        }
        break;
    }
    temp = Y;
    for (int i = X - 1; i >= 0; --i) {
        temp--;
        if (temp < 0) {
            break;
        }
        if (board->getChessBoard()[i][temp]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
            continue;
        }
        if (board->getChessBoard()[i][temp]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][temp]);
        }
        break;
    }

    return virtualSpots;
}

QTableWidgetItem* Bishop::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WBishop.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BBishop.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}

std::string Bishop::getClassName() const
{
    return "Bishop";
}

Piece* Bishop::clone() const
{
    return new Bishop(this->x, this->y, this->isWhite);
}





