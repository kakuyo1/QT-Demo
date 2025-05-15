#include "monitorlabel.h"

MonitorLabel::MonitorLabel(QWidget* parent) :
    QLabel(parent),
    cpuTimer(new QTimer(this)),
    memoryTimer(new QTimer(this)),
    typeperfProcess(new QProcess(this))
{
    CpuUsagePercent = 0;
    MemoryUsagePersent = 0;
    AllMemoryPhsy = 0;
    UsedMemoryPhsy = 0;
    AvailMemoryPhsy = 0;

    //定时获取CPU信息
    connect(cpuTimer, &QTimer::timeout, this, &MonitorLabel::getCPU);
    //定时获取内存信息
    connect(memoryTimer, &QTimer::timeout, this, &MonitorLabel::getMemory);
    //异步读取内存占有率
    connect(typeperfProcess, &QProcess::readyReadStandardOutput, this, &MonitorLabel::readCpuPercentVal);
    //捕获子进程"typeperf"退出信息
    connect(typeperfProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [this](
            int exitCode, QProcess::ExitStatus exitStatus){
                Q_UNUSED(this);
                qDebug() << "Progress TypePerf exit...";
                qDebug() << "Exit Code: " << exitCode;
                qDebug() << "Exit Status: " << exitStatus;
    });
}

MonitorLabel::~MonitorLabel()
{
    this->stop();
}

QSize MonitorLabel::sizeHint() const
{
    return QSize(200, 50);
}

QSize MonitorLabel::minimumSizeHint() const
{
    return QSize(100, 50);
}

void MonitorLabel::start(int timerIntervalNum)
{
    this->getCPU();
    this->getMemory();

    if(!cpuTimer->isActive()){
        cpuTimer->start(timerIntervalNum);
    }

    if(!memoryTimer->isActive()){
        memoryTimer->start(timerIntervalNum);
    }
}

void MonitorLabel::stop()
{
    if(typeperfProcess->state() == QProcess::Running){
        typeperfProcess->terminate();//尝试优雅关闭
        if(typeperfProcess->waitForFinished(100)) {//等100ms
            typeperfProcess->kill();//不等了，直接关
        }
    }

    if(cpuTimer->isActive()){
        cpuTimer->stop();
    }

    if(memoryTimer->isActive()){
        memoryTimer->stop();
    }

}

void MonitorLabel::getCPU()
{

   QString cmd = QString("\\Processor Information(_Total)\\% Processor Utility");

   if(typeperfProcess->state() == QProcess::NotRunning){
       typeperfProcess->start("typeperf", QStringList() << cmd);
       //typeperf启动失败或者不存在该命令
       if(!typeperfProcess->waitForStarted()) {
           qWarning() << "Failed to start typeperf:" << typeperfProcess->errorString();
       }
   }
}

void MonitorLabel::getMemory()
{
#if QT_VERSION >= QT_VERSION_CHECK(5,10,0)
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    AllMemoryPhsy = status.ullTotalPhys / MB;
    AvailMemoryPhsy = status.ullAvailPhys / MB;
    UsedMemoryPhsy = AllMemoryPhsy - AvailMemoryPhsy;
    MemoryUsagePersent = status.dwMemoryLoad;

    this->setMonitorText();//拿到Memory占用率了
#endif
}

void MonitorLabel::readCpuPercentVal()
{
    while(!typeperfProcess->atEnd()){
        QString typeperfInfo = QLatin1String(typeperfProcess->readLine());
        QString typeperfInfoEndWithSegm = typeperfInfo.split(",").last();
        typeperfInfoEndWithSegm.replace("\r", "");
        typeperfInfoEndWithSegm.replace("\n", "");
        QString typeperfInfoEndStringNum = typeperfInfoEndWithSegm.replace("\"","");

        bool ok;
        float typeperfInfoEndFloatNum = typeperfInfoEndStringNum.toFloat(&ok);
        if(ok) {
            CpuUsagePercent = qRound(typeperfInfoEndFloatNum);//四舍五入
        }
    }
    this->setMonitorText();//拿到CPU占用率了
}

void MonitorLabel::setMonitorText()
{
    CpuUsagePercent = (CpuUsagePercent > 100 ? 0 : CpuUsagePercent);
    QString MonitorText = QString("CPU %1%  Memory %2% (已用 %3 MB / 共 %4 MB)").arg(CpuUsagePercent).arg(
                MemoryUsagePersent).arg(UsedMemoryPhsy).arg(AllMemoryPhsy);
    this->setText(MonitorText);

    Q_EMIT textChanged(MonitorText);
    Q_EMIT valueChanged(CpuUsagePercent, MemoryUsagePersent, UsedMemoryPhsy, AllMemoryPhsy, AvailMemoryPhsy);
}
