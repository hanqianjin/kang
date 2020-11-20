#include "rtsa_lineedit.h"
#include <QMouseEvent>
#include <QMessageBox>

RtSa_LineEdit::RtSa_LineEdit(QWidget* parent, Qt::WindowFlags f): QLineEdit(parent)
{
    //connect(this,SIGNAL(clicked()),this,SLOT(slotClick()));
    // Do not respond mouse right button event.
//    this->setContextMenuPolicy(Qt::NoContextMenu);
//    this->setCursor(Qt::ArrowCursor);
}
void RtSa_LineEdit::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLineEdit::mousePressEvent(event);//将该事件传给父类处理
}
void RtSa_LineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    //emit clicked();
}
void RtSa_LineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}
void RtSa_LineEdit::mouseMoveEvent(QMouseEvent *event)
{
    return;
}
void RtSa_LineEdit::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
void RtSa_LineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    return;
}
void RtSa_LineEdit::focusInEvent(QFocusEvent *e)
{
    emit mFocus(this);
    return QLineEdit::focusInEvent(e);
}
