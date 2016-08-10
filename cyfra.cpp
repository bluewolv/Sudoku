#include "cyfra.h"

Cyfra::Cyfra(QWidget *parent, int indexX, int indexY) : QLabel(parent), pxm(new QPixmap(":/grafika/numerki/0.png")), m_red(false), m_indexX(indexX), m_indexY(indexY), m_num(-1)
{
    setPixmap(*pxm);
    setScaledContents(true);
    setFocusPolicy(Qt::ClickFocus);
}

//Events
void Cyfra::keyPressEvent(QKeyEvent *ev)
{
    int key = ev->key() - 48;

    if ( key >= 0 && key < 10 )
    {
        if ( m_red == false)
        {
            emit numChange(key, m_indexX, m_indexY);
        }
    }
}

//Signals

