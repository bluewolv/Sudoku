#ifndef CYFRA_H
#define CYFRA_H

#include <QDebug>
#include <QLabel>
#include <QWidget>
#include <QKeyEvent>

class Cyfra : public QLabel
{
    Q_OBJECT
public:
    explicit Cyfra(QWidget *parent = 0, int indexX = -1, int indexY = -1);

private:
    QPixmap *pxm;

    int m_indexX;
    int m_indexY;

public:
    bool m_red;
    int m_num;

protected:
    void keyPressEvent(QKeyEvent *ev);

signals:
    void numChange(int, int, int);

private slots:

};

#endif // CYFRA_H
