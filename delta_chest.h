#ifndef DELTA_CHEST_H
#define DELTA_CHEST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>


namespace Ui {
class Delta_Chest;
}

class Delta_Chest : public QWidget
{
    Q_OBJECT

public:
    explicit Delta_Chest(QWidget *parent = 0);
    ~Delta_Chest();

private slots:
    void on_ZeroButton_clicked();

    void on_StartButton_clicked();

    void on_PauseButton_clicked();

private:
    Ui::Delta_Chest *ui;

    void inverse_slove(double &,double &,double &,double,double,double);
    int angle_change_send(double angle);

    double La = 110;
    double Lb = 230;
    double R = 65;
    double r = 50;

};

#endif // DELTA_CHEST_H
