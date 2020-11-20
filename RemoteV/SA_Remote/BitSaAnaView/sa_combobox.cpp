#include "sa_combobox.h"
SA_Combobox::SA_Combobox(QWidget* parent): QComboBox(parent)
{
    this->setView(new QListView());
    position = SA_BOTTOM;
    posXOffset = 0;
    posYOffset = 0;
}

void SA_Combobox::focusOutEvent(QFocusEvent *e)
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

void SA_Combobox::focusInEvent(QFocusEvent *e)
{

    return QComboBox::focusInEvent(e);
}

void SA_Combobox::showPopup()
{
    QComboBox::showPopup();
    QWidget *popup = this->findChild<QFrame*>();
    popup->hide();
    qint32 x,y,w,h;
    w = popup->width();
    h = popup->height();
    switch (position) {
    case SA_BOTTOM:
        x = popup->x() + posXOffset;
        y = popup->y() + posYOffset + 1;
        break;
    case SA_TOP:
        x = popup->x() + posXOffset;
        y = popup->y()+ posYOffset - 1;
        break;
    case SA_LEFT:
        x = popup->x() - w + posXOffset;
        y = popup->y()-this->height() + posYOffset;
        break;
    case SA_RIGHT:
        x = popup->x() + this->width() + posXOffset;
        y = popup->y()-this->height() + posYOffset;
        break;
    }
    popup->setGeometry(x,y,w,h);
    popup->show();
    return;
}

void SA_Combobox::hidePopup()
{
    QComboBox::hidePopup();
    return;
}

void SA_Combobox::setPopupPotion(qint32 pos, qint32 Xoffset, qint32 Yoffset)
{
    position = pos;
    posXOffset = Xoffset;
    posYOffset = Yoffset;
    return;
}

void SA_Combobox::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();

    if(keyvalue == Qt::Key_F3 ||\
       keyvalue == Qt::Key_F4 ||\
       (keyvalue >= Qt::Key_0 && keyvalue <= Qt::Key_9) ||\
       (keyvalue >= Qt::Key_A && keyvalue <= Qt::Key_Z))
    {

        return;
    }
    return QComboBox::keyPressEvent(event);
}

void SA_Combobox::mousePressEvent(QMouseEvent *e)
{
    emit clicked(this);
    return QComboBox::mousePressEvent(e);
}

