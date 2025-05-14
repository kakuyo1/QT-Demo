#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QLinearGradient> //渐变
class Battery : public QWidget
{
    Q_OBJECT
public:
    Battery(QWidget *parent);
    ~Battery();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    double getCurrenValue() const;
private:
    //电池值变量
    double minValue;
    double maxValue;
    double TargetValue;
    double alarmValue;
    double currentValue;

    //电池增量方向
    bool isRightPlus;

    //伪动画效果的单次增量
    double animationStep;

    //画笔粗细
    double BorderPenWidth;

    //颜色变量
    QColor BorderColor;
    QColor HeadColorStart;
    QColor HeadColorEnd;
    QColor NormalColorStart;
    QColor NormalColorEnd;
    QColor AlarmColorStart;
    QColor AlarmColorEnd;

    //Rect圆半径变量
    double BorderRectRadius;
    double HeadRectRadius;
    double ChargeRectRadius;

    //电池框架主体
    QRectF borderRect;
protected:
    void setValue(double value);

private:
    void paintEvent(QPaintEvent *event) override;
    void drawBorder(QPainter* painter);
    void drawHead(QPainter* painter);
    void drawCharge(QPainter* painter);
    QTimer* timer;

private slots:
    void updateValue();
public slots:
    void setValue(int value);

signals:
    void valueChanged();//暂时没有接受者
};

#endif // BATTERY_H
