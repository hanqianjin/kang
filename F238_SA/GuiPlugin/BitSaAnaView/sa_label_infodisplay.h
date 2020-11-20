#ifndef SA_LABEL_INFODISPLAY_H
#define SA_LABEL_INFODISPLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class SA_Label_InfoDisplay:public QLabel
{
    Q_OBJECT
public:
    explicit SA_Label_InfoDisplay(QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());
};

#endif // SA_LABEL_INFODISPLAY_H
