#pragma execution_character_set("utf-8")
#include "eye.h"
#include "ui_eye.h"
#include <QDebug>

Eye::Eye(QFrame *parent) :
    QFrame(parent),
    ui(new Ui::Eye)
{
    ui->setupUi(this);
    QGridLayout *gridlayout = new QGridLayout;
    this->setLayout(gridlayout);
    gridlayout->addWidget(video_label);
//    video_label->setMaximumHeight(300);
    pic_video = cv::imread("D:\\Qt\\DriveRobot\\AutoDriveRobot\\show.jpg");
    pic = cv::imread("D:\\Qt\\DriveRobot\\AutoDriveRobot\\robto.jpg");
    showpicture(video_label,pic_video);

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

void Eye::openCamera()
{
    cap.open(0);
    if(!cap.isOpened())
        qDebug() << "frame is empty" << endl;
    timer->start(5);//changing the parameter can adjust the response rate
}

void Eye::readFarme()
{
    cap >> frame;
    showpicture(video_label,frame);
}

void Eye::closeCamera()
{
    timer->stop();
    cap.release();
    video_label->clear();
    showpicture(video_label,pic);
}
