/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  HeaderWidget.h
** Latest Version:             V1.0.0
** Latest modified Date:       2019/5/16
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Zhou Yuhan
** Created date:               2019/5/16
** Descriptions:               END
**
*********************************************************************************************************/

#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

class HeaderWidget : public QWidget
{
    Q_OBJECT

    enum SortTypeEnum
    {
        None = 0,
        NameUp,
        NameDown,
        SizeUp,
        SizeDown,
        TypeUp,
        TypeDown,
        DateUp,
        DateDown
    };

public:
    explicit HeaderWidget(QWidget *parent = NULL);

signals:
    void clicked(int sortType);

public slots:
//    void setSelectAll(bool select){};
    void resetSort();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QRect m_nameRect;
    QRect m_dateRect;
    QRect m_fileTypeRect;
    QRect m_fileSizeRect;
    QRect m_selectAllRect;
    int m_sortType;
};

#endif // HEADERWIDGET_H
