
#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "Board.h"
#include "Move.h"
#include "Player.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(bool isContinue, QWidget *parent = nullptr);
    void displayValidSpot();
    void displayBoard();
    void changePlayerTurn();
    void changeGameStatus();
    void promote(Move* move);
    ~Game();

private:
    Ui::Game *ui;
    std::vector<Player*> player;
    Player* playerTurn;
    Board* board;
    std::vector<Spot*> validSpot;
    Spot* spotStart;
    bool undo;
    Spot* positionOfKing;

private slots:
    void handleCellBoardviewClicked(int row, int column);

    void handleActionUnmute();

    void handleActionSave();

    void handleActionNewGame();

    void handleActionMute();

    void handleUndo();

    void handleRedo();

    void handleActionLoad();

    void handleExit();
};

#endif // GAME_H
