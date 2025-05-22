#include "frmbuttonsdisplay.h"
#include "./ui_frmbuttonsdisplay.h"

frmButtonsDisplay::frmButtonsDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frmButtonsDisplay)
{
    ui->setupUi(this);
    this->initForm();
    initShapeColorLists();//初始化颜色和形状的QList
    initButtonsConnects();//建立信号与槽

    //复位按钮connct
    connect(ui->resetButton, &QPushButton::clicked, this, &frmButtonsDisplay::tagReset);
}

frmButtonsDisplay::~frmButtonsDisplay()
{
    delete ui;
}

void frmButtonsDisplay::initForm()
{
    ui->mapLabel->setPixmap(QPixmap(":/image/bg_call.jpg"));
    this->resize(1000, 600);//初始宽高比
    this->initTagGeometry();//初始Tag位置
}

QSize frmButtonsDisplay::sizeHint() const
{
    return QSize(1000, 800);
}

QSize frmButtonsDisplay::minimumSizeHint() const
{
    return QSize(250, 200);
}

void frmButtonsDisplay::initShapeColorLists()
{
    changeColorButtons << ui->colorButton_Green << ui->colorButton_Blue << ui->colorButton_Red
                       << ui->colorButton_Grey << ui->colorButton_Black << ui->colorButton_Purple
                       << ui->colorButton_Yellow;
    changeShapeButtons << ui->shapeButton_Circle << ui->shapeButton_Police << ui->shapeButton_Bubble
                       << ui->shapeButton_Bubble2 << ui->shapeButton_Info << ui->shapeButton_Info2;
}

void frmButtonsDisplay::initButtonsConnects()
{
    for(auto& shapeButton : changeShapeButtons) {
        connect(shapeButton, &QPushButton::clicked, this, &frmButtonsDisplay::changeTagShape);
    }

    for(auto& colorButton : changeColorButtons) {
        connect(colorButton, &QPushButton::clicked, this, &frmButtonsDisplay::changeTagColor);
    }
    //stateChanged自动传递参数
    connect(ui->checkBox_Movable, &QCheckBox::stateChanged, mappingTag_1, &mappingTag::setMovable);
    connect(ui->checkBox_Movable, &QCheckBox::stateChanged, mappingTag_2, &mappingTag::setMovable);
    connect(ui->checkBox_Movable, &QCheckBox::stateChanged, mappingTag_3, &mappingTag::setMovable);
}

void frmButtonsDisplay::initTagGeometry()
{
    mappingTag_1 = new mappingTag(ui->mapLabel);
    mappingTag_1->setText("#1");
    mappingTag_1->setGeometry(QRect(5, 5, 60, 60));

    mappingTag_2 = new mappingTag(ui->mapLabel);
    mappingTag_2->setText("#2");
    mappingTag_2->setGeometry(QRect(75, 5, 60, 60));

    mappingTag_3 = new mappingTag(ui->mapLabel);
    mappingTag_3->setText("#3");
    mappingTag_3->setGeometry(QRect(145, 5, 60, 60));
}

void frmButtonsDisplay::changeTagShape()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int index = changeShapeButtons.indexOf(button);
    mappingTag_1->changeShape(index);
    mappingTag_2->changeShape(index);
    mappingTag_3->changeShape(index);
}

void frmButtonsDisplay::changeTagColor()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int index = changeColorButtons.indexOf(button);
    mappingTag_1->changeColor(index);
    mappingTag_2->changeColor(index);
    mappingTag_3->changeColor(index);
}

void frmButtonsDisplay::tagReset()
{
    mappingTag_1->setGeometry(QRect(5, 5, 60, 60));
    mappingTag_2->setGeometry(QRect(75, 5, 60, 60));
    mappingTag_3->setGeometry(QRect(145, 5, 60, 60));
}



