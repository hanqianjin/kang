#ifndef PM_DIALOG_DIGITINPUT_H
#define PM_DIALOG_DIGITINPUT_H

#include <QWidget>
#include <QMap>
#include <QPushButton>
#include "pm_interface.h"
#include "pm_user_variable.h"
#define BUTTON_MUM 18
namespace Ui {
class Pm_Dialog_Digitinput;
}

class Pm_Dialog_Digitinput : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_Digitinput(QWidget *parent = 0);
    ~Pm_Dialog_Digitinput();
private:
    void InitKeyboard();

public:
    void setInterface(BitPm_Interface *BitPmInterface);
    void showFreqUnit(bool isOn);
    void showAmptUnit(bool isOn);

    void initDisplay(qint32 index);

    void keyresponse(qint32 keyValue);
    void showAmptUnitIndex(qint32 index);
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

signals:
       void finishEntry(qint32);
       void ClockWiseDown(QKeyEvent *event);
   private:
       int amptdSpecCompareFunc(int unitNo);
       int timeSpecCompareFunc(int unitPos);
       int freqSpecCompareFunc(int unitPos);
       int enterFunc();
       void backSpace();
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
       QString getNewFreqDataStringValue(int clockWiseMode, qulonglong freStep,int unitNo);
       void getInitialAmplitudeVal(qreal amplitudeValue,uint entryNo,char *dataStr,qint32 amplitudeUnit);
private:
       Ui::Pm_Dialog_Digitinput *ui;
    BitPm_Interface *PmInterfaceObj;

    qint32  entryNo;
    qint32  unitNo;
    char newDataString[20];
    char oldDataString[20];
    bool blNumberInput;
    bool blFirstIn;

    bool blDotInput;
    bool bLeftKey;
    bool bRightKey;
    qint32 highLightIndex;

    bool mShiftKeyPressed;
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
      QPushButton* key_btn[BUTTON_MUM];
};

#endif // PM_DIALOG_DIGITINPUT_H
