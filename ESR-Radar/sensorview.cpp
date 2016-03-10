#include "sensorview.h"

sensorview::sensorview(QWidget *parent):QWidget(parent)
{
    width = 680;
    height = 90;

    label_width = 20;
    label_height = 20;

    for(int i = 0; i < 64 ; i++){
        ui_track[i] = new QLabel(this);
        ui_track[i]->setVisible(true);
        ui_track[i]->setStyleSheet("background-color:#555555");
    }

    int count = 0;
    for(int i = 0; i < 32 ; i++){
        //painter_bk.drawText(i*21,0,20,11,Qt::AlignCenter,QString::number(i));
        ui_track[count]->setGeometry(i*21+5 ,18+5 , label_width , label_height);
        count++;
    }
    for(int i = 0; i < 32 ; i++){
        //painter_bk.drawText(i*21,100,20,11,Qt::AlignCenter,QString::number(32+i));
        ui_track[count]->setGeometry(i*21+5 ,58+5 , label_width , label_height);
        count++;
    }
    mode = 1;
    radar_rule = rule();
}

void sensorview::paintEvent(QPaintEvent *event)
{
    QPainter painter_bk;
    QPen pen;

    painter_bk.begin(this);

    //background
    if(mode == 1){
        pen.setColor(QColor(0xff,0xa0,0x2f));
    }else{
        pen.setColor(QColor(0xa0,0xa0,0xff));
    }

    painter_bk.setPen(pen);
    painter_bk.drawRect(0, 0, width, height);
    //0 invalid : 잘못된//빨
    //1 new first time : 처음 새로 등장//주
    //2 new updated : 처음 새로 갱신//노
    //3 mature updated : 심사 숙고한 업대이트( : 지속적인)//초
    //4 mature coasted : 심사 숙고한 coasted//파
    //5 invalid merged : 잘못된 융합//남
    //6 invalid coasted : 잘못된 coasted//보
    //7 new coasted : coasted//
    for(int i = 0; i < 32 ; i++){
        painter_bk.drawText(i*21+5,3+5,20,11,Qt::AlignCenter,QString::number(i));
    }
    for(int i = 0; i < 32 ; i++){
        painter_bk.drawText(i*21+5,43+5,20,11,Qt::AlignCenter,QString::number(32+i));
    }
}

void sensorview::setData(TRACK *track){

    for(int i = 0; i < 64 ; i++){
        radar_rule.setData(track[i]);
        ui_track[i]->setStyleSheet("background-color:"+radar_rule.getSColor());
    }
}

void sensorview::setMode(int mode){
    this->mode = mode;
    radar_rule.setMode(mode);
}
