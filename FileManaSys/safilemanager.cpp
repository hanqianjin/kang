#include "safilemanager.h"
#include "./saveload/savedialog.h"
#include "./FileManagerWidget/FileManagerWidget.h"
#include "./hotplug/hotplughandler.h"
#define SAVEDIALOG static_cast<SaveDialog*>(m_saveDialog)
#define FILEWIDGET static_cast<FileManagerWidget*>(m_fileManagerWidget)

SAFileManager::SAFileManager(QWidget *parent) :
    QWidget(parent),
    m_saveDialog(NULL),
    m_fileManagerWidget(NULL),
    m_fileType(FILE_TYPE_STATE),
    m_moduleType(MODULE_TYPE_NONE),
    m_componentType(COMP_TYPE_NONE)
{
    HotplugManager::instance();
}

SAFileManager::~SAFileManager()
{
    if (NULL == m_saveDialog)
    {
        delete m_saveDialog;
        m_saveDialog = NULL;
    }
    if (NULL == m_saveDialog)
    {
        delete m_fileManagerWidget;
        m_fileManagerWidget = NULL;
    }
}

void SAFileManager::showSaveDialog()
{
    if(NULL == m_saveDialog)
    {
        initSaveDialog();
    }
    m_saveDialog->show();
}
void SAFileManager::showFileManagerWidget()
{
    if(NULL == m_fileManagerWidget)
    {

        initFileManagerWidget();
    }
    m_fileManagerWidget->show();
}

void SAFileManager::onFastSaveFinished(bool result)
{
    emit fastSaveFinishedSig(result);
}

void SAFileManager::onSaveFinished(bool result)
{
    emit saveFinishedSig(result);
}

void SAFileManager::onLoadFinished(bool result)
{
    emit loadFinishedSig(result);
}

void SAFileManager::onSaveType(int fileType)
{
    m_fileType = fileType;
    if(m_saveDialog)
    {
        SAVEDIALOG->setSavePath(m_fileType);
    }
}

void SAFileManager::onDestroySaveDialog()
{
    qDebug() << "Destroy SaveDialog";
    m_saveDialog = NULL;
    emit fastSaveDialogClosed();
}

void SAFileManager::onDestroyFileManagerWidget()
{
    qDebug() << "Destroy FileManagerWidget";
    m_fileManagerWidget = NULL;
    emit fileManagerWidgetClosed();

}

void SAFileManager::initSaveDialog()
{
    m_saveDialog = new SaveDialog();
    connect(SAVEDIALOG, &SaveDialog::pressPowerOff, this, &SAFileManager::pressPowerOffKeySig);
    connect(SAVEDIALOG, &SaveDialog::pressShift, this, &SAFileManager::pressShiftKeySig);
    connect(SAVEDIALOG, &SaveDialog::fastSaveFileSig, this, &SAFileManager::fastSaveFileSig);
    connect(this, &SAFileManager::fastSaveFinishedSig, SAVEDIALOG, &SaveDialog::onFastSaveFinished);
    connect(m_saveDialog, &QObject::destroyed, this, &SAFileManager::onDestroySaveDialog);
    SAVEDIALOG->setModuleType(m_moduleType);
    SAVEDIALOG->setCompType(m_componentType);
    SAVEDIALOG->setSavePath(m_fileType);
}

void SAFileManager::initFileManagerWidget()
{
    m_fileManagerWidget = new FileManagerWidget();
    connect(FILEWIDGET, &FileManagerWidget::loadFile, this, &SAFileManager::loadFileSig);
    connect(FILEWIDGET, &FileManagerWidget::saveFile, this, &SAFileManager::saveFileSig);
    connect(FILEWIDGET, &FileManagerWidget::pressPowerOff, this, &SAFileManager::pressPowerOffKeySig);
    connect(FILEWIDGET, &FileManagerWidget::pressShift, this, &SAFileManager::pressShiftKeySig);
    connect(FILEWIDGET, &FileManagerWidget::saveTypeChanged, this, &SAFileManager::onSaveType);
    connect(this, &SAFileManager::saveFinishedSig, FILEWIDGET, &FileManagerWidget::onSaveFinished);
    connect(this, &SAFileManager::loadFinishedSig, FILEWIDGET, &FileManagerWidget::onLoadFinished);
    connect(m_fileManagerWidget, &QObject::destroyed, this, &SAFileManager::onDestroyFileManagerWidget);
    FILEWIDGET->setFileType(m_fileType);
    FILEWIDGET->setComponentType(m_componentType);

    if (m_moduleType == MODULE_TYPE_AUTOSAVE)
    {
        FILEWIDGET->setModuleType(MODULE_TYPE_AUTO);
        FILEWIDGET->setAutoSaveState(true);
    }
    else
    {
        FILEWIDGET->setModuleType(m_moduleType);
        FILEWIDGET->setAutoSaveState(false);
    }
}

void SAFileManager::setModuleType(int type)
{
    m_moduleType = type;
}

void SAFileManager::setComponentType(int type)
{
    m_componentType = type;
}
