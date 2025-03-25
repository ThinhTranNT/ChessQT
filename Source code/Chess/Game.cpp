#include "Game.h"
#include "ui_GSame.h"
#include "Piece.h"
#include "SoundController.h"
#include "GameSaver.h"
#include "PromotionDialog.h"

std::vector<Piece*> Piece::sampleList;

Game::Game(bool isContinue, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    undo = false;

    ui->setupUi(this);

    player.push_back(new Player(1));
    player.push_back(new Player(0));
    playerTurn = player[0];

    board = new Board();
    ui->whiteTurn->setPixmap(QPixmap(":/Materials/ActiveWhiteTurn.png"));
    if(isContinue == true)
    {
        bool isWhiteTurn = true;
        board->deletePieces();
        GameSaver::load("RecordedGame.txt", isWhiteTurn, board);
        if(isWhiteTurn == false)
        {
            changePlayerTurn();
        }
    }
    displayBoard();

    spotStart = nullptr;

    positionOfKing = board->findPositionOfKing(playerTurn->getIsWhite());

    GameSaver::save("Undo.txt", playerTurn->getIsWhite(), board);
    GameSaver::save("Redo.txt", playerTurn->getIsWhite(), board);

    connect(ui->boardView, SIGNAL(cellClicked(int,int)), this, SLOT(handleCellBoardviewClicked(int,int)));
    connect(ui->actionMute, SIGNAL(triggered()), this, SLOT(handleActionMute()));
    connect(ui->actionUnmute, SIGNAL(triggered()), this, SLOT(handleActionUnmute()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(handleActionSave()));
    connect(ui->actionNew_game, SIGNAL(triggered()), this, SLOT(handleActionNewGame()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(handleActionLoad()));
    connect(ui->playButton, &QPushButton::released, this, &Game::handleActionNewGame);
    connect(ui->undoButton, &QPushButton::released, this, &Game::handleUndo);
    connect(ui->redoButton, &QPushButton::released, this, &Game::handleRedo);
    connect(ui->exitButton, &QPushButton::released, this, &Game::handleExit);

    ui->blockWindow->setVisible(false);
    ui->message->setVisible(false);
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
    ui->redoButton->setVisible(false);
    ui->undoButton->setVisible(false);
}

void Game::displayValidSpot()
{
    QIcon iconDot;
    iconDot.addFile(QString::fromUtf8(":/Materials/Dot.png"), QSize(), QIcon::Normal, QIcon::Off);

    for(int i = 0; i < (int)(validSpot.size()); i++)
    {
        QTableWidgetItem * dotItem = new QTableWidgetItem();
        dotItem->setIcon(iconDot);
        int x = validSpot[i]->getX() - '1';
        int y = validSpot[i]->getY() - 'a';
        if(!(board->getChessBoard()[x][y]->isEmpty()))
        {
            ui->boardView->item(7 - x,y)->setBackground(QBrush(QColor(255,97,97)));
            continue;
        }
        ui->boardView->setItem(7 - x, y, dotItem);
    }
}

void Game::displayBoard()
{

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            delete ui->boardView->takeItem(i,j);
            ui->boardView->setItem(i,j,board->getChessBoard()[7-i][j]->getIcon());
        }
    }
}

void Game::changePlayerTurn()
{
    if(playerTurn == player[0])
    {
        playerTurn = player[1];
        ui->blackTurn->setPixmap(QPixmap(":/Materials/ActiveBlackTurn.png"));
        ui->whiteTurn->setPixmap(QPixmap(":/Materials/WhiteTurn.png"));
        return;
    }
    playerTurn = player[0];
    ui->blackTurn->setPixmap(QPixmap(":/Materials/BlackTurn.png"));
    ui->whiteTurn->setPixmap(QPixmap(":/Materials/ActiveWhiteTurn.png"));
}

void Game::promote(Move* move)
{
    ui->blockWindow->setVisible(true);
    PromotionDialog* promotionDialog = new PromotionDialog();
    promotionDialog->exec();
    if(!promotionDialog->isActiveWindow())
    {
        move->promote(promotionDialog->getNamePromotedPiece());
        ui->blockWindow->setVisible(false);
    }
    delete promotionDialog;
}

Game::~Game()
{
    delete ui;
    validSpot.clear();
    if(board != nullptr)
    {
        delete board;
        board = nullptr;
    }

    if(player[0] != nullptr)
    {
        delete player[0];
        player[0] = nullptr;
    }
    if(player[1] != nullptr)
    {
        delete player[1];
        player[1] = nullptr;
    }

    playerTurn = nullptr;
}

void Game::handleCellBoardviewClicked(int row, int column)
{
    // lấy ô đang click chuột
    Spot * selectedSpot = board->getChessBoard()[7 - row][column];

    bool flag = false;

    // xoá hiển thị các ô đi được
    for(int i = 0; i < (int)(validSpot.size());i++)
    {
        int x = validSpot[i]->getX() - '1';
        int y = validSpot[i]->getY() - 'a';
        if(!(board->getChessBoard()[x][y]->isEmpty()))
        {
            ui->boardView->item(7 - x,y)->setBackground(QBrush());
            continue;
        }

        delete ui->boardView->takeItem(7 - x,y);
    }

    positionOfKing = board->findPositionOfKing(playerTurn->getIsWhite());
    if(board->isInCheck(playerTurn->getIsWhite()))
    {
        ui->boardView->item(7 - (positionOfKing->getX() - '1'),(positionOfKing->getY() - 'a'))->setBackground(QBrush(Qt::red));
    }

    // di chuyển quân cờ
    if(spotStart != nullptr)
    {

        int x_spotStart = spotStart->getX() - '1';
        int y_spotStart = spotStart->getY() - 'a';
        Move* move = nullptr;
        for(int i = 0; i < (int)(validSpot.size()); i++)
        {
            if(selectedSpot == validSpot[i])
            {
                SoundController::playPieceMoveSoundEffect();
                flag = true;
                int x = validSpot[i]->getX() - '1';
                int y = validSpot[i]->getY() - 'a';
                delete ui->boardView->takeItem(7 - x, y);
                ui->boardView->setItem(7 - x, y, ui->boardView->takeItem(7 - x_spotStart,y_spotStart));
                validSpot.clear();

                ui->undoButton->setVisible(true);
                ui->redoButton->setVisible(false);
                GameSaver::save("Undo.txt", playerTurn->getIsWhite(), board);
                undo = false;

                if(Move::lastMove != nullptr)
                {
                    delete Move::lastMove;
                    Move::lastMove = nullptr;
                }

                move = new Move(playerTurn, spotStart);
                move->setSpotEnd(selectedSpot);
                move->move(board);

                if(move->getIsAbleToPromote())
                {
                    promote(move);
                    displayBoard();
                }

                // Kiểm tra có phải nhập thành không
                if(move->getIsCastlingMove())
                {
                    if(selectedSpot->getY() == 'g')
                    {
                        delete ui->boardView->takeItem(7 - x, y - 1);
                        ui->boardView->setItem(7 - x, y - 1, ui->boardView->takeItem(7 - x,7));
                    }

                    if(selectedSpot->getY() == 'c')
                    {
                        delete ui->boardView->takeItem(7 - x, y + 1);
                        ui->boardView->setItem(7 - x, y + 1, ui->boardView->takeItem(7 - x,0));
                    }
                }

                if(move->getIsEnPassantMove())
                {
                    delete ui->boardView->takeItem(7 - x_spotStart, y);
                }

                Move::lastMove = move;

                positionOfKing = board->findPositionOfKing(playerTurn->getIsWhite());
                if(!board->isInCheck(playerTurn->getIsWhite()))
                {
                    ui->boardView->item(7 - (positionOfKing->getX() - '1'),(positionOfKing->getY() - 'a'))->setBackground(QBrush());
                }

                changeGameStatus();
                changePlayerTurn();

                positionOfKing = board->findPositionOfKing(playerTurn->getIsWhite());
                if(board->isInCheck(playerTurn->getIsWhite()))
                {
                    ui->boardView->item(7 - (positionOfKing->getX() - '1'),(positionOfKing->getY() - 'a'))->setBackground(QBrush(Qt::red));
                }

                break;
            }
        }

        if(flag == false && (!board->getChessBoard()[7 - row][column]->isEmpty()))
        {
            if(playerTurn->getIsWhite() != selectedSpot->getPiece()->getIsWhite())
            {
                return;
            }
            validSpot = board->getChessBoard()[7 - row][column]->getPiece()->getValidSpots(board);
            displayValidSpot();
        }

        if(selectedSpot->isEmpty())
        {
            spotStart = nullptr;
            return;
        }

        spotStart = selectedSpot;
        return;
    }

    // hiển thị các ô đi được
    if(selectedSpot->isEmpty())
    {
        return;
    }

    if(playerTurn->getIsWhite() != selectedSpot->getPiece()->getIsWhite())
    {
        return;
    }

    spotStart = selectedSpot;

    validSpot = board->getChessBoard()[7 - row][column]->getPiece()->getValidSpots(board);

    displayValidSpot();
}

void Game::changeGameStatus()
{
    if(board->checkGameStatus(playerTurn->getIsWhite()) == GameStatus::WHITE_WIN)
    {
        ui->blockWindow->setVisible(true);
        ui->message->setVisible(true);
        ui->playButton->setVisible(true);
        ui->exitButton->setVisible(true);
        ui->message->setPixmap(QPixmap(":/Materials/WhiteWin.png"));
    }
    if(board->checkGameStatus(playerTurn->getIsWhite()) == GameStatus::BLACK_WIN)
    {
        ui->blockWindow->setVisible(true);
        ui->message->setVisible(true);
        ui->playButton->setVisible(true);
        ui->exitButton->setVisible(true);
        ui->message->setPixmap(QPixmap(":/Materials/BlackWin.png"));
    }
    if(board->checkGameStatus(playerTurn->getIsWhite()) == GameStatus::DRAW)
    {
        ui->blockWindow->setVisible(true);
        ui->message->setVisible(true);
        ui->playButton->setVisible(true);
        ui->exitButton->setVisible(true);
        ui->message->setPixmap(QPixmap(":/Materials/Draw.png"));
    }
}

void Game::handleActionUnmute()
{
    SoundController::backgroundMusic->play();
    SoundController::isMute = false;
}

void Game::handleActionMute()
{
    SoundController::backgroundMusic->stop();
    SoundController::isMute = true;
}

void Game::handleActionSave()
{
    GameSaver::save("RecordedGame.txt", playerTurn->getIsWhite(), board);
}

void Game::handleActionNewGame()
{
    validSpot.clear();
    if(board != nullptr)
    {
        delete board;
        board = nullptr;
    }
    if(Move::lastMove != nullptr)
    {
        delete Move::lastMove;
        Move::lastMove = nullptr;
    }
    board = new Board();



    displayBoard();
    playerTurn = player[1];
    changePlayerTurn();
    spotStart = nullptr;
    ui->blockWindow->setVisible(false);
    ui->message->setVisible(false);
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
    ui->redoButton->setVisible(false);
    ui->undoButton->setVisible(false);
}

void Game::handleActionLoad()
{
    if(Move::lastMove != nullptr)
    {
        delete Move::lastMove;
        Move::lastMove = nullptr;
    }
    validSpot.clear();
    bool isWhiteTurn = true;
    board->deletePieces();
    GameSaver::load("RecordedGame.txt", isWhiteTurn, board);
    if(isWhiteTurn == false)
    {
        playerTurn = player[0];
        changePlayerTurn();
    }
    else
    {
        playerTurn = player[1];
        changePlayerTurn();
    }

    displayBoard();

    spotStart = nullptr;

    GameSaver::save("Undo.txt", playerTurn->getIsWhite(), board);
    GameSaver::save("Redo.txt", playerTurn->getIsWhite(), board);

    displayBoard();
    ui->blockWindow->setVisible(false);
    ui->message->setVisible(false);
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
    ui->redoButton->setVisible(false);
    ui->undoButton->setVisible(false);
}

void Game::handleUndo()
{
    if(Move::lastMove != nullptr)
    {
        delete Move::lastMove;
        Move::lastMove = nullptr;
    }
    if(undo == true)
    {
        return;
    }
    undo = true;
    spotStart = nullptr;
    validSpot.clear();

    GameSaver::save("Redo.txt", playerTurn->getIsWhite(), board);

    bool isWhiteTurn = true;
    board->deletePieces();
    GameSaver::load("Undo.txt", isWhiteTurn, board);
    changePlayerTurn();
    displayBoard();
    ui->redoButton->setVisible(true);
    ui->undoButton->setVisible(false);
}

void Game::handleRedo()
{

    if(undo == false)
    {
        return;
    }

    if(Move::lastMove != nullptr)
    {
        delete Move::lastMove;
        Move::lastMove = nullptr;
    }
    undo = false;

    spotStart = nullptr;
    validSpot.clear();

    bool isWhiteTurn = true;
    board->deletePieces();
    GameSaver::load("Redo.txt", isWhiteTurn, board);
    changePlayerTurn();
    displayBoard();
    ui->redoButton->setVisible(false);
    ui->undoButton->setVisible(true);
}

void Game::handleExit()
{
    ui->blockWindow->setVisible(false);
    ui->message->setVisible(false);
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
    ui->redoButton->setVisible(false);
    ui->undoButton->setVisible(false);
}

