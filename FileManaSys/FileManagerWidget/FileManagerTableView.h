/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileManagerTableView.h
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

#ifndef FILEMANAGERTABLEVIEW_H
#define FILEMANAGERTABLEVIEW_H
#pragma once

#include <QtWidgets/QTableView>
#include <QAbstractItemModel>
#include <QtWidgets/QAbstractItemDelegate>
#include <QHeaderView>
#include <QPainter>
#include <QDebug>
/*!
 *  @class TableView
 */
class FileManagerTableView : public QTableView
{
    Q_OBJECT

    Q_PROPERTY(QObject *model        WRITE setModel         READ model)
    Q_PROPERTY(QObject *itemDelegate WRITE setItemDelegate  READ itemDelegate)

public:
    FileManagerTableView(QWidget* parent = 0)
        : QTableView(parent)
    {

    }

    FileManagerTableView(const FileManagerTableView& /*other*/)
        :QTableView()
    {

    }

    ~FileManagerTableView()
    {

    }

    /*!
     * 设置数据模型
     * @param[in]  model 数据模型，实际为 QAbstractItemModel*
     */
    void setModel(QObject *model)
    {
        QAbstractItemModel* m = reinterpret_cast<QAbstractItemModel *>(model);
        QTableView::setModel(m);
    }

    /*!
     * 设置绘图代理
     * @param[in]  delegate 数据模型，实际为 QAbstractItemDelegate*
     */
    void setItemDelegate(QObject *delegate)
    {
        QAbstractItemDelegate* d = reinterpret_cast<QAbstractItemDelegate *>(delegate);
        QTableView::setItemDelegate(d);
    }

    /*!
     * 获取绘图代理
     * @return     数据模型，实际为 QAbstractItemDelegate*
     */
    QObject *itemDelegate() const
    {
        return QTableView::itemDelegate();
    }

    /*!
     * 获取数据模型
     * @return     数据模型，实际为 QAbstractItemModel*
     */
    QObject *model() const
    {
        return QTableView::model();
    }


protected:
//    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};


//该类实现自定义的表头,主要是为了在表头中加入CheckBox控件
class HeaderView_Check : public QHeaderView
{
  Q_OBJECT
public:
  explicit HeaderView_Check(Qt::Orientation orientation, QWidget *parent = 0);
private slots:
  void onStateChanged(int state);
signals:
  void stateChanged(Qt::CheckState);
protected:
  void paintSection(QPainter *painter, const QRect rect, int logicalIndex) const;
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  bool event(QEvent *event);
  void paintEvent(QPaintEvent *e)
  {
      qDebug()<<"paintEvent";
      QHeaderView::paintEvent(e);
  }
private:
  bool m_bPressed;
  bool m_bChecked;
  bool m_bTristate;
  bool m_bNoChange;
  bool m_bMoving;
};

#define CHECK_BOX_COLUMN 4
/*********************************************************************************************************
** End of file
*********************************************************************************************************/
#endif // FILEMANAGERTABLEVIEW_H
