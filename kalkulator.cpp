#include "kalkulator.h"
#include "ui_kalkulator.h"

Kalkulator::Kalkulator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
}

Kalkulator::~Kalkulator()
{
    delete ui;
}

