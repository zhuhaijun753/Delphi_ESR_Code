#include "planview.h"

planview::planview(QWidget *parent):QWidget(parent)
{
    width = 460;
    height = 600;

    state=0;
    ui_track_size = 14;

    for(int i = 0; i < 64 ; i++){
        ui_track[i] = new QLabel(this);
        ui_track[i]->setVisible(false);
        ui_track[i]->setAlignment(Qt::AlignCenter);
    }

    mode = 1;
    radar_rule = rule();
}

void planview::paintEvent(QPaintEvent *event)
{
    QPainter painter_bk;
    QPen pen;

    painter_bk.begin(this);

    //background
    if(mode == RB_POLAR){
        pen.setColor(QColor(0xff,0xa0,0x2f));
        painter_bk.setPen(pen);
        painter_bk.drawRect(0, 0, width, height);  // rectangle
        //600/3 = 200 200/10 = 20

        //y axis
        count = 180;
        for(int i = 0; i < 19 ; i++){
            painter_bk.drawText(1,i*33+6,20,11,Qt::AlignCenter ,QString::number(count));
            count-=10;
        }

        //x axis
        count = -40;
        for(int i = 1; i < 18 ; i++){
            painter_bk.drawText(i*26-13,height-10,20,11,Qt::AlignCenter ,QString::number(count)+"'");
            count+=5;
        }

        //angle
        pen.setColor(QColor(0x55,0x55,0x55));

        pen.setStyle(Qt::DashDotDotLine);
        painter_bk.setPen(pen);
        painter_bk.drawLine(width/2,0,width/2,height);
        painter_bk.drawLine(width/2,height,0,height-(4.5*33));
        painter_bk.drawLine(width/2,height,width,height-(4.5*33));

        painter_bk.drawLine(width/2,height,0,height-(17.5*33));
        painter_bk.drawLine(width/2,height,width,height-(17.5*33));

        //painter_bk.save();
        painter_bk.end();
    }else if(mode == RB_RECTANGULAR){
        pen.setColor(QColor(0xa0,0xa0,0xff));
        painter_bk.setPen(pen);
        painter_bk.drawRect(0, 0, width, height);  // rectangle
        //600/3 = 200 200/10 = 20

        //y axis
        count = 180;
        for(int i = 0; i < 19 ; i++){
            painter_bk.drawText(1,i*33+6,20,11,Qt::AlignCenter ,QString::number(count));
            count-=10;
        }

        //x axis
        count = -16;
        for(int i = 1; i < 18 ; i++){
            painter_bk.drawText(i*26-13,height-10,20,11,Qt::AlignCenter ,QString::number(count));
            count+=2;
        }

        //road
        pen.setColor(QColor(0x55,0x55,0x55));

        pen.setStyle(Qt::DashDotDotLine);
        painter_bk.setPen(pen);

        painter_bk.drawLine(width/2-26,0,width/2-26,height);
        painter_bk.drawLine(width/2+26,0,width/2+26,height);
        painter_bk.drawEllipse(width/2-26*1,height-33*1,26*2,26*4);
        painter_bk.drawEllipse(width/2-26*2,height-33*2,26*4,26*8);

        //painter_bk.save();
        painter_bk.end();
    }


}

void planview::setData(long id , int state ,float range, float angle , float range_rate){
    this->id = id;
    this->state = state;
    this->range = range;
    this->angle = angle;
    this->range_rate = range_rate;
}

void planview::setData(TRACK* track){

    for(int i = 0; i < 64 ; i++){
        if(track[i].STATUS == 0){
            ui_track[i]->setVisible(false);
        }else{
            ui_track[i]->setVisible(true);
            radar_rule.setData(track[i]);
            ui_track[i]->setStyleSheet("background-color:"+radar_rule.getSColor());
            if(mode == 1){
                ui_range = height-(int)(track[i].RANGE * 3.3);
                ui_angle = (width/2)+(int)(track[i].ANGLE * 5.1);

                ui_track[i]->setText(QString::number(i));
                ui_track[i]->setGeometry(ui_angle-(ui_track_size/2) ,ui_range-(ui_track_size/2) , ui_track_size , ui_track_size );

            }else{
                p = 3.141592/180*abs(track[i].ANGLE);
                y = track[i].RANGE*(float)(cos((double)p));

                if(track[i].ANGLE > 0){
                    x = track[i].RANGE*(float)(sin((double)p));
                }else{
                    x = -track[i].RANGE*(float)(sin((double)p));
                }

                ui_y = height-(int)(y * 3.3);
                ui_x = (width/2)+(int)(x * 13);

                ui_track[i]->setText(QString::number(i));
                ui_track[i]->setGeometry(ui_x-(ui_track_size/2) ,ui_y-(ui_track_size/2) , ui_track_size , ui_track_size );
            }

            //qDebug() << ui_angle-(ui_track_size/2)<<"\t"<<ui_range-(ui_track_size/2);

            //printf("%03x : %f , %f\n" ,track[i].id , track[i].RANGE,track[i].ANGLE);
        }
    }
}

void planview::setMode(int mode){
    this->mode = mode;
    radar_rule.setMode(mode);
}
