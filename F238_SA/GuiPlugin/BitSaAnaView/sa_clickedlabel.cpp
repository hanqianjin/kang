#include "sa_clickedlabel.h"
#include <QMouseEvent>
#include <QMessageBox>

SA_ClickedLabel::SA_ClickedLabel(QWidget *parent) : QLabel(parent)
{

}
void SA_ClickedLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        return;
    }
    QWidget::mousePressEvent(event);//将该事件传给父类处理
}
void SA_ClickedLabel::mouseReleaseEvent(QMouseEvent *event)
{
    //emit clicked();
}
void SA_ClickedLabel::slotClick()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit("单击"), QString::fromLocal8Bit("单击确定"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
