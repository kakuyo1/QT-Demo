#include "frmmonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmMonitor w;
    w.show();
    return a.exec();
}
