#include "sa_lineedit.h"
#include <QMouseEvent>
#include <QMessageBox>

SA_LineEdit::SA_LineEdit(QWidget* parent, Qt::WindowFlags f): QLineEdit(parent)
{
    //connect(this,SIGNAL(clicked()),this,SLOT(slotClick()));
}

void SA_LineEdit::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLineEdit::mousePressEvent(event);//将该事件传给父类处理
}
void SA_LineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    //emit clicked();
}
void SA_LineEdit::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void SA_LineEdit::focusInEvent(QFocusEvent *e)
{
    emit mFocus(this);
    return QLineEdit::focusInEvent(e);
}

void SA_LineEdit::keyPressEvent(QKeyEvent *event)
{
    return QLineEdit::keyPressEvent(event);
}