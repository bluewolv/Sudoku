#include "kontroler.h"
#include "ui_kontroler.h"

Kontroler::Kontroler(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Kontroler), model (new Model(this)), widok (new Widok(this))
{
    ui->setupUi(this);
    setCentralWidget(widok);
    resize(1000,815);
    widok->addModel(model);

    for (int x = 0; x < 9; ++x )
    {
        for (int y = 0; y <9; ++y )
        {
            connect(widok->tablica[x][y], SIGNAL(numChange(int,int,int)), this, SLOT(numChange(int,int,int)));
        }
    }

    connect(widok->newGame, SIGNAL(clicked(bool)), widok, SLOT(newGameDialog(bool)));
    connect(widok, SIGNAL(newGameSignal(int, bool)), this, SLOT(newGameSlot(int)) );
    connect(widok, SIGNAL(newGameSignal(int, bool)), model, SLOT(startTimer(int, bool)));
    connect(widok, SIGNAL(newGameSignal(int, bool)), model, SLOT(setActualBoard(int)));

    connect(model->timer, SIGNAL(timeout()), model, SLOT(updateTimer()));
    connect(model, SIGNAL(myTimeout(int)), widok->lcd, SLOT(display(int)));

    connect(widok->saveGame, SIGNAL(clicked(bool)), widok, SLOT(saveGameClicked(bool)));
    connect(widok, SIGNAL(saveGameSignal(int, int**)), model, SLOT(saveGame(int, int**)));

    connect(widok->loadGame, SIGNAL(clicked(bool)), model, SLOT(loadGame(bool)));
    connect(model, SIGNAL(newGameFromLoadGame(int, bool)), this, SLOT(newGameSlot(int)));
    connect(model, SIGNAL(newGameFromLoadGame(int, bool)), model, SLOT(startTimer(int, bool)));
    connect(model, SIGNAL(changeNums(int,int,int)), this, SLOT(numChange(int,int,int)));

    connect(widok->quit, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(this, SIGNAL(isThisWin()), model, SLOT(isThisWin()));
    connect(model, SIGNAL(win()), widok, SLOT(win()));

    connect(widok, SIGNAL(quitGame()), this, SLOT(close()));

}

Kontroler::~Kontroler()
{
    delete ui;
}

//slots
void Kontroler::numChange(int num, int x, int y, bool isRed)
{ 
    if ( !widok->tablica[x][y]->m_red )
    {
        widok->tablica[x][y]->setPixmap(model->sendPixmap(num, isRed));
        widok->tablica[x][y]->m_num = num;
        if (isRed == true && num != 0)
        {
            widok->tablica[x][y]->m_red = true;
        }
        model->modelTab[x][y] = num;
        emit isThisWin();
    }
}

void Kontroler::newGameSlot(int num)
{
    int wiersz = (num-1)*10+1;
    for ( int x = 0; x < 9; ++x )
    {
       int pozycja = 0;
       for ( int y = 0; y < 9; ++y )
       {
           widok->tablica[x][y]->m_red = false;
           numChange(( model->m_sudokuList[wiersz].at(pozycja++) ).digitValue(), x, y, true);
       }
       ++wiersz;
    }
}



