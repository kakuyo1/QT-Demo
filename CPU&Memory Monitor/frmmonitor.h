#ifndef FRMMONITOR_H
#define FRMMONITOR_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include "monitorlabel.h"


class MonitorLabel;
class frmMonitor : public QWidget
{
    Q_OBJECT

public:
    frmMonitor(QWidget *parent = nullptr);
    ~frmMonitor();
    void initForm();
private:
    MonitorLabel* LabelFirst;
    QLabel* LabelSecond;
    QLabel* LabelThird;
private Q_SLOTS:
    void customizingText(quint64 CpuUsagePersent, quint64 MemoryUsagePersent, quint64 UsedMemoryPhsy,
                         quint64 AllMemoryPhsy, quint64 AvailMemoryPhsy);
Q_SIGNALS:

};
#endif // FRMMONITOR_H
