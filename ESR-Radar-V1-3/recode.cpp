#include "recode.h"

Recode::Recode()
{
    track = new TRACK[MAX_TRACK_SIZE];
    mat_video_left = Mat::zeros(1,1,CV_32F);
    mat_video_right = Mat::zeros(1,1,CV_32F);

    frame = 0;
    file = new QFile();
    video_writer_left = new VideoWriter();
    video_writer_right= new VideoWriter();
}

void Recode::set_data(TRACK *track){
    this->track = track;
}

void Recode::set_video_left(Mat mat_video_left){
    this->mat_video_left = mat_video_left;
}

void Recode::set_video_right(Mat mat_video_right){
    this->mat_video_right = mat_video_right;
}

void Recode::set_filename(QString str, int flag){

    file->setFileName(str);

    if(flag == FILE_OPEN){
        file->open(QIODevice::WriteOnly);
    }

    if(flag == FILE_CLOSE){
        file->open(QIODevice::ReadOnly);
    }

    //
    double fps = 15;
    int fourcc= CV_FOURCC('X','V','I','D');
    video_writer_left->open(str.toStdString(),fourcc,fps,Size(LB_VIDEO_WIDTH,LB_VIDEO_HEIGHT));
    if(video_writer_left->isOpened()){
        qDebug()<<"L : Ture";
    }else{
        qDebug()<<"L : False";
    }

    video_writer_right->open(str.toStdString(),fourcc,fps,Size(LB_VIDEO_WIDTH,LB_VIDEO_HEIGHT));
    if(video_writer_right->isOpened()){
        qDebug()<<"R : Ture";
    }else{
        qDebug()<<"R : False";
    }
}

void Recode::Write(){
    QString content;
    QByteArray byte_str;

    frame++;
    content = QString("@%d\n").arg(frame);
    //data(track)
    for(int i = 0 ; i < MAX_TRACK_SIZE ; i++){
        if(track[i].STATUS != TRACK_DEFAULT){
            content = QString("#%d:%f,%f,%f,%f,%f,%f,%f,%f\n")
                    .arg(i)
                    .arg(track[i].STATUS)
                    .arg(track[i].RANGE)
                    .arg(track[i].ANGLE)
                    .arg(track[i].RANGE_RATE)
                    .arg(track[i].RANGE_ACCEL)
                    .arg(track[i].MED_RANGE_MODE)
                    .arg(track[i].X)
                    .arg(track[i].Y);
            byte_str.append(content);
            file->write(byte_str);
        }
    }
    //video
    *video_writer_left<<mat_video_left;
    *video_writer_right<<mat_video_right;
}

void Recode::Read(){

}

void Recode::stop(){
    file->close();
}

QPixmap Recode::get_video_left(){
    QImage img_map = QImage((unsigned char*)mat_video_left.data, mat_video_left.cols, mat_video_left.rows, mat_video_left.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

QPixmap Recode::get_video_right(){
    QImage img_map = QImage((unsigned char*)mat_video_right.data, mat_video_right.cols, mat_video_right.rows, mat_video_right.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

TRACK* Recode::get_track(){
    return track;
}
