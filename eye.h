#pragma execution_character_set("utf-8")
#ifndef EYE_H
#define EYE_H

#include <QWidget>
#include <QFrame>
#include <opencv/cv.h>
#include <opencv/cxcore.hpp>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QTimer>
#include <QString>
#include <string>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include <math.h>
#include <QGroupBox>
#include <QLayout>

using namespace std;
using namespace cv;

namespace Ui {
class Eye;
}

class Eye : public QFrame
{
    Q_OBJECT

public:
    explicit Eye(QFrame *parent = 0);
    ~Eye();
    QImage Mat2QImage(cv::Mat cvImg);

    QLabel *video_label = new QLabel;
    cv::Mat pic_video;
    cv::Mat pic;

    void showpicture(QLabel *label, cv::Mat image);

private:
    Ui::Eye *ui;

private:
    cv::VideoCapture cap;
    QTimer *timer;
    cv::Mat frame;
    //定义移动驾驶机器人的相机地址
    const string address1 = "http://192.168.10.123:7060/?action=stream.mjpg";
    const string address2 = "http://192.168.10.123:7060/?action=stream.mjpg";

private slots:
    void openCamera();
    void readFarme();
    void closeCamera();

};

#endif // EYE_H
