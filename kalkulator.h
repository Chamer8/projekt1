#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Kalkulator; }
QT_END_NAMESPACE

class Kalkulator : public QMainWindow
{
    Q_OBJECT

public:
    Kalkulator(QWidget *parent = nullptr);
    ~Kalkulator();

private:
    Ui::Kalkulator *ui;
};
#endif // KALKULATOR_H
