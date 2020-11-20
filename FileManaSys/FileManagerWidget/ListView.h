/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ListView.h
** Latest Version:             V1.0.0
** Latest modified Date:       2018/10/25
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Cai Gaojian
** Created date:               2018/10/25
** Descriptions:               END
**
*********************************************************************************************************/
#ifndef LISTVIEW_H_
#define LISTVIEW_H_

#include <QListView>

class ListView :public QListView
{
	Q_OBJECT

public:
	explicit ListView(QWidget *parent = Q_NULLPTR);
	~ListView() {};

	void focusOutEvent(QFocusEvent *e);
	void focusInEvent(QFocusEvent *e);

signals:
	void hideThePopup();

protected:
	bool viewportEvent(QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	QModelIndex		m_currentIndex;
	QModelIndex		m_pressedIndex;
};

#endif