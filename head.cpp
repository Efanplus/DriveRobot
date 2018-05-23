#pragma execution_character_set("utf-8")
#include "head.h"
#include "ui_head.h"
#include "qport.h"
#include "qsingleton.h"

Head::Head(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Head)
{
    ui->setupUi(this);
    QFont font("楷体",16);
    QGroupBox *GroupBox = new QGroupBox(tr("头部控制"));
    GroupBox->setFont(font);
    QGridLayout *GridLayout = new QGridLayout;
    this->setLayout(GridLayout);
    GridLayout->addWidget(GroupBox);
    GroupBox->setLayout(ui->gridLayout);

    connect(this,SIGNAL(send_order()),QPort::instance(),SLOT(send_order()));
}

Head::~Head()
{
    delete ui;
}

void Head::on_ZeroButton_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="09";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}

void Head::on_StartButton_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="07";
    //运动时间
    //电机角度控制
    double angle_LR = ui->lineEdit_head_LR->text().toDouble();
    int t_ms = abs((int)((angle_LR/10)*1000));
    int angle_LR_send = ((int)(angle_LR*100+0.5));
    str+=QString("%1").arg(t_ms, 4, 16, QChar('0'));
    str+=QString("%1").arg(angle_LR_send, 4, 16, QChar('0')).right(4);
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}

//void Head::on_Slider_head_LR_valueChanged(int value)
//{
//    QString tem;
//    ui->lineEdit_head_LR->setText(tem.setNum(ui->Slider_head_LR->value()));
//}

//void Head::on_Slider_head_valueChanged(int value)
//{
//    QString tem;
//    ui->lineEdit_head->setText(tem.setNum(ui->Slider_head->value()));
//}

void Head::on_PauseButton_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="05";
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}

void Head::on_StartButton_2_clicked()
{
    QString str;
    str.clear();
    str=order_start;
    str+="08";
    //运动时间
    //电机角度控制
    double angle = ui->lineEdit_head->text().toDouble();
    int angle_send = ((int)(angle*10000+0.5));
    str+=QString("%1").arg(angle_send, 8, 16, QChar('0')).right(8);
    str+=order_end;
    QPort::instance()->str_order = str;
    emit send_order();
}
