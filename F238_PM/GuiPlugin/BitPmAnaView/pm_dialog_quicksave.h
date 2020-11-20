#ifndef PM_DIALOG_QUICKSAVE_H
#define PM_DIALOG_QUICKSAVE_H

#include <QDialog>
#include <QDir>
#include <QDesktopWidget>
#include "pm_dialog_virtualkeyboard.h"
namespace Ui {
class Pm_Dialog_QuickSave;
}

#define PM_DEFAULT_SCREENSHOTS_PATH  "/app/UserData/Screen"

class Pm_Dialog_QuickSave : public QDialog
{
    Q_OBJECT

public:
    explicit Pm_Dialog_QuickSave(QWidget *parent = 0,qint32 DisplayMode = 0);
    ~Pm_Dialog_QuickSave();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_cancel_clicked();
    void on_pb_ok_clicked();
    void on_pb_Cancel_clicked();
    void on_pb_clear_clicked();
private:
    Ui::Pm_Dialog_QuickSave *ui;
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
    Pm_dialog_virtualkeyboard *mKeyBoard;

};

#endif // PM_DIALOG_QUICKSAVE_H
