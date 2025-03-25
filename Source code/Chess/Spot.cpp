#include "Spot.h"
#include"Piece.h"

Spot::Spot() : x(0), y(0), piece(nullptr)
{}

Spot::Spot(char x, char y, Piece* piece) : x(x), y(y), piece(piece)
{}

Spot::Spot(const Spot& spot)
{
    this->x = spot.x;
    this->y = spot.y;
    if (spot.piece != nullptr)
    {
        this->piece = spot.piece->clone();
    } else this->piece = nullptr;
}

Spot& Spot::operator=(const Spot& spot)
{
    if (this == &spot)
    {
        return *this;
    }
    this->x = spot.x;
    this->y = spot.y;
    delete this->piece;
    this->piece = spot.piece->clone();

    return *this;
}

Spot::~Spot()
{
    if(piece != nullptr)
    {
        delete piece;
    }
    piece = nullptr;
}

char Spot::getX() {
    return this->x;
}

char Spot::getY() {
    return this->y;
}

Piece* Spot::getPiece() const
{
    return this->piece;
}

bool Spot::isEmpty() const
{
    return this->piece == nullptr;
}

void Spot::changePiece(Piece* piece)
{
    Piece* oldPiece = this->piece;
    this->piece = piece;
    if (this->piece != nullptr)
    {
        this->piece->setLocation(this->getX(), this->getY());
    }
    if (oldPiece != nullptr)
    {
        delete oldPiece;
        oldPiece = nullptr;
    }
}

QTableWidgetItem* Spot::getIcon() const
{
    if(!this->isEmpty())
    {
        return piece->getIcon();
    }

    return nullptr;
}

void Spot::setPiece(Piece* piece)
{
    this->piece=piece;
    if(this->piece!=nullptr){
        this->piece->setLocation(this->getX(), this->getY());
    }
}
