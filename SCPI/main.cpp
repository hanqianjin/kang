#include "f238scpi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //be must use x64 run
    QApplication a(argc, argv);
    F238SCPI w;
    w.show();

    return a.exec();
}
