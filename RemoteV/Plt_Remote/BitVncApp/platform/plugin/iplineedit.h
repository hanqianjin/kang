#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H
#include <QLineEdit>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QObject>

class IPLineEdit: public QLineEdit
{
    Q_OBJECT
    enum {
        IP_NEXT_EDIT,
        IP_PREV_EDIT,
        IP_FINISH_EDIT,
        IP_SHOW_KEYBOARD
    };
public:
    explicit IPLineEdit(QWidget *parent = NULL);

signals:
    void loseFocus();
    void clicked();
    void ipEvent(qint32);
private:
    qint32 repeat;
    void focusInEvent(QFocusEvent *evet);
    void focusOutEvent(QFocusEvent *evet);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
};

#endif // IPLINEEDIT_H
