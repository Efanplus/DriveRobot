#pragma execution_character_set("utf-8")
#include "legs.h"
#include "ui_legs.h"

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
    GroupBox->setLayout(ui->gridLayout);
}

Legs::~Legs()
{
    delete ui;
}
