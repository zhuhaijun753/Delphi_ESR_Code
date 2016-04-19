#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>

#include <defines.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <reversing.h>

using namespace cv;

namespace Ui {
class Video;
}

class Video : public QMainWindow
{
    Q_OBJECT

public:
    explicit Video(QWidget *parent = 0);
    ~Video();
    void set_track_data(TRACK* track);

    void paint_video();
    QPixmap get_video_left();
    QPixmap get_video_right();

    void set_T_left(Mat mat_t_left);
    void set_T_right(Mat mat_t_right);

private:
    Ui::Video *ui;

    Mat mat_video_left;
    Mat mat_t_left;
    VideoCapture video_capture_left;

    Mat mat_video_right;
    Mat mat_t_right;
    VideoCapture video_capture_right;

    TRACK *track;
    QString str;

    float object_x,object_y;//u,v
    float cal_u(float x, float y);
    float cal_v(float x, float y);
};

#endif // VIDEO_H
