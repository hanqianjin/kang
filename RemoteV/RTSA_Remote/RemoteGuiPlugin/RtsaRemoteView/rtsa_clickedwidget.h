#ifndef RTSA_CLICKEDWIDGET_H
#define RTSA_CLICKEDWIDGET_H

#include <QObject>
#include <QWidget>

class RtSa_ClickedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RtSa_ClickedWidget(QWidget *parent = 0);

signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void slotClick();
};

#endif // RTSA_CLICKEDWIDGET_H
