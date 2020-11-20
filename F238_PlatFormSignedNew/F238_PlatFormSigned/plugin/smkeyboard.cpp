#include "smkeyboard.h"
#include "ui_smkeyboard.h"
#include <QKeyEvent>
SmKeyBoard::SmKeyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmKeyBoard)
{
    ui->setupUi(this);
    initMap();
}

SmKeyBoard::~SmKeyBoard()
{
    delete ui;
}

void SmKeyBoard::setTitle(QString str)
{
    ui->lblTitle->setText(str);
    return;
}

void SmKeyBoard::on_pb_cancel_clicked()
{
    this->hide();
    return;
}

void SmKeyBoard::initMap()
{
    qint32 btnCnt;
    key_btn = new QMap<QPushButton*,qint32>;
    key_btn->insert(ui->pb_0,Qt::Key_0);
    key_btn->insert(ui->pb_1,Qt::Key_1);
    key_btn->insert(ui->pb_2,Qt::Key_2);
    key_btn->insert(ui->pb_3,Qt::Key_3);
    key_btn->insert(ui->pb_4,Qt::Key_4);
    key_btn->insert(ui->pb_5,Qt::Key_5);
    key_btn->insert(ui->pb_6,Qt::Key_6);
    key_btn->insert(ui->pb_7,Qt::Key_7);
    key_btn->insert(ui->pb_8,Qt::Key_8);
    key_btn->insert(ui->pb_9,Qt::Key_9);
    key_btn->insert(ui->pb_add,Qt::Key_Minus);
    key_btn->insert(ui->pb_dot,Qt::Key_Period);
    key_btn->insert(ui->pb_del,Qt::Key_Backspace);
    key_btn->insert(ui->pb_clear,Qt::Key_Delete);
    key_btn->insert(ui->pb_enter,Qt::Key_Enter);

    btnCnt = key_btn->size();
    for(qint32 i=0;i<btnCnt;i++)
    {
        connect(key_btn->keys().at(i),SIGNAL(clicked()),this,SLOT(btn_clicked()));
    }
}
void SmKeyBoard::btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    qint32 keyValue;
    Qt::KeyboardModifier keyMod;
    QString keyText;
    //get key value and key text
    keyValue = key_btn->value(btn);
    if(keyValue>=0x21 && keyValue<=0x7E)
    {
        keyText = btn->text();
        char ch = keyText.toLatin1().data()[0];
        keyValue = ch;
    }else if(keyValue == Qt::Key_Space){
        keyText = " ";
    }else
    {
        keyText = "";
    }

    if(Qt::Key_Alt == keyValue)
    {
        keyMod = Qt::AltModifier;
    }else if(Qt::Key_Control == keyValue)
    {
        keyMod = Qt::ControlModifier;
    }else if(Qt::Key_Shift == keyValue)
    {
        keyMod = Qt::ShiftModifier;
    }else
    {
        keyMod = Qt::NoModifier;
    }
    //send key event
    QKeyEvent event(QKeyEvent::KeyPress,keyValue, keyMod,keyText);
    QApplication::sendEvent(qApp->focusWidget(),&event);

    //keyPressEvent(&event);
    return;

}
