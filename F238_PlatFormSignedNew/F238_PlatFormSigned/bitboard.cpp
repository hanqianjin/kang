#include "bitboard.h"
#include "ui_bitboard.h"
#include <QKeyEvent>

bitboard::bitboard(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::bitboard)
{
  ui->setupUi(this);
  QRegExp rx("([0-9]*)");
  ui->lineEdit->setValidator(new QRegExpValidator(rx, this));
  initKeyBoard();
}

bitboard::~bitboard()
{
  delete ui;
}

void bitboard::on_pushButton_13_clicked()
{
  this->close();
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2020-01-08}
*/
void bitboard::initKeyBoard()
{
  bitKeymap.insert(ui->pushButton_10,Qt::Key_0);
  bitKeymap.insert(ui->pushButton_6,Qt::Key_1);
  bitKeymap.insert(ui->pushButton_7,Qt::Key_2);
  bitKeymap.insert(ui->pushButton_2,Qt::Key_3);
  bitKeymap.insert(ui->pushButton,Qt::Key_4);
  bitKeymap.insert(ui->pushButton_5,Qt::Key_5);
  bitKeymap.insert(ui->pushButton_9,Qt::Key_6);
  bitKeymap.insert(ui->pushButton_8,Qt::Key_7);
  bitKeymap.insert(ui->pushButton_3,Qt::Key_8);
  bitKeymap.insert(ui->pushButton_4,Qt::Key_9);
  bitKeymap.insert(ui->pushButton_16,Qt::Key_Delete);
  bitKeymap.insert(ui->pushButton_11,Qt::Key_Period);
  bitKeymap.insert(ui->pushButton_12,Qt::Key_Minus);
  bitKeymap.insert(ui->pushButton_14,Qt::Key_Left);
  bitKeymap.insert(ui->pushButton_15,Qt::Key_Right);
  qint32 isumnum = bitKeymap.count();
  qint32 i = 0;
  for(i = 0;i < isumnum;i++)
    {
      connect(bitKeymap.keys().at(i),SIGNAL(clicked()),this,SLOT(keypress_clicked()));
    }
}

///
/// \brief bitboard::on_pushButton_17_clicked
/// push_17~push_20 for respone ctrl
///
void bitboard::on_pushButton_17_clicked()
{

}

void bitboard::on_pushButton_18_clicked()
{

}

void bitboard::on_pushButton_19_clicked()
{

}

void bitboard::on_pushButton_20_clicked()
{

}

void bitboard::keypress_clicked()
{
  qint32 keyval = bitKeymap.find(qobject_cast<QPushButton*>(QObject::sender())).value();
  QString textstr = NULL;
  switch (keyval)
    {
    case Qt::Key_0:
      textstr = QString("0");
      break;
    case Qt::Key_1:
      textstr = QString("1");
      break;
    case Qt::Key_2:
      textstr = QString("2");
      break;
    case Qt::Key_3:
      textstr = QString("3");
      break;
    case Qt::Key_4:
      textstr = QString("4");
      break;
    case Qt::Key_5:
      textstr = QString("5");
      break;
    case Qt::Key_6:
      textstr = QString("6");
      break;
    case Qt::Key_7:
      textstr = QString("7");
      break;
    case Qt::Key_8:
      textstr = QString("8");
      break;
    case Qt::Key_9:
      textstr = QString("9");
      break;
    case Qt::Key_Delete:
      textstr = QString("\117");
      break;
    case Qt::Key_Minus:
      textstr = QString("-1");
      break;
    case Qt::Key_Left:
      textstr = QString("<");
      break;
    case Qt::Key_Right:
      textstr = QString(">");
      break;
    case Qt::Key_Period:
      textstr = QString(".");
      break;
    default:
      break;
    }
  QKeyEvent tmpevent(QEvent::KeyPress,keyval,Qt::NoModifier,textstr);
  QApplication::sendEvent(ui->lineEdit,&tmpevent);
}
