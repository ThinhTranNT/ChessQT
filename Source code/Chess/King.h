#ifndef KING_H_
#define KING_H_

#include "Piece.h"

class King : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	King();
	King(bool isWhite);
	King(char x, char y, bool isWhite);
	~King();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;
    std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
	std::string getClassName() const;
	Piece* clone() const;

};

#endif //KING_H_




