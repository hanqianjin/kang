#ifndef F238SCPI_H
#define F238SCPI_H

#include <QMainWindow>

namespace Ui {
class F238SCPI;
}

class F238SCPI : public QMainWindow
{
    Q_OBJECT

public:
    explicit F238SCPI(QWidget *parent = 0);
    ~F238SCPI();

private:
    Ui::F238SCPI *ui;
};

#endif // F238SCPI_H
