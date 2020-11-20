#ifndef RTSA_DIALOG_QUICKSAVE_H
#define RTSA_DIALOG_QUICKSAVE_H

#include <QDialog>
#include <QDir>
#include <QDesktopWidget>
#include "rtsa_dialog_virtualkeyboard.h"
namespace Ui {
class RtSa_Dialog_QuickSave;
}

#define RTSA_DEFAULT_SCREENSHOTS_PATH  "/app/UserData/Screen"

class RtSa_Dialog_QuickSave : public QDialog
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_QuickSave(QWidget *parent = 0,qint32 DisplayMode = 0);
    ~RtSa_Dialog_QuickSave();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_cancel_clicked();
    void on_pb_ok_clicked();
    void on_pb_Cancel_clicked();
    void on_pb_clear_clicked();
private:
    Ui::RtSa_Dialog_QuickSave *ui;
    QString strInput,savePath;
    QPixmap mScreenShots;
    QWidget *mParent;
    qint32 mDisplayMode;
    void initVariable();
    void initDisplay();
    void initWidget();
    void initFunc();
    QString getDefaultFileName(QString mSavePath);
    bool SaveScreenShots();
    void backSpace();
    void clearAll();
    qint32 checkFileName(QString mFile);
    RtSa_dialog_virtualkeyboard *mKeyBoard;

};

#endif // RTSA_DIALOG_QUICKSAVE_H
