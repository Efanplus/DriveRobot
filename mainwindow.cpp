#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    arm = new Arm;
    eye = new Eye;
    head = new Head;
    legs = new Legs;
    delta = new Delta_Chest;
    QVBoxLayout *v_layout = new QVBoxLayout(ui->centralWidget);

    title = new QLabel(tr("驾驶机器人"));
    QFont font("楷体",28);
    title->setFont(font);
    title->setAlignment(Qt::AlignHCenter);
    title->setScaledContents(true);

    //机器人照片
    QWidget *robot_pic_w = new QWidget;
//    robot_pic_w->setMaximumSize(400,280);
    QGridLayout *robot_pic_layout = new QGridLayout;
    robot_pic_w->setLayout(robot_pic_layout);
    cv::Mat pic = cv::imread("D:\\Qt\\DriveRobot\\AutoDriveRobot\\robto.jpg");
    QLabel *robot_pic = new QLabel;
    robot_pic_layout->addWidget(robot_pic);
    eye->showpicture(robot_pic,pic);
//    gridlayout->addWidget(robot_pic_w,0,2);

    //串口，眼图像，照片
    QHBoxLayout *h_layout_port_eye = new QHBoxLayout;
    h_layout_port_eye->addWidget(QPort::instance());
    h_layout_port_eye->addWidget(eye);
    h_layout_port_eye->addWidget(robot_pic_w);

    //头和胳膊
    QVBoxLayout *v_layout_head_arm = new QVBoxLayout;
    v_layout_head_arm->addWidget(head);
    v_layout_head_arm->addWidget(arm);
    QWidget *head_arm = new QWidget;
    head_arm->setLayout(v_layout_head_arm);

    //控制模块
    QHBoxLayout *h_layout_controrl = new QHBoxLayout;
    h_layout_controrl->addWidget(head_arm);
    h_layout_controrl->addWidget(delta);
    h_layout_controrl->addWidget(legs);
    QGroupBox *groupbox_control = new QGroupBox;
    groupbox_control->setLayout(h_layout_controrl);


    //将主要功能放到一个frame中
    QFrame *main_layout_box = new QFrame;
    QVBoxLayout *v_layout_main = new QVBoxLayout;
    v_layout_main->addLayout(h_layout_port_eye);
    v_layout_main->addWidget(groupbox_control);
    main_layout_box->setLayout(v_layout_main);

    v_layout->addWidget(title);
    v_layout->addWidget(main_layout_box);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}
