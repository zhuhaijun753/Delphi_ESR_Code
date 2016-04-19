#ifndef RECODE_H
#define RECODE_H

#include <opencv2/opencv.hpp>

#include <reversing.h>
#include <defines.h>

#include <QString>
#include <QFile>
#include <QDebug>
#include <QPixmap>

#define FILE_OPEN  0
#define FILE_CLOSE 1

using namespace cv;

class Recode
{
private:
    int frame;
    Mat mat_video_left,mat_video_right;
    TRACK *track;
    QFile *file;

    VideoWriter *video_writer_left,*video_writer_right;
public:
    Recode();

    void set_filename(QString str, int flag = FILE_OPEN);
    void set_video_left(Mat mat_video_left);
    void set_video_right(Mat mat_video_right);
    void set_data(TRACK* track);
    void Write();
    void Read();
    void stop();

    QPixmap get_video_left();
    QPixmap get_video_right();

    TRACK* get_track();
};

#endif // RECODE_H
