#ifndef LEGS_H
#define LEGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "qport.h"
#include "qsingleton.h"


namespace Ui {
class Legs;
}

class Legs : public QWidget
{
    Q_OBJECT

public:
    explicit Legs(QWidget *parent = 0);
    ~Legs();

private slots:
    void on_Zero_Button_clicked();

    void on_Zero_Button_2_clicked();

    void on_Start_Button_2_clicked();

    void on_Start_Button_clicked();

    void on_Close_Button_2_clicked();

    void on_Close_Button_clicked();

    void on_pushButton_clicked();

private:
    Ui::Legs *ui;
    double angle_now_1 = 0;
    double angle_now_2 = 0;
    void update_angle(int num);
    void create_send_order(QString str_order);

signals:
    void send_order();
};

#endif // LEGS_H
