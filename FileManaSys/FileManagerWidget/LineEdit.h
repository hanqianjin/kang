/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  LineEdit.h
** Latest Version:             V1.0.0
** Latest modified Date:       2017/09/18
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 niu honglin
** Created date:               2017/09/18
** Descriptions:               END
**
*********************************************************************************************************/
#ifndef LINEEDIT_H_
#define LINEEDIT_H_

#include <QLineEdit>
#include <QFont>

class LineEdit :public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = Q_NULLPTR);
    ~LineEdit()
    {

    }

private:
	void mousePressEvent(QMouseEvent *event) {};
	void mouseReleaseEvent(QMouseEvent *event) {};
	void mouseDoubleClickEvent(QMouseEvent *) {};
	void mouseMoveEvent(QMouseEvent *) {};
};
#endif // !LINEEDIT_H_
