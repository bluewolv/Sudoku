#include "model.h"

Model::Model(QObject *parent) : QObject(parent), m_timer(0), m_actualBoard(0)
{
    for ( int x = 0; x < 10; ++x )
    {
        num[x].load(QString(":/grafika/numerki/%1.png").arg(x));
        numRed[x].load(QString(":/grafika/numerki_red/%1.png").arg(x));
    }

    QFile *sudokuFile = new QFile(QString(":/grafika/sudoku.txt"));
    sudokuFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream *strumien = new QTextStream(sudokuFile);
    while (!strumien->atEnd()) {
        m_sudokuList.append(strumien->readLine());
    }
    sudokuFile->close();
    delete sudokuFile;
    delete strumien;

    timer = new QTimer(this);
}

QPixmap Model::sendPixmap(int number, bool isRed)
{
    if ( isRed == true )
        return numRed[number];
    else
        return num[number];
}

//slots

void Model::startTimer(int, bool isThisLoadedGame)
{
    if (!isThisLoadedGame)
    {
        m_timer = 0;
    }

    timer->start(1000);
}

void Model::updateTimer()
{
    ++m_timer;
    emit myTimeout(m_timer);
}

void Model::setActualBoard(int boardNum)
{
    m_actualBoard = boardNum;
}

void Model::saveGame(int time, int **tab)
{
    QString string;
    QString numTemp;
    numTemp.setNum(m_actualBoard);
    string+=numTemp;
    string+="\r\n";
    numTemp.setNum(time);
    string+=numTemp;
    string+="\r\n";

    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            //qDebug() << tab[x][y];
            numTemp.setNum(tab[x][y]);
            string+=numTemp;
            string+=" ";
        }
        string+="\r\n";
    }

    QFile file("save.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << string;
    file.close();

    for ( int i = 0; i < 9; ++i )
       delete [] tab[i];
    delete [] tab;

}

void Model::loadGame(bool ignore)
{
    QString stringTemp;
    int boardNum;
    int time;
    int tab[9][9];
    QFile file("save.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        //error
    }

    QTextStream stream(&file);
    stream >> boardNum >> time;

    m_actualBoard = boardNum;
    m_timer = time;

    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            stream >> tab[x][y];
        }
    }

    emit newGameFromLoadGame(boardNum, true);
    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            emit changeNums(tab[x][y], x, y);
        }
    }
}

void Model::isThisWin()
{
    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            if ( modelTab[x][y] == 0 )
            {
                return;
            }
        }
    }

    for ( int x = 0; x < 9; ++x ) //wiersze
    {
        int y = 0;
        for ( int i = 0; i < 9; ++i )
        {
            y = i+1;
            for ( ; y < 9; ++y )
            {
                if ( modelTab[x][i] == modelTab[x][y] )
                {
                    return;
                }
            }
        }
    }

    for ( int x = 0; x < 9; ++x ) //kolumny
    {
        int y = 0;
        for ( int i = 0; i < 9; ++i )
        {
            y = i+1;
            for ( ; y < 9; ++y )
            {
                if ( modelTab[i][x] == modelTab[y][x] )
                {
                    return;
                }
            }
        }
    }

    //kwadraty

    for ( int x = 0; x < 9; ++x )
    {
        for ( int y = 0; y < 9; ++y )
        {
            int check = modelTab[x][y];
            int xTemp = x/3;
            int yTemp = y/3;
            int licznik = 0;

            for ( int xSecond = 0; xSecond < 3; ++xSecond )
            {
                for ( int ySecond = 0; ySecond < 3; ++ySecond )
                {
                    if ( check == modelTab[xTemp*3+xSecond][yTemp*3+ySecond])
                        ++licznik;
                }
            }

            if ( licznik != 1 )
            {
                return;
            }
        }
    }

    timer->stop();
    emit win();
}

