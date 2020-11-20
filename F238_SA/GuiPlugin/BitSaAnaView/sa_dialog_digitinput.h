#ifndef SA_DIALOG_DIGITINPUT_H
#define SA_DIALOG_DIGITINPUT_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QPushButton>
#include <QDebug>
class controlInterface;
class user_variable;

namespace Ui {
class SA_Dialog_DigitInput;
}

class SA_Dialog_DigitInput : public QDialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_DigitInput(controlInterface *interface,user_variable *puser_variable,qint32 index, QWidget *parent = 0);
    ~SA_Dialog_DigitInput();
    void initDisplay(qint32 index = -1);
    void initInputKey(QKeyEvent *event);
    Ui::SA_Dialog_DigitInput *ui;
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
private:
    int amptdSpecCompareFunc(int unitNo);
    int timeSpecCompareFunc(int unitPos);
    int freqSpecCompareFunc(int unitPos);
    void clearAll();
    void backSpace();
    void keyresponse(qint32 keyValue);
    void InitKeyboard();
    void keyupControl();
    void keydownControl();
    void keyleftControl();
    void keyrightControl();
    void keyclockwiseControl();
    void keyanticlockwiseControl();
    void valueIncreaseControl();
    void valueDecreaseControl();
    void getKnobValue(quint32 mode);
    QString getNewFreqDataStringValue(qint32 clockWiseMode, quint64 freStep, qint32 unitNo);
    QString getNewSweepTimeDataStringValue(int clockWiseMode, double sweepTime, int unitNo);
    void getInitialAmplitudeVal(double amplitudeValue, uint entryNo, char *dataStr,int amplitudeUnit = 0);
private:
    QWidget *mParent;
    controlInterface* mControl;
    user_variable *globalUserVariable;
    qint32  entryNo;
    qint32  unitNo;
    qint32 mDialogIndex;
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
    QPushButton* key_btn[19];
};

#endif // SA_DIALOG_DIGITINPUT_H
