#ifndef FOCUSLINEDIT_H
#define FOCUSLINEDIT_H

#include <QLineEdit>
#include <QFocusEvent>
#include <QObject>
class focuslinedit : public QLineEdit
{
  Q_OBJECT
public:  
  explicit focuslinedit(QWidget *parent = NULL);

signals:
  void loseFocus();
  void clicked();
private:
  void focusOutEvent(QFocusEvent *evet);
  void focusInEvent(QFocusEvent *evet);
  void mousePressEvent(QMouseEvent *e);
  void keyPressEvent(QKeyEvent *e);
};

#endif // FOCUSLINEDIT_H
