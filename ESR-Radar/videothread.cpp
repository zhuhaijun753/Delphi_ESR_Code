#include "videothread.h"

videothread::videothread()
{
    capture = NULL;

}

bool videothread::init(){
    capture.open(0);

    if(!capture.isOpened()){
        state = false;
    }else{
        state = true;
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    }

    return state;
}

void videothread::run(){
    while(state){
        capture>>convert_mat;
        cvtColor(convert_mat,result_mat,CV_RGB2BGR);
        //측정해서 객채 위치 그리기
        line(result_mat,Point(5,160),Point(635,160),CV_RGB(0,0,255),3);
        line(result_mat,Point(5,320),Point(635,320),CV_RGB(0,0,255),3);

    }
}

QImage videothread::get_image(){
    //cv::Mat color_image(origin->height,origin->width,CV_8UC3,origin->imageData) ,convert_image;

    return_image = QImage((uchar*) result_mat.data, result_mat.cols, result_mat.rows, result_mat.step, QImage::Format_RGB888);
    return return_image;
}

void videothread::stop(){
    state = false;
}

void videothread::set_state(int state){
    this->state = state;
}

Mat videothread::get_frame(){
    return result_mat;
}
