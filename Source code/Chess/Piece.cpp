#include "Piece.h"


Piece* Piece::addSample(Piece* sample)
{
    Piece::sampleList.push_back(sample);

    return sample;
}


Piece::Piece() : x(0), y(0), isWhite(false), isKilled(false), isMoved(false)
{}

Piece::Piece(bool isWhite) : x(0), y(0), isWhite(isWhite), isKilled(false), isMoved(false)
{}

Piece::Piece(char x, char y, bool isWhite) : x(x), y(y), isWhite(isWhite), isKilled(false), isMoved(false)
{}

Piece::~Piece(){}

//getter
char Piece::getX()
{
	return this->x;
}

char Piece::getY()
{
	return this->y;
}

bool Piece::getIsWhite() const
{
	return this->isWhite;
}

bool Piece::getIsKilled()
{
	return this->isKilled;
}

bool Piece::getIsMoved()
{
	return this->isMoved;
}

//setter
void Piece::setLocation(char x, char y)
{
	this->x = x;
	this->y = y;
}

void Piece::setIsKilled()
{
	this->isKilled = true;
}

void Piece::setIsMoved()
{
	this->isMoved = true;
}

void Piece::setIsWhite()
{
    this->isWhite = true;
}

bool Piece::isEnemy(Piece* other) const
{
	return this->isWhite != other->getIsWhite();
}

Piece* Piece::getClone(std::string pieceName)
{
    for(int i = 0; i < (int)(sampleList.size()); i++)
    {
        if(sampleList[i]->getClassName() == pieceName)
        {
            return sampleList[i]->clone();
        }
    }

    return nullptr;
}

void Piece::deleteSampleList()
{
    for (int i = 0; i < (int)(Piece::sampleList.size()); i++)
    {
        delete Piece::sampleList[i];
        sampleList[i] = nullptr;
    }
    Piece::sampleList.clear();
}
