#include "iplineedit.h"

IPLineEdit::IPLineEdit(QWidget *parent) : QLineEdit(parent)
{
    repeat = 0;
}

void IPLineEdit::focusInEvent(QFocusEvent *evet)
{
    emit ipEvent(IP_SHOW_KEYBOARD);
    repeat = 1;
    this->selectAll();
    QLineEdit::focusInEvent(evet);
}
void IPLineEdit::focusOutEvent(QFocusEvent *evet)
{
    emit ipEvent(IP_FINISH_EDIT);
    repeat = 0;
    QLineEdit::focusOutEvent(evet);
}

void IPLineEdit::keyPressEvent(QKeyEvent *e)
{
    qint32 value = e->key();
    switch (value)
    {
    //focus to next lineEdit
    case Qt::Key_Up:
    case Qt::Key_Period:
        emit ipEvent(IP_NEXT_EDIT);
        break;
    case Qt::Key_Right:
        if(cursorPosition()==text().length())
            emit ipEvent(IP_NEXT_EDIT);
        else
            QLineEdit::keyPressEvent(e);
        break;
    case Qt::Key_Left:
        if(cursorPosition()==0)
            emit ipEvent(IP_PREV_EDIT);
        else
            QLineEdit::keyPressEvent(e);
        break;
    case Qt::Key_Down:
        emit ipEvent(IP_PREV_EDIT);
        break;
    case Qt::Key_Enter:
        emit ipEvent(IP_FINISH_EDIT);
        repeat = 0;
        break;
    case Qt::Key_Delete:
        this->clear();
        break;
    default:
        QLineEdit::keyPressEvent(e);
        break;
    }
}

void IPLineEdit::keyReleaseEvent(QKeyEvent *e)
{
    qint32 value = e->key();
    switch (value)
    {
    //focus to next lineEdit
    case Qt::Key_Period:
        emit ipEvent(IP_NEXT_EDIT);
        break;
    default:
        QLineEdit::keyReleaseEvent(e);
        break;
    }
}

void IPLineEdit::mousePressEvent(QMouseEvent *e)
{
    //emit clicked();
    if(repeat)
    {
        repeat = 0;
    }
    emit ipEvent(IP_SHOW_KEYBOARD);
    return;
}
