#ifndef RTSA_DIALOG_SPECTROGRAM_CURSOR_H
#define RTSA_DIALOG_SPECTROGRAM_CURSOR_H

#include <QWidget>
#include "rtsa_interface.h"
#include "rtsa_dialog_digitinput.h"
#include <QKeyEvent>

namespace Ui {
class RtSa_Dialog_Spectrogram_Cursor;
}

class RtSa_Dialog_Spectrogram_Cursor : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_Spectrogram_Cursor(RtSa_Dialog_Digitinput *mInput, RtSa_Interface *mInterface, QWidget *parent = 0);
    ~RtSa_Dialog_Spectrogram_Cursor();
    void initDisplay();
    void showInputDialog(qint32 index);
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_edit_Position_clicked();

    void finishEntry_Display(qint32 index);

    void DigitalKeyRespond(QKeyEvent *event);

    void on_pb_cancel_clicked();

    void on_combo_Cursor_currentIndexChanged(int index);

    void on_combo_State_currentIndexChanged(int index);

    void on_pb_ClearAll_clicked();

private:
    void refreshPosition();
    void refreshTime();
    void refreshState();
private:
    Ui::RtSa_Dialog_Spectrogram_Cursor *ui;
    RtSa_Interface *mControl;
    RtSa_Dialog_Digitinput *mInputDialog;
};

#endif // RTSA_DIALOG_SPECTROGRAM_CURSOR_H
