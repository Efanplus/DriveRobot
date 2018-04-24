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
}

Arm::~Arm()
{
    delete ui;
}
