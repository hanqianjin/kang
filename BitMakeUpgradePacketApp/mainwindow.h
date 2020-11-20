#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

typedef struct updatep
{
  qint32 itype;//File Folder:0\nFile:1\nExtension:2
  char name[64];
}UPDATEPRO,*PUPDATEPRO;
typedef struct uppro
{
  qint32 isum;
  char swver[64];
  char hwver[64];
  char update[64];
}UPPRO,*PUPPRO;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

//  void keyPressEvent(QKeyEvent *event);
private:
  Ui::MainWindow *ui;

  void GetSum();
  void GenConfig();
  UPPRO upproperty;
  PUPDATEPRO upitempro;

private:
  UPPRO readpro;
  UPDATEPRO readitempro;  
};

#endif // MAINWINDOW_H
