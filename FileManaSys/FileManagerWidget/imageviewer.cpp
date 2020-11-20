#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPainter>
#include <QDir>

ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewer),
    m_moveFlag(false),
    m_pen(QPen(QColor(Qt::black), 1)),
    SCALED_MAX(160),
    SCALED_MIN(80),
    SCALED_INTERVAL(20)
{
    ui->setupUi(this);

    ui->m_scaledSlider->setRange(SCALED_MIN, SCALED_MAX);
    ui->m_scaledSlider->setValue(SCALED_MIN);
    ui->m_imageNameLabel->setText("");
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->m_scaledSlider->setVisible(false);

    m_imageName[FilePath] = "";
    m_imageName[FileName] = "";

    connect(ui->m_scaledSlider, &QSlider::valueChanged, this, &ImageViewer::onScaledChanged);
    connect(ui->m_closeImageButton, &QPushButton::clicked, this, &ImageViewer::onImageViewerClosed);
    connect(ui->m_preButton, &QPushButton::clicked, this, &ImageViewer::navigationButtonClicked);
    connect(ui->m_nextButton, &QPushButton::clicked, this, &ImageViewer::navigationButtonClicked);
    connect(ui->m_zoomInButton, &QPushButton::clicked, this, &ImageViewer::zoomButtonClicked);
    connect(ui->m_zoomOutButton, &QPushButton::clicked, this, &ImageViewer::zoomButtonClicked);
}

ImageViewer::~ImageViewer()
{
    delete ui;
    m_imageName[0].clear();
    m_imageName[1].clear();
    m_imagesName.clear();
}

void ImageViewer::initImageViewer(const QString &path, const QString &name, const QList<QString> &names)
{
    m_imageName[FilePath] = path;
    m_imageName[FileName] = name;
    m_imagesName = names;

    ui->m_scaledSlider->setValue(SCALED_MIN);
    ui->m_scaledlabel->setText(QString("%1 %").arg(SCALED_MIN));

    showImage(SCALED_MIN / 100);
    setNavigationButtonEnable();

    this->setVisible(true);
}

void ImageViewer::setPen(const QPen &pen)
{
    m_pen = pen;
}

void ImageViewer::mousePressEvent(QMouseEvent *event)
{
    //判断鼠标按下时，光标所在位置是否在可拖动范围内，若能拖动，则保存当前光标位置和滑动条的值
    m_moveFlag = judgeMoveEnable(event->pos());
    if(m_moveFlag)
    {
        m_mousePressPos = event->pos();
        m_mousePressScaledValue.setX(ui->scrollArea->horizontalScrollBar()->value());
        m_mousePressScaledValue.setY(ui->scrollArea->verticalScrollBar()->value());
    }
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event)
{
    //判光标所在位置是否在可拖动范围内，且当前处于可拖动状态时，计算图片显示位置
    //否则，设置为不可拖动状态
    if(judgeMoveEnable(event->pos()) && m_moveFlag)
    {
        double ratioX = double(event->pos().x() - m_mousePressPos.x()) / ui->m_imageLabel->width();
        double ratioY = double(event->pos().y() - m_mousePressPos.y()) / ui->m_imageLabel->height();
        int barX = m_mousePressScaledValue.x() - ui->scrollArea->horizontalScrollBar()->maximum() * ratioX;
        int barY = m_mousePressScaledValue.y() - ui->scrollArea->verticalScrollBar()->maximum() * ratioY;
        ui->scrollArea->horizontalScrollBar()->setValue(barX);
        ui->scrollArea->verticalScrollBar()->setValue(barY);
    }
    else
    {
        m_moveFlag = false;
    }
}

void ImageViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(m_pen);
    painter.drawLine(ui->scrollArea->x() - 1, 0, ui->scrollArea->x() - 1, this->height());
    painter.drawLine(ui->scrollArea->x() + ui->scrollArea->width(), 0, ui->scrollArea->x() + ui->scrollArea->width(), this->height());
}

void ImageViewer::onScaledChanged(int value)
{
    ui->m_scaledlabel->setText(QString("%1 %").arg(value));
    double ratio = double(value) / 100;
    showImage(ratio);
}

void ImageViewer::onImageViewerClosed()
{
    if(this->isVisible())
    {
        this->setVisible(false);
    }
}

void ImageViewer::navigationButtonClicked()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    int index = m_imagesName.indexOf(m_imageName[FileName]);

    if(btn == ui->m_preButton)
    {
        m_imageName[FileName] = m_imagesName.at(index - 1);
    }
    else if(btn == ui->m_nextButton)
    {
        m_imageName[FileName] = m_imagesName.at(index + 1);
    }

    ui->m_scaledSlider->setValue(SCALED_MIN);
    ui->m_scaledlabel->setText(QString("%1 %").arg(SCALED_MIN));

    showImage(SCALED_MIN / 100);
    setNavigationButtonEnable();
}

void ImageViewer::zoomButtonClicked()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());

    QString valueStr = ui->m_scaledlabel->text();
    valueStr.chop(2);
    int value = valueStr.toInt();

    if(btn == ui->m_zoomInButton && SCALED_MAX > value)
    {
        value += SCALED_INTERVAL;
    }
    else if(btn == ui->m_zoomOutButton && SCALED_MIN < value)
    {
        value -= SCALED_INTERVAL;
    }

    ui->m_scaledlabel->setText(QString("%1 %").arg(value));
    double ratio = double(value) / 100;
    showImage(ratio);
}

bool ImageViewer::judgeMoveEnable(const QPoint &point)
{
    return (point.x() > ui->scrollArea->x()
            && point.x() < (ui->scrollArea->x() + ui->scrollArea->width())
            && point.y() > ui->scrollArea->y()
            && point.y() < (ui->scrollArea->y() + ui->scrollArea->height()));
}

void ImageViewer::setNavigationButtonEnable()
{
    ui->m_preButton->setEnabled(!(m_imageName[FileName] == m_imagesName.first()));
    ui->m_nextButton->setEnabled(!(m_imageName[FileName] == m_imagesName.last()));
}

void ImageViewer::showImage(double ratio)
{
    QImage image(QString("%1/%2").arg(m_imageName[FilePath]).arg(m_imageName[FileName]));
    int width = image.width();
    int height = image.height();
    QImage scaledImage = image.scaled(width * ratio, height * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->m_imageLabel->setPixmap(QPixmap::fromImage(scaledImage));
    ui->m_imageNameLabel->setText(m_imageName[FileName]);
}
