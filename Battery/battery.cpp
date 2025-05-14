#include "battery.h"

Battery::Battery(QWidget *parent) : isRightPlus(false), timer(new QTimer(this))//要设置父亲为frmBattery
{
    this->setParent(parent);
    //值
    minValue = 0.0;
    maxValue = 100.0;
    TargetValue = 0.0;
    alarmValue = 30.0;
    currentValue = 0.0;

    //颜色
    BorderColor = QColor(100, 100, 100);
    HeadColorStart = QColor(100, 100, 100);
    HeadColorEnd = QColor(80, 80, 80);
    NormalColorStart = QColor(121, 227, 87);
    NormalColorEnd = QColor(24, 133, 87);
    AlarmColorStart = QColor(250, 6, 6);
    AlarmColorEnd = QColor(204, 125, 22);

    //电池框架+画笔
    BorderPenWidth = 5.0;
    BorderRectRadius = 8.0;
    HeadRectRadius = 5.0;
    ChargeRectRadius = 5.0;
    //单次增量
    animationStep = 0.5;

    //启动定时器(每10ms进行一次updateValue, 实现类似的动画效果)
    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, &Battery::updateValue);
}

Battery::~Battery()
{
    if(timer->isActive()) timer->stop();// timer 由 Qt 父子关系自动管理
}

void Battery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //初始画笔画刷
    QPainter painter(this);//QPainter 是一个非常典型的栈对象。
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    drawBorder(&painter);
    drawHead(&painter);
    drawCharge(&painter);
}

void Battery::drawBorder(QPainter* painter)
{
    painter->save();

    double BorderHeadWidth = width() / 15.0;
    double BatteryRectWidth = width() - BorderHeadWidth;

    QPointF leftTop(BorderPenWidth, BorderPenWidth);
    QPointF rightBottom(BatteryRectWidth, height() - BorderPenWidth);
    borderRect = QRectF(leftTop, rightBottom);

    painter->setPen(QPen(BorderColor, BorderPenWidth)); //设置画笔
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(borderRect, BorderRectRadius, BorderRectRadius);

    painter->restore();
}

void Battery::drawHead(QPainter* painter)
{
    painter->save();

    QPointF headTopLeft(borderRect.topRight().x(), height() / 3);
    QPointF headBottomRight(width(), height() - height() / 3);
    QRectF HeadRect(headTopLeft, headBottomRight);

    QLinearGradient gradient(HeadRect.topLeft(), HeadRect.bottomLeft());
    gradient.setColorAt(0.0, HeadColorStart);
    gradient.setColorAt(1.0, HeadColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRoundedRect(HeadRect, HeadRectRadius, HeadRectRadius);

    painter->restore();
}

void Battery::drawCharge(QPainter* painter)
{
    if (TargetValue == minValue || currentValue <= minValue) return;

    painter->save();
    //设置渐变
    QLinearGradient gradient(QPointF(0, 0), QPointF(0, height()));
    if(currentValue <= alarmValue) {
        gradient.setColorAt(0.0, AlarmColorStart);
        gradient.setColorAt(1.0, AlarmColorEnd);
    } else {
        gradient.setColorAt(0.0, NormalColorStart);
        gradient.setColorAt(1.0, NormalColorEnd);
    }

    //设置页边距
    double margin = qMin(width(), height()) / 20;
    //设置charge区域高和宽
    double unit = (borderRect.width() - 2 * margin) / (maxValue - minValue);
    double chargeRectWidth = unit * currentValue;
    //设置charge框架
    QPointF leftTop(borderRect.topLeft().x() + margin, borderRect.topLeft().y() + margin);
    QPointF rightBottom(chargeRectWidth + margin + BorderPenWidth, height() - margin);
    QRectF chargeRect(leftTop, rightBottom);
    //画笔
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    //绘制
    painter->drawRoundedRect(chargeRect, ChargeRectRadius, ChargeRectRadius);

    painter->restore();
}


QSize Battery::sizeHint() const
{
    return QSize(500, 250);
}

QSize Battery::minimumSizeHint() const {
    return QSize(500, 250);  //最小尺寸
}

void Battery::setValue(double value)
{
    if(TargetValue == value) return;//没变化

    if(value > maxValue) {
        TargetValue = maxValue;
    } else if(value < minValue) {
        TargetValue = minValue;
    }

    if(value > currentValue) {
        isRightPlus = true;
    } else if(value < currentValue) {
        isRightPlus = false;
    } else {

    }

    TargetValue = value;
    emit valueChanged();
    timer->start();//动画开始
}

void Battery::setValue(int value)
{
    setValue(static_cast<double>(value));
}

void Battery::updateValue()
{
    if (qAbs(currentValue - TargetValue) <= animationStep) {
            currentValue = TargetValue;
            timer->stop();
            this->update();
            return;
    }

    if(TargetValue == currentValue) {
        timer->stop();
        return;
    }

    if(isRightPlus) {
        currentValue += animationStep;
            if(currentValue >= TargetValue) {
                timer->stop();
            }
    } else {
        currentValue -= animationStep;
            if(currentValue <= TargetValue) {
                timer->stop();
            }
    }
    this->update();
}

double Battery::getCurrenValue() const
{
    return currentValue;
}
