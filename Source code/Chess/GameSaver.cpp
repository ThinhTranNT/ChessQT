#include "GameSaver.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include <fstream>
#include "Move.h"
#include "Player.h"


Piece* GameSaver::classifyPiece(std::string className)
{
    if (className == "Pawn")
    {
        return new Pawn(false);
    }
    if (className == "Rook")
    {
        return new Rook(false);
    }
    if (className == "Knight")
    {
        return new Knight(false);
    }
    if (className == "Bishop")
    {
        return new Bishop(false);
    }
    if (className == "Queen")
    {
        return new Queen(false);
    }
    if (className == "King")
    {
        return new King(false);
    }
    return nullptr;
}
void GameSaver::save(std::string fileName, bool isWhiteTurn, Board* oldBoard)
{
    std::ofstream outFile;
    outFile.open(fileName);
    if(!outFile.is_open())
    {
        return;
    }
    outFile << (int)(isWhiteTurn) << "\n";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (oldBoard->getChessBoard()[i][j]->isEmpty() != true)
            {
                outFile << oldBoard->getChessBoard()[i][j]->getPiece()->getClassName();
                outFile << " ";
                outFile << oldBoard->getChessBoard()[i][j]->getPiece()->getX();
                outFile << " ";
                outFile << oldBoard->getChessBoard()[i][j]->getPiece()->getY();
                outFile << " ";
                if (oldBoard->getChessBoard()[i][j]->getPiece()->getIsWhite() == true)
                {
                    outFile << "true";
                }
                else {
                    outFile << "false";
                }
                outFile << " ";
                if (oldBoard->getChessBoard()[i][j]->getPiece()->getIsMoved() == true)
                {
                    outFile << "true";
                }
                else
                {
                    outFile << "false";
                }
                outFile << "\n";
            }
        }
    }
    if(Move::lastMove != nullptr)
    {
        outFile << "\n" << Move::lastMove->getNamePieceMove();
        outFile << "\n" << Move::lastMove->getSpotStart()->getX() << Move::lastMove->getSpotStart()->getY();
        outFile << "\n" << Move::lastMove->getSpotEnd()->getX() << Move::lastMove->getSpotEnd()->getY();
    }

    outFile.close();
}
void GameSaver::load(std::string fileName, bool& isWhiteTurn, Board* newBoard)
{
    std::ifstream inFile;
    inFile.open(fileName);
    if(!inFile.is_open())
    {
        return;
    }
    std::string line = "";
    std::string className = "";
    char X = 0;
    char Y = 0;
    std::string isWhite = "";
    std::string isMoved = "";
    int countSpace = 0;

    if(!inFile.eof())
    {
        getline(inFile, line);
        if(line == "1")
        {
            isWhiteTurn = true;
        }
        if(line == "0")
        {
            isWhiteTurn = false;
        }
        line = "";
    }
    newBoard->deletePieces();
    while (!inFile.eof())
    {
        line = "";
        className = "";
        X = 0;
        Y = 0;
        isWhite = "";
        isMoved = "";
        getline(inFile, line);
        if(line == "")
        {
            break;
        }
        countSpace = 0;
        for (int i = 0; i < (int)(line.size()); i++)
        {
            if (line[i] != ' ' && countSpace == 4)
            {
                isMoved = isMoved + line[i];
            }
            if (line[i] != ' ' && countSpace == 3)
            {
                isWhite = isWhite + line[i];
            }
            if (line[i] != ' ' && countSpace == 2)
            {
                Y = line[i];
            }
            if (line[i] != ' ' && countSpace == 1)
            {
                X = line[i];
            }
            if (line[i] != ' ' && countSpace == 0)
            {
                className = className + line[i];
            }
            if (line[i] == ' ')
            {
                countSpace++;
            }
        }

        Piece* piece = classifyPiece(className);
        piece->setLocation(X, Y);

        if (isWhite == "true")
        {
            piece->setIsWhite();
        }
        if (isMoved == "true")
        {
            piece->setIsMoved();
        }
        int x = int(X - '1');
        int y = Y - 'a';
        newBoard->getChessBoard()[x][y]->changePiece(piece);
    }

    if(!inFile.eof())
    {
        if(Move::lastMove != nullptr)
        {
            delete Move::lastMove;
            Move::lastMove = nullptr;
        }
        getline(inFile, line);
        Move::lastMove = new Move(new Player(), newBoard->getChessBoard()[0][0]);
        Move::lastMove->setPieceMove(line);
        getline(inFile, line);
        Move::lastMove->setSpotStart(newBoard->getChessBoard()[line[0] - '1'][line[1] - 'a']);
        getline(inFile, line);
        Move::lastMove->setSpotEnd(newBoard->getChessBoard()[line[0] - '1'][line[1] - 'a']);
        line = "";
    }

    inFile.close();
}
