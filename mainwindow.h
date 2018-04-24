#pragma execution_character_set("utf-8")

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arm.h"
#include "delta_chest.h"
#include "eye.h"
#include "head.h"
#include "legs.h"
#include "qport.h"
#include "qsingleton.h"
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected slots:
    void mousePressEvent(QMouseEvent *event);

private:
    Arm *arm;
    Eye *eye;
    Head *head;
    Legs *legs;
    Delta_Chest *delta;
    QLabel *title;
};

#endif // MAINWINDOW_H
