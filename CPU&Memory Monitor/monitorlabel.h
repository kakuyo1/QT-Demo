#ifndef MONITORLABEL_H
#define MONITORLABEL_H
#define MB (1024 * 1024)
#define KB (1024)
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QSysInfo>
#include "windows.h"
class MonitorLabel : public QLabel
{
    Q_OBJECT
public:
    MonitorLabel(QWidget* parent);
    ~MonitorLabel();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    quint64 CpuUsagePercent;
    quint64 MemoryUsagePersent;
    quint64 AllMemoryPhsy;
    quint64 UsedMemoryPhsy;
    quint64 AvailMemoryPhsy;

    QTimer* cpuTimer;
    QTimer* memoryTimer;

    QProcess* typeperfProcess;
public:
    void start(int timerIntervalNum);
private:
    void stop();
private Q_SLOTS:
    void getCPU();
    void getMemory();
    void readCpuPercentVal();
    void setMonitorText();
Q_SIGNALS:
    void textChanged(QString msg);//for copy(复制)
    void valueChanged(quint64 CpuUsagePercent, quint64 MemoryUsagePersent, quint64 UsedMemoryPhsy,
                     quint64 AllMemoryPhsy, quint64 AvailMemoryPhsy);//for customizing(定制)
};

#endif // MONITORLABEL_H
