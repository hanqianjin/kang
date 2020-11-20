/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileManagerTableView.cpp
** Latest Version:             V1.0.0
** Latest modified Date:       2019/5/15
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Zhou Yuhan
** Created date:               2019/5/15
** Descriptions:               END
**
*********************************************************************************************************/

#include "FileSystemModel.h"
#include "FileManagerTableView.h"
#include <QMouseEvent>
#include <QDebug>
#include <QDirModel>
#include <QCheckBox>

/**
 * 自定义表头
 *
 *
 *
 */
HeaderView_Check::HeaderView_Check(Qt::Orientation orientation, QWidget *parent)
  : QHeaderView(orientation, parent),
  m_bPressed(false),
  m_bChecked(false),
  m_bTristate(false),
  m_bNoChange(false),
  m_bMoving(false)
{
    // setStretchLastSection(true);
    setHighlightSections(false);//被选部分是否高亮显示（突出），默认是fals
    setMouseTracking(true);//是否捕获鼠标移动事件
    // 响应鼠标
    setSectionsClickable(true);
}


// 槽函数，用于更新复选框状态
void HeaderView_Check::onStateChanged(int state)
{
    if (state == Qt::PartiallyChecked)
    {
        m_bTristate = true;
        m_bNoChange = true;
    }
    else
    {
        m_bNoChange = false;
    }

    m_bChecked = (state != Qt::Unchecked);
    update();
}


void HeaderView_Check::paintSection(QPainter *painter, const QRect rect, int logicalIndex) const
{
    qDebug()<<"\n\n\n\n\n\n\n\n\n5555555555555555555555555555555555555"<<logicalIndex;
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    qDebug()<<"\n\n\n\n\n\n\n\n\nrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr"<<logicalIndex;
    if (logicalIndex == CHECK_BOX_COLUMN)
    {
        QStyleOptionButton option;
        option.initFrom(this);
        if (m_bChecked)
            option.state |= QStyle::State_Sunken;

        if (m_bTristate && m_bNoChange)
            option.state |= QStyle::State_NoChange;
        else
            option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off;
        if (testAttribute(Qt::WA_Hover) && underMouse())
        {
            if (m_bMoving)
                option.state |= QStyle::State_MouseOver;
            else
                option.state &= ~QStyle::State_MouseOver;
        }
        QCheckBox checkBox;
        option.iconSize = QSize(20, 20);
        option.rect = rect;
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter , &checkBox);
        //style()->drawItemPixmap(painter, rect, Qt::AlignCenter, QPixmap(":/ images/checkBoxChecked"));
        //style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
    }
}

void HeaderView_Check::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent";
    int nColumn = logicalIndexAt(event->pos());
    if ((event->buttons() & Qt::LeftButton) && (nColumn == CHECK_BOX_COLUMN))
    {
        m_bPressed = true;
    }
    else
    {
        QHeaderView::mousePressEvent(event);
    }
}
// 鼠标从表头释放，发送信号，更新model数据
void HeaderView_Check::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_bPressed)
    {
        if (m_bTristate && m_bNoChange)
        {
            m_bChecked = true;
            m_bNoChange = false;
        }
        else
        {
            m_bChecked = !m_bChecked;
        }
        update();
        Qt::CheckState state;
        state = m_bChecked ? Qt::Checked : Qt::Unchecked;
        emit stateChanged(state);
    }
    else
    {
        QHeaderView::mouseReleaseEvent(event);
    }
    m_bPressed = false;
}

// 鼠标滑过、离开，更新复选框状态
bool HeaderView_Check::event(QEvent *event)
{
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
    {
        QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
        int nColumn = logicalIndexAt(pEvent->x());
        if (nColumn == CHECK_BOX_COLUMN)
        {
            m_bMoving = (event->type() == QEvent::Enter);
            update();
            return true;
        }
    }
    return QHeaderView::event(event);
}

//void FileManagerTableView::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    // 文件管理界面不响应双击
//    Q_UNUSED(event)
//    return QTableView::mouseDoubleClickEvent(event);
//}

void FileManagerTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    FileSystemModel* fileModel = qobject_cast<FileSystemModel*>(model());
    fileModel->setCurrentIndex(current.row());
}
