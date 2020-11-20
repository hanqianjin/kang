#ifndef RTSA_DIALOG_DIGITINPUT_H
#define RTSA_DIALOG_DIGITINPUT_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include "rtsa_remote_interface.h"
#include "rtsa_user_variable.h"

namespace Ui {
class RtSa_Dialog_Digitinput;
}

class RtSa_Dialog_Digitinput : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_Digitinput(QWidget *parent = 0);
    ~RtSa_Dialog_Digitinput();
    void setInterface(Rtsa_Remote_Interface *RtsaRemoteInterface);
    void setUserVariable(RtSa_User_Variable* userVariable);
    void initDisplay(qint32 index);
    void setMarkerUpdateID(qint32 index);
    void showFreqUnit(bool isOn);
    void showAmptUnit(bool isOn);
    void showAmptUnitIndex(qint32 index);
    void keyresponse(qint32 keyValue);
    qint32 getEntryNo();
    qint32 getUnitNo();
    void clearEdit();
   protected:
       void keyPressEvent(QKeyEvent *event);
   private slots:
       void on_pb_cancel_clicked();
       void btn_clicked();
       void on_freqBtnUnit1_clicked();

       void on_freqBtnUnit2_clicked();

       void on_freqBtnUnit3_clicked();

       void on_freqBtnUnit4_clicked();

       void on_amptBtnUnit1_clicked();

       void on_amptBtnUnit2_clicked();

       void on_amptBtnUnit3_clicked();

       void on_amptBtnUnit4_clicked();

       void on_amptBtnUnit5_clicked();

       void on_amptBtnUnit6_clicked();

       void on_amptBtnUnit7_clicked();

//       void on_timeBtnUnit1_clicked();

//       void on_timeBtnUnit2_clicked();

//       void on_timeBtnUnit3_clicked();

//       void on_timeBtnUnit4_clicked();

//       void on_btnClear_clicked();

signals:
       void finishEntry(qint32);
       void ClockWiseDown(QKeyEvent *event);
   private:
       int amptdSpecCompareFunc(int unitNo);
       int timeSpecCompareFunc(int unitPos);
       int freqSpecCompareFunc(int unitPos);
       int enterFunc();
       void backSpace();
       void InitKeyboard();
       void keyupControl();
       void keydownControl();
       void keyleftControl();
       void keyrightControl();
       void keyclockwiseControl();
       void keyanticlockwiseControl();
       void valueIncreaseControl();
       void valueDecreaseControl();
       void clearAll();
       void getKnobValue(quint32 mode);
       QString getNewFreqDataStringValue(int clockWiseMode,unsigned long long freStep,int unitNo);
       QString getNewSweepTimeDataStringValue(int clockWiseMode, double sweepTime, int unitNo);
private:
    Ui::RtSa_Dialog_Digitinput *ui;
   Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_User_Variable* m_usr_variable;
//    QWidget* pParent;
//    user_variable* m_usr_variable;
    qint32  entryNo;
    qint32  unitNo;
    char newDataString[20];
    char oldDataString[20];
    bool blNumberInput;
    bool blFirstIn;//Johnson 0703
    //Johnson 0608
    bool blDotInput;
    bool bLeftKey;
    bool bRightKey;
    qint32 highLightIndex;
    bool mShiftKeyPressed;
    qint32 mCurMarkerID;
    QMap <QPushButton*,qint32> mBtnkey; //button -- keyvalue
      enum
      {
          VIRTUAL_KEY_1 = 0, VIRTUAL_KEY_2, VIRTUAL_KEY_3, VIRTUAL_KEY_4,
          VIRTUAL_KEY_5, VIRTUAL_KEY_6, VIRTUAL_KEY_7,
          VIRTUAL_KEY_8, VIRTUAL_KEY_9, VIRTUAL_KEY_0,VIRTUAL_KEY_ACROSS,
          VIRTUAL_KEY_DOT,VIRTUAL_KEY_BACKSPACE,
          VIRTUAL_KEY_CLEARALL,VIRTUAL_KEY_UP,VIRTUAL_KEY_DOWN,VIRTUAL_KEY_LEFT,
          VIRTUAL_KEY_RIGHT
      };
      QPushButton* key_btn[18] =
      {
          NULL
      };
};

#endif // RTSA_DIALOG_DIGITINPUT_H
