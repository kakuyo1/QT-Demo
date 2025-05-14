#ifndef FRMBATTERY_H
#define FRMBATTERY_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QDebug>
#include "battery.h"
//QT_BEGIN_NAMESPACE
//namespace Ui { class frmBattery; }
//QT_END_NAMESPACE

class Battery;
class frmBattery : public QWidget
{
    Q_OBJECT

public:
    frmBattery(QWidget *parent = nullptr);
    ~frmBattery();

private:
//    Ui::frmBattery *ui;
    QSlider* slider;
    Battery* battery;
private slots:
    void initFrom();
};
#endif // FRMBATTERY_H
