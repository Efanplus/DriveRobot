#pragma execution_character_set("utf-8")
#include "legs.h"
#include "ui_legs.h"
#include <QFrame>

Legs::Legs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Legs)
{
    ui->setupUi(this);
    QFont font("楷体",16);
    QGroupBox *GroupBox = new QGroupBox(tr("腿部控制"));
    GroupBox->setFont(font);
    QGridLayout *GridLayout = new QGridLayout;
    this->setLayout(GridLayout);
    GridLayout->addWidget(GroupBox);
    QVBoxLayout *v_layout = new QVBoxLayout;
    GroupBox->setLayout(v_layout);
    QFrame *frame1 = new QFrame;
    QFrame *frame2 = new QFrame;
    frame1->setLayout(ui->gridLayout_2);
    frame2->setLayout(ui->gridLayout_3);
    v_layout->addWidget(frame1);
    v_layout->addWidget(frame2);
    connect(this,SIGNAL(send_order()),QPort::instance(),SLOT(send_order()));
}

Legs::~Legs()
{
    delete ui;
}

void Legs::on_Zero_Button_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="2004";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
    update_angle(1);
    str.clear();
    str=order_start;
    str+="2005";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
    update_angle(2);
}

void Legs::on_Zero_Button_2_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="2002";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
    str.clear();
    str=order_start;
    str+="2003";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}

void Legs::on_Start_Button_2_clicked()
{
    if(!ui->lineEdit_A->text().isEmpty())
    {
        QString str;
        str.clear();
        str=order_start;
        str+="240001";
        str+=order_end;
        QPort::instance()->str_order = str;
        emit send_order();
        str.clear();
        str=order_start;
        str+="240100";
        str+=order_end;
        QPort::instance()->str_order = str;
        emit send_order();

        str.clear();
        str=order_start;
        str += "22";
        str += "0A";
        double joint_v = 10;
        str += QString("%1").arg((int)(joint_v*Proportion_angle_pulse),4,16,QLatin1Char('0'));
        double angle_1 = ui->lineEdit_A->text().toDouble();
        int angle_1_send = angle_1*Proportion_angle_pulse;
        str += QString("%1").arg(angle_1_send,8,16,QLatin1Char('0')).right(8);
        str += order_end;
        QPort::instance()->str_order = str;
        emit send_order();
        ui->lineEdit_A->clear();
    }
    else if(!ui->lineEdit_B->text().isEmpty())
    {
        QString str;
        str.clear();
        str=order_start;
        str+="240101";
        str+=order_end;
        QPort::instance()->str_order = str;
        emit send_order();
        str.clear();
        str=order_start;
        str+="240000";
        str+=order_end;
        QPort::instance()->str_order = str;
        emit send_order();

        str.clear();
        str=order_start;
        str += "22";
        str += "0C";
        double joint_v = 10;
        str += QString("%1").arg((int)(joint_v*Proportion_angle_pulse),4,16,QLatin1Char('0'));
        double angle_2 = ui->lineEdit_B->text().toDouble();
        int angle_2_send = angle_2*Proportion_angle_pulse;
        str += QString("%1").arg(angle_2_send,8,16,QLatin1Char('0')).right(8);
        str += order_end;
        QPort::instance()->str_order = str;
        emit send_order();
        ui->lineEdit_B->clear();
    }
}

void Legs::on_Start_Button_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str += "25";

    if(!ui->lineEdit_C->text().isEmpty())
    {
        str += "00";//定义三电机为左腿踏板电机
        double angle_3 = ui->lineEdit_C->text().toDouble();
        int angle_3_send = (int)(abs(angle_3)*10+0.5);
        if(angle_3 > 0)
            str += "00";
        else
            str += "01";
        str += QString("%1").arg(angle_3_send,4,16,QLatin1Char('0'));
        angle_now_1 += angle_3;
        update_angle(1);
    }
    else if(!ui->lineEdit_D->text().isEmpty())
    {
        str += "01";//定义三电机为左腿踏板电机
        double angle_4 = ui->lineEdit_D->text().toDouble();
        int angle_4_send = (int)(abs(angle_4)*10+0.5);
        if(angle_4 > 0)
            str += "00";
        else
            str += "01";
        str += QString("%1").arg(angle_4_send,4,16,QLatin1Char('0'));
        angle_now_2 += angle_4;
        update_angle(2);
    }
    str += order_end;
    QPort::instance()->str_order = str;
    emit send_order();
    ui->lineEdit_C->clear();
    ui->lineEdit_D->clear();
}

void Legs::update_angle(int num)
{
    QString tem;
    if(num == 1)
        ui->lineEdit->setText(tem.setNum(angle_now_1));
    else if(num == 2)
        ui->lineEdit_2->setText(tem.setNum(angle_now_2));
}

void Legs::create_send_order(QString str_order)
{
    QString str;
    str.clear();
    str=order_start;
    str+=str_order;
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}

void Legs::on_Close_Button_2_clicked()
{
    create_send_order("260A");
    create_send_order("260C");
}

void Legs::on_Close_Button_clicked()
{
    create_send_order("260D");
    create_send_order("260E");
}


/***********************************
*@抱闸松开
* ************************************/
void Legs::on_pushButton_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="240001";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
    str.clear();
    str=order_start;
    str+="240101";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}
