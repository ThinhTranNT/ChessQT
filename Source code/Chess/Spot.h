#ifndef SPOT_H_
#define SPOT_H_

#include <QTableWidgetItem>

class Piece;

class Spot {
protected:
    char x;
    char y;
    Piece* piece;
public:
    Spot();
    Spot(char x, char y, Piece* piece);
    Spot(const Spot& spot);
    Spot& operator=(const Spot& spot);
    ~Spot();
    char getX();
    char getY();
    Piece* getPiece() const;
    QTableWidgetItem* getIcon() const;
    void changePiece(Piece* piece);

    void setPiece(Piece* piece); //addition to get valid spot!!!

    bool isEmpty() const;

};

#endif //SPOT_H_
