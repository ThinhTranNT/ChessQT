#include "PromotionDialog.h"
#include "ui_PromotionDialog.h"

PromotionDialog::PromotionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PromotionDialog)
{
    ui->setupUi(this);
    connect(ui->queenButton, &QPushButton::released, this, &PromotionDialog::promoteToQueen);
    connect(ui->rookButton, &QPushButton::released, this, &PromotionDialog::promoteToRook);
    connect(ui->bishopButton, &QPushButton::released, this, &PromotionDialog::promoteToBishop);
    connect(ui->knightButton, &QPushButton::released, this, &PromotionDialog::promoteToKnight);
}

PromotionDialog::~PromotionDialog()
{
    delete ui;
}

void PromotionDialog::promoteToQueen()
{
    namePromotedPiece = "Queen";
    this->close();
}
void PromotionDialog::promoteToBishop()
{
    namePromotedPiece = "Bishop";
    this->close();
}
void PromotionDialog::promoteToRook()
{
    namePromotedPiece = "Rook";
    this->close();
}
void PromotionDialog::promoteToKnight()
{
    namePromotedPiece = "Knight";
    this->close();
}

std::string PromotionDialog::getNamePromotedPiece()
{
    return namePromotedPiece;
}
