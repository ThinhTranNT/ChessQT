#ifndef PAWN_H_
#define PAWN_H_

#include "Piece.h"

class Pawn : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	Pawn();
	Pawn(bool isWhite);
	Pawn(char x, char y, bool isWhite);
	~Pawn();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;// trả về chính xác ô được đi
    std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
	std::string getClassName() const;
	Piece* clone() const;

	//virtual Piece* promote(std::string className) const; //phong Tot
};

#endif //PAWN_H_
