/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileSystemModel.cpp
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
#include <QDebug>

QVariant FileSystemModel::data( const  QModelIndex &index,  int  role) const
   {
    if (!index.isValid() || index.model() != this)
        return QVariant();

    if ( Qt::TextAlignmentRole == role && index.column() == 1 )
        return  Qt::AlignCenter;

    if (role == Qt::CheckStateRole && index.column() == 4)
       {
            if (rowCheckStateMap.contains(index.row()))
                return rowCheckStateMap[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
            return Qt::Unchecked;
       }

    if(index.column() < 4)
        return  QFileSystemModel::data(index, role);
    return QVariant();
   }

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

//    if (index.column() == 4 || index.column() == 0 || index.column() == 3)
    return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;

//    return  QFileSystemModel::flags(index);
}


bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
           return false;
    if (role == Qt::CheckStateRole && index.column() == 4)
    {
        if (value == Qt::Checked)
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            checkModelindexList.append(index);
            fileCheckNum++;
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
            checkModelindexList.removeOne(index);
            if(fileCheckNum) fileCheckNum--;
        }

        emit selectfileChange(fileCheckNum);
        emit dataChanged(index,index);
    }
    return QFileSystemModel::setData(index,value,role);
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug()<<section<<orientation<<role;
    if(section == 4)
    {
        switch (role)
        {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
            if (orientation == Qt::Horizontal)
            {
                return QString(tr(" "));
            }
        default:
            return QVariant();
        }
    }
    else
        return QFileSystemModel::headerData(section,orientation,role);

}

bool FileSystemModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent,column,column+count-1);
    fileColumn = column + count;
    endInsertColumns();

    return true;
}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return fileColumn;
}

bool FileSystemModel::selectAllCheckMap(const QString &currentpath)
{
    fileCheckNum = 0;
    QString path = currentpath;
    QFileInfo info(path);
    if (info.isFile())
    {
        path = path.left(path.lastIndexOf("/"));
    }
    QModelIndex parent = QFileSystemModel::index(path);
    int rowCount = QFileSystemModel::rowCount(parent);
    for (int row = 0; row < rowCount; ++row)
    {
        QModelIndex index = parent.child(row, 4);
        setData(index, Qt::Checked, Qt::CheckStateRole);
    }
    return true;
}

bool FileSystemModel::IsCurrentSelectAll(const QString &currentPath)
{
    QModelIndex parentIndex = index(currentPath);
    int count = rowCount(parentIndex);
    int num = getFileCheckNum();
    if (count == num)
    {
        return true;
    }
    return false;
}

QModelIndex FileSystemModel::getCheckIndex(long Num)
{
    if(Num < 0 || checkModelindexList.size() <= Num)
       return QModelIndex();

    return checkModelindexList.at(Num);
}

int FileSystemModel::currentIndex()
{
    return m_currentIndex;
}

void FileSystemModel::setCurrentIndex(int index)
{
    m_currentIndex = index;
    emit layoutChanged();
}
