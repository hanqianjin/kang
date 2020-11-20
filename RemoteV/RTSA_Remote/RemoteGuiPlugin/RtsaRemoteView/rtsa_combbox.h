#ifndef RTSA_COMBBOX_H
#define RTSA_COMBBOX_H

#include <QObject>

#include <QWidget>
#include <Qt>
#include <QComboBox>
#include <QAbstractItemView>
enum{
    RTSA_BOTTOM = 0,
    RTSA_TOP = 1,
    RTSA_LEFT = 2,
    RTSA_RIGHT = 3,
};
class RtSa_CombBox : public QComboBox
{
    Q_OBJECT
public:
    explicit RtSa_CombBox(QWidget* parent = NULL);
    void showPopup();
    void hidePopup();
    void setPopupPotion(qint32 pos, qint32 Xoffset = 0,qint32 Yoffset = 0);
protected:
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *event);
signals:
    void mFocusOut(qint32 index);
    void mFocus(RtSa_CombBox* e);
    void clicked(RtSa_CombBox* e);
protected:
    void mousePressEvent(QMouseEvent* event);
    qint32 position;
    qint32 posXOffset;
    qint32 posYOffset;
};

#endif // RTSA_COMBBOX_H
