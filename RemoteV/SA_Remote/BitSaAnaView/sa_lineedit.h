#ifndef SA_LINEEDIT_H
#define SA_LINEEDIT_H

#include <QWidget>
#include <Qt>
#include <QLineEdit>

class SA_LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SA_LineEdit(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

signals:
    void clicked();
    void mFocus(SA_LineEdit* e);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual void focusInEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *event);
private slots:
    void slotClick();
};


#endif // SA_LINEEDIT_H
