/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ConfigureInfo.cpp
** Latest Version:             V1.0.0
** Latest modified Date:       2019/5/21
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Zhou Yuhan
** Created date:               2019/5/21
** Descriptions:               END
**
*********************************************************************************************************/

#include "ConfigureInfo.h"
#include "../globaldef.h"
#include <QEvent>
#include <QKeyEvent>

ConfigureInfo::ConfigureInfo(QWidget *parent) : QDialog(parent)
, m_strLabel("")
, m_strCancel("")
, m_strOk("")
, m_strClose("")
, m_configInfoType(CONFIGURE_INFO_UNKNOW)
, m_fileName("")
{
    ui.setupUi(this);
    connect(ui.m_OKButton, &QPushButton::clicked, this, &ConfigureInfo::accept);
    connect(ui.m_cancelButtton, &QPushButton::clicked, this, &ConfigureInfo::reject);
    connect(ui.m_closeButton, &QPushButton::clicked, this, &ConfigureInfo::reject);
   // setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    move(QPoint(365,315));
}

ConfigureInfo::~ConfigureInfo()
{

}

/**
* @brief:语言翻译
* @return:    void
*/
void ConfigureInfo::translateLanguage()
{
    //ui.retranslateUi(this);
    if(m_strLabel.trimmed().length() > 0)
    {
        if ( CONFIGURE_INFO_REPLACE_FILE == m_configInfoType ||
             CONFIGURE_INFO_REPLACE_DIR == m_configInfoType ||
             CONFIGURE_INFO_CONTAIN_PATH == m_configInfoType ||
             CONFIGURE_INFO_EXIST_SAVENAME == m_configInfoType)
        {
            QString tmp = QString(tr(m_strLabel.toUtf8())).arg(m_fileName);
            ui.m_infoLabel->setText(tmp);
        }
        else
        {
            ui.m_infoLabel->setText(tr(m_strLabel.toUtf8()));
        }
    }
    if (m_strWarning.trimmed().length() > 0)
    {
        ui.m_warningLabel->setText(tr(m_strWarning.toUtf8()));
    }
    if (m_strCancel.trimmed().length() > 0)
    {
        ui.m_cancelButtton->setText(tr(m_strCancel.toUtf8()));
    }
    if(m_strOk.trimmed().length() > 0)
    {
        ui.m_OKButton->setText(tr(m_strOk.toUtf8()));
    }
    if (m_strClose.trimmed().length() > 0)
    {
        ui.m_closeButton->setText(tr(m_strClose.toUtf8()));
    }
}

void ConfigureInfo::initReplaceFile(QString fileName)
{
    m_configInfoType = CONFIGURE_INFO_REPLACE_FILE;
    setWarning(false);
    m_strLabel = QT_TR_NOOP("The file name %1 already exists, do you want to replace it?");
    m_fileName = fileName;
    translateLanguage();
}

void ConfigureInfo::initContainsFilePath(QString dirName)
{
    m_configInfoType = CONFIGURE_INFO_CONTAIN_PATH;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Target folder is subdirectory of folder %1.");
    m_fileName = dirName;
    translateLanguage();
}

void ConfigureInfo::initFolderNameTransFinite()
{
    m_configInfoType = CONFIGURE_INFO_FOLDER_TRANSFINITE;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Target folder name is too long.");
    translateLanguage();
}

void ConfigureInfo::initReplaceDir(QString dirName)
{
    m_configInfoType = CONFIGURE_INFO_REPLACE_DIR;
    setWarning(false);
    m_strLabel = QT_TR_NOOP("The folder name %1 already exists, do you want to replace it?");
    m_fileName = dirName;
    translateLanguage();
}

void ConfigureInfo::initRemoveFile()
{
    m_configInfoType = CONFIGURE_INFO_REMOVE_FILE;
    setWarning(false);
    m_strLabel = QT_TR_NOOP("Are you sure to delete the choosed files?");
    translateLanguage();
}

void ConfigureInfo::initRemoveFailed()
{
    m_configInfoType = CONFIGURE_INFO_REMOVE_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Delete failed.");
    translateLanguage();
}

void ConfigureInfo::initIllegalFolderName()
{
    m_configInfoType = CONFIGURE_INFO_ILLEGAL_NAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Folder name contains illegal characters.");
    translateLanguage();
}

void ConfigureInfo::initEmptyFolderName()
{
    m_configInfoType = CONFIGURE_INFO_EMPTY_NAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Folder name can not be empty.");
    translateLanguage();
}

void ConfigureInfo::initMkdirFailed()
{
    m_configInfoType = CONFIGURE_INFO_MKDIR_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Create folder failed.");
    translateLanguage();
}

void ConfigureInfo::initExistFolderName()
{
    m_configInfoType = CONFIGURE_INFO_EXIST_NAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Create folder failed,folder have existed.");
    translateLanguage();
}

void ConfigureInfo::initRenameUselessFile()
{
    m_configInfoType = CONFIGURE_INFO_USELESS_FILE;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Rename failed, you choosed useless files.");
    translateLanguage();
}

void ConfigureInfo::initRenameIllegal()
{
    m_configInfoType = CONFIGURE_INFO_ILLEGAL_RENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("File name contains illegal characters.");
    translateLanguage();
}

void ConfigureInfo::initRenameEmpty()
{
    m_configInfoType = CONFIGURE_INFO_EMPTY_RENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("File name can not be empty.");
    translateLanguage();
}

void ConfigureInfo::initRenameSame()
{
    m_configInfoType = CONFIGURE_INFO_SAME_RENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Rename failed, new name is same as original.");
    translateLanguage();
}

void ConfigureInfo::initRenameExist()
{
    m_configInfoType = CONFIGURE_INFO_EXSIT_RENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Rename failed, file name already exists.");
    translateLanguage();
}

void ConfigureInfo::initRenameFailed()
{
    m_configInfoType = CONFIGURE_INFO_RENAME_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Rename file failed.");
    translateLanguage();
}

void ConfigureInfo::initLoadUselessFile()
{
    m_configInfoType = CONFIGURE_INFO_LOAD_USELESS;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Load failed, you choosed useless file.");
    translateLanguage();
}

void ConfigureInfo::initLoadDir()
{
    m_configInfoType = CONFIGURE_INFO_LOAD_DIR;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("You can not load a folder.");
    translateLanguage();
}

void ConfigureInfo::initFastSaveFile()
{
    m_configInfoType = CONFIGURE_INFO_LOAD_DIR;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Filename can not be empty!");
    translateLanguage();
}

void ConfigureInfo::initKeyPadFastSaveFile()
{
    m_configInfoType = CONFIGURE_INFO_LOAD_DIR;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Filename is invalid!");
    translateLanguage();
}

void ConfigureInfo::setWarning(bool isWaring)
{
    if (isWaring)
    {
        ui.m_closeButton->show();
        ui.m_OKButton->hide();
        ui.m_cancelButtton->hide();
        ui.m_imageLabel->setPixmap(QPixmap(":/images/filewidgetimage/warn.png"));
        m_strWarning = QT_TR_NOOP("Warning");
        m_strClose = QT_TR_NOOP("OK");
    }
    else
    {
        ui.m_closeButton->hide();
        ui.m_OKButton->show();
        ui.m_cancelButtton->show();
        ui.m_imageLabel->setPixmap(QPixmap(":/images/filewidgetimage/notice.png"));
        m_strWarning = QT_TR_NOOP("Notice");
        m_strOk = QT_TR_NOOP("OK");
        m_strCancel = QT_TR_NOOP("Cancel");
    }
}

void ConfigureInfo::initIllegalSaveName()
{
    m_configInfoType = CONFIGURE_INFO_ILLEGAL_SAVENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("File name contains illegal characters.");
    translateLanguage();
}

void ConfigureInfo::initSaveNameEmpty()
{
    m_configInfoType = CONFIGURE_INFO_EMPTY_SAVENAME;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("File name can not be empty.");
    translateLanguage();
}

void ConfigureInfo::initSaveNameExist(QString fileName)
{
    m_configInfoType = CONFIGURE_INFO_EXIST_SAVENAME;
    setWarning(false);
    m_strLabel = QT_TR_NOOP("The file name already exists, do you want to replace it?");
    m_fileName = fileName;
    translateLanguage();
}

bool ConfigureInfo::event(QEvent *e)
{
    QEvent::Type eType = e->type();
    if (eType == QEvent::KeyPress)
    {
        QKeyEvent *keyEvt = static_cast<QKeyEvent*> (e);
        if (keyEvt->key() == Qt::Key_Escape)
        {
            reject();
            return true;
        }
        if (keyEvt->key() == Qt::Key_Shift)
        {
            return true;
        }
    }
    return QDialog::event(e);
}

void ConfigureInfo::initSaveFailed()
{
    m_configInfoType = CONFIGURE_INFO_SAVE_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Save failed.");
    translateLanguage();
}

void ConfigureInfo::initLoadFailed()
{
    m_configInfoType = CONFIGURE_INFO_LOAD_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Load failed.");
    translateLanguage();
}

void ConfigureInfo::initFastSaveFailed()
{
    m_configInfoType = CONFIGURE_INFO_SAVE_FAIL;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("Fast Save failed.");
    translateLanguage();
}

void ConfigureInfo::initLoadWrongType()
{
    m_configInfoType = CONFIGURE_INFO_WRONG_LOADTYPE;
    setWarning(true);
    m_strLabel = QT_TR_NOOP("File type must be state or trace.");
    translateLanguage();
}

void ConfigureInfo::hideEvent(QHideEvent *e)
{
    ui.m_cancelButtton->setText("");
    ui.m_closeButton->setText("");
    ui.m_OKButton->setText("");
    ui.m_infoLabel->setText("");
    ui.m_warningLabel->setText("");
    QDialog::hideEvent(e);
}
