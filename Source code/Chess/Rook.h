#ifndef ROOK_H_
#define ROOK_H_

#include "Piece.h"

class Rook : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	Rook();
	Rook(bool isWhite);
	Rook(char x, char y, bool isWhite);
	~Rook();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;
    std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
    std::string getClassName() const;
    Piece* clone() const;

};

#endif //ROOK_H_
