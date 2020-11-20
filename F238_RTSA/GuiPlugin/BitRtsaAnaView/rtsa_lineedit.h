#ifndef RTSA_LINEEDIT_H
#define RTSA_LINEEDIT_H

#include <QWidget>
#include <Qt>
#include <QLineEdit>

class RtSa_LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit RtSa_LineEdit(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

signals:
    void clicked();
    void mFocus(RtSa_LineEdit* e);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void focusInEvent(QFocusEvent *e);
private slots:
    void slotClick();
};


#endif // RTSA_LINEEDIT_H
