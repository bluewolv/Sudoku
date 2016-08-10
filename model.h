#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QPixmap>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QErrorMessage>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
private:
    QPixmap num[10];
    QPixmap numRed[10];
    int m_timer;
    int m_actualBoard;

public:
    QPixmap sendPixmap(int number, bool isRed = false);
    QStringList m_sudokuList;
    QTimer *timer;
    int modelTab[9][9] = {-1};

signals:
    void myTimeout(int);
    void newGameFromLoadGame(int, bool);
    void changeNums(int num, int x, int y);
    void win();

private slots:
    void startTimer(int, bool = false);
    void updateTimer();
    void setActualBoard(int boardNum);
    void saveGame(int time, int **tab);
    void loadGame(bool ignore);
    void isThisWin();

};

#endif // MODEL_H
