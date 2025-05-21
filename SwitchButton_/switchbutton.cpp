#include "switchbutton.h"

SwitchButton::SwitchButton(QWidget* parent) : QPushButton(parent), StatusOnorOff(false)
{
    connect(this, &QPushButton::clicked, this, &SwitchButton::onClicked);
}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::initImage()
{
    QIcon buttonIcon(ImagePath);
    this->setText("");//去除文字
    this->setIcon(buttonIcon);//设置图片
    this->setIconSize(this->size());//调整图片大小与按钮一致
    this->setStyleSheet(QString("QPushButton { border: none; background: transparent; }"));//去除边框
}

void SwitchButton::toggle()
{
    StatusOnorOff = !StatusOnorOff;
    ImagePath = StatusOnorOff ? onImagePath : offImagePath;
    initImage();
    Q_EMIT(statusChanged(isOn()));
}

QString SwitchButton::getImagePath() const
{
    return ImagePath;
}

void SwitchButton::setImagePath(const QString& imagepath)
{
    ImagePath = imagepath;
}

void SwitchButton::setOnImagePath(const QString &onImagePath)
{
    this->onImagePath = onImagePath;
}

void SwitchButton::setOffImagePath(const QString &offImagePath)
{
    this->offImagePath = offImagePath;
}

bool SwitchButton::isOn() const
{
    return StatusOnorOff;
}

void SwitchButton::onClicked()
{
    toggle();
}
