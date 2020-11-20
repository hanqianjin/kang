/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileSystemModel.h
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

#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>

class FileSystemModel : public QFileSystemModel
{
    Q_OBJECT
    //Q_ENABLE_COPY(FileSystemModel)

public:
    FileSystemModel(QObject* parent = 0)
        : QFileSystemModel(parent), m_currentIndex(0)
    {
        fileColumn = 4;
        fileCheckNum = 0;
        rowCheckStateMap.clear();
        checkModelindexList.clear();
    }

    QVariant data( const  QModelIndex &index,  int  role = Qt::DisplayRole) const;


    Qt::ItemFlags flags(const QModelIndex &index) const;


    bool setData(const QModelIndex &index, const QVariant &value, int role);

    //重写获得头函数
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    //重写列插入函数
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    //重写获得列数函数 用于增加一列
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //清空选择列表
    bool clearCheckMap(void)
    {
        fileCheckNum = 0;
        rowCheckStateMap.clear();
        emit dataChanged(QModelIndex(),QModelIndex());
        return true;
    }

    //清空索引列表
    bool clearCheckIndexList(void)
    {
        checkModelindexList.clear();
        fileCheckNum = 0;
        emit selectfileChange(fileCheckNum);
        return true;
    }

    // 将所有行全部选中
    bool selectAllCheckMap(const QString &currentpath);

    // 是否当前全部选中
    bool IsCurrentSelectAll(const QString &currentPath);

    //获得指定项文件
    QModelIndex getCheckIndex(long Num);

    //获得当前选择的项数
    long getFileCheckNum(void)
    { return fileCheckNum;}

    void refreshModel()
    {
        beginInsertRows(QModelIndex(),0,0);
        endInsertRows();
    }

    /**
    * @brief:设置是否显示选择功能
    * @param[in]:
    * @return:
    * @note:默认有选择框
    */
    void setSelect(bool isSelect)
    {
        if(isSelect)
        {
            fileColumn = 4;
        }
        else
        {
            fileColumn = 3;
        }
    }
    int currentIndex();
    void setCurrentIndex(int index);
signals:
    void selectfileChange(const long Num);

private:
    QMap<int, Qt::CheckState> rowCheckStateMap;
    QList<QModelIndex> checkModelindexList;
    int fileColumn;
    long fileCheckNum;
    int m_currentIndex;
};
#endif // FILESYSTEMMODEL_H
