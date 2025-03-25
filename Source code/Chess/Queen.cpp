#include "Queen.h"
#include <vector>

Piece* Queen::bootstrapObject = Piece::addSample(new Queen());

Queen::Queen() : Piece()
{}

Queen::Queen(bool isWhite) : Piece(isWhite)
{}

Queen::Queen(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

Queen::~Queen()
{}

std::vector<Spot*> Queen::getValidSpots(Board* board) const
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

std::vector<Spot*> Queen::getVirtualSpots(Board* board) const
{
    std::vector<Spot*> virtualSpots;
    int X = int(this->x - '1');
    int Y = this->y - 'a';

    for (int i = X + 1; i < 8; ++i) {
        if (board->getChessBoard()[i][Y]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][Y]);
            continue;
        }
        if (board->getChessBoard()[i][Y]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][Y]);
        }
        break;
    }
    for (int i = X - 1; i >= 0; --i) {
        if (board->getChessBoard()[i][Y]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[i][Y]);
            continue;
        }
        if (board->getChessBoard()[i][Y]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[i][Y]);
        }
        break;
    }
    for (int j = Y + 1; j < 8; ++j) {
        if (board->getChessBoard()[X][j]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[X][j]);
            continue;
        }
        if (board->getChessBoard()[X][j]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[X][j]);
        }
        break;
    }
    for (int j = Y - 1; j >= 0; --j) {
        if (board->getChessBoard()[X][j]->isEmpty()) {
            virtualSpots.push_back(board->getChessBoard()[X][j]);
            continue;
        }
        if (board->getChessBoard()[X][j]->getPiece()->getIsWhite() != this->isWhite) {
            virtualSpots.push_back(board->getChessBoard()[X][j]);
        }
        break;
    }

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

QTableWidgetItem* Queen::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WQueen.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BQueen.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}

std::string Queen::getClassName() const
{
    return "Queen";
}

Piece* Queen::clone() const
{
    return new Queen(this->x, this->y, this->isWhite);
}





