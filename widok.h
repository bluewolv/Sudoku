#ifndef WIDOK_H
#define WIDOK_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QInputDialog>
#include <QMessageBox>

#include <plansza.h>
#include <cyfra.h>
#include <model.h>

class Widok : public QWidget
{
    Q_OBJECT
public:
    explicit Widok(QWidget *parent = 0);

private:
    Model *modelWsk;

    QHBoxLayout* mainLayout;
        QGridLayout* siatkaCyfr;
        QVBoxLayout* menu;

    Plansza* plansza;

    void newTab();

public:
    void addModel(Model *);

    Cyfra *tablica[9][9] = {NULL};
    QLCDNumber *lcd;
    QPushButton *newGame;
    QPushButton *saveGame;
    QPushButton *loadGame;
    QPushButton *quit;
protected:

signals:
    void newGameSignal(int, bool);
    void saveGameSignal(int boardNum, int **);
    void quitGame();

private slots:
    void newGameDialog(bool isChecked);
    void saveGameClicked(bool ignore);
    void win();
};

#endif // WIDOK_H
