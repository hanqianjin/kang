#include "pm_combbox.h"
#include <QMouseEvent>
#include <QDebug>
#include <QListView>
#include <QApplication>
Pm_CombBox::Pm_CombBox(QWidget* parent): QComboBox(parent)
{
    this->setView(new QListView());
    position = PM_BOTTOM;
    posXOffset = 0;
    posYOffset = 0;
}

void Pm_CombBox::focusOutEvent(QFocusEvent *e)
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
void Pm_CombBox::focusInEvent(QFocusEvent *e)
{
//    emit mFocus(this);
//    emit clicked(this);
    return QComboBox::focusInEvent(e);
}

void Pm_CombBox::mousePressEvent(QMouseEvent *event)
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
void Pm_CombBox::showPopup()
{
    QComboBox::showPopup();
    QWidget *popup = this->findChild<QFrame*>();
    popup->hide();
//    popup->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    qint32 x,y,w,h;
    w = popup->width();
    h = popup->height();
    switch (position) {
    case PM_BOTTOM:
        x = popup->x() + posXOffset;
        y = popup->y() + posYOffset;
        break;
    case PM_TOP:
        x = popup->x() + posXOffset;
        y = popup->y()- h -this->height()+ posYOffset;
        break;
    case PM_LEFT:
        x = popup->x() - w + posXOffset;
        y = popup->y()-this->height() + posYOffset;
        break;
    case PM_RIGHT:
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

void Pm_CombBox::hidePopup()
{
    QComboBox::hidePopup();
    return;
}

void Pm_CombBox::setPopupPotion(qint32 pos, qint32 Xoffset, qint32 Yoffset)
{
    position = pos;
    posXOffset = Xoffset;
    posYOffset = Yoffset;
    return;
}
void Pm_CombBox::keyPressEvent(QKeyEvent *event)
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

