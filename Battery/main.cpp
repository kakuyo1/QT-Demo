#include "frmbattery.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmBattery w;
    w.setWindowTitle("Battery Test");
    w.show();
    return a.exec();
}
