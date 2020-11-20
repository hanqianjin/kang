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

#include "HeaderWidget.h"
#include <QPainter>
#include <QMouseEvent>

HeaderWidget::HeaderWidget(QWidget *parent) :
    QWidget(parent)
  , m_sortType(NameUp)
{
    setFixedSize(QSize(760, 35));
    m_nameRect = rect().adjusted(0, 0, -460, 0);
    m_fileSizeRect = rect().adjusted(300, 0, -360, 0);
    m_fileTypeRect = rect().adjusted(400, 0, -260, 0);
    m_dateRect = rect().adjusted(500, 0, -60, 0);
    m_selectAllRect = rect().adjusted(700, 0, 0, 0);
}

void HeaderWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/images/filewidgetimage/header.png"));
    //painter.fillRect(rect(), QColor(211, 215, 207));
    QPen pen;
    pen.setColor(QColor("black"));
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setStyle(Qt::SolidLine);
    QFont font;
    font.setFamily("Arial Regular");
    font.setPixelSize(15);
    font.setBold(true);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(m_nameRect.adjusted(40, 0 , 0, 0), Qt::AlignVCenter | Qt::AlignLeft, tr("Filename"));
    painter.drawText(m_fileSizeRect.adjusted(2, 0 , 0, 0), Qt::AlignVCenter | Qt::AlignLeft, tr("Size"));
    painter.drawText(m_fileTypeRect.adjusted(2, 0 , 0, 0), Qt::AlignVCenter | Qt::AlignLeft, tr("Type"));
    painter.drawText(m_dateRect.adjusted(2, 0 , 0, 0), Qt::AlignVCenter | Qt::AlignLeft, tr("Date modified"));

    QFontMetrics fm(font);
    switch (m_sortType)
    {
        case NameUp:
            painter.drawPixmap(40 + 20 + fm.width(tr("Filename")), 13, QPixmap(":/images/filewidgetimage/up.png"));
            break;
        case NameDown:
            painter.drawPixmap(40 + 20 + fm.width(tr("Filename")), 13, QPixmap(":/images/filewidgetimage/down.png"));
            break;
        case SizeUp:
            painter.drawPixmap(300 + 12 + fm.width(tr("Size")), 13, QPixmap(":/images/filewidgetimage/up.png"));
            break;
        case SizeDown:
            painter.drawPixmap(300 + 12 + fm.width(tr("Size")), 13, QPixmap(":/images/filewidgetimage/down.png"));
            break;
        case TypeUp:
            painter.drawPixmap(400 + 12 + fm.width(tr("Type")), 13, QPixmap(":/images/filewidgetimage/up.png"));
            break;
        case TypeDown:
            painter.drawPixmap(400 + 12 + fm.width(tr("Type")), 13, QPixmap(":/images/filewidgetimage/down.png"));
            break;
        case DateUp:
            painter.drawPixmap(500 + 20 + fm.width(tr("Date modified")), 13, QPixmap(":/images/filewidgetimage/up.png"));
            break;
        case DateDown:
            painter.drawPixmap(500 + 20 + fm.width(tr("Date modified")), 13, QPixmap(":/images/filewidgetimage/down.png"));
            break;
        default:
            break;
    }
}

void HeaderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_nameRect.contains(event->pos()))
    {
        m_sortType = (m_sortType == NameUp) ? NameDown : NameUp;
    }
    else if (m_fileSizeRect.contains(event->pos()))
    {
        m_sortType = (m_sortType == SizeUp) ? SizeDown : SizeUp;
    }
    else if (m_fileTypeRect.contains(event->pos()))
    {
        m_sortType = (m_sortType == TypeUp) ? TypeDown : TypeUp;
    }
    else if (m_dateRect.contains(event->pos()))
    {
        m_sortType = (m_sortType == DateUp) ? DateDown : DateUp;
    }
    emit clicked(m_sortType);
    update();
}

void HeaderWidget::resetSort()
{
    m_sortType = NameUp;
    emit clicked(m_sortType);
    update();
}
