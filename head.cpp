#pragma execution_character_set("utf-8")
#include "head.h"
#include "ui_head.h"
#include "qport.h"

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
    str="23";
    str+="08";
    str+="24";
    QPort::instance()->str_order = str;
    emit send_order();
}

void Head::on_StartButton_clicked()
{
    QString str;
    str.clear();
    str="23";
    str+="07";
    //运动时间
    //电机角度控制
    double angle_LR = ui->lineEdit_head_LR->text().toDouble();
    double angle = ui->lineEdit_head->text().toDouble();
    angle = ((int)(angle*100+0.5));
    str+=QString("%1").arg((int)angle, 4, 16, QChar('0')).right(4);
    str+="24";
    QPort::instance()->str_order = str;
    emit send_order();
}
