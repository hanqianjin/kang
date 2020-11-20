/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ListView.cpp
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
#include "ListView.h"
#include <QMouseEvent>
#include <QDebug>

ListView::ListView(QWidget *parent)
	:QListView(parent)
	, m_currentIndex(QModelIndex())
	, m_pressedIndex(QModelIndex())
{
	setAutoScroll(false);
}

void ListView::focusOutEvent(QFocusEvent *e)
{
	QListView::focusOutEvent(e);
	emit hideThePopup();
	setCurrentIndex(m_pressedIndex);
	qDebug() << "pressedIndex@:"<< m_pressedIndex.row();
}

void ListView::focusInEvent(QFocusEvent *e)
{
	QListView::focusInEvent(e);
	setMouseTracking(false);
	setFocus(Qt::ActiveWindowFocusReason);
	activateWindow();

	m_currentIndex = currentIndex();
	m_pressedIndex = m_currentIndex;
}

bool ListView::viewportEvent(QEvent *event)
{
	QEvent::Type type = event->type();

	if ((QEvent::MouseButtonPress == type) || (QEvent::MouseButtonDblClick == type))
	{
		if (Qt::RightButton == static_cast<QMouseEvent*>(event)->button() ||
			Qt::MidButton == static_cast<QMouseEvent*>(event)->button())
		{
			return true;
		}

		m_currentIndex = currentIndex();
		m_pressedIndex = indexAt(static_cast<QMouseEvent *>(event)->pos());
		if (!m_pressedIndex.isValid())
		{
			m_pressedIndex = m_currentIndex;
		}

		bool ret = QListView::viewportEvent(event);

		qDebug() << "currentIndex@:" << m_currentIndex.row()<<"      pressIndex@:"<< m_pressedIndex.row();
		return ret;
	}
	else if (QEvent::MouseButtonRelease == type)
	{
		QFocusEvent e(QEvent::Close);
		focusOutEvent(&e);
		qDebug() << "MouseButtonRelease";
	}
	
	return QListView::viewportEvent(event);
}

void ListView::mouseMoveEvent(QMouseEvent *event)
{
	QListView::mouseMoveEvent(event);
	setCurrentIndex(m_currentIndex);
}