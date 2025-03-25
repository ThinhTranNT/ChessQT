#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class PromotionDialog;
}

class PromotionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PromotionDialog(QWidget *parent = nullptr);
    std::string getNamePromotedPiece();
    ~PromotionDialog();

private:
    Ui::PromotionDialog *ui;
    std::string namePromotedPiece;

private slots:
    void promoteToQueen();
    void promoteToBishop();
    void promoteToRook();
    void promoteToKnight();

};

#endif // PROMOTIONDIALOG_H
