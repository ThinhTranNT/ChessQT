#ifndef GAMESAVER_H
#define GAMESAVER_H
#include "Board.h"
#include <string>

class GameSaver
{

public:
    static void save(std::string fileName, bool isWhiteTurn, Board* oldBoard);
    static void load(std::string fileName, bool& isWhiteTurn, Board* newBoard);
    static Piece* classifyPiece(std::string className);
};

#endif // GAMESAVER_H
