#include "focuslinedit.h"

focuslinedit::focuslinedit(QWidget *parent) : QLineEdit(parent)
{

}

void focuslinedit::focusOutEvent(QFocusEvent *evet)
{
    emit loseFocus();
    QLineEdit::focusOutEvent(evet);
}

void focuslinedit::focusInEvent(QFocusEvent *evet)
{
    //this->selectAll();
    QLineEdit::focusInEvent(evet);
}

void focuslinedit::mousePressEvent(QMouseEvent *e)
{
    QLineEdit::mousePressEvent(e);
    emit clicked();
    return ;
}

void focuslinedit::keyPressEvent(QKeyEvent *e)
{
    qint32 value = e->key();
    switch (value)
    {
    case Qt::Key_Enter:
        emit loseFocus();
        QLineEdit::keyPressEvent(e);
        break;
    case Qt::Key_Delete:
        this->clear();
        break;
    default:
        QLineEdit::keyPressEvent(e);
        break;
    }
}
