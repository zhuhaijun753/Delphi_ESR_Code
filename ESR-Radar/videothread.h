#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QDebug>
using namespace cv;

class videothread : public QThread
{
    Q_OBJECT
private :
    void run();
    VideoCapture capture;//릴리즈 설정해야됨
    Mat convert_mat,result_mat;

    QImage return_image;

    bool state;

public:
    videothread();

    bool init();
    QImage get_image();
    void stop();
    void set_state(int state);
    Mat get_frame();
};

#endif // VIDEOTHREAD_H
