#include "Rook.h"
#include <vector>

Piece* Rook::bootstrapObject = Piece::addSample(new Rook());

Rook::Rook() : Piece()
{}

Rook::Rook(bool isWhite) : Piece(isWhite)
{}

Rook::Rook(char x, char y, bool isWhite) : Piece(x, y, isWhite)
{}

Rook::~Rook()
{}


std::vector<Spot*> Rook::getValidSpots(Board* board) const
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

std::vector<Spot*> Rook::getVirtualSpots(Board* board) const
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

    return virtualSpots;
}

QTableWidgetItem* Rook::getIcon() const
{
    QIcon icon;
    if(isWhite == true)
    {
        icon.addFile(QString::fromUtf8(":/Materials/WRook.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
    {
        icon.addFile(QString::fromUtf8(":/Materials/BRook.png"), QSize(), QIcon::Normal, QIcon::Off);
    }


    QTableWidgetItem * item = new QTableWidgetItem();
    item->setIcon(icon);
    return item;
}

std::string Rook::getClassName() const
{
    return "Rook";
}

Piece* Rook::clone() const
{
    return new Rook(this->x, this->y, this->isWhite);
}





