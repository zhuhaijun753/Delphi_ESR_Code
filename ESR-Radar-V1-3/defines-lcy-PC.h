#ifndef DEFINES_H
#define DEFINES_H
#include <opencv2/opencv.hpp>

////////////////////////////////////////

#define RIGHT_CLICK 1
#define LEFT_CLICK 2

////////////////////////////////////////

#define LB_VIEW_WIDTH 600
#define LB_VIEW_HEIGHT 600

#define ZOOM_SIZE 10//측정 줌 크기 (확대 축소 범위 10단계)
#define ZOOM_SEPERATE 20//VIEW에 눈금자를 그리기위해 분리 시켜놓은 크기
#define PIXEL_RADUATION_SIZE 30//픽셀 눈금 간격
#define REAL_RADUATION_SIZE 10//실제 눈금 간격
#define TRACK_SIZE 5//트렉 크기
#define TRACK_AREA_MUMBER 18//트랙 영역 구분 수
#define TRACK_MR_DISTANCE_ERROR_RATE 0.25//트랙 MID-RANGE 오차 범위
#define TRACK_LR_DISTANCE_ERROR_RATE 0.5//트랙 LONG-RNAGE 오차 범위
#define TRACK_RANGE_RATE_ERROR_RATE 0.12//트랙 속도 오차 범위
#define TRACK_MR_DISTANCE_FUSION_RATE 1.25//트랙 MID-RANGE 오차 범위
#define TRACK_LR_DISTANCE_FUSION_RATE 2.5//트랙 LONG-RNAGE 오차 범위

#define TRACK_STATUS_DEFAULT 0//STATUS(STATE)가 0일
#define TRACK_MED_RANGE_MODE_DEFAULT 0//단파 장파 측정 둘다 아닐시

#define TRACK_MR_UPDATE_ONLY 1//MID RANGE 만 측정 될때
#define TRACK_LR_UPDATE_ONLY 2//LONG RANGE 만 측정 될때
#define TRACK_MR_LR_UPDATE 3//MR LR 둘다 측정 될때
#define TRACK_MED_ALL_UPDATE 4//모든 레이더 측정값 표현

#define TRACK_DEFAULT 0//
#define TRACK_STATIC 1//객체 고정
#define TRACK_MOVING 2//객체 이동
#define TRACK_STATIC_MOVING 3//객체가 존재 하되 이동
#define TRACK_GRAP 4//백터 값 쥐고 있는상태(계속 쌓고 있는 상태)
#define TRACK_FLICKER 5//백터값이 공란일경우

#define TRACK_VECTOR_MAX_SIZE 100//트렉 백터 최대 크기

#define TRACK_VIEW_BASIC 0//기본 회색 상태(트렉 번호 표시 X)
#define TRACK_VIEW_TRAJECTORY 1//추적 및 사각 영역
#define TRACK_VIEW_BLOB 2//영역 그룹화
#define TRACK_VIEW_K_NN 3//K_NN
#define TRACK_VIEW_S_CCL 4//S_CCL
#define TRACK_VIEW_RBNN 5//RBNN
#define TRACK_VIEW_AUTOMATIC_CLUSTERING 6//

typedef struct{
    int Status;//센서 상태
    float Range;//측정 거리(range)
    float HBr;//Heading-Bearing-relation(seta)
    float Rate;//Range Rate : 속도
    float Accel;//Range Accel : 가속
    int Mode;//센서 측정 모드 : 0) 둘다 측정 x 1)MR만 측정 2)LR만 측정 3)둘다 측정
    float Obstacle_Area;//Obstacle Area : 장애물 추출 사각영역
    int Obstacle_Accuracy;//Obstacle Accuracy : 백터 크기(민감도)
    float Obstacle_Ignore_Rate;//장애물 속도가 일정 이하이면 무시
    int Obstacle_Flicker_Save;//깜빡인것 허용치 최대 범위(size에 따른 %임 예를들어 10개의 size를 vector에다가 입력해서 그중 10%라 하면 1개의 깜빡임은 눈감아 주는것임)(값이 높을수록 깜빡인것도 장애물로 인정, 값이 낮을수록 깜빡인것은 장애물로 불인정)
}LimitData;

typedef struct{
    LimitData min;//최소
    LimitData max;//최대
}Limit;//제한범위

typedef struct{
    int level;//줌기능
}Zoom;

typedef struct{
    int view_width_langth[ZOOM_SIZE];//줌 확대 영역 가로 길이
    int view_height_langth[ZOOM_SIZE];//줌 확대 영역 세로 길이
}ZoomLength;

typedef struct{
    float x;
    float y;
    int id;//군접 id
    cv::Scalar color;//색상(구분용)
    int count;//군집에 속한 점의 갯수
}Cluster;

////////////////////////////////////////

#define LB_TABLE_WIDTH 600
#define LB_TABLE_HEIGHT 720

#define TABLE_HEIGHT_SIZE 11
#define TABLE_WIDTH_SIZE 85

#define TABLE_HEIGHT_LINE_NUMABER 65
#define TABLE_WIDTH_LINE_NUMBER 6

////////////////////////////////////////
#define LB_VIDEO_WIDTH 640
#define LB_VIDEO_HEIGHT 480

#endif // DEFINES_H
