#ifndef PM_CLICKEDWIDGET_H
#define PM_CLICKEDWIDGET_H

#include <QObject>
#include <QWidget>

class Pm_ClickedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Pm_ClickedWidget(QWidget *parent = 0);

signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void slotClick();
};

#endif // PM_CLICKEDWIDGET_H
