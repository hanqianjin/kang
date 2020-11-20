#include "rtsa_clickedwidget.h"
#include <QMouseEvent>
#include <QMessageBox>

RtSa_ClickedWidget::RtSa_ClickedWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
}

void RtSa_ClickedWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QWidget::mousePressEvent(event);//将该事件传给父类处理
}
void RtSa_ClickedWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //emit clicked();
}
void RtSa_ClickedWidget::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
