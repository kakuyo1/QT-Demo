#ifndef MAPPINGTAG_H
#define MAPPINGTAG_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
class mappingTag : public QLabel
{
    Q_OBJECT
public:
    explicit mappingTag(QWidget *parent = nullptr);
    ~mappingTag();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void paintEvent(QPaintEvent *event) override;
    void changeColor(int index);
    void changeShape(int index);
    void setMovable(int status);
    bool eventFilter(QObject* watched, QEvent* event) override;
    void setText(QString text);
    enum TagShapes {
        TagShape_Circle,
        TagShape_Police,
        TagShape_Bubble1,
        TagShape_Bubble2,
        TagShape_Info1,
        TagShape_Info2
    };

    enum TagColors {
        TagColor_Green,
        TagColor_Blue,
        TagColor_Red,
        TagColor_Grey,
        TagColor_Black,
        TagColor_Purple,
        TagColor_Yellow
    };
private:
    TagShapes currentShape;//Tag的当前图案枚举
    TagColors currentColor;//Tag的当前颜色枚举

    QString alarmColor;//报警颜色
    QString normalColor;//普通颜色
    QString currentColorchar;//Tag的当前颜色
    bool isAlarmColor;
    QString tagText;

    bool movable;
    bool isPressed;//左键按下
    QPoint tagPosition;

    QString imgType;
    QString imgPathWithNoColorType;
    QString imgWholePath;

    QTimer* colorChangeTimer;

//    static const QMap<TagShapes, QString> shapesMap;
//    static const QMap<TagColors, QString> colorsMap;
    void checkAlarm();

private Q_SLOTS:


Q_SIGNALS:

};


#endif // MAPPINGTAG_H
