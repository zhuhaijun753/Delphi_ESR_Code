#include "view.h"

View::View()
{
    //
    track = new TRACK[MAX_TRACK_SIZE];
    //트랙 초기화
    for(int i = 0 ; i < MAX_TRACK_SIZE ; i++){
        track[i].AMP = 0;
        track[i].ANGLE = 0;
        track[i].BRIDGE = 0;
        track[i].GROUPING = 0;
        track[i].id = 0;
        track[i].LAT_RATE = 0;
        track[i].MED_RANGE_MODE = 0;
        track[i].ONCOMMING = 0;
        track[i].RANGE = 0;
        track[i].RANGE_ACCEL = 0;
        track[i].RANGE_RATE = 0;
        track[i].ROLLING = 0;
        track[i].STATUS = 0;
        track[i].WIDTH = 0;
        track[i].X = 0;
        track[i].Y = 0;
        track_color[i] = Scalar(random(100,200),random(100,200),random(100,200));
    }

    vector_track = new vector<TRACK>[MAX_TRACK_SIZE];

    //룰 생성
    extraction_rule = new Rule();

    //맵 초기설정
    mat_map = Mat::zeros(LB_VIEW_HEIGHT,LB_VIEW_WIDTH,CV_8UC3);

    //줌 크기 설정
    for(int i = 0; i < ZOOM_SIZE ; i++){
        zoom_length.view_height_langth[i]=200-i*20;
        zoom_length.view_width_langth[i]=-100+i*10;
    }
    //배경
    background_line_color = Scalar(255,160,47);
    background_text_color = Scalar(100,100,100);
    background_ellipse_color = Scalar(50,50,50);

    //영역 구분을 위한 색상 표기
    Scalar tmp_color[TRACK_AREA_MUMBER] = {
        Scalar(200,0,0),Scalar(200,0,50),Scalar(200,0,100),
        Scalar(200,0,150),Scalar(200,0,200),Scalar(150,0,200),
        Scalar(100,0,200),Scalar(50,0,200),Scalar(0,0,200),
        Scalar(0,50,200),Scalar(0,100,200),Scalar(0,150,200),
        Scalar(0,200,200),Scalar(0,200,150),Scalar(0,200,100),
        Scalar(0,200,50),Scalar(0,200,0),Scalar(255,255,255)
    };

    for(int i = 0 ; i < TRACK_AREA_MUMBER ; i++){
        track_color[i] = tmp_color[i];
    }

    for(int i = 0; i < TRACK_AREA_MUMBER ; i++){
        track_ellipse_color[i] =  tmp_color[i];
    }

    //fps
    fps = 0;
    frame = 0;
}

View::~View(){
}

//Set Value
void View::set_zoom_data(Zoom zoom){
    this->zoom = zoom;
}

void View::set_data_measurement(Limit data_measurement){
    this->data_measurement = data_measurement;
}

void View::set_track_data(TRACK *track){
    this->track = track;
}

void View::set_track_vector_data(vector<TRACK> *vector_track){
    this->vector_track = vector_track;
}

//Main View
void View::paint_init(){
    set_background_map();
}

void View::paint_view(){
    //여기다 FPS 표시
    set_background_map();
    set_track_map();
}

QPixmap View::get_view(){
    QImage img_map = QImage((unsigned char*)mat_map.data, mat_map.cols, mat_map.rows, mat_map.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

void View::set_background_map(){


    //qDebug()<<fps_view_start_time.currentTime().second()<<" "<<fps_view_start_time.currentTime().msec();
    fps_view_start_time = clock();

    //맵 초기화
    mat_map = Mat::zeros(LB_VIEW_HEIGHT,LB_VIEW_WIDTH,CV_8UC3);

    //레이더 센서 범위 그림(large)
    ellipse(mat_map,
            RotatedRect(
                Point2f(LB_VIEW_WIDTH/2,LB_VIEW_HEIGHT),
                Size2f(
                    (float)(174.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2) ,
                    (float)(174.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2)
                ),
                PIXEL_RADUATION_SIZE
                ),
            Scalar(0,0,255),2
            );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,255),2
    );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,255),2
    );
    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );
    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );
    //레이더 센서 범위 그림(mid)
    ellipse(mat_map,
            RotatedRect(
                Point2f(LB_VIEW_WIDTH/2,LB_VIEW_HEIGHT),
                Size2f(
                    (float)(60.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2) ,
                    (float)(60.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2)
                ),
                PIXEL_RADUATION_SIZE
                ),
            Scalar(255,0,0),2
            );

    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(255,0,0),2
    );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(255,0,0),2
    );


    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );

    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );

    //세로 눈금
    for(int i = 0; i < ZOOM_SEPERATE ; i++){
        //line(mat_map,Point(LB_VIEW_WIDTH/2,i*PIXEL_RADUATION_SIZE) , Point(LB_VIEW_WIDTH/2 + 5,i*PIXEL_RADUATION_SIZE),background_line_color);
        tmp_float = (zoom_length.view_height_langth[zoom.level] - i*(REAL_RADUATION_SIZE-zoom.level));
        str.sprintf("%3.0f(m)",tmp_float);
        putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH/2-15,i*PIXEL_RADUATION_SIZE),1,0.5,background_text_color);
    }

    //가로 눈금
    for(int i = 1; i < ZOOM_SEPERATE ; i++){
        line(mat_map,Point(i*PIXEL_RADUATION_SIZE,LB_VIEW_HEIGHT) , Point(i*PIXEL_RADUATION_SIZE,LB_VIEW_HEIGHT-5),background_line_color);
        tmp_float = ( zoom_length.view_width_langth[zoom.level]+i*(REAL_RADUATION_SIZE-zoom.level) );
        //str.setNum(tmp_float);
        str.sprintf("%2.0f(m)",tmp_float);
        putText(mat_map,str.toStdString(),Point(i*PIXEL_RADUATION_SIZE-7,LB_VIEW_HEIGHT-7),1,0.5,background_text_color);
    }

    //원형으로 영역 표시(측정 최대 거리에서 상대적인 표현)
    for(int i = 0; i <= ZOOM_SEPERATE ; i++){
        ellipse(mat_map,RotatedRect(Point2f(LB_VIEW_WIDTH/2,LB_VIEW_HEIGHT),Size2f(PIXEL_RADUATION_SIZE*i*2,PIXEL_RADUATION_SIZE*i*2),PIXEL_RADUATION_SIZE),background_ellipse_color);
    }

    //축설명
    str.sprintf("- : Long Range");
    putText(mat_map,str.toStdString(),Point(2,10),1,0.7,Scalar(0,0,255));
    str.sprintf("- : Mid Range");
    putText(mat_map,str.toStdString(),Point(2,25),1,0.7,Scalar(255,0,0));
    str.sprintf("o : Track");
    putText(mat_map,str.toStdString(),Point(2,40),1,0.7,Scalar(255,255,255));

    //배경 라운드
    rectangle(mat_map,Rect(0,0,LB_VIEW_WIDTH,LB_VIEW_HEIGHT),background_line_color);

}

void View::set_track_map(){

    extraction_rule->set_data_measurement(data_measurement);

    for(int i = 0; i < MAX_TRACK_SIZE ; i++){
        extraction_rule->set_track(track[i]);
        if(extraction_rule->analysis() ){
            paint_target_using_med_range(i);
            paint_track(i);
        }
    }

    fps_view_end_time = clock();
    frame++;
    fps =(double)(fps_view_end_time-fps_view_start_time)/CLOCKS_PER_SEC;
    str.sprintf("Frame : %ld" , frame);
    putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH-90,10),1,0.7,Scalar(0,255,255));
    str.sprintf("Speed : %0.3f" , fps);
    putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH-90,25),1,0.7,Scalar(0,255,255));

}

void View::paint_target_using_med_range(int i){
    //타겟 융합 범위
    if(track[i].MED_RANGE_MODE == TRACK_MR_UPDATE_ONLY){
        //트랙 거리 정확도
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_ERROR_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_ERROR_RATE),PIXEL_RADUATION_SIZE ),Scalar(255,255,0));
        //서로 다른 두 타갯 융합 영역(거리 기준)
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE),PIXEL_RADUATION_SIZE ),Scalar(255,255,0), 1 , 10);
        //서로 다른 두 타갯 융합 영역(각도 기준)
        line(mat_map,
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],-6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],-6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Scalar(255,255,0)
        );
    }

    if(track[i].MED_RANGE_MODE == TRACK_LR_UPDATE_ONLY){
        //트랙 거리 정확도
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_LR_DISTANCE_ERROR_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_LR_DISTANCE_ERROR_RATE),PIXEL_RADUATION_SIZE ),Scalar(0,255,255));
        //서로 다른 두 타갯 융합 영역(거리 기준)
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_LR_DISTANCE_FUSION_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_LR_DISTANCE_FUSION_RATE),PIXEL_RADUATION_SIZE ),Scalar(0,255,255), 1, 10);
        //서로 다른 두 타갯 융합 영역(각도 기준)
        line(mat_map,
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],2)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],2)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],-2)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],-2)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Scalar(0,255,255)
        );
    }

    if(track[i].MED_RANGE_MODE == TRACK_MR_LR_UPDATE){
        //트랙 거리 정확도
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_ERROR_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_ERROR_RATE),PIXEL_RADUATION_SIZE ),Scalar(0,255,0));
        //서로 다른 두 타갯 융합 영역(거리 기준)
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) )
                                     , Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE),PIXEL_RADUATION_SIZE ),Scalar(0,255,0), 1 , 10);
        //서로 다른 두 타갯 융합 영역(각도 기준)
        line(mat_map,
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Point2f(
                 LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(track[i],-6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
                 LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(track[i],-6)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
             ),
             Scalar(0,255,0)
        );
    }
}

void View::paint_track(int i){

    if(track[i].RANGE_RATE > TRACK_RANGE_RATE_ERROR_RATE){
        //다가올 때
        //트랙 중점
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) ) , Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,0,0));
        //트랙 속도
        str.sprintf("Rate : %3.1f", track[i].RANGE_RATE );
        putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)+TRACK_SIZE,check_track_y_axis(i)-11),1,0.7,Scalar(255,0,0));
    }else if(track[i].RANGE_RATE < -TRACK_RANGE_RATE_ERROR_RATE){
        //다가갈 때
        //트랙 중점
        ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) ) , Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(0,255,0));
        //트랙 속도
        str.sprintf("Rate : %3.1f", track[i].RANGE_RATE );
        putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)+TRACK_SIZE,check_track_y_axis(i)-11),1,0.7,Scalar(0,255,0));
    }

    //트랙 중점
    ellipse(mat_map,RotatedRect( Point2f( check_track_x_axis(i),check_track_y_axis(i) ) , Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,255));

    //트렉 번호
    str.setNum((i));
    putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)-TRACK_SIZE/2-2,check_track_y_axis(i)-5),1,0.8,Scalar(255,255,255));

    //트렉 상태
    str.sprintf("%1.0f" , track[i].STATUS);
    putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)-TRACK_SIZE/2+25,check_track_y_axis(i)-7),1,0.8,Scalar(255,100,100));

    //트랙 극좌표계( r, seta)
    str.sprintf("( %3.2f,%3.2f )",track[i].RANGE,track[i].ANGLE);
    putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)+TRACK_SIZE,check_track_y_axis(i)+2),1,0.7,Scalar(255,255,255));

    //트랙 직교 좌표계(단위 : m)
    str.sprintf("( %3.2f,%3.2f )", track[i].X ,track[i].Y );
    putText(mat_map,str.toStdString(),Point2f(check_track_x_axis(i)+TRACK_SIZE,check_track_y_axis(i)+15),1,0.7,Scalar(255,255,255));

}

//Trajectory View
void View::paint_object_trajectory_init(){
    set_object_trajectory_background_map();
}

void View::paint_object_trajectory_view(int flag){
    //여기다 FPS 표시
    set_object_trajectory_background_map();
    set_object_trajectory_map(flag);
}

void View::set_object_trajectory_background_map(){
    fps_view_start_time = clock();
    //맵 초기화
    mat_map = Mat::zeros(LB_VIEW_HEIGHT,LB_VIEW_WIDTH,CV_8UC3);

    //레이더 센서 범위 그림(large)
    ellipse(mat_map,
            RotatedRect(
                Point2f(LB_VIEW_WIDTH/2,LB_VIEW_HEIGHT),
                Size2f(
                    (float)(174.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2) ,
                    (float)(174.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2)
                ),
                PIXEL_RADUATION_SIZE
                ),
            Scalar(0,200,0),2
            );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,200,0),2
    );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,200,0),2
    );
    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );
    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,10)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );
    //레이더 센서 범위 그림(mid)
    ellipse(mat_map,
            RotatedRect(
                Point2f(LB_VIEW_WIDTH/2,LB_VIEW_HEIGHT),
                Size2f(
                    (float)(60.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2) ,
                    (float)(60.0/(REAL_RADUATION_SIZE-zoom.level)*PIXEL_RADUATION_SIZE*2)
                ),
                PIXEL_RADUATION_SIZE
                ),
            Scalar(0,200,0),2
            );

    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,200,0),2
    );
    line(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(0,0)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,200,0),2
    );


    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );

    rectangle(mat_map,
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(174,-90)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Point2f(
             LB_VIEW_WIDTH/2 + cal_azimuth_angle_area_x(60,-45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) ),
             LB_VIEW_HEIGHT - cal_azimuth_angle_area_y(60,45)*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level))
         ),
         Scalar(0,0,0),-1
    );

    //세로 눈금
    for(int i = 0; i < ZOOM_SEPERATE ; i++){

        line(mat_map,Point(0,i*PIXEL_RADUATION_SIZE) , Point(LB_VIEW_WIDTH,i*PIXEL_RADUATION_SIZE),Scalar(20,20,20));
        tmp_float = (zoom_length.view_height_langth[zoom.level] - i*(REAL_RADUATION_SIZE-zoom.level));
        str.sprintf("%3.0f(m)",tmp_float);
        putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH/2-10,i*PIXEL_RADUATION_SIZE),1,0.5,background_text_color);
    }

    //가로 눈금
    for(int i = 1; i < ZOOM_SEPERATE ; i++){
        line(mat_map,Point(i*PIXEL_RADUATION_SIZE,0) , Point(i*PIXEL_RADUATION_SIZE,LB_VIEW_HEIGHT),Scalar(20,20,20));
        tmp_float = ( zoom_length.view_width_langth[zoom.level]+i*(REAL_RADUATION_SIZE-zoom.level) );
        //str.setNum(tmp_float);
        str.sprintf("%2.0f(m)",tmp_float);
        putText(mat_map,str.toStdString(),Point(i*PIXEL_RADUATION_SIZE-7,LB_VIEW_HEIGHT-7),1,0.5,background_text_color);
    }

    //축설명
    str.sprintf("- : RADAR");
    putText(mat_map,str.toStdString(),Point(2,10),1,0.7,Scalar(0,200,0));
    str.sprintf("-,o : Right");
    putText(mat_map,str.toStdString(),Point(2,25),1,0.7,Scalar(100,100,255));
    str.sprintf("-,o : Left");
    putText(mat_map,str.toStdString(),Point(2,40),1,0.7,Scalar(255,100,100));
    str.sprintf("o : Object Point");
    putText(mat_map,str.toStdString(),Point(2,55),1,0.7,Scalar(255,255,0));
    str = toUniString("o : Detection Point");
    putText(mat_map,str.toStdString(),Point(2,70),1,0.7,Scalar(255,0,255));
    str = toUniString("o : Moving Point");
    putText(mat_map,str.toStdString(),Point(2,85),1,0.7,Scalar(0,255,255));

}

void View::set_object_trajectory_map(int flag){
    extraction_rule->set_data_measurement(data_measurement);
    //qDebug()<<data_measurement.min.Obstacle_Accuracy<<" "<<data_measurement.min.Obstacle_Area;
    for(int i = 0; i < MAX_TRACK_SIZE;i++){
        cal_object_trajectory_vector_track(i);
        paint_object_trajectory_track(i,flag);
    }


    fps_view_end_time = clock();
    frame++;
    fps =(double)(fps_view_end_time-fps_view_start_time)/CLOCKS_PER_SEC;

    str.sprintf("Frame : %ld" , frame);
    putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH-90,10),1,0.7,Scalar(0,255,255));
    str.sprintf("Speed : %0.3f" , fps);
    putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH-90,25),1,0.7,Scalar(0,255,255));

}

void View::paint_object_trajectory_track(int i , int flag){

    float x1,y1,x2,y2;
    float center_x,center_y;
    float x_min,y_min,x_max,y_max;
    center_x = 0.0;
    center_y = 0.0;

    Scalar color;
    int size;

    if(flag == TRACK_VIEW_BASIC){
        if( data_measurement.min.Status <= vector_track[i].back().STATUS && vector_track[i].back().STATUS <= data_measurement.max.Status){
            x2 = cal_azimuth_angle_area_x(vector_track[i].back().RANGE,vector_track[i].back().ANGLE);
            y2 = cal_azimuth_angle_area_y(vector_track[i].back().RANGE,vector_track[i].back().ANGLE);
            ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,0),-1);
            //str = QString::number(i);
            //putText(mat_map,str.toStdString(),Point(check_track_x_axis(x2),check_track_y_axis(y2)-3),1,0.7,Scalar(255,255,0));
        }
    }

    if(flag == TRACK_VIEW_TRAJECTORY){
        if(vector_track_movement == TRACK_STATIC){
            color = Scalar(255,255,255);

            if( (int)vector_track[i].size() > data_measurement.min.Obstacle_Accuracy){
                //연속되는 점 설정
                x2 = cal_azimuth_angle_area_x(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);
                y2 = cal_azimuth_angle_area_y(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);

                //str.sprintf("%d",i);
                //putText(mat_map,str.toStdString(),Point(check_track_x_axis(x2),check_track_y_axis(y2)-3),1,0.7,Scalar(255,255,255));
                //ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,255),-1);
                x_min = x2;x_max = x2;
                y_min = y2;y_max = y2;
                center_x += x2;
                center_y += y2;

                //초기 설정
                for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
                    //str.sprintf("%d : <%f %f> %f" , vector_track[i].at(j).id , x2 , y2 ,vector_track[i].at(j).RANGE_RATE );
                    //qDebug()<<str;
                    x1 = cal_azimuth_angle_area_x(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                    y1 = cal_azimuth_angle_area_y(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                    x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

                    center_x += x2;
                    center_y += y2;

                    x_min = min(x_min,x2);
                    y_min = min(y_min,y2);
                    x_max = max(x_max,x2);
                    y_max = max(y_max,y2);

                    ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,0,255));
                }

                center_x = center_x/vector_track[i].size();
                center_y = center_y/vector_track[i].size();

                //qDebug()<<x_min<<" "<<y_min<<" "<<x_max<<" "<<y_max;
                rectangle(mat_map,Point2f(check_track_x_axis(x_min),check_track_y_axis(y_min)),Point2f(check_track_x_axis(x_max),check_track_y_axis(y_max)),Scalar(255,255,0) );

                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(center_x),check_track_y_axis(center_y)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,0),-1);
                str.sprintf("%d",i);
                putText(mat_map,str.toStdString(),Point(check_track_x_axis(center_x),check_track_y_axis(center_y)-3),1,0.7,Scalar(255,255,255));

                x2 = cal_azimuth_angle_area_x(vector_track[i].back().RANGE,vector_track[i].back().ANGLE);
                y2 = cal_azimuth_angle_area_y(vector_track[i].back().RANGE,vector_track[i].back().ANGLE);
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(100,255,255),-1);

            }
        }

        if(vector_track_movement == TRACK_MOVING){
            for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
                if(j == 1){
                    color = Scalar(255,255,255);

                    x2 = cal_azimuth_angle_area_x(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);

                    str.sprintf("%d",i);
                    putText(mat_map,str.toStdString(),Point(check_track_x_axis(x2),check_track_y_axis(y2)-3),1,0.7,Scalar(255,255,255));
                    ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,0),-1);
                }

                x1 = cal_azimuth_angle_area_x(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                y1 = cal_azimuth_angle_area_y(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

                if(vector_track[i].at(j).X > 0){
                    color = Scalar(100,100,255);
                }else{
                    color = Scalar(255,100,100);
                }

                //line(mat_map,Point(10,10),Point(200,200), color);
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),color,-1);

                line(mat_map,
                     Point2f(
                         check_track_x_axis(x1),
                         check_track_y_axis(y1)
                     ),
                     Point2f(
                         check_track_x_axis(x2),
                         check_track_y_axis(y2)
                     ),
                     color
                );

                if(j == (int)vector_track[i].size()-1){
                    color = Scalar(255,0,255);

                    x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

                    ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(0,255,255),-1);
                }
            }
        }

        if(vector_track_movement == TRACK_STATIC_MOVING){
            for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
                if(j == 1){
                    color = Scalar(255,255,255);

                    x2 = cal_azimuth_angle_area_x(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);

                    str.sprintf("%d",i);
                    putText(mat_map,str.toStdString(),Point(check_track_x_axis(x2),check_track_y_axis(y2)-3),1,0.7,Scalar(255,255,255));
                    ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,255),-1);
                }

                x1 = cal_azimuth_angle_area_x(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                y1 = cal_azimuth_angle_area_y(vector_track[i].at(j-1).RANGE,vector_track[i].at(j-1).ANGLE);
                x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

                color = Scalar(255,255,0);

                //line(mat_map,Point(10,10),Point(200,200), color);
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),color,-1);

                line(mat_map,
                     Point2f(
                         check_track_x_axis(x1),
                         check_track_y_axis(y1)
                     ),
                     Point2f(
                         check_track_x_axis(x2),
                         check_track_y_axis(y2)
                     ),
                     color
                );
            }
        }
        /*
        if(vector_track_movement == TRACK_FLICKER){

            for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
                if(j == 1){
                    color = Scalar(120,120,120);

                    x2 = cal_azimuth_angle_area_x(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[i].at(0).RANGE,vector_track[i].at(0).ANGLE);

                    str.sprintf("%d",i);
                    putText(mat_map,str.toStdString(),Point(check_track_x_axis(x2),check_track_y_axis(y2)-3),1,0.7,Scalar(200,200,200));
                    ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,255),-1);
                }

                x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(120,120,120));
            }
        }
        */
    }

    if(flag == TRACK_VIEW_BLOB){
        //코드 명칭 규격화 후 수정
        //int size;
        //color = Scalar(random(100,255),random(100,255),random(100,255));

        for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
            x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
            y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

            //ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(150,150,150));
            point_cluster.x = x2;
            point_cluster.y = y2;
            point_cluster.id = i;
            point_cluster.color = track_color[i];
            //qDebug()<<i<<" "<<x2<<" "<<y2;

            vector_cluster.push_back(point_cluster);

        }

        if(i == MAX_TRACK_SIZE-1){
            size = vector_cluster.size();
            Mat tmp_mat_map = Mat::zeros(LB_VIEW_HEIGHT,LB_VIEW_WIDTH,CV_8UC3);
            for(int j = 0 ; j < size ; j++){
                x2 = vector_cluster.at(j).x;
                y2 = vector_cluster.at(j).y;
                color = vector_cluster.at(j).color;

                ellipse(tmp_mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*0.5,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*0.5),PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE ),Scalar(255,255,255),-1);
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),color,-1);
            }

            Mat im;
            cvtColor(tmp_mat_map,im,CV_BGR2GRAY);
            SimpleBlobDetector::Params params;
            params.minDistBetweenBlobs = 0.5f;
            params.filterByInertia = false;
            params.filterByConvexity = false;
            params.filterByColor = false;
            params.filterByCircularity = false;
            params.filterByArea = true;
            params.minArea = 10.0f-(float)zoom.level;
            params.maxArea = 12000.0f;

            SimpleBlobDetector detector(params);

            // Storage for blobs
            std::vector<KeyPoint> keypoints;

            // Detect blobs
            detector.detect(im, keypoints);

            //그리기
            //drawKeypoints( im, keypoints, mat_map, Scalar(255,0,0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

            //측정 객체 중점
            //qDebug()<<keypoints.size();
            for (int k = 0; k < (int)keypoints.size(); k++){
                x2 = keypoints[k].pt.x;
                y2 = keypoints[k].pt.y;
                //qDebug()<<k<<" : "<<x2<<" "<<y2;
                ellipse(mat_map,RotatedRect(Point2f(x2,y2) ,Size2f(PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*0.5,PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*0.5),PIXEL_RADUATION_SIZE/(REAL_RADUATION_SIZE-zoom.level)*TRACK_MR_DISTANCE_FUSION_RATE ),Scalar(255,255,255));
                str.sprintf("%d",k);
                putText(mat_map,str.toStdString(),Point2f(x2,y2-10),1,0.7,Scalar(255,255,255));

            }
            //imshow("keypoints", im );
            vector_cluster.clear();
        }
    }

    if(flag == TRACK_VIEW_K_NN){
        //1) 측정 거리 허용치를 적용할 것인지 말것인지
        //원래는 적용하면 안됨
        //그러나 거리의 차아 일정거리 이상이면
        //새로운 군집이 생겼다고 반응해야함.

        for(int j = 1 ; j < (int)vector_track[i].size() ; j++){
            x2 = cal_azimuth_angle_area_x(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);
            y2 = cal_azimuth_angle_area_y(vector_track[i].at(j).RANGE,vector_track[i].at(j).ANGLE);

            //ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x2),check_track_y_axis(y2)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(150,150,150));
            point_cluster.x = x2;
            point_cluster.y = y2;
            point_cluster.id = i;
            point_cluster.color = track_color[i];
            //qDebug()<<i<<" "<<x2<<" "<<y2;

            vector_cluster.push_back(point_cluster);
        }
        vector_cluster.clear();
    }

    if(flag == TRACK_VIEW_AUTOMATIC_CLUSTERING){
        if(i == 0){//모든 Track의 백터 값을 삽입해야함. i 부분만 삽입하는게 아니다
            for(int j = 0; j < MAX_TRACK_SIZE ; j++){
                cal_object_trajectory_vector_track(j);
                for(int k = 0; k < (int)vector_track[j].size() ; k++){

                    x2 = cal_azimuth_angle_area_x(vector_track[j].at(k).RANGE,vector_track[j].at(k).ANGLE);
                    y2 = cal_azimuth_angle_area_y(vector_track[j].at(k).RANGE,vector_track[j].at(k).ANGLE);

                    point_cluster.x = x2;
                    point_cluster.y = y2;
                    point_cluster.id = TRACK_DEFAULT;
                    //point_cluster.color = track_color[i];
                    //qDebug()<<i<<" "<<x2<<" "<<y2;

                    vector_cluster.push_back(point_cluster);
                }
            }
            //자동 클러스터링 시작
            float distance = 2.5;//0.25m
            int clust_num = 0;
            bool check;
            for(int j = 0; j < (int)vector_cluster.size() ; j++){
                check = false;
                for(int k = 0 ; k < (int)vector_cluster.size() ; k++){
                    //기준점 x,y 설정
                    x1 = vector_cluster.at(j).x;
                    y1 = vector_cluster.at(j).y;
                    x2 = vector_cluster.at(k).x;
                    y2 = vector_cluster.at(k).y;
                    if(vector_cluster.at(k).id == TRACK_DEFAULT){
                        if(cal_point_distance(x1,y1,x2,y2)<= distance ){
                            vector_cluster.at(k).id = clust_num;
                            vector_cluster.at(k).color = track_color[clust_num];
                            check = true;
                        }
                    }else{
                        if(cal_point_distance(x1,y1,x2,y2)<= distance ){
                            vector_cluster.at(k).id = vector_cluster.at(j).id;
                            vector_cluster.at(k).color = vector_cluster.at(j).color;
                        }
                    }
                }
                if(check == true){
                    clust_num++;
                }
            }

            float cx,cy;
            int count;
            vector<Cluster> vector_cluster_center;
            Cluster cluster_center;
            Scalar color;
            //초기 넘버는 null상태에서 비교 하는 값임으로 0부터 시작 안함 1부터 시작임
            for(int j = 1; j < clust_num ; j++){
                cx = 0.0;
                cy = 0.0;
                count = 0;
                for(int k = 0; k < (int)vector_cluster.size() ; k++){
                    if(vector_cluster.at(k).id == j){
                        count++;
                        cx += vector_cluster.at(k).x;
                        cy += vector_cluster.at(k).y;
                        color = vector_cluster.at(k).color;
                    }
                }
                cx = cx/count;
                cy = cy/count;

                cluster_center.color = color;
                cluster_center.x = cx;
                cluster_center.y = cy;
                cluster_center.count = count;
                cluster_center.id = j;

                vector_cluster_center.push_back(cluster_center);
                //qDebug()<<j<<" : {"<<cx<<","<<cy<<"} ,"<<count;
            }

            //paint
            for(int j = 0; j < (int)vector_cluster.size() ; j++){
                x1 = vector_cluster.at(j).x;
                y1 = vector_cluster.at(j).y;
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x1),check_track_y_axis(y1)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),vector_cluster.at(j).color);
            }

            clust_num = vector_cluster_center.size();
            for(int j = 0; j < vector_cluster_center.size() ; j++){
                x1 = vector_cluster_center.at(j).x;
                y1 = vector_cluster_center.at(j).y;
                ellipse(mat_map,RotatedRect(Point2f(check_track_x_axis(x1),check_track_y_axis(y1)) ,Size2f(TRACK_SIZE,TRACK_SIZE),TRACK_SIZE ),Scalar(255,255,255));
                str.sprintf("%d",j);
                putText(mat_map,str.toStdString(),Point(check_track_x_axis(x1),check_track_y_axis(y1)-3),1,0.7,Scalar(255,255,255));
            }

            str.sprintf("Cluster : %d",clust_num);
            putText(mat_map,str.toStdString(),Point(LB_VIEW_WIDTH-90,40),1,0.7,Scalar(0,255,255));

            vector_cluster_center.clear();
            vector_cluster.clear();
        }

        /*
        for(int i = 0 ; i < vector_cluster.size() ; i++){
            qDebug()<<i<<" : "<<vector_cluster.at(i).id<<" , "<<clust_id<<" : "<<vector_cluster.at(i).x<<","<<vector_cluster.at(i).y;
        }
        */


    }
}

void View::cal_object_trajectory_vector_track(int i){

    vector_track[i].push_back(track[i]);
    extraction_rule->set_vector_track(vector_track[i]);

    vector_track_movement = extraction_rule->object_trajectory();
    if(vector_track_movement==TRACK_STATUS_DEFAULT){
        vector_track[i].clear();
    }

    if(vector_track_movement==TRACK_STATIC){
        if(vector_track[i].size() > TRACK_VECTOR_MAX_SIZE){
            vector_track[i].erase(vector_track[i].begin());
        }
    }
}

//ui algorithm
Scalar View::check_track_area(int track_num){

    float range = (float)(REAL_RADUATION_SIZE - zoom.level);
    int color_num = 0;
    float length = track[track_num].X*track[track_num].X + track[track_num].Y+track[track_num].Y;
    length = sqrt(length);

    for(int i = 0; i < TRACK_AREA_MUMBER ; i++){
        if(range*(i) < length && length < range*(i+1)){
            color_num = i;
            break;
        }
    }

    return track_ellipse_color[color_num];
}

float View::check_track_x_axis(int track_num){
    return LB_VIEW_WIDTH/2 + track[track_num].X*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) );
}

float View::check_track_y_axis(int track_num){
    return LB_VIEW_HEIGHT - track[track_num].Y*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level));
}

float View::check_track_x_axis(float x){
    return LB_VIEW_WIDTH/2 + x*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level) );
}

float View::check_track_y_axis(float y){
    return LB_VIEW_HEIGHT - y*( (float)PIXEL_RADUATION_SIZE/(float)(REAL_RADUATION_SIZE-zoom.level));
}

float View::cal_azimuth_angle_area_x(TRACK track , float angle){
    if(track.ANGLE+angle > 0){
        return track.RANGE*(float)(sin((double)(PIE/180*abs(track.ANGLE+angle))));
    }else{
        return -track.RANGE*(float)(sin((double)(PIE/180*abs(track.ANGLE+angle))));
    }
}

float View::cal_azimuth_angle_area_y(TRACK track , float angle){
    return track.RANGE*(float)(cos((double)(PIE/180*abs(track.ANGLE+angle))));
}

float View::cal_azimuth_angle_area_x(float range, float angle){
    if(angle > 0){
        return range*(float)(sin((double)(PIE/180*abs(angle))));
    }else{
        return -range*(float)(sin((double)(PIE/180*abs(angle))));
    }
}

float View::cal_azimuth_angle_area_y(float range , float angle){
    return range*(float)(cos((double)(PIE/180*abs(angle))));
}

float View::cal_point_distance(float x1 , float y1 , float x2 , float y2){
    return (float)sqrt( (double)((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) );
}

//random
int View::random(int start, int end){
    return start+(rand()%(end-start));
}

//퍼온거 유니코드 깨짐 방지 : 써도 안됨 필요 없
QString View::toUniString(QString str){
    QTextCodec * codec = QTextCodec::codecForName("eucKR");
    QString localeStr = codec->toUnicode(str.toUtf8().constData());

    return localeStr;
}
