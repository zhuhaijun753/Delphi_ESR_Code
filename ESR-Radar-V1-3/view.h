#ifndef VIEW_H
#define VIEW_H

#include <opencv2/opencv.hpp>
#include <defines.h>
#include <rule.h>

#include <vector>
#include <time.h>

#include <QImage>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QDateTime>
#include <QTime>

using namespace cv;
using namespace std;

class View
{
public:
    View();
    ~View();

    void set_zoom_data(Zoom zoom);
    void set_data_measurement(Limit data_measurement);
    void set_track_data(TRACK *track);
    void set_track_vector_data(vector<TRACK> *vector_track);

    QPixmap get_view();

    //Main View
    void paint_init();
    void paint_view();

    void set_background_map();
    void set_track_map();

    //Trajectory View
    void paint_object_trajectory_init();
    void paint_object_trajectory_view(int flag = 0);
    void set_object_trajectory_background_map();
    void set_object_trajectory_map(int flag = 0);

private:
    //
    Mat mat_map;//보여줄 맵
    //색상
    Scalar track_color[MAX_TRACK_SIZE];
    Scalar background_line_color;
    Scalar background_text_color;
    Scalar background_ellipse_color;
    Scalar track_ellipse_color[TRACK_AREA_MUMBER];

    QString str;//string

    Limit data_measurement;//데이터 측정 범위 설정
    Zoom zoom;//줌 단계(확대 축소 레벨)
    ZoomLength zoom_length;//줌 크기 설정
    TRACK *track;//트렉
    TRACK relay_track;//지속트렉 검출용(테스트용)
    vector<TRACK> *vector_track;//sp matrix = 수정

    Cluster point_cluster;
    vector<Cluster> vector_cluster;

    Rule *extraction_rule;//규칙
    int vector_track_movement;//Track 현제 상태

    float tmp_float;//임시계산값
    float azimuth_angle_area_x,azimuth_angle_area_y;//x,y좌표(view에서 그릴)

    //시간 관련
    clock_t fps_view_start_time;//frame number
    clock_t fps_view_end_time;
    double fps;
    long frame;

    QString toUniString(QString str);//유니 코드 깨짐 방지

    Scalar check_track_area(int track_num);//트렉 영역에따른 색상을 구분하기 위한 영역검출
    float check_track_x_axis(int track_num);//ui좌표계로 변환
    float check_track_y_axis(int track_num);//ui좌표계로 변환

    float check_track_x_axis(float x);//ui좌표계로 변환
    float check_track_y_axis(float y);//ui좌표계로 변환

    float cal_azimuth_angle_area_x(TRACK track , float angle);//view좌표계로 변환(x)
    float cal_azimuth_angle_area_y(TRACK track , float angle);//view좌표계로 변환(y)

    float cal_azimuth_angle_area_x(float range , float angle);//view좌표계로 변환(x)
    float cal_azimuth_angle_area_y(float range , float angle);//view좌표계로 변환(y)

    float cal_point_distance(float x1 , float y1 , float x2 , float y2);//두점사이 거리 계산
    int random(int start, int end);

    //Main
    void paint_target_using_med_range(int i);//long-range , mid-range그리기
    void paint_track(int i);//메인 뷰 트렉 그리기

    //Trajectory View
    void paint_object_trajectory_track(int i , int flag = 0);//검출된 트렉 영역 그리기
    void cal_object_trajectory_vector_track(int i);//검출할 드렉영역 계산


};

#endif // VIEW_H
