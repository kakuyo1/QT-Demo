#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H
#include <QPushButton>
#include <QWidget>

class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    SwitchButton(QWidget* parent);
    ~SwitchButton();
    void initImage();
    void toggle();
    QString getImagePath() const;
    void setImagePath(const QString& imagepath);
    void setOnImagePath(const QString& onImagePath);
    void setOffImagePath(const QString& offImagePath);
    bool isOn() const;
private:
    QString ImagePath;   //当前图片路径
    QString onImagePath; // 开启状态图片路径
    QString offImagePath; // 关闭状态图片路径
    bool StatusOnorOff; //状态
private Q_SLOTS:
    void onClicked();
Q_SIGNALS:
    void statusChanged(bool isOn);
};

#endif // SWITCHBUTTON_H
