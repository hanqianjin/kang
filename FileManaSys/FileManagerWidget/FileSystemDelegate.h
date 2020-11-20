/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileSystemDelegate.h
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

#pragma once

#include <QtWidgets/QStyledItemDelegate>

class FileSystemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    FileSystemDelegate()
    {

    }
    FileSystemDelegate(const FileSystemDelegate&) : QStyledItemDelegate()
    {
    }

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

    void getFileType(const QString& path, QString& fileType) const;

    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const Q_DECL_OVERRIDE;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
