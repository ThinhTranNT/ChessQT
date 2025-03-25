#ifndef QUEEN_H_
#define QUEEN_H_

#include "Piece.h"

class Queen : public Piece
{
private:
    static Piece* bootstrapObject;
public:

	Queen();
	Queen(bool isWhite);
	Queen(char x, char y, bool isWhite);
	~Queen();

	//for overriding
	std::vector<Spot*> getValidSpots(Board* board) const;
    std::vector<Spot*> getVirtualSpots(Board* board) const;
    QTableWidgetItem* getIcon() const;
	std::string getClassName() const;
	Piece* clone() const;

};

#endif //QUEEN_H_
