/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  imageviewer.h
** Latest Version:             V1.0.0
** Latest modified Date:       2020/4/30
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Gao Qiang
** Created date:               2020/4/30
** Descriptions:               END
**
*********************************************************************************************************/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPen>

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPen pen READ pen WRITE setPen)

    enum Image
    {
        FilePath = 0,
        FileName,
    };

public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();
    /**
     * @brief initImageViewer: 初始化并显示图片浏览器，保存相关数据
     * @param path: 当前目录路径
     * @param name: 当前显示的文件名
     * @param names: 当前目录下所有文件的文件名
     */
    void initImageViewer(const QString &path, const QString &name, const QList<QString> &names);

    QPen pen() const { return m_pen; }
    void setPen(const QPen &pen);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void onScaledChanged(int value);
    /**
     * @brief onImageViewerClosed: 关闭图片浏览器
     */
    void onImageViewerClosed();
    /**
     * @brief navigationButtonClicked: 导航按钮槽函数
     */
    void navigationButtonClicked();
    /**
     * @brief zoomButtonClicked: 缩放按钮槽函数
     */
    void zoomButtonClicked();

private:
    /**
     * @brief judgeMoveEnable: 根据光标指针位置判断图片是否能被拖动
     * @param point: 光标指针坐标
     * @return : true: 能拖动， false: 不能拖动
     */
    bool judgeMoveEnable(const QPoint &point);
    /**
     * @brief setNavigationButtonEnable: 设置导航按钮使能
     */
    void setNavigationButtonEnable();
    /**
     * @brief showImage: 根据缩放比率显示图片
     * @param ratio: 缩放比率
     */
    void showImage(double ratio);

private:
    Ui::ImageViewer *ui;
    QString m_imageName[2];//[0]: 当前目录路径, [1]: 当前显示的文件名
    QPoint m_mousePressPos;//鼠标按下时的坐标
    QPoint m_mousePressScaledValue;//鼠标按下时滑动条的值, x: 水平滑动条, y: 垂直滑动条
    bool m_moveFlag;//保存能否被拖动的状态， true: 能拖动, false: 不能拖动
    QPen m_pen;
    QList<QString> m_imagesName;//当前目录下所有文件的文件名

    const double SCALED_MAX;//最大缩放系数
    const double SCALED_MIN;//最小缩放系数
    const double SCALED_INTERVAL;//缩放间隔
};

#endif // IMAGEVIEWER_H
