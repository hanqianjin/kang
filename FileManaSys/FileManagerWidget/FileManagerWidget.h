/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  FileManagerWidget.h
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

#ifndef WIDGET_H
#define WIDGET_H

#include "FileSystemModel.h"
#include "FileSystemDelegate.h"
#include "FileManagerTableView.h"
#include "ConfigureInfo.h"
#include "StateBox.h"
#include "../globaldef.h"
#include "imageviewer.h"
#include <QWidget>
#include <QDir>
#include <QTime>

namespace Ui {
class FileManagerWidget;
}

class FileManagerWidget : public QWidget
{
    Q_OBJECT

    enum Device
    {
        None = 0,
        Device_Local,
        Device_Usb,
        Device_Sd,
    };

public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();
    void initModel();
    void initWidget();
    void initSignalAndSlot();
    void initWarningBox();
    QString getTopDir();
    QString getAutoMTestDir();
    void reset();
    void onSaveFinished(bool result);
    void onLoadFinished(bool result);
    void setFileType(int type);
    void setModuleType(int type);
    void setComponentType(int type);   
    void setAutoSaveState(bool state);

private slots:
    void onValueChanged(int value);
    void onRangeChanged(int min, int max);
    void onBackButtonClicked();
    void onForwardButtonClicked();
    void onFileHeaderClicked(int sortType);
    void onTableViewClicked(QModelIndex index);
    bool selectAll();
    void onDeleteButtonClicked();
    void onCopyButtonClicked();
    void onPasteButtonClicked();
    void onNewfolderButtonClicked();
    void onRenameButtonClicked();
    void onLoadButtonClicked();
    void onLocalButtonClicked();
    void onUsbButtonClicked();
    void onSdButtonClicked();
    void onDeviceStatusUpdated();
    void onNameButtonClicked();
    void onOkbuttonClicked();
    void onCancelButtonClicked();
    void onTableViewDoubleClicked(QModelIndex index);
    void onTimeOut();
    void onStateBoxClosed();
    void onCurrentIndexChanged(int index);
signals:
    void loadFile(QString fileName);
    void saveFile(QString fileName, int fileType);
    void resetHeader();
    void pressShift();
    void pressPowerOff();
    void saveTypeChanged(int fileType);
protected:
    bool event(QEvent *e);
    void showEvent(QShowEvent *e);
private:
    bool cd_up();
    bool cdTheFolder(QModelIndex index);
    bool cdTheFolder(QString targetPath);
    void clearCheckIndex();
    void onDirectoryLoaded();
    bool rmfile();
    bool removeDir(QString & dirPath);
    bool copy();
    bool paste();
    bool mkdir(QString dirName);
    bool rename(QString newName);
    qint64 fileSelectNum();
    qint64 DirfileNum(QString Dir);
    void setCopyAndDeleteEnable(bool state);
    void setRenameAndLoadEnable(bool state);
    void setPasteEnable(bool state);
    void sleepSomeTime(unsigned int msec);
    void resetPaste();
    void setLocalEnable(bool state);
    void setUsbEnable(bool state);
    void setSdEnable(bool state);
    void setDevice(int device);
    void setFilters();
    void setAutoSaveFilters();
    void setScrollerProperty();
    bool save(QString fileName, int fileType);
    bool isStateOrTrace(QString fileName);
    void flushTableView();
    void setAutoMeasureFile();

private:
    Ui::FileManagerWidget *ui;
    FileSystemModel *m_model;
    QDir *m_directory;
    QString m_currentFilePath;//当前路径
    QList<QString> m_selectName;
    QList<QString> m_copyList;
    QString m_copySourcePath;
    StateBox *m_stateBox;
    int m_device;
    bool m_firstTimeShow;
    bool m_isSaveStateBox;
    int m_moduleType;
    int m_componentType;
    QMap<int, QString> m_moduleSuffixMap;
    bool m_isAutoSave;
    //image view
    ImageViewer *m_imageViewer;
    QString m_imageSelectedName;
};

#endif // WIDGET_H
