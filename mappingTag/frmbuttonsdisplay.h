#ifndef FRMBUTTONSDISPLAY_H
#define FRMBUTTONSDISPLAY_H

#include <QWidget>
#include <mappingtag.h>
#include <QPainter>
#include <QDebug>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class frmButtonsDisplay; }
QT_END_NAMESPACE

class mappingTag;
class frmButtonsDisplay : public QWidget
{
    Q_OBJECT

public:
    frmButtonsDisplay(QWidget *parent = nullptr);
    ~frmButtonsDisplay();
    void initForm();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    Ui::frmButtonsDisplay *ui;
    mappingTag* mappingTag_1;//这里命名不规范，一会驼峰一会加_,最好统一
    mappingTag* mappingTag_2;
    mappingTag* mappingTag_3;
    QList<QPushButton*> changeShapeButtons;
    QList<QPushButton*> changeColorButtons;
private:
    void initShapeColorLists();
    void initButtonsConnects();
    void initTagGeometry();
private Q_SLOTS:
    void changeTagShape();
    void changeTagColor();
    void tagReset();
};
#endif // FRMBUTTONSDISPLAY_H
