#ifndef RULE_H
#define RULE_H

#include <defines.h>//정의문이나 사용자 변수 지정용 Header
#include <reversing.h>//리버싱에 관련된 자료 및 함수를 사용하기 위한 Header
#include <vector>
#include <math.h>

#include <QDebug>

using namespace std;

class Rule
{
    //식별하는 기준을 나타내기 위한 클레스
public:
    Rule();//생성자(변수 초기화)

    void set_data_measurement(Limit data_measurement);//제한 조건 입력
    void set_track(TRACK track);//트렉 입력
    void set_vector_track(vector<TRACK> vector_track);//객채 경로 탐색 백터 입력

    bool analysis();//트렉 추출 조건 분석
    int object_trajectory();//객채 추적 분석

    bool check_cycle_fuction(float x1, float y1, float x2, float y2, float r);
    bool check_if_function(float measurement_value, float if1, float if2, float flag=0);

    int check_static_object();
    int check_moving_object();
    int check_flicker_object();//보류
    //cluserting
    void set_cluster_point(float x, float y , int id);
    int check_cluster_object();
private:
    Limit data_measurement;//Limit 사용자 변수
    TRACK track;//TRACK 사용자 변수
    vector<TRACK> vector_track;//object trajectory 백터

    int track_num;//Track 번호=(id)
    bool check;//분석 상태 확인
};

#endif // RULE_H
