#include "lobby.h"
#include "ui_lobby.h"
#include "SoundController.h"
#include "Piece.h"
#include "Move.h"


Lobby::Lobby(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lobby)
{
    game = nullptr;
    ui->setupUi(this);

    connect(ui->playButton, &QPushButton::released, this, &Lobby::handlePlayButtonClicked);
    connect(ui->speaker, &QPushButton::released, this, &Lobby::handleSpeakerClicked);

    connect(ui->newGameButton, &QPushButton::released, this, &Lobby::handleNewGameButtonClicked);
    connect(ui->continueButton, &QPushButton::released, this, &Lobby::handleContinueButtonClicked);


    SoundController::setBackgroundMusic();
    ui->newGameButton->setVisible(false);
    ui->continueButton->setVisible(false);
}

Lobby::~Lobby()
{
    if(game != nullptr)
    {
        delete game;
        game = nullptr;
    }
    delete ui;

    SoundController::deleteSoundController();
    Piece::deleteSampleList();
    delete Move::lastMove;
}

void Lobby::handlePlayButtonClicked()
{
    ui->newGameButton->setVisible(true);
    ui->continueButton->setVisible(true);
    ui->playButton->setVisible(false);
}

void Lobby::handleSpeakerClicked()
{
    if(ui->speaker->isChecked())
    {
        SoundController::backgroundMusic->pause();
        SoundController::isMute = true;
    }
    else
    {
        SoundController::backgroundMusic->play();
        SoundController::isMute = false;
    }
}

void Lobby::handleNewGameButtonClicked()
{
    this->hide();
    game = new Game(false);
    game->show();
}

void Lobby::handleContinueButtonClicked()
{
    this->hide();
    game = new Game(true);
    game->show();
}
