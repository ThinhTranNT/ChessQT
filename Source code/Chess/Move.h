#ifndef MOVE_H_
#define MOVE_H_

#include "Player.h"
#include "Board.h"
#include <string>

class Move
{
private:
    Player* player;
    Spot* spotStart;
    Spot* spotEnd;
    bool isCastlingMove;
    bool isAbleToPromote;
    bool isEnPassantMove;
    std::string namePieceMove;
    std::string namePieceKilled;

public:
    static Move* lastMove;

    Move(Player* playerTurn, Spot* spotStart);
    ~Move();

    //Setter // gán giá trị cho spotEnd = spot được chọn để đi => setSpotEnd(Spot* spotEnd)
    void setSpotEnd(Spot* spotEnd);
    void setSpotStart(Spot* spotStart);

    void setIsCastlingMove();
    void setIsAbleToPromote();
    void setIsEnPassantMove();

    void setPieceMove(std::string pieceMove);
    void setPieceKilled();

    //Getter
    Player* getPlayer() const;
    Spot* getSpotStart() const;
    Spot* getSpotEnd() const;
    bool getIsCastlingMove() const;
    bool getIsAbleToPromote() const;
    bool getIsEnPassantMove() const;
    std::string getNamePieceMove() const;
    std::string getNamePieceKilled() const;

    void move(Board* board); // di chuyển piece từ spotStart -> spotEnd, xoá vùng nhớ spotEnd nếu có ( removePieceKilled.

    void castlingMove(Board* board);
    void promote(std::string namePiece);
    void enPassant(Board* board);
};




#endif // !MOVE_H_
