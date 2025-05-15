#include "frmmonitor.h"

frmMonitor::frmMonitor(QWidget *parent)
    : QWidget(parent)
{
    this->initForm();
}

frmMonitor::~frmMonitor()
{
    delete LabelFirst;
    delete LabelSecond;
    delete LabelThird;
}

void frmMonitor::initForm()
{
    this->setWindowTitle("CPU-Memory-Monitor");
    //强制最小窗口
    this->setMinimumSize(600, 400);
    //字体大小
    QFont font;
    font.setPixelSize(20);
    setFont(font);
    //Label字体居中
    LabelFirst = new MonitorLabel(this);//标签
    LabelSecond = new QLabel(this);
    LabelThird = new QLabel(this);

    LabelFirst->setAlignment(Qt::AlignCenter);
    LabelSecond->setAlignment(Qt::AlignCenter);
    LabelThird->setAlignment(Qt::AlignCenter);
    //风格
    const QString FIRST_QSS = QString("QLabel { background-color : rgb(0, 0, 0); color : rgb(%1)}").arg("222, 112, 23");
    const QString SECOND_QSS = QString("QLabel { background-color : rgb(0, 0, 0); color : rgb(%1)}").arg("25, 222, 29");
    const QString THIRD_QSS = QString("QLabel { background-color : rgb(0, 0, 0); color : rgb(%1)}").arg("29, 31, 222");
    LabelFirst->setStyleSheet(FIRST_QSS);
    LabelSecond->setStyleSheet(SECOND_QSS);
    LabelThird->setStyleSheet(THIRD_QSS);
    //初始化label文字
    LabelFirst->setText("Waiting for data...");
    LabelSecond->setText("Waiting for data...");
    LabelThird->setText("Waiting for data...");
    //标签随窗口缩放
    LabelFirst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    LabelSecond->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    LabelThird->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //垂直布局
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(LabelFirst, 1);
    layout->addWidget(LabelSecond, 1);
    layout->addWidget(LabelThird, 1);
    layout->setSpacing(5);
    layout->setContentsMargins(5,5,5,5);

    //设置主窗口布局
    this->setLayout(layout);

    //把 LabelFirst 的最新文本内容直接设置到 LabelSecond
    connect(LabelFirst, &MonitorLabel::textChanged, LabelSecond, &QLabel::setText);

    //通过Monitor信号传送来的数据定制Text给LabelThird
    connect(LabelFirst, &MonitorLabel::valueChanged, this, &frmMonitor::customizingText);

    //启动MonitorLabel定时器，让他开始获取CPU Meomory信息
    LabelFirst->start(1000);
}

void frmMonitor::customizingText(quint64 CpuUsagePersent, quint64 MemoryUsagePersent, quint64 UsedMemoryPhsy,
                                 quint64 AllMemoryPhsy, quint64 AvailMemoryPhsy)
{
    Q_UNUSED(AvailMemoryPhsy);
    QString LabelThirdText = tr("中央处理器 %1%  内存%2% (已用 %3 MB / 共 %4 MB)").arg(CpuUsagePersent).
            arg(MemoryUsagePersent).arg(UsedMemoryPhsy).arg(AllMemoryPhsy);
    LabelThird->setText(LabelThirdText);
}

