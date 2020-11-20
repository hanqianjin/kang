#ifndef PM_COMBBOX_H
#define PM_COMBBOX_H

#include <QObject>

#include <QWidget>
#include <Qt>
#include <QComboBox>
#include <QAbstractItemView>
enum{
    PM_BOTTOM = 0,
    PM_TOP = 1,
    PM_LEFT = 2,
    PM_RIGHT = 3,
};
class Pm_CombBox : public QComboBox
{
    Q_OBJECT
public:
    explicit Pm_CombBox(QWidget* parent = NULL);
    void showPopup();
    void hidePopup();
    void setPopupPotion(qint32 pos, qint32 Xoffset = 0,qint32 Yoffset = 0);
protected:
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *event);
signals:
    void mFocusOut(qint32 index);
    void mFocus(Pm_CombBox* e);
    void clicked(Pm_CombBox* e);
protected:
    void mousePressEvent(QMouseEvent* event);
    qint32 position;
    qint32 posXOffset;
    qint32 posYOffset;
};

#endif // PM_COMBBOX_H
