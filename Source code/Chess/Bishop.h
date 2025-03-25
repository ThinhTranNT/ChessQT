#ifndef BISHOP_H_
#define BISHOP_H_

#include "Piece.h"

class Bishop : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	Bishop();
	Bishop(bool isWhite);
	Bishop(char x, char y, bool isWhite);
	~Bishop();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;
	std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
	std::string getClassName() const;
	Piece* clone() const;

};

#endif //BISHOP_H_
