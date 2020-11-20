#ifndef RTSA_DIALOG_BWSETUP_H
#define RTSA_DIALOG_BWSETUP_H

#include <QWidget>
#include <QButtonGroup>
#include "rtsa_remote_interface.h"
#include "rtsa_user_variable.h"
#include <QKeyEvent>

namespace Ui {
class RtSa_Dialog_BWSetup;
}

class RtSa_Dialog_BWSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_BWSetup(RtSa_User_Variable *UserVariable = NULL, Rtsa_Remote_Interface *RtsaRemoteInterface = NULL,QWidget *parent = 0);
    ~RtSa_Dialog_BWSetup();
    void InitDisplay();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void InitRBWAutoInfo();
    void InitRBWIndex();
    void InitFFTWindow();
private slots:
    void on_pb_cancel_clicked();

    void RBW_Change(qint32 index);

    void FFT_Change(qint32 index);

    void RbwAuto(qint32 index);

private:
    Ui::RtSa_Dialog_BWSetup *ui;
     Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_User_Variable* globalUserVariable;
    qint32 mCurRBWIndex;
    qint32 mCurFFTWindow;
    QButtonGroup *mRBWGroup;
    QButtonGroup *mFFTGroup;
    QButtonGroup *mAutoGroup;
};

#endif // RTSA_DIALOG_BWSETUP_H
