#include "Move.h"
#include "Piece.h"

Move* Move::lastMove = nullptr;

Move::Move(Player* playerTurn, Spot* spotStart)
    : player(new Player(playerTurn->getIsWhite())), spotStart(spotStart), spotEnd(nullptr),
    isCastlingMove(false), isAbleToPromote(false), namePieceKilled("")
{
    if (this->spotStart->getPiece() != nullptr)
    {
        this->namePieceMove = this->spotStart->getPiece()->getClassName();
    }
    else this->namePieceMove = "";
}

Move::~Move()
{
    if(this->player != nullptr)
    {
        delete player;
        player = nullptr;
    }

    // vùng nhớ spotStart và end đã được xoá ở Destructor của Board
    spotStart = nullptr;
    spotEnd = nullptr;
}

//Setter
void Move::setSpotEnd(Spot* spotEnd)
{
    this->spotEnd = spotEnd;
}

void Move::setSpotStart(Spot* spotStart)
{
    this->spotStart = spotStart;
}

void Move::setIsCastlingMove()
{
    if (this->spotStart->getPiece()->getClassName() != "King")
    {
        this->isCastlingMove = false;
        return;
    }

    if (this->spotEnd->getY() - this->spotStart->getY() == 2 || this->spotEnd->getY() - this->spotStart->getY() == -2)
    {
        this->isCastlingMove = true;
    }
    else this->isCastlingMove = false;
}

void Move::setIsAbleToPromote()
{
    if (this->spotStart->getPiece()->getClassName() != "Pawn")
    {
        this->isAbleToPromote = false;
        return;
    }

    if (this->spotEnd->getX() == '8' || this->spotEnd->getX() == '1')
    {
        this->isAbleToPromote = true;
        return;
    }

    this->isAbleToPromote = false;
}

void Move:: setIsEnPassantMove()
{
    if (this->namePieceMove != "Pawn")
    {
        this->isEnPassantMove = false;
        return;
    }

    if (this->spotEnd->getY() == this->spotStart->getY())
    {
        this->isEnPassantMove = false;
        return;
    }

    if (this->spotEnd->getPiece() == nullptr)
    {
        this->isEnPassantMove = true;
        return;
    }

    this->isEnPassantMove = false;
}

void Move::setPieceMove(std::string pieceMove)
{
    this->namePieceMove = pieceMove;
}

void Move::setPieceKilled()
{
    if (this->isEnPassantMove)
    {
        this->namePieceKilled = "Pawn";
        return;
    }

    if (this->spotEnd->getPiece() == nullptr)
    {
        this->namePieceKilled = "";
        return;
    }

    this->namePieceKilled = this->spotEnd->getPiece()->getClassName();
}

//Getter
Player* Move::getPlayer() const
{
    return this->player;
}

Spot* Move::getSpotStart() const
{
    return this->spotStart;
}

Spot* Move::getSpotEnd() const
{
    return this->spotEnd;
}

bool Move::getIsCastlingMove() const
{
    return this->isCastlingMove;
}

bool Move::getIsAbleToPromote() const
{
    return this->isAbleToPromote;
}

bool Move::getIsEnPassantMove() const
{
    return this->isEnPassantMove;
}

std::string Move::getNamePieceMove() const
{
    return this->namePieceMove;
}

std::string Move::getNamePieceKilled() const
{
    return this->namePieceKilled;
}

void Move::move(Board* board) // di chuyển piece từ spotStart -> spotEnd
{
    this->setIsCastlingMove();
    this->setIsAbleToPromote();
    this->setIsEnPassantMove();
    this->setPieceKilled();
    this->spotStart->getPiece()->setIsMoved();

    this->spotEnd->changePiece(this->spotStart->getPiece());
    this->spotStart->setPiece(nullptr);

    if (this->isCastlingMove) castlingMove(board);
    if (this->isEnPassantMove) enPassant(board);

}

void Move::castlingMove(Board* board)
{
    int row = 7;
    if (this->player->getIsWhite())
    {
        row = 0;
    }

    if (this->spotEnd->getY() == 'g')
    {
        Piece* rook = board->getChessBoard()[row][7]->getPiece();
        board->getChessBoard()[row][5]->changePiece(rook);
        board->getChessBoard()[row][7]->setPiece(nullptr);

        return;
    }

    Piece* rook = board->getChessBoard()[row][0]->getPiece();
    board->getChessBoard()[row][3]->changePiece(rook);
    board->getChessBoard()[row][0]->setPiece(nullptr);

}

void Move::promote(std::string namePiece)
{
    if(namePiece == "")
    {
        namePiece = "Rook";
    }
    Piece* promotedPiece = Piece::getClone(namePiece);
    promotedPiece->setIsMoved();
    if(spotEnd->getPiece()->getIsWhite())
    {
        promotedPiece->setIsWhite();
    }
    promotedPiece->setLocation(spotEnd->getX(),spotEnd->getY());
    this->spotEnd->changePiece(promotedPiece);
}

void Move::enPassant(Board* board)
{
    int d = -1;
    if (!this->player->getIsWhite())
    {
        d = 1;
    }

    int X = this->spotEnd->getX() - '1';
    int Y = this->spotEnd->getY() - 'a';

    board->getChessBoard()[X + d][Y]->changePiece(nullptr);
}

