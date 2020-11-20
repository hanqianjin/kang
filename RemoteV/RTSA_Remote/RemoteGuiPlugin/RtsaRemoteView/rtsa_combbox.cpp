#include "rtsa_combbox.h"
#include <QMouseEvent>
#include <QDebug>
#include <QListView>
#include <QApplication>
RtSa_CombBox::RtSa_CombBox(QWidget* parent): QComboBox(parent)
{
    this->setView(new QListView());
    position = RTSA_BOTTOM;
    posXOffset = 0;
    posYOffset = 0;
}

void RtSa_CombBox::focusOutEvent(QFocusEvent *e)
{
//    if(this->view()->hasFocus())
//    {
//        emit mFocusOut(1);
//    }
//    else
//    {
//        emit mFocusOut(0);
//    }
    return /*QComboBox::focusOutEvent(e)*/;
}
void RtSa_CombBox::focusInEvent(QFocusEvent *e)
{
//    emit mFocus(this);
//    emit clicked(this);
    return QComboBox::focusInEvent(e);
}

void RtSa_CombBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
//        showPopup();
//        this->setStyleSheet("QComboBox{background-image: url(:/sa/image/dropdown_click.png);}");
//        emit clicked(this);
    }
    emit clicked(this);
    QComboBox::mousePressEvent(event);//将该事件传给父类处理
}
void RtSa_CombBox::showPopup()
{
    QComboBox::showPopup();
    QWidget *popup = this->findChild<QFrame*>();
    popup->hide();
//    popup->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    qint32 x,y,w,h;
    w = popup->width();
    h = popup->height();
    switch (position) {
    case RTSA_BOTTOM:
        x = popup->x() + posXOffset;
        y = popup->y() + posYOffset;
        break;
    case RTSA_TOP:
        x = popup->x() + posXOffset;
        y = popup->y()- h -this->height()+ posYOffset;
        break;
    case RTSA_LEFT:
        x = popup->x() - w + posXOffset;
        y = popup->y()-this->height() + posYOffset;
        break;
    case RTSA_RIGHT:
        x = popup->x() + this->width() + posXOffset;
        y = popup->y()-this->height() + posYOffset;
        break;
    }
    popup->setGeometry(x,y,w,h);
//    popup->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    popup->show();
//    qDebug()<<x<<y<<w<<h;
    return;
}

void RtSa_CombBox::hidePopup()
{
    QComboBox::hidePopup();
    return;
}

void RtSa_CombBox::setPopupPotion(qint32 pos, qint32 Xoffset, qint32 Yoffset)
{
    position = pos;
    posXOffset = Xoffset;
    posYOffset = Yoffset;
    return;
}
void RtSa_CombBox::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        QWidget::keyPressEvent(event);
        //showPopup();
        break;
    case Qt::Key_Shift:
    case Qt::Key_Escape:
        QWidget::keyPressEvent(event);
    default:
        break;
    }
    return;
}

