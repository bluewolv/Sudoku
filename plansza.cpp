#include "plansza.h"

Plansza::Plansza(QWidget *parent) : QLabel(parent)
{
    plansza = new QPixmap();
    plansza->load(":/grafika/plansza.jpg");

    setPixmap(*plansza);
    setScaledContents(true);
    setFrameStyle(1);
    QSizePolicy m_policy = sizePolicy();
    m_policy.setHorizontalPolicy(QSizePolicy::Minimum);
    m_policy.setVerticalPolicy(QSizePolicy::Minimum);
    setSizePolicy(m_policy);
    setMinimumSize(200, 200);
    setBaseSize(600, 600);
    updateGeometry();
    update();
}

void Plansza::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size())
    {
        resize(event->size().width(),event->size().width());
        updateGeometry();
        update();
    }
}



