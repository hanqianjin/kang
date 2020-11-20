#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QString>
#include "../FileManagerWidget/ConfigureInfo.h"
#include "./FileManagerWidget/StateBox.h"
namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = 0);
    ~SaveDialog();
    void setSavePath(QString path);
    void setSavePath(int fileType);
    void setModuleType(int type);
    void setCompType(int type);
    QString getFile();
    bool writeData(const QString &data);
public slots:
    void onSaveFile(QString file, int fileType);
    void onFastSaveFinished(bool result);
signals: 
    void fastSaveFileSig(QString file, int fileType);
    void pressShift();
    void pressPowerOff();
protected:
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event)Q_DECL_OVERRIDE;
private:
    void setDefaultFileName();
    int getFileNum(QList<int> &fileNumList);
private slots: 
    void init();

    void onClearClicked();

    void onFileNameClicked();

    void onOkClicked();

    void onCancelClicked();

    void onStateboxClosed();
private:
    Ui::SaveDialog *ui;
    int m_fileType;
    QString m_fileName;
    QString m_fileSuffix;
    QString m_path;
    QMap<int, QString> m_fileTypeMap;
    QMap<int, QString> m_fileSuffixMap;
    ConfigureInfo *m_configureInfo;
    StateBox *m_stateBox;
    int m_moduleType;
    QMap<int, QString> m_moduleSuffixMap;
};

#endif // SAVEDIALOG_H
