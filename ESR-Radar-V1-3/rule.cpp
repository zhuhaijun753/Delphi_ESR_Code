#include "rule.h"

Rule::Rule()
{
}

void Rule::set_data_measurement(Limit data_measurement){
    this->data_measurement = data_measurement;
}

void Rule::set_vector_track(vector<TRACK> vector_track){
    this->vector_track = vector_track;
}

void Rule::set_track(TRACK track){
    this->track = track;
}

bool Rule::analysis(){
    bool check = true;

    //rule 1 : State 범위
    if( !(data_measurement.min.Status <= track.STATUS && track.STATUS <= data_measurement.max.Status) ){
        check = false;
        return check;
    }

    //rule 2 : State 범위
    if( !(data_measurement.min.Range <= track.RANGE && track.RANGE <= data_measurement.max.Range) ){
        check = false;
        return check;
    }

    //rule 3 : HBr(Heading Bearing) 범위
    if( !(data_measurement.min.HBr <= track.ANGLE && track.ANGLE <= data_measurement.max.HBr) ){
        check = false;
        return check;
    }

    //rule 4 : Mode 범위
    if(data_measurement.min.Mode != TRACK_MED_ALL_UPDATE){
        if( !(data_measurement.min.Mode <= track.MED_RANGE_MODE && track.MED_RANGE_MODE <= data_measurement.max.Mode) ){
            check = false;
            return check;
        }
    }

    //rule 5 : Rate 범위
    if( !(data_measurement.min.Rate <= track.RANGE_RATE && track.RANGE_RATE <= data_measurement.max.Rate) ){
        check = false;
        return check;
    }

    //rule 6 : Accel 범위
    if( !(data_measurement.min.Accel <= track.RANGE_ACCEL && track.RANGE_ACCEL <= data_measurement.max.Accel) ){
        check = false;
        return check;
    }

    return check;
}

int Rule::object_trajectory(){

    int size = vector_track.size();
    int check[2] = {TRACK_STATUS_DEFAULT,TRACK_STATUS_DEFAULT};

    if( (data_measurement.min.Status <= vector_track.back().STATUS && vector_track.back().STATUS <= data_measurement.max.Status)&& data_measurement.min.Mode != TRACK_MED_RANGE_MODE_DEFAULT){
        //step 1) 고정 물체 확인하기
        check[0] = check_static_object();
        //step 2) 이동 물체 확인하기
        check[1] = check_moving_object();
    }else{
        return check_flicker_object();
    }

    //step 3) 최종 결과값(Obstacle Trajectory)
    if(check[0] == TRACK_STATIC && check[1] != TRACK_MOVING){
        return TRACK_STATIC;
    }

    if(check[0] != TRACK_STATIC && check[1] == TRACK_MOVING){
        return TRACK_MOVING;
    }

    if(check[0] == TRACK_STATIC && check[1] == TRACK_MOVING){
        return TRACK_STATIC_MOVING;
    }

    if(size < data_measurement.min.Persistence){
        return TRACK_GRAP;
    }

    return TRACK_STATUS_DEFAULT;
}

bool Rule::check_cycle_fuction(float x1,float y1, float x2, float y2, float r){

    //float test = (10+11)*(10+11)+(10-11)*(10-11);
    //qDebug()<<test;
    double rtmp = pow((double)(x1-x2),2.0)+pow((double)(y1-y2),2.0);
    rtmp = sqrt(rtmp);
    //qDebug()<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<r;

    if(rtmp < (double)r){
        return true;
    }
    return false;
}

bool Rule::check_if_function(float measurement_value,float if1, float if2 , float flag){
    /////////////////////////////////
    //영역 범주내에 속하면 : true
    if(flag == 0){
        if(if1<= measurement_value && measurement_value <= if2){
            return true;
        }else{
            return false;
        }
    }
    //영역 범부내에 속하지 않으면 : true
    if(flag == 1){
        if(if1<= measurement_value && measurement_value <= if2){
            return false;
        }else{
            return true;
        }
    }
    /////////////////////////////////
    return false;
}

int Rule::check_static_object(){

    /////////////////////////////////
    //속도는 일정하더라도 그에 따른 좌표까지 같으면 그건 재자리에 있는것과 동일하다. 속도가 있으면 제자리에 공존하기 불가능
    int accuracy = 1;//민감도
    int size = vector_track.size();

    if(size < data_measurement.max.Persistence){
        return TRACK_GRAP;
    }

    //영역 판단
    for(int i = 1; i < size ; i++){
        if(check_cycle_fuction(vector_track.at(0).X,vector_track.at(0).Y,vector_track.at(i).X,vector_track.at(i).Y,data_measurement.min.Cohesion/100.0)){
            if( check_if_function(vector_track.at(i-1).RANGE_RATE,-data_measurement.min.CriticalSpeed,data_measurement.max.CriticalSpeed , 0)){
                accuracy++;
            }
        }
    }

    //잡음 생존치
    if( accuracy >= size ){
        return TRACK_STATIC;
    }else{
        return TRACK_STATUS_DEFAULT;
    }
    /////////////////////////////////
    return TRACK_STATUS_DEFAULT;
}

int Rule::check_moving_object(){

    /////////////////////////////////
    // 좌표는 이동중이고, 그에 따른 트랙은 고정, 어디서 오던 상관 없음
    // 단 속도가 존재 하는 조건!
    int accuracy = 1;
    int size = vector_track.size();

    for(int i = 1; i < size ; i++){
        if(!check_cycle_fuction(vector_track.at(i-1).X,vector_track.at(i-1).Y,vector_track.at(i).X,vector_track.at(i).Y,data_measurement.min.Cohesion/100.0)){
            if( check_if_function(vector_track.at(i-1).RANGE_RATE,-data_measurement.min.CriticalSpeed,data_measurement.max.CriticalSpeed , 1)){
                accuracy++;
            }
        }
    }

    //잡음 생존치
    if(accuracy >= size){
        return TRACK_MOVING;
    }else{
        return TRACK_STATUS_DEFAULT;
    }
    /////////////////////////////////
    return TRACK_STATUS_DEFAULT;
}

int Rule::check_flicker_object(){

    /////////////////////////////////
    //int size = vector_track.size();
    int flicker_size = data_measurement.max.Persistence*data_measurement.max.Viability/100;

    if(flicker_size != 0){
        //잔상 여부 확인하기 위해 우선시 적으로 판단해야할 것 생각
        //if( (data_measurement.min.Status <= vector_track.back().STATUS && vector_track.back().STATUS <= data_measurement.max.Status)&& data_measurement.min.Mode != TRACK_MED_RANGE_MODE_DEFAULT){
            if(vector_track.back().RANGE <= 0){
                return TRACK_STATUS_DEFAULT;
            }else{
                return TRACK_FLICKER;
            }
        //}
    }
    /////////////////////////////////
    return TRACK_STATUS_DEFAULT;
}

