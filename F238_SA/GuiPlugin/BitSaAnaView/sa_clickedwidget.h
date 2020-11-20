#ifndef SA_CLICKEDWIDGET_H
#define SA_CLICKEDWIDGET_H

#include <QObject>
#include <QWidget>

class SA_ClickedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SA_ClickedWidget(QWidget *parent = NULL);

signals:
    void clicked();
    void focusIn();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void focusInEvent(QFocusEvent *e);
//    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void slotClick();
};

#endif // SA_CLICKEDWIDGET_H
