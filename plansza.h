#ifndef PLANSZA_H
#define PLANSZA_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QResizeEvent>
#include <QLayout>
#include <QSize>

class Plansza : public QLabel
{
    Q_OBJECT
public:
    explicit Plansza(QWidget *parent = 0);
private:
    QPixmap* plansza;
protected:
    void resizeEvent(QResizeEvent *event);
signals:

public slots:
};

#endif // PLANSZA_H
