#include "sa_clickedwidget.h"
#include <QMouseEvent>
#include <QMessageBox>

SA_ClickedWidget::SA_ClickedWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
}

void SA_ClickedWidget::mousePressEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::LeftButton)
//    {
//        emit clicked();
//    }
//    QWidget::mousePressEvent(event);//将该事件传给父类处理
}

void SA_ClickedWidget::mouseMoveEvent(QMouseEvent *event)
{
    //emit clicked();
    return;
}
void SA_ClickedWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    return QWidget::mouseReleaseEvent(event);//将该事件传给父类处理;
}
void SA_ClickedWidget::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
void SA_ClickedWidget::focusInEvent(QFocusEvent *e)
{
    emit focusIn();
    return QWidget::focusInEvent(e);
}
