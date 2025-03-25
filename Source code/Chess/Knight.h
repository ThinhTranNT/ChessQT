#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Piece.h"

class Knight : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	Knight();
	Knight(bool isWhite);
	Knight(char x, char y, bool isWhite);
	~Knight();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;
    std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
	std::string getClassName() const;
	Piece* clone() const;

};

#endif //KNIGHT_H_
