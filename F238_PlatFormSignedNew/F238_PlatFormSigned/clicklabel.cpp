#include "clicklabel.h"
#include <QMouseEvent>

ClickLabel:: ClickLabel(QWidget *parent) : QLabel(parent)
{

}

void ClickLabel::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
  {
      emit clicked();
      return;
  }
  QWidget::mousePressEvent(event);
}
