#pragma execution_character_set("utf-8")

#include "delta_chest.h"
#include "ui_delta_chest.h"
#include <QMessageBox>
#include <QtMath>

Delta_Chest::Delta_Chest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Delta_Chest)
{
    ui->setupUi(this);
    QFont font("楷体",16);
    QFont font_English("Times New Roman",16);
    QGridLayout *Delta_g_layout = new QGridLayout;
    QGroupBox *Delta = new QGroupBox(tr("Delta"));
//    QGroupBox *Control = new QGroupBox;
//    QWidget *Control = new QWidget;
//    QVBoxLayout *v_control_layout = new QVBoxLayout;
    QGroupBox *Control_coordinate = new QGroupBox(tr("坐标控制"));
    QGroupBox *Control_OneWay = new QGroupBox(tr("单轴控制"));
    QWidget *Control_buttons = new QWidget;
    QVBoxLayout *v_layout = new QVBoxLayout;
    Delta->setFont(font_English);
    Control_coordinate->setFont(font);
    Control_OneWay->setFont(font);
    this->setLayout(Delta_g_layout);
    Delta_g_layout->addWidget(Delta);
    Delta->setLayout(v_layout);


    v_layout->addWidget(Control_coordinate);
    v_layout->addWidget(Control_OneWay);
    v_layout->addWidget(Control_buttons);
    Control_coordinate->setLayout(ui->horizontalLayout_2);
    Control_OneWay->setLayout(ui->gridLayout);
    Control_buttons->setLayout(ui->horizontalLayout);
}

Delta_Chest::~Delta_Chest()
{
    delete ui;
}

void Delta_Chest::inverse_slove(double &re_ang1,double &re_ang2,double &re_ang3,double x,double y,double z)
{
    double K1=(pow(La,2)-pow(Lb,2)-pow(x,2)-pow(y,2)-pow(z,2)-pow((R-r),2)+(R-r)*(sqrt(3)*x+y))/Lb+2*z;
    double U1=(-4)*(R-r-(sqrt(3)/2)*x-(1/2)*y);
    double V1=K1-4*z;

    double K2=(pow(La,2)-pow(Lb,2)-pow(x,2)-pow(y,2)-pow(z,2)-pow((R-r),2)-(R-r)*(sqrt(3)*x-y))/Lb+2*z;
    double U2=(-4)*(R-r+(sqrt(3)/2)*x-(1/2)*y);
    double V2=K2-4*z;

    double K3=(pow(La,2)-pow(Lb,2)-pow(x,2)-pow(y,2)-pow(z,2)-pow((R-r),2)-2*y*(R-r))/Lb+2*z;
    double U3=(-4)*(R-r+y);
    double V3=K3-4*z;


    //关于t的方程判别式，小于0的情况排除，目的是避免了出现奇异位置，同时也不可避免的会出现位置空洞.


   double panbieshi1=pow(U1,2)-4*K1*V1;
   double panbieshi2=pow(U2,2)-4*K2*V2;
   double panbieshi3=pow(U3,2)-4*K3*V3;



   if(panbieshi1<0||panbieshi2<0||panbieshi3<0)
   {

       QMessageBox::warning(this,"warning","the location is not found",QMessageBox::Yes);
   }

   else
   {
       double t11=((-U1)+sqrt(pow(U1,2)-4*K1*V1))/(2*K1);
       double t12=((-U1)-sqrt(pow(U1,2)-4*K1*V1))/(2*K1);

       double t21=((-U2)+sqrt(pow(U2,2)-4*K2*V2))/(2*K2);
       double t22=((-U2)-sqrt(pow(U2,2)-4*K2*V2))/(2*K2);

       double t31=((-U3)+sqrt(pow(U3,2)-4*K3*V3))/(2*K3);
       double t32=((-U3)-sqrt(pow(U3,2)-4*K3*V3))/(2*K3);

       double ang11=2*atan(t11) ;
       double ang12=2*atan(t12) ;
       double ang21=2*atan(t21) ;
       double ang22=2*atan(t22) ;
       double ang31=2*atan(t31) ;
       double ang32=2*atan(t32) ;

       if(ang11>ang12)
           re_ang1=ang11;
       else
           re_ang1=ang12;


       if(ang21>ang22)
           re_ang2=ang21;
       else
           re_ang2=ang22;


       if(ang31>ang32)
           re_ang3=ang31;
       else
           re_ang3=ang32;

       re_ang1=re_ang1*180/M_PI;
       re_ang2=re_ang2*180/M_PI;
       re_ang3=re_ang3*180/M_PI;
   }
}

int Delta_Chest::angle_change_send(double angle)
{
    angle = ((int)(angle*100+0.5))/100.00;
    //角度为负的转化
    if(angle<0)angle=pow(2,15)-angle;
    return angle;
}

void Delta_Chest::on_ZeroButton_clicked()
{

}

void Delta_Chest::on_StartButton_clicked()
{
    double x = ui->x_coordinate->text().toDouble();
    double y = ui->y_coordinate->text().toDouble();
    double z = ui->z_coordinate->text().toDouble();
    double angle_1;
    double angle_2;
    double angle_3;
    inverse_slove(angle_1,angle_2,angle_3,x,y,z);
    int angle1_send = angle_change_send(angle_1);
    int angle2_send = angle_change_send(angle_2);
    int angle3_send = angle_change_send(angle_3);
}

void Delta_Chest::on_PauseButton_clicked()
{

}
