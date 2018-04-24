#pragma execution_character_set("utf-8")
#include "head.h"
#include "ui_head.h"

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
}

Head::~Head()
{
    delete ui;
}
