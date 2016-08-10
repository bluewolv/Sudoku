#include "kontroler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kontroler w;
    w.show();

    return a.exec();
}
