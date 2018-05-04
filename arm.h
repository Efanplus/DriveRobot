#ifndef ARM_H
#define ARM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "qport.h"

namespace Ui {
class Arm;
}

class Arm : public QWidget
{
    Q_OBJECT

public:
    explicit Arm(QWidget *parent = 0);
    ~Arm();

private slots:
    void on_ZeroButton_2_clicked();

    void on_StartButton_2_clicked();

    void on_horizontalSlider_x_2_valueChanged(int value);

    void on_PauseButton_2_clicked();

private:
    Ui::Arm *ui;
    double angle_now = 0;

signals:
    void send_order();
};

#endif // ARM_H
