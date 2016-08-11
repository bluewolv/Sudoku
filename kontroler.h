#ifndef KONTROLER_H
#define KONTROLER_H

#include <QMainWindow>
#include <model.h>
#include <widok.h>

namespace Ui {
class Kontroler;
}

class Cyfra;

class Kontroler : public QMainWindow
{
    Q_OBJECT
public:
    explicit Kontroler(QWidget *parent = 0);
    ~Kontroler();

private:
    Ui::Kontroler *ui;

    Model* model;
    Widok* widok;

public:

signals:
    void isThisWin();

private slots:
    void numChange(int num, int x, int y, bool isRed = false);
    void newGameSlot(int);

};

#endif // KONTROLER_H

//test for GitHub
