#pragma execution_character_set("utf-8")
#include "eye.h"
#include "ui_eye.h"
#include <QDebug>

Eye::Eye(QFrame *parent) :
    QFrame(parent),
    ui(new Ui::Eye)
{
    ui->setupUi(this);
    QVBoxLayout *v_layout = new QVBoxLayout;
    QHBoxLayout *h_layout = new QHBoxLayout;
    QWidget *video = new QWidget;
    QFrame *buttons = new QFrame;
    this->setLayout(v_layout);
    v_layout->addWidget(video);
    v_layout->addWidget(buttons);

    video->setLayout(h_layout);
    h_layout->addWidget(videoL_label);
    h_layout->addWidget(videoR_label);

    buttons->setLayout(ui->horizontalLayout);
    //    video_label->setMaximumHeight(300);
    pic_video = cv::imread("D:\\Qt\\DriveRobot\\DriveRobot\\show.jpg");
    pic = cv::imread("D:\\Qt\\DriveRobot\\DriveRobot\\robto.jpg");
    showpicture(videoL_label,pic_video);
    showpicture(videoR_label,pic);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readFarme()));
//    openCamera();
}

Eye::~Eye()
{
    delete ui;
}

QImage Eye::Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {
        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols, cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                     cvImg.cols,cvImg.rows,
                     cvImg.cols*cvImg.channels(),
                     QImage::Format_RGB888);
    }
    return qImg;
}

void Eye::showpicture(QLabel *label, cv::Mat image)
{
    if(image.empty())
    {
        qDebug() << "the image to show in label is empty";
        return;
    }
    cv::Mat image_change;
    cv::Size v_size(label->size().width(),label->size().height());
    cv::resize(image,image_change,v_size);
//    std::cout << image_change.size << endl;
//    qDebug() << label->size();
//    cv::namedWindow("image_change", CV_WINDOW_NORMAL);
//    cv::imshow("image_change", image_change);
//    cv::waitKey(27);
    QImage qimage = Mat2QImage(image_change);
    label->setPixmap(QPixmap::fromImage(qimage));
//    qimage.scaled(label->width(),label->height(),Qt::KeepAspectRatioByExpanding);
//    qDebug() << "++++++++++++++++++++++++";
    return;
}

cv::Mat Eye::pic_turn90(cv::Mat image,int camera_name)
{
    cv::Mat dst1;
    cv::transpose(image,dst1);
    cv::Mat dst2;
    if(camera_name == 1)
        cv::flip(dst1,dst2,0);
    else if(camera_name == 2)
        cv::flip(dst1,dst2,1);
    return dst2;
}


void Eye::openCamera()
{
    capL.open(0);
    if(!capL.isOpened())
        qDebug() << "frame is empty(L)" << endl;
    capR.open(2);
    if(!capR.isOpened())
        qDebug() << "frame is empty(R)" << endl;
    timer->start(5);//changing the parameter can adjust the response rate
}

void Eye::readFarme()
{
    capL >> frameL;
    frameL = pic_turn90(frameL,1);
    showpicture(videoL_label,frameL);
    capR >> frameR;
    frameR = pic_turn90(frameR,2);
    showpicture(videoR_label,frameR);
}

void Eye::closeCamera()
{
    timer->stop();
    capL.release();
    capR.release();
    videoL_label->clear();
    videoR_label->clear();
    showpicture(videoL_label,pic);
    showpicture(videoR_label,pic);
}

void Eye::on_OpencameraButton_clicked()
{
    openCamera();
}

void Eye::on_ClosecameraButton_clicked()
{
    closeCamera();
}
