#ifndef FRMDISPLAY_H
#define FRMDISPLAY_H

#include <QWidget>
#include "switchbutton.h"
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class frmDisplay; }
QT_END_NAMESPACE

class SwitchButton;
class frmDisplay : public QWidget
{
    Q_OBJECT


public:
    frmDisplay(QWidget *parent = nullptr);
    ~frmDisplay();
    void initForm();

private slots:

private:
    Ui::frmDisplay *ui;
    QString iconOneStatusOffPath;
    QString iconOneStatusOnPath;
    QString iconTwoStatusOffPath;
    QString iconTwoStatusOnPath;
    QString iconThreeStatusOffPath;
    QString iconThreeStatusOnPath;
};
#endif // FRMDISPLAY_H
