#include "mappingtag.h"

mappingTag::mappingTag(QWidget *parent) : QLabel(parent)
  , currentShape(TagShape_Police)
  , currentColor(TagColor_Green)
  , alarmColor(QString("red"))
  , normalColor(QString("black"))
  , currentColorchar("green")
  , isAlarmColor(false)
  , tagText("")
  , movable(false)
  , isPressed(false)
  , tagPosition(0, 0)
  , imgType("police")//初始时暂时用绿色警察
  , imgPathWithNoColorType(":/image/devicebutton/devicebutton")
  , imgWholePath(":/image/devicebutton/devicebutton_green_police.png")
  , colorChangeTimer(new QTimer(this))

{
    colorChangeTimer->setInterval(200);
    connect(colorChangeTimer, &QTimer::timeout, this, &mappingTag::checkAlarm);
    this->installEventFilter(this);//自己监视自己的所有事件
}

mappingTag::~mappingTag()
{
    if(colorChangeTimer->isActive()) {
        colorChangeTimer->stop();
        delete colorChangeTimer;
    }
}

QSize mappingTag::sizeHint() const
{
    return QSize(50, 50);
}

QSize mappingTag::minimumSizeHint() const
{
    return QSize(10, 10);
}

void mappingTag::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::NoBrush);

    //绘制图像
    QImage tagImage(imgWholePath);//图像最好缓存起来cacheTagImage，变化多,写在.h中,防止每次paint都scale,毕竟移动都paint

    if(!tagImage.isNull()) {
        tagImage.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawImage(0, 0, tagImage);
    } else {
        // 绘制默认占位图像或显示错误
        painter.setBrush(Qt::gray);
        painter.drawRect(rect());
        painter.drawText(rect(), Qt::AlignCenter, "Image Not Found");
    }

    //绘制文字
    QFont font;
    font.setPixelSize(20);
    font.setBold(true);
    painter.setFont(font);

    QRect rect = this->rect();
    if(currentShape == TagShape_Police) {
        rect.translate(0, 15);//改变控件的坐标轴，y轴在控件内下移15像素
        painter.drawText(rect, Qt::AlignCenter, tagText);
    } else if(currentShape == TagShape_Info1) {
        rect.translate(0, -5);
        painter.drawText(rect, Qt::AlignCenter, tagText);
    } else if(currentShape == TagShape_Info2) {
        rect.translate(0, -5);
        painter.drawText(rect, Qt::AlignCenter, tagText);
    } else if(currentShape == TagShape_Circle) {
        rect.translate(0, 0);
        painter.drawText(rect, Qt::AlignCenter, tagText);
    } else if(currentShape == TagShape_Bubble1) {
        rect.translate(0, 0);
        painter.drawText(rect, Qt::AlignCenter, tagText);
    } else if(currentShape == TagShape_Bubble2) {
        rect.translate(0, 0);
        painter.drawText(rect, Qt::AlignCenter, tagText);
    }


}

void mappingTag::changeColor(int index)
{
    if(colorChangeTimer->isActive()) {
        colorChangeTimer->stop();
    }
    currentColor = (TagColors)index;

    switch (currentColor) {
    case TagColor_Green :
        currentColorchar = "green";
        break;
    case TagColor_Blue :
        currentColorchar = "blue";
        break;
    case TagColor_Red :
        currentColorchar = "red";
        break;
    case TagColor_Grey :
        currentColorchar = "gray";
        break;
    case TagColor_Black :
        currentColorchar = "black";
        break;
    case TagColor_Purple :
        currentColorchar = "purple";
        break;
    case TagColor_Yellow :
        currentColorchar = "yellow";
        break;
    default :
        currentColorchar = "green";
        break;
    }

    imgWholePath = QString("%1_%2_%3.png").arg(imgPathWithNoColorType).arg(currentColorchar).arg(imgType);
    update();
    if(currentColor == TagColor_Red) {
        //        checkAlarm();没卵用
        if(!colorChangeTimer->isActive()) {
            colorChangeTimer->start();
        }
    }
}

void mappingTag::changeShape(int index)
{
    if(colorChangeTimer->isActive()) {
        colorChangeTimer->stop();
    }
    currentShape = (TagShapes)index;

    if(currentShape == TagShape_Police) {
        imgType = "police";
    } else if(currentShape == TagShape_Info1) {
        imgType = "msg";
    } else if(currentShape == TagShape_Info2) {
        imgType = "msg2";
    } else if(currentShape == TagShape_Circle) {
        imgType = "circle";
    } else if(currentShape == TagShape_Bubble1) {
        imgType = "bubble";
    } else if(currentShape == TagShape_Bubble2) {
        imgType = "bubble2";
    }

    imgWholePath = QString("%1_%2_%3.png").arg(imgPathWithNoColorType).arg(currentColorchar).arg(imgType);
    update();
    if(currentColor == TagColor_Red) {
        //        checkAlarm(); 没卵用
        if(!colorChangeTimer->isActive()) {
            colorChangeTimer->start();
        }
    }
}

void mappingTag::setMovable(int status)
{
    movable = (bool)status;
}

bool mappingTag::eventFilter(QObject *watched, QEvent *event)
{
    int type = event->type();
    //鼠标事件
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    if (type == QEvent::MouseButtonPress) {
        if(mouseEvent->buttons() == Qt::LeftButton) {
            tagPosition = mouseEvent->pos();//this->rect().topLeft() == 0,mouseEvent->pos()是相对于事件目标控件
            qDebug() << tagPosition;
            return true;
        }
    } else if (type == QEvent::MouseMove && movable) {//非常快速
        int dx = mouseEvent->x() - tagPosition.x();
        int dy = mouseEvent->y() - tagPosition.y();
        this->move(QPoint(this->x(), this->y()) + QPoint(dx, dy));//this->x(), this->y()属于父控件坐标系,在这里是主窗口
        return true;
    } else if (type == QEvent::MouseButtonRelease) {
        isPressed = false;
        if(this->parent()) { //有父类
            QMetaObject::invokeMethod(this->parent(), "update");//给父类处理
        }
    } else if (type == QEvent::MouseButtonDblClick) {
        //暂不处理
    }
    return QObject::eventFilter(watched, event);//交给父类
}

void mappingTag::checkAlarm()
{
    if (currentColor != TagColor_Red) {//不是红色就赶紧走，别update了
            isAlarmColor = false;
            colorChangeTimer->stop();
            return;
        }

    if(isAlarmColor){
        imgWholePath = QString("%1_%2_%3.png").arg(imgPathWithNoColorType).arg(alarmColor).arg(imgType);
    } else {
        imgWholePath = QString("%1_%2_%3.png").arg(imgPathWithNoColorType).arg(normalColor).arg(imgType);
    }
    isAlarmColor = !isAlarmColor;

    update();
}

void mappingTag::setText(QString text)
{
    if(!text.isNull()) {
        tagText = text;
        this->update();
    }
}


