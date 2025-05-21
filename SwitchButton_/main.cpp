#include "frmdisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmDisplay w;
    w.show();
    return a.exec();
}
