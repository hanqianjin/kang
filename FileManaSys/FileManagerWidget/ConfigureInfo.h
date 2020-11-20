/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ConfigureInfo.h
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

#ifndef __CONFIGUREINFODLG__
#define __CONFIGUREINFODLG__

#include "ui_confirmWidget.h"
#include <QtWidgets/QDialog>

class ConfigureInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureInfo(QWidget *parent = Q_NULLPTR);
    ~ConfigureInfo();

    /**
    * @brief:语言翻译
    * @return:    void
    */
    void translateLanguage();

Q_SIGNALS :
    void onSave();
    void onSaveFail();
    void pressPowerOff();

public:
    void initReplaceFile(QString fileName);
    void initContainsFilePath(QString dirName);
    void initFolderNameTransFinite();
    void initReplaceDir(QString dirName);
    void initRemoveFile();
    void initRemoveFailed();
    void initIllegalFolderName();
    void initEmptyFolderName();
    void initMkdirFailed();
    void initExistFolderName();
    void initRenameUselessFile();
    void initRenameIllegal();
    void initRenameEmpty();
    void initRenameSame();
    void initRenameExist();
    void initRenameFailed();
    void initLoadUselessFile();
    void initLoadDir();
    void initIllegalSaveName();
    void initSaveNameEmpty();
    void initSaveNameExist(QString fileName);
    void initFastSaveFile();
    void initKeyPadFastSaveFile();
    void initLoadWrongType();
    void initSaveFailed();
    void initFastSaveFailed();
    void initLoadFailed();

protected:
    bool event(QEvent *e);
    void hideEvent(QHideEvent *e);

private:
    void setWarning(bool isWaring);

private:
    Ui::confirmWidget ui;
    int m_configInfoType;
    QString m_strLabel;
    QString m_strWarning;
    QString m_strCancel;
    QString m_strOk;
    QString m_strClose;
    QString m_fileName;
};
#endif
