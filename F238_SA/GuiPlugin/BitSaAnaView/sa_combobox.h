#ifndef SA_COMBOBOX_H
#define SA_COMBOBOX_H

#include <QObject>

#include <QWidget>
#include <Qt>
#include <QComboBox>
#include <QAbstractItemView>
#include <QKeyEvent>
#include <QListView>
#include <QLineEdit>
#include <QApplication>
enum{
    SA_BOTTOM = 0,
    SA_TOP = 1,
    SA_LEFT = 2,
    SA_RIGHT = 3,
};
class SA_Combobox : public QComboBox
{
    Q_OBJECT
public:
    explicit SA_Combobox(QWidget* parent = NULL);
    void showPopup();
    void hidePopup();
    void setPopupPotion(qint32 pos, qint32 Xoffset = 0,qint32 Yoffset = 0);
protected:
    void focusOutEvent(QFocusEvent *e);
    void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *e);
signals:
    void mFocusOut(qint32 index);
    void mFocus(SA_Combobox* e);
    void clicked(SA_Combobox* e);
protected:
    qint32 position;
    qint32 posXOffset;
    qint32 posYOffset;
};

#endif // SA_COMBOBOX_H
