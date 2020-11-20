#include "clickablelabel.h"
#include <QMouseEvent>
#include <QMessageBox>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f): QLabel(parent)
{
    //connect(this,SIGNAL(clicked()),this,SLOT(slotClick()));
}
void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLabel::mousePressEvent(event);//将该事件传给父类处理
}
void ClickableLabel::mouseReleaseEvent(QMouseEvent *event)
{
    //emit clicked();
}
void ClickableLabel::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
