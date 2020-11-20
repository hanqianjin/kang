#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QObject>
#include <QLabel>

class ClickLabel : public QLabel
{
  Q_OBJECT
public:

  explicit ClickLabel(QWidget *parent = NULL);

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKLABEL_H
