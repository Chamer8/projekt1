#include <calc.h>
#include <ui_calc.h>
#include <QFile>
#include <QTextStream>


// Przechowuje aktualną wartość obliczeń
double calcVal = 0.0;

// Zdefiniuje, czy to był ostatni przycisk matematyczny, na który kliknięto, pozniej sczytuje te klawisze i zmienia wartosc na true
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;

// konstruktor
calc::calc(QWidget *parent) :
    // nazywa QMainWindow konstruktorem
    QMainWindow(parent),

    // Utwórz klasę UI i przypisz ją do członka interfejsu użytkownika
    ui(new Ui::calc)
{
    ui->setupUi(this);


    // Umieszcza 0.0 na wyświetlaczu
    ui->Display->setText(QString::number(calcVal));

    // Będzie zawierał odniesienia do wszystkich przycisków numerycznych
    QPushButton *numButtons[10];

    // Przejdź przez lokalizowanie przycisków
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);

        // Pobierz przyciski według nazwy i dodaj do tablicy, refenrencja na obiekt QpushButton
        numButtons[i] = calc::findChild<QPushButton *>(butName);

        // Po zwolnieniu przycisku wywołaj num_pressed(). Realased jak puszcze to sie dzieje
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    // Podłącz sygnały i gniazda dla matematycznych przyciskow
    connect(ui->Dodawanie, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Odejmowanie, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Mnozenie, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Dzielenie, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    // podlaczenie przycisku rownania
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
}

calc::~calc()
{
    delete ui;
}

void calc::NumPressed(){

    // Nadawca zwraca wskaźnik do wciśniętego przycisku
    QPushButton *button = (QPushButton *)sender();

    // Uzyskaj numer na przycisku
    QString butVal = button->text();

    // Uzyskaj wartość na wyświetlaczu
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){

        // calcVal = butVal.toDouble();
        ui->Display->setText(butVal);

    } else {
        // Umieść nowy numer na prawo od tego, co tam jest
        QString newVal = displayVal + butVal;

        // Double version of number
        double dblNewVal = newVal.toDouble();

        // calcVal = newVal.toDouble();

        // Ustawienie wartości na wyświetlaczu i zezwolenie na 16 cyfr
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));

    }
}

void calc::MathButtonPressed(){

    // Anuluj poprzednie kliknięcia przycisków matematycznych
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;


    // Zapisz aktualną wartość na wyświetlaczu
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    // Nadawca zwraca wskaźnik do wciśniętego przycisku
    QPushButton *button = (QPushButton *)sender();

    // Pobierz symbol matematyczny na przyciskuGet math symbol on the button
    QString butVal = button->text();
    // porównuje, porównuje ButVal do cudzyslowie
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;}
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;}
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;}
    else if (QString::compare(butVal, "^", Qt::CaseInsensitive) == 0){
        powTrigger = true;}
    else {
        subTrigger = true;}

    // wyczyszczenie wyświetlacza
    ui->Display->setText("");
}
void calc::EqualButtonPressed(){
    // Przechowuje nowe obliczenia
    double solution = 0.0;

    // Uzyskaj wartość na wyświetlaczu
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    // Upewnij się, że został naciśnięty przycisk matematyczny
    // valc val razy dbl cos tam
    if(addTrigger || subTrigger || multTrigger || divTrigger || powTrigger ){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;}
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;}
        else if(multTrigger){
            solution = calcVal * dblDisplayVal;}
        else if(powTrigger){
            solution = qPow(calcVal, dblDisplayVal);
    }
        else {
            solution = calcVal / dblDisplayVal;
        }
    }

    // Umieść rozwiązanie na wyświetlaczu
    ui->Display->setText(QString::number(solution));

}

void calc::on_ClearBtn_clicked()
{
    calcVal = 0.0;
    ui->Display->setText(QString::number(calcVal));
}


void calc::on_calculateLog_clicked()
{
    double a = ui->loga->value();
    double b = ui->logb->value();
    double c = ui->logc->value();

    c = log(b)/log(a);


    ui->logc->setValue(c);
}

void calc::on_sinBtn_clicked()
{
    double x = ui->sin->value();
    double wynik = qSin(x);

    ui->sinWynik->setValue(wynik);
}

void calc::on_calculatePot_clicked()
{
    double x = ui->potx->value();
    double n = ui->potn->value();
    double a = ui->pota->value();

    a = qPow(x,n);

    ui->pota->setValue(a);
}


void calc::on_calculatePier_clicked()
{
    double x = ui->pierx->value();
    double n = ui->piern->value();

    n = qSqrt(x);

    ui->piern->setValue(n);
}


void calc::on_sinacBtn_clicked()
{
    double a = ui->sina->value();
    double c = ui->sinc->value();

    double x = a/c;

    ui->sinalfa->setValue(x);
}



void calc::on_cosbcBtn_clicked()
{
    double b = ui->cosb->value();
    double c = ui->cosc->value();

    double x = b/c;


    ui->cosalfa->setValue(x);
}


void calc::on_cosBtn_clicked()
{
    double x = ui->cos->value();
    double wynik = qCos(x);

    ui->cosWynik->setValue(wynik);
}


void calc::on_cosbcBtn2_clicked()
{
    double x = ui->cos->value();
    double wynik = qSin(x);

    ui->cosWynik->setValue(wynik);
}


void calc::on_tgabBtn_clicked()
{
    double a = ui->tga->value();
    double b = ui->tgb->value();

    double x = a/b;


    ui->tgalfa->setValue(x);
}


void calc::on_tgBtn_clicked()
{
    double x = ui->tg->value();
    double wynik = qTan(x);

    ui->tgWynik->setValue(wynik);
}


void calc::on_cotgbaBtn_clicked()
{
    double b = ui->cotgb->value();
    double a = ui->cotga->value();

    double x = b/a;


    ui->cotgalfa->setValue(x);
}


void calc::on_cotgBtn_clicked()
{
    double x = ui->cotg->value();
    double wynik = (x*3.14)/180;

    ui->cotgWynik->setValue(wynik);
}


void calc::on_PLNOblicz_clicked()
{
    double x = ui->PLN1->value();

    QFile plik("D:/PROGRAMOWANIE/POLITECHNIKA/4 sem/PROGRAMOWANIE APLIKACYJNE/1 PROJEKT DO ODDANIA/pln-inne.txt");
    plik.open(QIODevice::ReadOnly);
    QTextStream s(&plik);
    QString pln1;
    QString pln2;
    QString pln3;
    QString pln4;


    for(int i=0; i<4;i++) {
        if(i==0) {
            pln1 = s.readLine();
        }
        else if(i==1) {
            pln2 = s.readLine();
        }
        else if(i==2) {
            pln3 = s.readLine();
        }
        else if(i==3) {
            pln4 = s.readLine();
        }
    }
    double pln1d = pln1.toDouble();
    double pln2d = pln2.toDouble();
    double pln3d = pln3.toDouble();
    double pln4d = pln4.toDouble();

    //double pln_pln = x*1;
    //double pln_usd = x*0.23;
    //double pln_eur = x*0.21;
    //double pln_chf = x*0.22;

    double pln_pln = x*pln1d;
    double pln_usd = x*pln2d;
    double pln_eur = x*pln3d;
    double pln_chf = x*pln4d;

    ui->PLN2->setValue(pln_pln);
    ui->USD2->setValue(pln_usd);
    ui->EUR2->setValue(pln_eur);
    ui->CHF2->setValue(pln_chf);
}


void calc::on_USDOblicz_clicked()
{
    double x = ui->USD1->value();

    QFile plik("D:/PROGRAMOWANIE/POLITECHNIKA/4 sem/PROGRAMOWANIE APLIKACYJNE/1 PROJEKT DO ODDANIA/usd-inne.txt");
    plik.open(QIODevice::ReadOnly);
    QTextStream s(&plik);
    QString usd1;
    QString usd2;
    QString usd3;
    QString usd4;


    for(int i=0; i<4;i++) {
        if(i==0) {
            usd1 = s.readLine();
        }
        else if(i==1) {
            usd2 = s.readLine();
        }
        else if(i==2) {
            usd3 = s.readLine();
        }
        else if(i==3) {
            usd4 = s.readLine();
        }
    }
    double usd1d = usd1.toDouble();
    double usd2d = usd2.toDouble();
    double usd3d = usd3.toDouble();
    double usd4d = usd4.toDouble();

    //double usd_pln = x*4.43;
    //double usd_usd = x*1;
    //double usd_eur = x*0.95;
    //double usd_chf = x*0.98;

    double usd_pln = x*usd1d;
    double usd_usd = x*usd2d;
    double usd_eur = x*usd3d;
    double usd_chf = x*usd4d;

    ui->PLN2->setValue(usd_pln);
    ui->USD2->setValue(usd_usd);
    ui->EUR2->setValue(usd_eur);
    ui->CHF2->setValue(usd_chf);
}


void calc::on_EUROblicz_clicked()
{
    double x = ui->EUR1->value();

    QFile plik("D:/PROGRAMOWANIE/POLITECHNIKA/4 sem/PROGRAMOWANIE APLIKACYJNE/1 PROJEKT DO ODDANIA/eur-inne.txt");
    plik.open(QIODevice::ReadOnly);
    QTextStream s(&plik);
    QString eur1;
    QString eur2;
    QString eur3;
    QString eur4;


    for(int i=0; i<4;i++) {
        if(i==0) {
            eur1 = s.readLine();
        }
        else if(i==1) {
            eur2 = s.readLine();
        }
        else if(i==2) {
            eur3 = s.readLine();
        }
        else if(i==3) {
            eur4 = s.readLine();
        }
    }
    double eur1d = eur1.toDouble();
    double eur2d = eur2.toDouble();
    double eur3d = eur3.toDouble();
    double eur4d = eur4.toDouble();



    //double eur_pln = x*4.68;
    //double eur_usd = x*1.06;
    //double eur_eur = x*1;
    //double eur_chf = x*1.03;

    double eur_pln = x*eur1d;
    double eur_usd = x*eur2d;
    double eur_eur = x*eur3d;
    double eur_chf = x*eur4d;

    ui->PLN2->setValue(eur_pln);
    ui->USD2->setValue(eur_usd);
    ui->EUR2->setValue(eur_eur);
    ui->CHF2->setValue(eur_chf);
}



void calc::on_CHFOblicz_clicked()
{
    double x = ui->CHF1->value();

    QFile plik("D:/PROGRAMOWANIE/POLITECHNIKA/4 sem/PROGRAMOWANIE APLIKACYJNE/1 PROJEKT DO ODDANIA/chf-inne.txt");
    plik.open(QIODevice::ReadOnly);
    QTextStream s(&plik);
    QString chf1;
    QString chf2;
    QString chf3;
    QString chf4;


    for(int i=0; i<4;i++) {
        if(i==0) {
            chf1 = s.readLine();
        }
        else if(i==1) {
            chf2 = s.readLine();
        }
        else if(i==2) {
            chf3 = s.readLine();
        }
        else if(i==3) {
            chf4 = s.readLine();
        }
    }
    double chf1d = chf1.toDouble();
    double chf2d = chf2.toDouble();
    double chf3d = chf3.toDouble();
    double chf4d = chf4.toDouble();

    //double chf_pln = x*4.52;
    //double chf_usd = x*1.02;
    //double chf_eur = x*0.97;
    //double chf_chf = x*1;

    double chf_pln = x*chf1d;
    double chf_usd = x*chf2d;
    double chf_eur = x*chf3d;
    double chf_chf = x*chf4d;

    ui->PLN2->setValue(chf_pln);
    ui->USD2->setValue(chf_usd);
    ui->EUR2->setValue(chf_eur);
    ui->CHF2->setValue(chf_chf);
}

