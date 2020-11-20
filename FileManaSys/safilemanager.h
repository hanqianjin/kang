#ifndef SAFILEMANAGER_H
#define SAFILEMANAGER_H

#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QFileInfo>
#include "globaldef.h"

class SAFileManager : public QWidget
{
    Q_OBJECT

public:
    SAFileManager(QWidget *parent = 0);
    ~SAFileManager();
    /**
    * @brief : show快速保存弹窗
    * @return : void
    */
    void            showSaveDialog();
    /**
    * @brief : show文件管理窗口
    * @return : void
    */
    void            showFileManagerWidget();

    /**
    * @brief : 设置测量模式
    * @return : void
    */
    void            setModuleType(int type);

    /**
    * @brief : 设置测量组件
    * @return : void
    */
    void            setComponentType(int type);

public slots:
    /**
    * @brief : 快速保存结束后外部信号需连接的槽函数
    * @return : void
    */
    void            onFastSaveFinished(bool result);
    /**
    * @brief : 保存结束后外部信号需连接的槽函数
    * @return : void
    */
    void            onSaveFinished(bool result);
    /**
    * @brief : 载入结束后外部信号需连接的槽函数
    * @return : void
    */
    void            onLoadFinished(bool result);
signals:
    /**
    * @brief : 载入文件后抛出的信号（对外）
    * @return : void
    */
    void            loadFileSig(QString fileName);
    /**
    * @brief : 保存文件后抛出的信号（对外）
    * @return : void
    */
    void            saveFileSig(QString fileName, int fileType);
    /**
    * @brief : 快速保存文件后抛出的信号（对外）
    * @return : void
    */
    void            fastSaveFileSig(QString file, int fileType);
    /**
    * @brief : 点击shift后抛出的信号（对外）
    * @return : void
    */
    void            pressShiftKeySig();
    /**
    * @brief : 按关机键后抛出的信号（对外）
    * @return : void
    */
    void            pressPowerOffKeySig();

    void            fastSaveDialogClosed();

    void            fileManagerWidgetClosed();
    //内部使用的信号
    void            fastSaveFinishedSig(bool result);
    void            saveFinishedSig(bool result);
    void            loadFinishedSig(bool result);
private:
    void            initSaveDialog();
    void            initFileManagerWidget();
private slots:
    void            onSaveType(int fileType);
    void            onDestroySaveDialog();
    void            onDestroyFileManagerWidget();
private:
    QDialog*        m_saveDialog;
    QWidget*        m_fileManagerWidget;
    int             m_fileType;
    int             m_moduleType;
    int             m_componentType;
};

#endif
