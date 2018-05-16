﻿#ifndef DELTA_CHEST_H
#define DELTA_CHEST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "qport.h"

#define angle1_zero 30
#define angle2_zero 30
#define angle3_zero 30

#define x_zero 0
#define y_zero 0
#define z_zero -321.0946


namespace Ui {
class Delta_Chest;
}

class Delta_Chest : public QWidget
{
    Q_OBJECT

public:
    explicit Delta_Chest(QWidget *parent = 0);
    ~Delta_Chest();

    void onemovesendturn(double angle1,double angle2,double angle3);
    int t_ms = 8000;

private slots:
    void on_ZeroButton_clicked();

    void on_StartButton_clicked();

    void on_PauseButton_clicked();

    void on_lineEdit_x_textChanged(const QString &arg1);

    void on_lineEdit_y_textChanged(const QString &arg1);

    void on_lineEdit_z_textChanged(const QString &arg1);

    void on_horizontalSlider_x_sliderReleased();

    void on_horizontalSlider_y_sliderReleased();

    void on_horizontalSlider_z_sliderReleased();

private:
    Ui::Delta_Chest *ui;

    void inverse_slove(double &,double &,double &,double,double,double);
    int angle_change_send(double angle);
    int caculate_time(double angle1,double angle2,double angle3);

    // 此位置lb为主动臂，la为从动臂，位置互换。
    double La = 245;
    double Lb = 110;
    double R = 65;
    double r = 25;

    double angle_1;
    double angle_2;
    double angle_3;

    double x_now = x_zero;
    double y_now = y_zero;
    double z_now = z_zero;
    void setvalue_now();
    double now_ang1 = angle1_zero;
    double now_ang2 = angle2_zero;
    double now_ang3 = angle3_zero;

    double x_axis;
    double y_axis;
    double z_axis;

signals:
    void send_order();


};

#endif // DELTA_CHEST_H
