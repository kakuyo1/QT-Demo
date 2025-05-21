#include "frmdisplay.h"
#include "./ui_frmdisplay.h"

frmDisplay::frmDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmDisplay)
    , iconOneStatusOffPath(":/image/imageswitch/btncheckoff1.png")
    , iconOneStatusOnPath(":/image/imageswitch/btncheckon1.png")
    , iconTwoStatusOffPath(":/image/imageswitch/btncheckoff2.png")
    , iconTwoStatusOnPath(":/image/imageswitch/btncheckon2.png")
    , iconThreeStatusOffPath(":/image/imageswitch/btncheckoff3.png")
    , iconThreeStatusOnPath(":/image/imageswitch/btncheckon3.png")
{

    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    this->initForm();
    connect(ui->SwitchButtonOne, &SwitchButton::statusChanged, this, [](bool isOn) {
        qDebug() << "SwitchButtonOne is" << (isOn ? "ON" : "OFF");
    });
    connect(ui->SwitchButtonTwo, &SwitchButton::statusChanged, this, [](bool isOn) {
        qDebug() << "SwitchButtonTwo is" << (isOn ? "ON" : "OFF");
    });
    connect(ui->SwitchButtonThree, &SwitchButton::statusChanged, this, [](bool isOn) {
        qDebug() << "SwitchButtonThree is" << (isOn ? "ON" : "OFF");
    });
}

frmDisplay::~frmDisplay()
{
    delete ui;
}

void frmDisplay::initForm()
{
    // 设置按钮的开启和关闭图片路径, 默认为关闭
    ui->SwitchButtonOne->setOffImagePath(iconOneStatusOffPath);//关闭
    ui->SwitchButtonOne->setOnImagePath(iconOneStatusOnPath);//开启
    ui->SwitchButtonOne->setImagePath(iconOneStatusOffPath);//默认关闭

    ui->SwitchButtonTwo->setOffImagePath(iconTwoStatusOffPath);
    ui->SwitchButtonTwo->setOnImagePath(iconTwoStatusOnPath);
    ui->SwitchButtonTwo->setImagePath(iconTwoStatusOffPath);

    ui->SwitchButtonThree->setOffImagePath(iconThreeStatusOffPath);
    ui->SwitchButtonThree->setOnImagePath(iconThreeStatusOnPath);
    ui->SwitchButtonThree->setImagePath(iconThreeStatusOffPath);
    //初始化
    ui->SwitchButtonOne->initImage();
    ui->SwitchButtonTwo->initImage();
    ui->SwitchButtonThree->initImage();
}



