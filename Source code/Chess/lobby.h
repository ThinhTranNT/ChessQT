#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "Game.h"


namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
    Q_OBJECT

public:

    Lobby(QWidget *parent = nullptr);
    ~Lobby();

private slots:
    void handlePlayButtonClicked();

    void handleSpeakerClicked();

    void handleNewGameButtonClicked();

    void handleContinueButtonClicked();

private:
    Ui::Lobby *ui;
    Game* game;
};

#endif // LOBBY_H
