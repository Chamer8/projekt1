#ifndef calc_H
#define calc_H

#include <QMainWindow>

namespace Ui {
class calc;
}

class calc : public QMainWindow
{
    Q_OBJECT

public:
    explicit calc(QWidget *parent = 0);
    ~calc();

private:
    Ui::calc *ui;

    //Te sloty są wykonywane po przesłaniu sygnału (np. kliknięcie przycisku Numer)
private slots :
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void on_ClearBtn_clicked();
    void on_calculateLog_clicked();
    void on_sinBtn_clicked();
    void on_calculatePot_clicked();
    void on_calculatePier_clicked();
    void on_sinacBtn_clicked();
    void on_sinacBtn_2_clicked();
    void on_cosBtnalfa_clicked();
    void on_cosBtnradiany_clicked();
    void on_cosbcBtn_clicked();
    void on_tgBtnalfa_clicked();
    void on_cosBtn_clicked();
    void on_cosbcBtn2_clicked();
    void on_tgabBtn_clicked();
    void on_tgBtn_clicked();
    void on_cotgbaBtn_clicked();
    void on_cotgBtn_clicked();
    void on_PLNOblicz_clicked();
    void on_USDOblicz_clicked();
    void on_EUROblicz_clicked();
    void on_CHFOblicz_clicked();
};

#endif // calc_H
