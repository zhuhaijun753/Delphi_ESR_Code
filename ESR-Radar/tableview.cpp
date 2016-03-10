#include "tableview.h"

tableview::tableview(QWidget *parent):QWidget(parent)
{
    QString title[5]={"State" , "Range" , "Deg" , "Range Rate" , "Range Accel"};
    int title_width[5]={50,50,40,80,80};
    int title_x[5]={20,70,120,160,240};

    for(int i = 0; i < 5 ; i++){
        this->title[i] = title[i];
        this->title_width[i] = title_width[i];
        this->title_x[i] = title_x[i];
    }

    width = 680;
    height = 462;

    label_x = 20;
    label_y = 9;
    table_width=30;
    table_height=14;

    font.setPointSize(8);

    for(int i = 0; i < 64 ; i++){
        ui_range[i] = new QLabel(this);
        ui_range[i]->setVisible(true);
        ui_range[i]->setFont(font);
        ui_range[i]->setAlignment(Qt::AlignCenter);
        ui_range[i]->setStyleSheet("color:#ffffff");
        ui_range[i]->setText(QString::number(0));

        ui_angle[i] = new QLabel(this);
        ui_angle[i]->setVisible(true);
        ui_angle[i]->setFont(font);
        ui_angle[i]->setAlignment(Qt::AlignCenter);
        ui_angle[i]->setStyleSheet("color:#ffffff;");
        ui_angle[i]->setText(QString::number(0));

        ui_x[i] = new QLabel(this);
        ui_x[i]->setVisible(true);
        ui_x[i]->setFont(font);
        ui_x[i]->setAlignment(Qt::AlignCenter);
        ui_x[i]->setStyleSheet("color:#ffffff");
        ui_x[i]->setText(QString::number(0));

        ui_y[i] = new QLabel(this);
        ui_y[i]->setVisible(true);
        ui_y[i]->setFont(font);
        ui_y[i]->setAlignment(Qt::AlignCenter);
        ui_y[i]->setStyleSheet("color:#ffffff;");
        ui_y[i]->setText(QString::number(0));

        //ui_angle[i]->setFont(font);
        ui_state[i] = new QLabel(this);
        ui_state[i]->setVisible(true);
        ui_state[i]->setFont(font);
        ui_state[i]->setAlignment(Qt::AlignCenter);
        ui_state[i]->setStyleSheet("color:#ffffff;");
        ui_state[i]->setText(QString::number(0));

        ui_range_rate[i] = new QLabel(this);
        ui_range_rate[i]->setVisible(true);
        ui_range_rate[i]->setFont(font);
        ui_range_rate[i]->setAlignment(Qt::AlignCenter);
        ui_range_rate[i]->setStyleSheet("color:#ffffff;");
        ui_range_rate[i]->setText(QString::number(0));

        ui_range_accel[i] = new QLabel(this);
        ui_range_accel[i]->setVisible(true);
        ui_range_accel[i]->setFont(font);
        ui_range_accel[i]->setAlignment(Qt::AlignCenter);
        ui_range_accel[i]->setStyleSheet("color:#ffffff;");
        ui_range_accel[i]->setText(QString::number(0));
    }

    int count = 0;

    for(int i = 0; i < 32 ; i++){

        ui_state[count]->setGeometry(title_x[0]+title_width[0]/4,table_height*(i+1)+4,title_width[0],label_y);
        ui_range[count]->setGeometry(title_x[1]+title_width[1]/4,table_height*(i+1)+4,title_width[1],label_y);
        ui_angle[count]->setGeometry(title_x[2]+title_width[2]/4,table_height*(i+1)+4,title_width[2],label_y);

        ui_x[count]->setGeometry(title_x[1]+title_width[1]/4,table_height*(i+1)+4,title_width[1],label_y);
        ui_y[count]->setGeometry(title_x[2]+title_width[2]/4,table_height*(i+1)+4,title_width[2],label_y);

        ui_range_rate[count]->setGeometry(title_x[3]+title_width[3]/5,table_height*(i+1)+4,title_width[3],label_y);
        ui_range_accel[count]->setGeometry(title_x[4]+title_width[4]/5,table_height*(i+1)+4,title_width[4],label_y);

        count++;
    }

    for(int i = 0; i < 32 ; i++){
        ui_state[count]->setGeometry(width/2+title_x[0]+title_width[0]/4,table_height*(i+1)+4,title_width[0],label_y);
        ui_range[count]->setGeometry(width/2+title_x[1]+title_width[1]/4,table_height*(i+1)+4,title_width[1],label_y);
        ui_angle[count]->setGeometry(width/2+title_x[2]+title_width[2]/4,table_height*(i+1)+4,title_width[2],label_y);

        ui_x[count]->setGeometry(width/2+title_x[1]+title_width[1]/4,table_height*(i+1)+4,title_width[1],label_y);
        ui_y[count]->setGeometry(width/2+title_x[2]+title_width[2]/4,table_height*(i+1)+4,title_width[2],label_y);

        ui_range_rate[count]->setGeometry(width/2+title_x[3]+title_width[3]/5,table_height*(i+1)+4,title_width[3],label_y);
        ui_range_accel[count]->setGeometry(width/2+title_x[4]+title_width[4]/5,table_height*(i+1)+4,title_width[4],label_y);
        count++;
    }

    mode = 1;
}

void tableview::paintEvent(QPaintEvent *event)
{
    QPainter painter_bk;
    QPen pen;

    painter_bk.begin(this);

    //background
    if(mode == RB_POLAR){
        pen.setColor(QColor(0xff,0xa0,0x2f));
    }else if(mode == RB_RECTANGULAR){
        pen.setColor(QColor(0xa0,0xa0,0xff));
    }

    painter_bk.setPen(pen);
    painter_bk.drawRect(0, 0, width, height);

    painter_bk.setFont(font);

    for(int i = 0 ; i < 5 ; i++){
        painter_bk.drawText(title_x[i]+11,table_height/2-5,title_width[i],table_height,Qt::AlignCenter,title[i]);
    }
    for(int i = 0 ; i < 5 ; i++){
        painter_bk.drawText(width/2+title_x[i]+11,table_height/2-5,title_width[i],table_height,Qt::AlignCenter,title[i]);
    }
    //
    painter_bk.drawLine(1*table_width,0,1*table_width,height);

    for(int i = 0; i < 34; i++){
        painter_bk.drawLine(0,i*table_height,width,i*table_height);
    }

    int count = 0;
    for(int i = 0; i < 32; i++){
        painter_bk.drawText((table_width/2)-10,table_height*(i+1)+4,label_x,label_y,Qt::AlignCenter,QString::number(count));
        count++;
    }

    //
    painter_bk.drawLine(width/2,0,width/2,height);
    painter_bk.drawLine(width/2+table_width,0,width/2+table_width,height);

    for(int i = 0; i < 32; i++){
        painter_bk.drawText(width/2+(table_width/2)-10,table_height*(i+1)+4,label_x,label_y,Qt::AlignCenter,QString::number(count));
        count++;
    }
    //
}

void tableview::setData(TRACK *track){

    for(int i = 0; i < 64 ; i++){
        ui_state[i]->setText(QString::number(track[i].STATUS));
        ui_range[i]->setText(QString::number(track[i].RANGE));
        ui_angle[i]->setText(QString::number(track[i].ANGLE));

        p = 3.141592/180*abs(track[i].ANGLE);
        y = track[i].RANGE*(float)(cos((double)p));

        if(track[i].ANGLE > 0){
            x = track[i].RANGE*(float)(sin((double)p));
        }else{
            x = -track[i].RANGE*(float)(sin((double)p));
        }

        str.sprintf("%3.2f", x);
        ui_x[i]->setText(str);
        str.sprintf("%3.2f", y);
        ui_y[i]->setText(str);
        ui_range_rate[i]->setText(QString::number(track[i].RANGE_RATE));
        ui_range_accel[i]->setText(QString::number(track[i].RANGE_ACCEL));
    }

}

void tableview::setMode(int mode){

    this->mode = mode;

    if(mode == RB_POLAR){
        for(int i = 0; i < 64 ; i++){
            ui_x[i]->setVisible(false);
            ui_y[i]->setVisible(false);
            ui_range[i]->setVisible(true);
            ui_angle[i]->setVisible(true);
        }
        QString title[5]={"State" , "Range" , "Deg" , "Range Rate" , "Range Accel"};
        int title_width[5]={50,50,40,80,80};
        int title_x[5]={20,70,120,160,240};

        for(int i = 0; i < 5 ; i++){
            this->title[i] = title[i];
            this->title_width[i] = title_width[i];
            this->title_x[i] = title_x[i];
        }
    }else if(mode == RB_RECTANGULAR){
        for(int i = 0; i < 64 ; i++){
            ui_x[i]->setVisible(true);
            ui_y[i]->setVisible(true);
            ui_range[i]->setVisible(false);
            ui_angle[i]->setVisible(false);
        }
        QString title[5]={"State" , "X" , "Y" , "Range Rate" , "Range Accel"};
        int title_width[5]={50,50,40,80,80};
        int title_x[5]={20,70,120,160,240};

        for(int i = 0; i < 5 ; i++){
            this->title[i] = title[i];
            this->title_width[i] = title_width[i];
            this->title_x[i] = title_x[i];
        }
    }
}
