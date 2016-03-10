#include "rule.h"

rule::rule()
{
    mode = 1;
}

void rule::setData(TRACK track){

    if(mode == RB_POLAR){
        if(track.STATUS == 0||track.STATUS == 6){
            //회색
            scolor = "#555555";
        }else if(track.STATUS==1||track.STATUS == 2||track.STATUS == 7){
            //노랑색
            scolor = "#ffff00";
        }else if(track.STATUS==5){
            scolor = "#ff0000";
        }else{
            if(track.RANGE_RATE > 1){
                scolor = "#00ff00";
            }else if(track.RANGE_RATE < -1){
                scolor = "#ff00ff";
            }else{
                scolor = "#000000";
            }
        }
    }else if(mode == RB_RECTANGULAR){
        if(track.STATUS == 0||track.STATUS == 6){
            //회색
            scolor = "#555555";
        }else{
            p = 3.141592/180*abs(track.ANGLE);
            y = track.RANGE*(float)(cos((double)p));

            if(track.ANGLE > 0){
                x = track.RANGE*(float)(sin((double)p));
            }else{
                x = -track.RANGE*(float)(sin((double)p));
            }

            r = sqrt(double(x*x+y*y));
            a=1;b=10;//1차 경계
            if( (x*x)/(a*a)+(y*y)/(b*b) < 1 ){
                scolor = "#ff0000";
            }else{
                a=2;b=20;//2차 경계
                if( (x*x)/(a*a)+(y*y)/(b*b) < 1 ){
                    scolor = "#ffff00";
                }else{
                    scolor = "#0000ff";
                }
            }
        }
    }

}

void rule::setMode(int mode){
    this->mode = mode;
}

QColor rule::getColor(){
    return color;
}

QString rule::getSColor(){
    return scolor;
}
