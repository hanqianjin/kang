#ifndef SA_DIALOG_QUICKSAVE_H
#define SA_DIALOG_QUICKSAVE_H

#include <QDialog>
#include <QDir>
#include <QDesktopWidget>

class controlInterface;
class SA_Dialog_VirtualKeyboard;
namespace Ui {
class SA_Dialog_QuickSave;
}

class SA_Dialog_QuickSave : public QDialog
{
    Q_OBJECT
#define SA_DEFAULT_SCREENSHOTS_PATH  "/app/UserData/Screen"
public:
    explicit SA_Dialog_QuickSave(controlInterface *interface, QWidget *parent = 0);
    ~SA_Dialog_QuickSave();
    void init();
    void setDisplayMode(QString mode);
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_cancel_clicked();
    void on_pb_ok_clicked();
    void on_pb_Cancel_clicked();
    void on_pb_clear_clicked();
private:
    SA_Dialog_VirtualKeyboard *mKeyboard;
    controlInterface* mControl;
    Ui::SA_Dialog_QuickSave *ui;
    QString strInput,savePath;
    QPixmap mScreenShots;
    QWidget *mParent;
    void initVariable();
    void initDisplay();
    void initWidget();
    void initFunc();
    QString getDefaultFileName(QString mSavePath);
    bool SaveScreenShots();
    void backSpace();
    void clearAll();
    qint32 checkFileName(QString mFile);
};

#endif // SA_DIALOG_QUICKSAVE_H
