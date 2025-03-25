#ifndef PIECE_H_
#define PIECE_H_

#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include <QTableWidgetItem>

class Piece
{
private:
    static std::vector<Piece*> sampleList;

protected:
	char x;
	char y;
    bool isWhite;
	bool isKilled;
	bool isMoved;

    static Piece* addSample(Piece* sample);

public:
	Piece();
	Piece(bool isWhite);
	Piece(char x, char y, bool isWhite);
    virtual ~Piece();

	
	//getter
	virtual char getX();
	virtual char getY();
	virtual bool getIsWhite() const;
	virtual bool getIsKilled();
	virtual bool getIsMoved();

	//setter
	virtual void setLocation(char x, char y);
	virtual void setIsKilled(); //set isKilled value
	virtual void setIsMoved(); //set isMoved value
    virtual void setIsWhite();

	virtual bool isEnemy(Piece* other) const; // kiểm tra other có phải team địch không

	//for overriding
	virtual std::vector<Spot*> getValidSpots(Board* board) const = 0;// trả về chính xác ô được đi
	virtual std::vector<Spot*> getVirtualSpots(Board* board) const = 0;
	virtual std::string getClassName() const = 0;
    virtual QTableWidgetItem* getIcon() const = 0;
	virtual Piece* clone() const = 0;
    static Piece* getClone(std::string pieceName);

    static void deleteSampleList();
};

#endif //PIECE_H_

