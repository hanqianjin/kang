#ifndef BITBOARD_H
#define BITBOARD_H

#include <QDialog>
#include <QPushButton>
#include <QMap>

namespace Ui {
  class bitboard;
}

class bitboard : public QDialog
{
  Q_OBJECT

public:
  explicit bitboard(QWidget *parent = 0);
  ~bitboard();

private slots:
  void on_pushButton_13_clicked();

  void on_pushButton_17_clicked();

  void on_pushButton_18_clicked();

  void on_pushButton_19_clicked();

  void on_pushButton_20_clicked();

  void keypress_clicked();
private:
  Ui::bitboard *ui;
  QMap<QPushButton*,qint32> bitKeymap;
  void initKeyBoard();
};

#endif // BITBOARD_H

