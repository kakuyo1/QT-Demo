#include "frmbattery.h"
#include "ui_frmbattery.h"

frmBattery::frmBattery(QWidget *parent)
    : QWidget(parent)
    , slider(new QSlider(Qt::Vertical,this))
    , battery(new Battery(this))
{
    //ui->setupUi(this);//手动设置的 QHBoxLayout 与 ui->setupUi(this) 生成的布局冲突，可能导致窗口渲染失败。
    //初始化
    this->setMinimumSize(500, 250);
    this->initFrom();
}

frmBattery::~frmBattery()
{
    delete slider;// slider 由 Qt 父子关系自动管理,可以不手动删除
    delete battery;// battery 由 Qt 父子关系自动管理,可以不手动删除
}

void frmBattery::initFrom()
{


    //设置电池控件
//    battery->setGeometry(0, 0, 200, 100);//移除 battery->setGeometry(0, 0, 200, 100)，让布局管理器动态调整
    battery->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //设置滑块属性
    slider->setTickPosition(QSlider::TicksRight);
    slider->setTickInterval(5);
    slider->setRange(0,100);
    slider->setValue(50);
    slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    //添加布局
    QHBoxLayout* widgets_layout = new QHBoxLayout(this);
    widgets_layout->addWidget(battery);
    widgets_layout->addWidget(slider);
    widgets_layout->setSpacing(10); // 控件间距
    widgets_layout->setContentsMargins(10, 10, 10, 10); // 布局边距

    //设置布局
    this->setLayout(widgets_layout);
    this->setMinimumSize(500, 250);// 确保布局后再次设置最小尺寸（可选）
    connect(slider, &QSlider::valueChanged, battery, static_cast<void (Battery::*)(int)>(&Battery::setValue));
    battery->setValue(50);

    //象征性接受battery的值改变信号
    connect(battery, &Battery::valueChanged, [this](){
        qDebug() << "battery value changed to : " << battery->getCurrenValue() ;
    });
}

