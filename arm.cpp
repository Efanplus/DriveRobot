#pragma execution_character_set("utf-8")
#include "arm.h"
#include "ui_arm.h"

Arm::Arm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arm)
{
    ui->setupUi(this);
    QFont font("楷体",16);
    QGroupBox *GroupBox = new QGroupBox(tr("臂控制"));
    GroupBox->setFont(font);
    QGridLayout *GridLayout = new QGridLayout;
    QVBoxLayout *v_layout = new QVBoxLayout;
    QGroupBox *control = new QGroupBox;
    QGroupBox *show_now = new QGroupBox;
    this->setLayout(GridLayout);
    GridLayout->addWidget(GroupBox);
    GroupBox->setLayout(v_layout);
    v_layout->addWidget(control);
    control->setLayout(ui->gridLayout_2);
    v_layout->addWidget(show_now);
    show_now->setLayout(ui->horizontalLayout_3);
    connect(this,SIGNAL(send_order()),QPort::instance(),SLOT(send_order()));
}

Arm::~Arm()
{
    delete ui;
}

void Arm::on_ZeroButton_2_clicked()
{
    QString str;
    str.clear();
    str="23";
    str+="2001";
    str+="24";
    QPort::instance()->str_order = str;
    emit send_order();
    angle_now = 0;
    QString tem;
    ui->lineEdit_arm_now->setText(tem.setNum(angle_now));
}

void Arm::on_StartButton_2_clicked()
{
    QString str;
    str.clear();
    str="23";
    str += "21";
    double angle = ui->lineEdit_arm->text().toDouble();
    if(angle > 0)
        str += "00";
    else
        str += "01";
    /****************************
     * 电机速度设定
     * **************************/
    str += "32";

    uint angle_send = (int)(abs(angle) * 10 + 0.5);
    str += QString("%1").arg(angle_send,4,16,QLatin1Char('0'));
    str+="24";
    QPort::instance()->str_order = str;
    emit send_order();
    angle_now = ui->lineEdit_arm_now->text().toDouble();
    angle_now += angle;
    QString tem;
    ui->lineEdit_arm_now->setText(tem.setNum(angle_now));
}

void Arm::on_horizontalSlider_x_2_valueChanged(int value)
{
    QString tem;
    ui->lineEdit_arm->setText(tem.setNum(ui->horizontalSlider_x_2->value()));
}

void Arm::on_PauseButton_2_clicked()
{
    QString str;
    str.clear();
    str="23";
    str+="260B";
    str+="24";
    QPort::instance()->str_order = str;
    emit send_order();
}
