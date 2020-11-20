#ifndef SA_CLICKEDLABEL_H
#define SA_CLICKEDLABEL_H
#include <QLabel>
#include <QObject>
#include <QWidget>

class SA_ClickedLabel: public QLabel
{
    Q_OBJECT
public:
    explicit SA_ClickedLabel(QWidget *parent = NULL);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void slotClick();
};

#endif // SA_CLICKEDLABEL_H
