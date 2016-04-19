#include "video.h"
#include "ui_video.h"

Video::Video(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Video)
{
    track = new TRACK();

    mat_t_left = Mat::zeros(3,3,CV_32F);
    mat_t_right = Mat::zeros(3,3,CV_32F);

    video_capture_left.open(0);
    video_capture_left.set(CV_CAP_PROP_FRAME_WIDTH, LB_VIDEO_WIDTH);
    video_capture_left.set(CV_CAP_PROP_FRAME_HEIGHT, LB_VIDEO_HEIGHT);

    video_capture_right.open(1);
    video_capture_right.set(CV_CAP_PROP_FRAME_WIDTH, LB_VIDEO_WIDTH);
    video_capture_right.set(CV_CAP_PROP_FRAME_HEIGHT, LB_VIDEO_HEIGHT);

    mat_video_left = Mat::zeros(LB_VIDEO_HEIGHT,LB_VIDEO_WIDTH,CV_8UC3);
    putText(mat_video_left,"Video(Left)",Point2f(LB_VIDEO_WIDTH/2-100,LB_VIDEO_HEIGHT/2),2,0.9,Scalar(255,255,255));

    mat_video_right = Mat::zeros(LB_VIDEO_HEIGHT,LB_VIDEO_WIDTH,CV_8UC3);
    putText(mat_video_right,"Video(Right)",Point2f(LB_VIDEO_WIDTH/2-100,LB_VIDEO_HEIGHT/2),2,0.9,Scalar(255,255,255));

    ui->setupUi(this);
    ui->LB_Video_Left->setPixmap(get_video_left());
    ui->LB_Video_Right->setPixmap(get_video_right());

}

Video::~Video()
{
    delete ui;
}

void Video::paint_video(){
    if(video_capture_left.isOpened() == true){
        video_capture_left>>mat_video_left;
        cvtColor(mat_video_left,mat_video_left,CV_RGB2BGR);
        /*
        for(int i = 0; i < 64 ; i++){
            if(track[i].STATUS != TRACK_STATUS_DEFAULT){
                object_x = cal_u(track[i].X,track[i].Y);
                object_y = cal_v(track[i].X,track[i].Y);
                //rectangle(mat_video,Rect(object_x-5,240-object_y-5,10,10),Scalar(255,0,0),2);
                qDebug()<<track[i].id<<" "<<object_x<<" "<<object_y;

                str.sprintf("( %d )", (int)(track[i].id+1) );
                putText(mat_video,str.toStdString(),Point2f(object_x,240-object_y),1,0.8,Scalar(255,0,0));
            }
        }
        */
    }else{
        mat_video_left = Mat::zeros(LB_VIDEO_HEIGHT,LB_VIDEO_WIDTH,CV_8UC3);
        putText(mat_video_left,"Disconnected Video(Left)",Point2f(LB_VIDEO_WIDTH/2-180,LB_VIDEO_HEIGHT/2),2,0.9,Scalar(255,255,255));
    }

    if(video_capture_right.isOpened() == true){
        video_capture_right>>mat_video_right;
        cvtColor(mat_video_right,mat_video_right,CV_RGB2BGR);
    }else{
        mat_video_right = Mat::zeros(LB_VIDEO_HEIGHT,LB_VIDEO_WIDTH,CV_8UC3);
        putText(mat_video_right,"Disconnected Video(Right)",Point2f(LB_VIDEO_WIDTH/2-180,LB_VIDEO_HEIGHT/2),2,0.9,Scalar(255,255,255));
    }
    //imshow("sample" , mat_video);
    ui->LB_Video_Left->setPixmap(get_video_left());
    ui->LB_Video_Right->setPixmap(get_video_right());
}

QPixmap Video::get_video_left(){
    QImage img_map = QImage((unsigned char*)mat_video_left.data, mat_video_left.cols, mat_video_left.rows, mat_video_left.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

QPixmap Video::get_video_right(){
    QImage img_map = QImage((unsigned char*)mat_video_right.data, mat_video_right.cols, mat_video_right.rows, mat_video_right.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

void Video::set_track_data(TRACK *track){
    this->track = track;
}

void Video::set_T_left(Mat mat_t_left){
    this->mat_t_left = mat_t_left;
}

void Video::set_T_right(Mat mat_t_right){
    this->mat_t_right = mat_t_right;
}

float Video::cal_u(float x, float y){
    float a,b,c;
    a = mat_t_left.at<float>(0,0);
    b = mat_t_left.at<float>(1,0);
    c = mat_t_left.at<float>(2,0);
    return a*x+b*y+c;
}

float Video::cal_v(float x, float y){
    float a,b,c;
    a = mat_t_left.at<float>(0,1);
    b = mat_t_left.at<float>(1,1);
    c = mat_t_left.at<float>(2,1);
    return a*x+b*y+c;
}
