#include "widok.h"

Widok::Widok(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout;

    plansza = new Plansza(this);
    mainLayout->addWidget(plansza);

    menu = new QVBoxLayout;
    mainLayout->addLayout(menu);

    lcd = new QLCDNumber(this);
    lcd->setMinimumWidth(200);
    lcd->setMaximumWidth(350);

    menu->addWidget(lcd);

    menu->addSpacing(400);

    newGame = new QPushButton("New Game", this);
    saveGame = new QPushButton("Save", this);
    loadGame = new QPushButton("Load Last Game", this);
    quit = new QPushButton("Quit", this);

    QSizePolicy policy = newGame->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    newGame->setSizePolicy(policy);
    newGame->setMaximumWidth(150);

    policy = saveGame->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    saveGame->setSizePolicy(policy);
    saveGame->setMaximumWidth(150);

    policy = loadGame->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    loadGame->setSizePolicy(policy);
    loadGame->setMaximumWidth(150);

    policy = this->quit->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    quit->setSizePolicy(policy);
    quit->setMaximumWidth(150);

    menu->addWidget(newGame);
    menu->addWidget(saveGame);
    menu->addWidget(loadGame);
    menu->addWidget(quit);

    siatkaCyfr = new QGridLayout(plansza);
    newTab();
    siatkaCyfr->setContentsMargins(5,12,10,11);
    siatkaCyfr->setHorizontalSpacing(1);
    siatkaCyfr->setVerticalSpacing(5);

    this->setLayout(mainLayout);
}

void Widok::newTab()
{
    for (int i = 0; i < 9; ++i )
    {
        for (int j = 0; j < 9; ++j )
        {
            tablica[i][j] = new Cyfra(plansza, i, j);
            siatkaCyfr->addWidget(tablica[i][j], i, j);
        }
    }
}

void Widok::addModel(Model *wsk)
{
    modelWsk = wsk;
}

//slots
void Widok::newGameDialog(bool isChecked)
{
    bool *ok = new bool(false);
    int num = QInputDialog::getInt(this, "Którą planszę otworzyć?", "Wybierz jedną z 50:", 1, 1, 50, 1, ok);
    if (*ok == true)
    {
        emit newGameSignal(num, false);
    }
    delete ok;
}

void Widok::saveGameClicked(bool ignore)
{
    int **tab = new int *[9];
    for ( int i = 0; i < 9; ++i )
       tab[i] = new int [9];

    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            tab[x][y] = tablica[x][y]->m_num;
        }
    }

    emit saveGameSignal(lcd->intValue(), tab );
}

void Widok::win()
{
    int value = QMessageBox::information(this, "Congratulation!", "You have finished Sudoku!", "Ok", "Quit");
    if ( value == 1 )
        emit quitGame();
}

