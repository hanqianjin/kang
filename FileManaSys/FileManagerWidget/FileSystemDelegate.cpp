/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileSystemDelegate.cpp
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

#include "FileSystemDelegate.h"
#include "FileSystemModel.h"
#include <QDebug>
#include <QPainter>
#include <QTableView>
#include <QFileInfo>
#include <QDateTime>

void FileSystemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QWidget* w = const_cast<QWidget *>(option.widget);
    QTableView* view = static_cast<QTableView*>(w);
    FileSystemModel* model = qobject_cast<FileSystemModel*>(view->model());
    int row = view->selectionModel()->currentIndex().row();
    if (row != model->currentIndex())
    {
        //若文件增加会造成selctionModel和当前选择项不匹配的情况，此时要手动设置两者一致否则会出现两条蓝色标签
        row = model->currentIndex();
        view->selectionModel()->setCurrentIndex(model->index(row, 0, QModelIndex()), QItemSelectionModel::SelectCurrent);
    }
    int checked = Qt::Unchecked;
    if (5 == model->columnCount(index))
    {
        checked = model->data(index.sibling(index.row(), 4), Qt::CheckStateRole).toInt();
    }
    //bool ok = false;

    QPen pen;
    pen.setColor(QColor("black"));
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setStyle(Qt::SolidLine);
    QFont font;
    font.setFamily("Arial Regular");
    font.setPixelSize(15);
    font.setBold(false);

    /*if (option.state & (QStyle::State_On | QStyle::State_Sunken | QStyle::State_Selected))
    {
        ok = true;
    }*/

    if (index.row() % 2 == 0)
    {
        painter->fillRect(option.rect.adjusted(0, 0, 0, 0), QColor(250, 250, 250));
    }
    else
    {
        painter->fillRect(option.rect.adjusted(0, 0, 0, 0), QColor(240, 240, 240));
    }
    if (model->currentIndex() == index.row())
    {
        painter->fillRect(option.rect.adjusted(0, 0, 0, 0), QColor(255, 181, 0));
    }

    if (0 == index.column())
    {
        QString path = index.data().toString();
        QRect pixmapRect = option.rect.adjusted(10, 10, 0, -8);
        pixmapRect.setWidth(18);
        pixmapRect.setHeight(18);
        if (model->fileInfo(index).isDir())
        {
            painter->drawPixmap(pixmapRect, QPixmap(":/images/filewidgetimage/folder.png"));
        }
        else
        {
            painter->drawPixmap(pixmapRect, QPixmap(":/images/filewidgetimage/file.png"));
        }

        painter->setPen(pen);
        painter->setFont(font);
        QFontMetrics fm(font);
        QString strText = fm.elidedText(index.data().toString(), Qt::ElideRight, 250);
        painter->drawText(option.rect.adjusted(40, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, strText);
    }
    else if (1 == index.column())
    {
        QString strSize =index.data().toString();
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, strSize);
    }
    else if (2 == index.column())
    {
        QString path = model->fileInfo(index).fileName();
        QString fileType = index.data().toString();
        if (model->fileInfo(index).isDir())
        {
            fileType = "Folder";
        }
        else
        {
            getFileType(path, fileType);
        }
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft,fileType);
    }
    else if (3 == index.column())
    {
        QDateTime dateTime = model->fileInfo(index).lastModified();
        QString strBuffer;
        strBuffer = dateTime.toString("yyyy/MM/dd  A  hh:mm:ss");
        strBuffer.replace("上午","AM");
        strBuffer.replace("下午","PM");
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft, strBuffer);
    }
    else if (4 == index.column())
    {
        QRect checkRect = option.rect;
        checkRect.adjust(10, 7, 0, 0);
        checkRect.setWidth(20);
        checkRect.setHeight(20);

        if (checked == Qt::Checked)
        {
            painter->drawPixmap(checkRect, QPixmap(":/images/filewidgetimage/check.png"));
        }
        else
        {
            painter->drawPixmap(checkRect, QPixmap(":/images/filewidgetimage/uncheck.png"));
        }
    }
}


void FileSystemDelegate::getFileType(const QString& path, QString& fileType) const
{
    if (path.endsWith("state") || path.endsWith("STATE"))
    {
        fileType = "STATE";
    }
    else if (path.endsWith("trace") || path.endsWith("TRACE"))
    {
        fileType = "TRACE";
    }
    else if (path.endsWith("csv") || path.endsWith("CSV"))
    {
        fileType = "CSV";
    }
    else if (path.endsWith("png") || path.endsWith("PNG"))
    {
        fileType = "PNG";
    }
    else if (path.endsWith("jpg") || path.endsWith("JPG"))
    {
        fileType = "JPG";
    }
    else if (path.endsWith("meas") || path.endsWith("MEAS"))
    {
        fileType = "MEAS";
    }
    else if (path.endsWith("dat") || path.endsWith("DAT"))
    {
        fileType = "DAT";
    }
    else
    {
        fileType = "File";
    }
}

QSize FileSystemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

bool FileSystemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.isValid() && 4 == index.column())
    {
        return false;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
