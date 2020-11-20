/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileManagerWidget.cpp
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

#include "FileManagerWidget.h"
#include "ui_FileManagerWidget.h"
#include "CopyFileThread.h"
#include "ProgressBarDlg.h"
#include "../keyBoard/englishkeyboard.h"
#include "../hotplug/hotplughandler.h"
#include "unistd.h"
#include <QScrollBar>
#include <QScroller>

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::FileManagerWidget)
  , m_model(new FileSystemModel)
  , m_directory(new QDir)
  , m_stateBox(NULL)
  , m_firstTimeShow(true)
  , m_isSaveStateBox(false)
  , m_isAutoSave(false)
  , m_imageViewer(NULL)
  , m_imageSelectedName(QString(""))
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    move(QPoint(1,1));

    initWarningBox();
    initSignalAndSlot();
    initModel();
    initWidget();
}

FileManagerWidget::~FileManagerWidget()
{
    blockSignals(true);
    delete ui;
    if (m_model)
    {
        delete m_model;
        m_model = NULL;
    }
    if (m_directory)
    {
        delete m_directory;
        m_directory = NULL;
    }
}

void FileManagerWidget::initWidget()
{
    ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);//只能选择一项
    ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置每次选择一行
    ui->m_tableView->setShowGrid(false);//隐藏表格线
    ui->m_tableView->verticalHeader()->hide();//隐藏垂直表头
    ui->m_tableView->horizontalHeader()->hide();
    ui->m_tableView->horizontalHeader()->resizeSection(0, 300); //设置表头第1列的宽度为300
    ui->m_tableView->horizontalHeader()->resizeSection(1, 100); //设置表头第2列的宽度为100
    ui->m_tableView->horizontalHeader()->resizeSection(2, 100); //设置表头第3列的宽度为100
    ui->m_tableView->horizontalHeader()->resizeSection(3, 220); //设置表头第4列的宽度为200
    ui->m_tableView->horizontalHeader()->resizeSection(4, 38); //设置表头第5列的宽度为50
    ui->m_tableView->verticalHeader()->setDefaultSectionSize(35);
    ui->m_tableView->horizontalHeader()->setSectionsClickable(true);//允许鼠标点击列头
    ui->m_tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->m_tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->m_tableView->setItemDelegate(new FileSystemDelegate);
    ui->m_customBar->setRange(0, 0);
    setScrollerProperty();

    setUsbEnable(HotplugManager::instance()->isExistDev(Media_Type_USB));
    setSdEnable(HotplugManager::instance()->isExistDev(Media_Type_SD));
    setFilters();

    ui->m_nameButton->setText(tr("File Name"));
    QStringList items;
    items << TYPE_STATE << TYPE_STATE_AND_DATA /*<< TYPE_SCREEN_IMAGE <<TYPE_MEASURE_DATA << TYPE_LIMIT*/;
    ui->comboBox->addItems(items);
    ui->comboBox->setCurrentIndex(0);

    //ui->m_typeButton->setText(tr(TYPE_STATE));
    m_moduleSuffixMap.insert(MODULE_TYPE_NONE, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_RF, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_MODU, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_OTA, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_PVT, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_CAT, "trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_CCDF,"trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_AUTO,"trace");
    m_moduleSuffixMap.insert(MODULE_TYPE_BEAM,"trace");

    //image viewer
    m_imageViewer = new ImageViewer(this);
    m_imageViewer->move(this->x(), 45);
    m_imageViewer->setVisible(false);
}

void FileManagerWidget::initModel()
{

    m_copyList.clear();
    //m_directory->setPath(QDir::currentPath());  //shiyan
    QDir topDir(getTopDir());

    if (!topDir.exists())
    {
        if (!topDir.mkpath(getTopDir()))
        {
            return;
        }
    }
    m_directory->setPath(getTopDir());
    m_currentFilePath = m_directory->absolutePath();
    m_model->setRootPath(m_currentFilePath);
    setDevice(Device_Local);
    onDirectoryLoaded();

    m_model->setReadOnly(false);  //可编辑
    m_model->sort(0, Qt::AscendingOrder);  //文件排序
    m_model->setNameFilterDisables(false);  //显示所有文件包括除了"."。
    //setExtFilter("ALL");
    m_model->insertColumns(m_model->columnCount(), 1);

    ui->m_tableView->setModel(m_model);
    ui->m_tableView->setRootIndex(m_model->index(m_currentFilePath));
    ui->m_tableView->setCurrentIndex(QModelIndex());

    setCopyAndDeleteEnable(false);
    setRenameAndLoadEnable(false);
    setPasteEnable(false);
}

void FileManagerWidget::initSignalAndSlot()
{
    connect(ui->m_customBar, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->m_tableView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(ui->m_tableView->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(onRangeChanged(int, int)));
    connect(ui->m_tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTableViewClicked(QModelIndex)));
    connect(ui->m_tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableViewDoubleClicked(QModelIndex)));

    connect(ui->m_headerWidget, &HeaderWidget::clicked, this, &FileManagerWidget::onFileHeaderClicked);
    connect(this, &FileManagerWidget::resetHeader, ui->m_headerWidget, &HeaderWidget::resetSort);
    connect(ui->m_checkAllBox, &QCheckBox::clicked, this, &FileManagerWidget::selectAll);

    connect(ui->m_backButton, &QPushButton::clicked, this, &FileManagerWidget::onBackButtonClicked);
    connect(ui->m_forwardButton, &QPushButton::clicked, this, &FileManagerWidget::onForwardButtonClicked);
    connect(ui->m_copyButton, &QPushButton::clicked, this, &FileManagerWidget::onCopyButtonClicked);
    connect(ui->m_pasteButton, &QPushButton::clicked, this, &FileManagerWidget::onPasteButtonClicked);
    connect(ui->m_deleteButton, &QPushButton::clicked, this, &FileManagerWidget::onDeleteButtonClicked);
    connect(ui->m_newFolderButton, &QPushButton::clicked, this, &FileManagerWidget::onNewfolderButtonClicked);
    connect(ui->m_renameButton, &QPushButton::clicked, this, &FileManagerWidget::onRenameButtonClicked);
    connect(ui->m_loadButton, &QPushButton::clicked, this, &FileManagerWidget::onLoadButtonClicked);
    connect(ui->m_localButton, &QPushButton::clicked, this, &FileManagerWidget::onLocalButtonClicked);
    connect(ui->m_usbButton, &QPushButton::clicked, this, &FileManagerWidget::onUsbButtonClicked);
    connect(ui->m_sdButton, &QPushButton::clicked, this, &FileManagerWidget::onSdButtonClicked);
    connect(ui->m_nameButton, &QPushButton::clicked, this, &FileManagerWidget::onNameButtonClicked);
    connect(ui->m_okButton, &QPushButton::clicked, this, &FileManagerWidget::onOkbuttonClicked);
    connect(ui->m_cancelButton, &QPushButton::clicked, this, &FileManagerWidget::onCancelButtonClicked);
    connect(ui->m_closeButton, &QPushButton::clicked, this, &FileManagerWidget::onCancelButtonClicked);
    connect(HotplugManager::instance(), &HotplugManager::sigDeviceStatusUpdated, this, &FileManagerWidget::onDeviceStatusUpdated);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));

    connect(m_stateBox, &StateBox::stateboxClosed, this, &FileManagerWidget::onStateBoxClosed);
}

void FileManagerWidget::initWarningBox()
{
    if (NULL == m_stateBox)
    {
        m_stateBox = new StateBox(this);
    }
    m_stateBox->close();
}

void FileManagerWidget::onValueChanged(int value)
{
    ui->m_tableView->verticalScrollBar()->setValue(value);
    ui->m_customBar->setValue(value);
}

void FileManagerWidget::onRangeChanged(int min, int max)
{
    ui->m_customBar->setRange(min, max);
}

void FileManagerWidget::onBackButtonClicked()
{
    cd_up();
}

void FileManagerWidget::onForwardButtonClicked()
{
    QModelIndex index = ui->m_tableView->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    if (m_model->fileInfo(index).isDir())
    {
        cdTheFolder(index);
    }
}

bool FileManagerWidget::cd_up()
{   
    if (getTopDir() == m_directory->absolutePath() ||
        USB_TOP_DIR == m_directory->absolutePath() ||
        SD_TOP_DIR == m_directory->absolutePath())
    {
        return false;
    }

    if (m_directory->cdUp())
    {
        m_currentFilePath = m_directory->absolutePath();
        m_model->setRootPath(m_currentFilePath);
        QModelIndex absoluteindex = m_model->index(m_currentFilePath);

        if (absoluteindex.isValid())
        {
            ui->m_tableView->setRootIndex(absoluteindex);
            onDirectoryLoaded();
            clearCheckIndex();
            if (m_copyList.size() > 0)
                setPasteEnable(true);
            else
                setPasteEnable(false);
            return true;
        }
    }
    return false;
}

bool FileManagerWidget::cdTheFolder(QModelIndex index)
{
    if (!index.isValid())
    {
        return false;
    }

    //点击前5列进入文件夹
    if (index.column() < 5)
    {
        //当点击在文件夹上时，进入该文件夹
        if (m_model->fileInfo(index).isDir())
        {
            m_directory->cd(m_model->filePath(index));
            m_currentFilePath = m_directory->absolutePath();
            m_model->setRootPath(m_currentFilePath);
            QModelIndex absoluteindex = m_model->index(m_currentFilePath);
            if (absoluteindex.isValid())
            {
                ui->m_tableView->setRootIndex(absoluteindex);
                onDirectoryLoaded();
                clearCheckIndex();
                if (m_copyList.size() > 0)
                    setPasteEnable(true);
                else
                    setPasteEnable(false);
                return true;
            }
        }
    }
    return false;
}

bool FileManagerWidget::cdTheFolder(QString targetPath)
{
    if (targetPath.isEmpty() || !QFile::exists(targetPath))
    {
        targetPath = getTopDir();
    }

    m_directory->cd(targetPath);
    m_currentFilePath = m_directory->absolutePath();
    m_model->setRootPath(m_currentFilePath);

    QModelIndex absoluteindex = m_model->index(m_currentFilePath);
    if (absoluteindex.isValid())
    {
        ui->m_tableView->setRootIndex(absoluteindex);
        onDirectoryLoaded();
        clearCheckIndex();
        if (m_copyList.size() > 0)
            setPasteEnable(true);
        else
            setPasteEnable(false);
        return true;
    }
    return false;
}

void FileManagerWidget::onFileHeaderClicked(int sortType)
{
    int column = (sortType-1)/2;
    Qt::SortOrder order = ((sortType-1)%2 == 0) ? Qt::AscendingOrder : Qt::DescendingOrder;
    ui->m_tableView->sortByColumn(column, order);
    ui->m_tableView->setCurrentIndex(QModelIndex());

    if (!m_selectName.isEmpty())
    {
        // 清除选中， 设置选中
        m_model->clearCheckMap();
        for (int i = 0; i < m_selectName.count(); ++i)
        {
            // 设置checked
            QModelIndex index = m_model->index(m_selectName.at(i));
            m_model->setData(index.sibling(index.row(), CHECK_BOX_COLUMN), Qt::Checked, Qt::CheckStateRole);
        }
        ui->m_tableView->repaint();
    }
}

void FileManagerWidget::onTableViewClicked(QModelIndex index)
{
    if (4 == index.column())
    {
        int checked = m_model->data(index, Qt::CheckStateRole).toInt();
        int row = index.row();
        QModelIndex parentIndex = index.parent();
        QModelIndex indexAA = m_model->index(row, 0, parentIndex);
        if (checked == Qt::Unchecked)
        {
            if (!m_selectName.contains(m_model->filePath(indexAA)))
            {
                m_selectName.append(m_model->filePath(indexAA));
            }
        }
        else if (checked == Qt::Checked)
        {
            m_selectName.removeAll(m_model->filePath(indexAA));
        }

        m_model->setData(index, (Qt::Checked == checked ? Qt::Unchecked : Qt::Checked), Qt::CheckStateRole);

        QString currentPath = m_directory->absolutePath();

        if (m_model->getFileCheckNum() > 0)
        {
            setCopyAndDeleteEnable(true);
        }
        else
        {
            setCopyAndDeleteEnable(false);
        }

        if (m_model->getFileCheckNum() == 1)
        {
            setRenameAndLoadEnable(true);
        }
        else
        {
            setRenameAndLoadEnable(false);
        }

        if (m_model->IsCurrentSelectAll(currentPath))
        {
            ui->m_checkAllBox->setChecked(true);
        }
        else
        {
            ui->m_checkAllBox->setChecked(false);
        }

        ui->m_tableView->viewport()->repaint();
    }
    else if(m_model->fileInfo(index).suffix() == "png")
    {
        //判断图片是否被选中
        //若未选中，则保存图片名后返回
        //若选中，则则打开图片浏览器
        if(m_model->fileInfo(index).fileName() != m_imageSelectedName)
        {
            m_imageSelectedName = m_model->fileInfo(index).fileName();
            return ;
        }
        qDebug() << m_currentFilePath;
        QStringList filters;
        filters << QString("*.png") << QString("*.PNG");
        QDir dir(m_currentFilePath);
        dir.setNameFilters(filters);
        m_imageViewer->initImageViewer(m_currentFilePath, m_model->fileInfo(index).fileName(), dir.entryList());
    }
}

void FileManagerWidget::onTableViewDoubleClicked(QModelIndex index)
{
    if (0 == index.column())
    {
        QModelIndex index = ui->m_tableView->currentIndex();
        if (!index.isValid())
        {
            return;
        }
        if (m_model->fileInfo(index).isDir())
        {
            cdTheFolder(index);
        }
        //由于截图浏览打开方式改为选中后单击打开，故将此双击逻辑屏蔽
//        else if(m_model->fileInfo(index).suffix() == "png")
//        {
//            qDebug() << m_currentFilePath;
//            QStringList filters;
//            filters << QString("*.png") << QString("*.PNG");
//            QDir dir(m_currentFilePath);
//            dir.setNameFilters(filters);
//            m_imageViewer->initImageViewer(m_currentFilePath, m_model->fileInfo(index).fileName(), dir.entryList());
//        }
    }
}

void FileManagerWidget::clearCheckIndex()
{
    m_model->clearCheckIndexList();
    m_model->clearCheckMap();
    m_selectName.clear();
    ui->m_checkAllBox->setChecked(false);
    setCopyAndDeleteEnable(false);
    setRenameAndLoadEnable(false);
    ui->m_tableView->setCurrentIndex(QModelIndex());
    m_imageSelectedName = QString("");
}

bool FileManagerWidget::selectAll(void)
{
    QString currentPath = m_directory->absolutePath();
    if (m_model->IsCurrentSelectAll(currentPath))
    {
        // 当前全部选中，反选
        clearCheckIndex();
        setCopyAndDeleteEnable(false);
        setRenameAndLoadEnable(false);
    }
    else
    {
        // 当前全部选中，反选
        clearCheckIndex();
        // 当前尚未全部选中，全选
        m_model->selectAllCheckMap(currentPath);
        QModelIndex indexParent = m_model->index(currentPath);
        int rowCount = m_model->rowCount(indexParent);
        for (int i = 0; i < rowCount; ++i)
        {
            QModelIndex indexAA = m_model->index(i, 0, indexParent);
            m_selectName.append(m_model->filePath(indexAA));
        }
        setCopyAndDeleteEnable(true);
        if (m_model->getFileCheckNum() == 1)
        {
            setRenameAndLoadEnable(true);
        }
        else
        {
            setRenameAndLoadEnable(false);
        }
    }

    ui->m_tableView->viewport()->update();

    if (m_model->IsCurrentSelectAll(currentPath))
    {
        ui->m_checkAllBox->setChecked(true);
    }
    else
    {
        ui->m_checkAllBox->setChecked(false);
    }

    return true;
}

void FileManagerWidget::onDirectoryLoaded()
{
    if (m_isAutoSave && m_currentFilePath.endsWith("MTest"))
    {
        ui->m_backButton->setEnabled(false);
        ui->m_forwardButton->setEnabled(false);
        ui->m_pathLabel->setText("Auto Measure");
        return;
    }
    ui->m_backButton->setEnabled(true);
    ui->m_forwardButton->setEnabled(true);

    QString modifyPath = m_currentFilePath;
    QString showPath = modifyPath;
    if (modifyPath.startsWith(getTopDir()))
    {
        int prefixLength = getTopDir().length() - QString("/UserData").length();
        showPath = modifyPath.mid(prefixLength);
    }
    else if (modifyPath.startsWith("/media"))
    {
        int prefixLength = QString("/media").length();
        showPath = modifyPath.mid(prefixLength);
    }
    showPath.prepend(tr("Path:"));

//#ifndef _WIN32
//    modifyPath = modifyPath.remove(QString("/mnt"));
//#endif

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(18);
    font.setBold(false);
    QFontMetrics fm(font);
    QString strPathText = fm.elidedText(showPath, Qt::ElideRight, 600);

    ui->m_pathLabel->setText(strPathText);
}

void FileManagerWidget::onDeleteButtonClicked()
{
    rmfile();
}

void FileManagerWidget::onCopyButtonClicked()
{
    copy();
}

void FileManagerWidget::onPasteButtonClicked()
{
    paste();
}

void FileManagerWidget::onNewfolderButtonClicked()
{
    EnglishKeyboard keyPad;
    keyPad.reset(20);
    if (keyPad.exec() == QDialog::Accepted)
    {
        QString dirName = keyPad.getInputStr().trimmed();
        mkdir(dirName);
    }
}

void FileManagerWidget::onRenameButtonClicked()
{
    EnglishKeyboard keyPad;
    keyPad.reset(20);
    if (keyPad.exec() == QDialog::Accepted)
    {
        QString newName = keyPad.getInputStr().trimmed();
        rename(newName);
    }
}

void FileManagerWidget::onLoadButtonClicked()
{
    if (m_model->getFileCheckNum() != 1)
    {
        return;
    }
    QModelIndex index = m_model->getCheckIndex(0);

    if (!index.isValid())
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initLoadUselessFile();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            clearCheckIndex();
            return;
        }
    }

    QFileInfo fileInfo = m_model->fileInfo(index);
    if (m_model->isDir(index))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initLoadDir();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            clearCheckIndex();
            return;
        }
    }
    else
    {
        QString fullName = fileInfo.absoluteFilePath();
        if (!isStateOrTrace(fullName))
        {
            ConfigureInfo *configureDlg = new ConfigureInfo(this);
            configureDlg->initLoadWrongType();
            if (configureDlg->exec() == QDialog::Rejected)
            {
                clearCheckIndex();
                return;
            }
        }
        emit loadFile(fullName);
        clearCheckIndex();
    }
}

void FileManagerWidget::onLocalButtonClicked()
{
    if (m_isAutoSave)
    {
        cdTheFolder(getAutoMTestDir());
    }
    else
    {
        cdTheFolder(getTopDir());
    }
    setDevice(Device_Local);
    onDirectoryLoaded();
}

void FileManagerWidget::onUsbButtonClicked()
{
    QString targetPath = USB_PATH_1;
    cdTheFolder(targetPath);
    setDevice(Device_Usb);
    onDirectoryLoaded();
}

void FileManagerWidget::onSdButtonClicked()
{
    QString targetPath = SD_PATH;
    cdTheFolder(targetPath);
    setDevice(Device_Sd);
    onDirectoryLoaded();
}

void FileManagerWidget::onNameButtonClicked()
{
    EnglishKeyboard keyPad;
    keyPad.reset(20);
    if (keyPad.exec() == QDialog::Accepted)
    {
        QString newName = keyPad.getInputStr().trimmed();

        unsigned char GucRegularString[] = {'.', '\\', '/', ':', '*', '?', '<', '>','|', ';', '&', '`', '\'',  '\"' };
        for (int i = 0; i < sizeof(GucRegularString); i++)
        {
            if (newName.contains(GucRegularString[i]))
            {
                ConfigureInfo *configureDlg = new ConfigureInfo(this);
                configureDlg->initIllegalSaveName();
                if (configureDlg->exec() == QDialog::Rejected)
                {
                    return;
                }
            }
        }

        ui->m_nameButton->setText(newName);
    }
}

void FileManagerWidget::onCancelButtonClicked()
{
    close();
//    reset();
}

void FileManagerWidget::onOkbuttonClicked()
{
    if (m_isAutoSave)
    {
        onCancelButtonClicked();
        return;
    }

    QString fileName = ui->m_nameButton->text();
    QString saveType = ui->comboBox->lineEdit()->text();
    FILE_TYPE fileType;
    if (TYPE_STATE == saveType)
    {
        fileType = FILE_TYPE_STATE;
    }
    else if (TYPE_STATE_AND_DATA == saveType)
    {
        fileType = FILE_TYPE_STATE_AND_DATA;
    }
    else if (TYPE_SCREEN_IMAGE == saveType)
    {
        fileType = FILE_TYPE_SCREEN_IMAGE;
    }
    else if (TYPE_MEASURE_DATA == saveType)
    {
        fileType = FILE_TYPE_MEASURE_DATA;
    }
    else if (TYPE_LIMIT == saveType)
    {
        fileType = FILE_TYPE_LIMIT;
    }

    save(fileName, fileType);
//    reset();
}

bool FileManagerWidget::rename(QString newName)
{
    if (m_model->getFileCheckNum() != 1)
    {
        return false;
    }

    unsigned char GucRegularString[] = {'.', '\\', '/', ':', '*', '?', '<', '>','|', ';', '&', '`', '\'', '\"' };
    for (int i = 0; i < sizeof(GucRegularString); i++)
    {
        if (newName.contains(GucRegularString[i]))
        {
            ConfigureInfo *configureDlg = new ConfigureInfo(this);
            configureDlg->initRenameIllegal();
            if (configureDlg->exec() == QDialog::Rejected)
            {
                return false;
            }
        }
    }

    if (newName.isEmpty())
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRenameEmpty();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    QModelIndex index = m_model->getCheckIndex(0);

    if (!index.isValid())
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRenameUselessFile();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    QFileInfo fileInfo = m_model->fileInfo(index);
    QString suffix = fileInfo.completeSuffix();
    QString absoluteName = fileInfo.absoluteFilePath();
    QString fullName;
    if (fileInfo.isFile())
    {
        fullName = m_currentFilePath + '/' + newName + '.' + suffix;
    }
    else if (fileInfo.isDir())
    {
        fullName = m_currentFilePath+ '/' + newName;
    }

    if (!QString::compare(fullName, absoluteName))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRenameSame();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    if (QFile::exists(fullName))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRenameExist();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    if (QFile(absoluteName).rename(fullName))
    {
        clearCheckIndex();
        return true;
    }
    else
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRenameFailed();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }
}

bool FileManagerWidget::mkdir(QString dirName)
{
    QModelIndex index = m_model->index(m_directory->absolutePath());
    if (!index.isValid())
    {
        return false;
    }

    unsigned char GucRegularString[] = {'.', '\\', '/', ':', '*', '?', '<', '>','|', ';', '&', '`', '\'',  '\"' };
    for (int i = 0; i < sizeof(GucRegularString); i++)
    {
        if (dirName.contains(GucRegularString[i]))
        {
            ConfigureInfo *configureDlg = new ConfigureInfo(this);
            configureDlg->initIllegalFolderName();
            if (configureDlg->exec() == QDialog::Rejected)
            {
                return false;
            }
        }
    }

    if (dirName.isEmpty())
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initEmptyFolderName();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    if (!QFile::exists(m_directory->absolutePath()))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initMkdirFailed();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    const QString dirPath = m_directory->absolutePath() + '/' + dirName;
    if (QFile::exists(dirPath))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initExistFolderName();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    if (m_model->mkdir(index, dirName).isValid())
    {
        clearCheckIndex();
        return true;
    }
    else
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initMkdirFailed();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }
}

bool FileManagerWidget::rmfile()
{
    QModelIndex index;
    bool ok;
    if (m_model->getFileCheckNum() == 0)
    {
    }
    else
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initRemoveFile();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            clearCheckIndex();
            return false;
        }

        for (int i = 0; i < m_model->getFileCheckNum(); i++)
        {
            index = m_model->getCheckIndex(i);

            if (!index.isValid())
            {
                continue;
            }
            if (m_model->fileInfo(index).isDir())
            {
                QString dirPath = m_model->filePath(index);

                ok = removeDir(dirPath);
            }
            else
            {
                ok = m_model->remove(index);
            }

            if (!ok)
            {
                ConfigureInfo *configureDlg = new ConfigureInfo(this);
                configureDlg->initRemoveFailed();
                if (configureDlg->exec() == QDialog::Rejected)
                {
                    clearCheckIndex();
                    return false;
                }
            }
        }
        clearCheckIndex();
        return true;
    }

    return false;
}

//文件夹删除 递归删除
bool FileManagerWidget::removeDir(QString & dirPath)
{
    QDir dir(dirPath);
    //获得子目录
    QStringList files = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    //使用迭代器访问项
    QList<QString>::iterator f = files.begin();

    bool error = true;
    //递归删除
    for (; f != files.end(); f++)
    {
        QString filePath = QDir::toNativeSeparators(dir.path() + '/' + (*f));
        QFileInfo fi(filePath);
        if (fi.isFile() || fi.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                error = false;
            }
        }
        else if (fi.isDir())
        {
            if (!removeDir(filePath))
            {
                error = false;
            }
        }
    }

    if (!dir.rmdir(QDir::toNativeSeparators(dir.path())))
    {
        error = false;
    }

    return error;
}

bool FileManagerWidget::copy()
{
    QModelIndex index;
    QString filePath;
    if (m_model->getFileCheckNum() == 0)
    {
        return false;
    }
    else
    {
        m_copyList.clear();
        for (int i = 0; i < m_model->getFileCheckNum(); i++)
        {
            index = m_model->getCheckIndex(i);

            if (!index.isValid())
                continue;

            filePath = m_model->filePath(index);
            m_copyList.append(filePath);
            setPasteEnable(true);
        }
        m_copySourcePath = m_currentFilePath;
        clearCheckIndex();
    }
    return true;
}

bool FileManagerWidget::paste()
{
    clearCheckIndex();
    if (!m_currentFilePath.compare(m_copySourcePath))
    {
        return false;
    }

    foreach(QString fileName, m_copyList)
    {
        if (!QFile::exists(fileName))
        {
            return false;
        }
    }   

    QFileInfo targetFolder(m_currentFilePath);
    if (targetFolder.fileName().length() > 40)
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initFolderNameTransFinite();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    QList<QString> copyDisableList;
    for (int i = 0; i < m_copyList.size(); ++i)
    {
        QString filePath = m_copyList.at(i);
        if (filePath.isEmpty())
        {
            continue;
        }

        QFileInfo file(filePath);
        QString newName = m_currentFilePath + "/" + file.fileName();
        if (file.isFile())
        {
            if (QFile::exists(newName))
            {
                ConfigureInfo *configureDlg = new ConfigureInfo(this);
                configureDlg->initReplaceFile(file.fileName());
                if (configureDlg->exec() == QDialog::Rejected)
                {
                    copyDisableList.append(filePath);
                    continue;
                }
                QFile::remove(newName);
            }
        }

        else if (file.isDir())
        {
            if (newName.contains(filePath))
            {
                ConfigureInfo *configureDlg = new ConfigureInfo(this);
                configureDlg->initContainsFilePath(file.fileName());
                if (configureDlg->exec() == QDialog::Rejected)
                {
                    copyDisableList.append(filePath);
                }
            }
            else if (QFile::exists(newName))
            {
                ConfigureInfo *configureDlg = new ConfigureInfo(this);
                configureDlg->initReplaceDir(file.fileName());
                if (configureDlg->exec() == QDialog::Rejected)
                {
                    copyDisableList.append(filePath);
                    continue;
                }
                removeDir(newName);
            }
        }
    }

    for (int i = 0; i < copyDisableList.size(); ++i)
    {
        m_copyList.removeOne(copyDisableList.at(i));
    }

    m_isSaveStateBox = false;
    m_stateBox->showMessage(QString("Copying..."));
    sleepSomeTime(100);

    CopyFileThread *cypThread = new CopyFileThread();
    ProgressBarDlg *cypProgress = new ProgressBarDlg(this);
    cypProgress->setGeometry(191, 140, 300, 150);
    connect(cypThread, SIGNAL(G_sndProgressValue(qint64, qint64)), cypProgress, SLOT(S_updateProgress(qint64, qint64)));
    connect(cypThread, SIGNAL(G_sndFileCount()), cypProgress, SLOT(S_setFileCount()));
    connect(cypThread, SIGNAL(G_DialogHide()), cypProgress, SLOT(S_DlgHide()));
    connect(cypThread, SIGNAL(G_ProgressReset()), cypProgress, SLOT(S_resetProgress()));
    connect(cypProgress, SIGNAL(S_closeDlg()), cypThread, SLOT(G_quitThread()));
    cypProgress->set_fileNum(fileSelectNum());
    cypProgress->setWindowTitle(tr("Copy"));
    cypProgress->S_setOperationName(tr("Copying..."));
    cypThread->start();

    ui->m_tableView->setUpdatesEnabled(false);
    /*遍历容器，复制或移动文件*/
    for (int i = 0; i < m_copyList.size(); ++i)
    {
        QString filePath = m_copyList.at(i);
        if (filePath.isEmpty())
        {
            continue;
        }
        QFileInfo file(filePath);
        QString newName = m_currentFilePath + "/" + file.fileName();

        if (file.isFile())
        {
            if (!cypThread->get_run())
            {
                break;
            }

            while (cypThread->get_start())
            {
               QThread::msleep(10);
            }

            /*设置源文件和目标文件路径*/
            cypThread->set_srcpath(filePath);
            cypThread->set_targetpath(newName);
            /*标记为复制文件*/
            cypThread->set_file();
            /*开始复制*/
            cypThread->set_start();

            cypProgress->S_setFileName(file.fileName());
            /*若线程已停止运行，则可能用户点击取消，跳出循环，终止文件复制或移动文件操作*/
            if (!cypThread->get_run()) break;
            cypProgress->exec();
        }

        else if (file.isDir())
        {

            if (!cypThread->get_run())
            {
                break;
            }
            while (cypThread->get_start())
            {
                QThread::msleep(10);
            }

            cypThread->set_srcpath(filePath);
            cypThread->set_targetpath(m_currentFilePath);
            cypThread->set_dir();
            cypThread->set_start();

            /*设置复制的文件名显示进度条对话框*/
            cypProgress->S_setFileName(file.fileName());
            /*若线程已停止运行，则可能用户点击取消，跳出循环，终止文件复制或移动文件操作*/
            if (!cypThread->get_run()) break;
            cypProgress->exec();
        }
    }

    flushTableView();
    sync();
    cypThread->set_run(false);
    cypThread->quit();
    m_stateBox->close();
    resetPaste();
    m_isSaveStateBox = false;
    m_stateBox->showMessage(QString("Copy Successfully"), true);
    ui->m_tableView->setUpdatesEnabled(true);
    clearCheckIndex();
    return true;
}

qint64 FileManagerWidget::fileSelectNum(void)
{
    qint64 ret = 0;

    for (int i = 0; i < m_copyList.size(); i++)
    {
        QString filePath = m_copyList.at(i);

        QFileInfo file(filePath);

        if (file.isFile() || file.isSymLink())
        {
            ret++;
        }
        else
        {
            ret += DirfileNum(filePath);
        }
    }
    return ret;
}

qint64 FileManagerWidget::DirfileNum(QString Dir)
{
    qint64 ret = 1;//文件夹也计算

    QDir dir(Dir);
    /*获得子目录*/
    QStringList files = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    /*使用迭代器访问项*/
    QList<QString>::iterator f = files.begin();

    for (; f != files.end(); f++)
    {
        QString filePath = QDir::toNativeSeparators(dir.path() + '/' + (*f));
        QFileInfo fi(filePath);
        if (fi.isFile() || fi.isSymLink())
        {
            ret++;
        }
        else if (fi.isDir())
        {
            ret += DirfileNum(filePath);
        }
    }
    return ret;
}

void FileManagerWidget::setCopyAndDeleteEnable(bool state)
{
    ui->m_copyButton->setEnabled(state);
    ui->m_deleteButton->setEnabled(state);
}

void FileManagerWidget::setRenameAndLoadEnable(bool state)
{
    ui->m_renameButton->setEnabled(state);
    ui->m_loadButton->setEnabled(state);
}

void FileManagerWidget::setPasteEnable(bool state)
{
    ui->m_pasteButton->setEnabled(state);
}

void FileManagerWidget::setLocalEnable(bool state)
{
    ui->m_localButton->setEnabled(state);
}

void FileManagerWidget::setUsbEnable(bool state)
{
    ui->m_usbButton->setEnabled(state);
}

void FileManagerWidget::setSdEnable(bool state)
{
    if (!m_isAutoSave)
    {
        ui->m_sdButton->setEnabled(state);
    }
}

QString FileManagerWidget::getTopDir()
{
#if __arm__
    return TOP_DIR;
#endif
    QString homePath = QDir::homePath();
    QString topPath = homePath + "/UserData";
    return topPath;
}

QString FileManagerWidget::getAutoMTestDir()
{
    QString homePath;
#if __arm__
    homePath = "/app";
#else
    homePath = QDir::homePath();
#endif

    QString path;
    if (m_componentType == COMP_TYPE_FDD)
    {
        path = homePath+"/AutoMeasure/FDD/MTest";
    }
    else if (m_componentType == COMP_TYPE_TDD)
    {
        path = homePath+"/AutoMeasure/TDD/MTest";
    }

    return path;
}

void FileManagerWidget::sleepSomeTime(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void FileManagerWidget::resetPaste()
{
    m_copyList.clear();
    setPasteEnable(false);
}

void FileManagerWidget::setDevice(int device)
{
    m_device = device;
}

void FileManagerWidget::onDeviceStatusUpdated()
{
    if (HotplugManager::instance()->isExistDev(Media_Type_USB))
    {
        setUsbEnable(true);
    }
    else
    {
        setUsbEnable(false);
        if (Device_Usb == m_device)
        {
            onLocalButtonClicked();
        }
    }

    if (HotplugManager::instance()->isExistDev(Media_Type_SD))
    {
        setSdEnable(true);
    }
    else
    {
        setSdEnable(false);
        if (Device_Sd == m_device)
        {
            onLocalButtonClicked();
        }
    }
}

void FileManagerWidget::setFilters()
{
    QStringList filters;
    m_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::AllDirs);
    filters << QString("*.state") << QString("*.STATE")
            << QString("*.trace") << QString("*.TRACE")
            << QString("*.png") << QString("*.PNG")
            << QString("*.csv") << QString("*.CSV")
            << QString("*.jpg") << QString("*.JPG")
            << QString("*.dat") << QString("*.DAT") ;
    m_model->setNameFilters(filters);
}

void FileManagerWidget::setAutoSaveFilters()
{
    QStringList filters;
    m_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::AllDirs);
    filters << QString("*.meas") << QString("*.MEAS");
    m_model->setNameFilters(filters);
}

void FileManagerWidget::setScrollerProperty()
{
    QScroller *scroller = QScroller::scroller(ui->m_tableView->viewport());
    QScrollerProperties prop = scroller->scrollerProperties();
    prop.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0.5);
    prop.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.1);
    prop.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.5);
    prop.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.001);
    prop.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    prop.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    scroller->setScrollerProperties(prop);
    scroller->grabGesture(ui->m_tableView->viewport(), QScroller::TouchGesture);
    scroller->grabGesture(ui->m_tableView->viewport(), QScroller::LeftMouseButtonGesture);
}

bool FileManagerWidget::save(QString fileName, int fileType)
{
    if (fileName.isEmpty())
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initSaveNameEmpty();
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
    }

    QString fullName;
    QString warningName;
    QString suffix;
    switch (fileType)
    {
    case FILE_TYPE_STATE:
        suffix = "state";
        break;
    case FILE_TYPE_STATE_AND_DATA:
        suffix = m_moduleSuffixMap.value(m_moduleType,"trace");
        break;
    case FILE_TYPE_SCREEN_IMAGE:
        suffix = "png";
        break;
    case FILE_TYPE_MEASURE_DATA:
    case FILE_TYPE_LIMIT:
        suffix = "csv";
        break;
    default:
        break;
    }

    warningName = fileName + '.' + suffix;
    fullName = m_currentFilePath + '/' + fileName + '.' + suffix;

    if (QFile::exists(fullName))
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initSaveNameExist(warningName);
        if (configureDlg->exec() == QDialog::Rejected)
        {
            return false;
        }
        QFile::remove(fullName);
    }

    emit saveFile(fullName, fileType);
    return true;
}

void FileManagerWidget::reset()
{
    onLocalButtonClicked();
    resetPaste();
    ui->m_nameButton->setText(tr("File Name"));
    //ui->comboBox->setCurrentIndex(0);
    emit resetHeader();
}

bool FileManagerWidget::event(QEvent *e)
{
    QEvent::Type eType = e->type();
    if (eType == QEvent::KeyPress)
    {
        QKeyEvent *keyEvt = static_cast<QKeyEvent*> (e);
        if (keyEvt->key() == Qt::Key_Escape && !m_stateBox->isVisible())
        {
            close();
            reset();
            return true;
        }
        if (keyEvt->key() == Qt::Key_Shift && !m_stateBox->isVisible())
        {
            emit pressShift();
            close();
            reset();
            return true;
        }
        if (keyEvt->key() == Qt::Key_PowerOff)
        {
            emit pressPowerOff();
        }
    }
    return QWidget::event(e);
}

void FileManagerWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
    //reset();
    if (m_firstTimeShow)
    {
        QTimer::singleShot(50, this, SLOT(onTimeOut()));
        QTimer::singleShot(100, this, SLOT(onTimeOut()));
        QTimer::singleShot(200, this, SLOT(onTimeOut()));
        QTimer::singleShot(500, this, SLOT(onTimeOut()));
    }
}

void FileManagerWidget::onTimeOut()
{
    clearCheckIndex();
    m_firstTimeShow = false;
}

bool FileManagerWidget::isStateOrTrace(QString fileName)
{
    bool state = false;
    if (fileName.endsWith("state") || fileName.endsWith("STATE"))
    {
        state = true;
    }
    else if (fileName.endsWith("trace") || fileName.endsWith("TRACE"))
    {
        state = true;
    }
    else if (fileName.endsWith("meas") || fileName.endsWith("MEAS"))
    {
        state = true;
    }
    else if (fileName.endsWith("dat") || fileName.endsWith("DAT"))
    {
        state = true;
    }
    return state;
}

void FileManagerWidget::onStateBoxClosed()
{
    if (m_isSaveStateBox)
    {
        m_isSaveStateBox = false;
        close();
    }
}

void FileManagerWidget::onCurrentIndexChanged(int index)
{
    Q_UNUSED(index)

    QString saveType = ui->comboBox->lineEdit()->text();
    FILE_TYPE fileType;
    if (TYPE_STATE == saveType)
    {
        fileType = FILE_TYPE_STATE;
    }
    else if (TYPE_STATE_AND_DATA == saveType)
    {
        fileType = FILE_TYPE_STATE_AND_DATA;
    }
    else if (TYPE_SCREEN_IMAGE == saveType)
    {
        fileType = FILE_TYPE_SCREEN_IMAGE;
    }
    else if (TYPE_MEASURE_DATA == saveType)
    {
        fileType = FILE_TYPE_MEASURE_DATA;
    }
    else if (TYPE_LIMIT == saveType)
    {
        fileType = FILE_TYPE_LIMIT;
    }

    emit saveTypeChanged(fileType);
}

void FileManagerWidget::onSaveFinished(bool result)
{
    if (result)
    {
        //m_isSaveStateBox = true;
        //m_stateBox->showMessage(QString("Save Successfully"), true);
        close();
    }
    else
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initSaveFailed();
        configureDlg->exec();
    }
}

void FileManagerWidget::onLoadFinished(bool result)
{
    if (result)
    {
        //m_isSaveStateBox = true;
        //m_stateBox->showMessage(QString("Load Successfully"), true);
        close();
    }
    else
    {
        ConfigureInfo *configureDlg = new ConfigureInfo(this);
        configureDlg->initLoadFailed();
        configureDlg->exec();
    }
}

void FileManagerWidget::setFileType(int type)
{
    if (type >= 1)
    {
        ui->comboBox->setCurrentIndex(type - 1);
    }
    else
    {
        ui->comboBox->setCurrentIndex(0);
    }
}

void FileManagerWidget::setModuleType(int type)
{
    m_moduleType = type;
}

void FileManagerWidget::setAutoMeasureFile()
{
    ui->m_backButton->setEnabled(false);
    ui->m_forwardButton->setEnabled(false);
    ui->m_sdButton->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->m_nameButton->setEnabled(false);
    ui->m_newFolderButton->setEnabled(false);
    setAutoSaveFilters();

    QString dir = getAutoMTestDir();
    QDir autoDir(dir);
    if (!autoDir.exists())
    {
        if (!autoDir.mkpath(dir))
        {
            return;
        }
    }
    cdTheFolder(dir);

    ui->m_pathLabel->setText("Auto Measure");
}

void FileManagerWidget::setComponentType(int type)
{
    m_componentType = type;
}

void FileManagerWidget::setAutoSaveState(bool state)
{
    m_isAutoSave = state;
    if(m_isAutoSave)
    {
        setAutoMeasureFile();
    }
}

void FileManagerWidget::flushTableView()
{
    if (!QFile::exists(m_directory->absolutePath()))
    {
        return;
    }

    QString fileName = "!@@@!%%%!$$$!Test!@@@!%%%!$$$";
    QString filePath = m_directory->absolutePath() + '/' + fileName;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QFile::remove(filePath);
}
