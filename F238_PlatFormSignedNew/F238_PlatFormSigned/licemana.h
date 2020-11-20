#ifndef LICEMANA_H
#define LICEMANA_H

#include <QWidget>
#include <QLabel>

namespace Ui {
  class licemana;
}

class licemana : public QWidget
{
  Q_OBJECT

public:
  explicit licemana(QWidget *parent = 0);
  ~licemana();

  void SetTemperSysinfo();
  void OutTest();
private slots:
  void on_pushButton_19_clicked();

private:
  Ui::licemana *ui;

  void Xx(QLabel* pl,qint32 it);
};

#endif // LICEMANA_H
