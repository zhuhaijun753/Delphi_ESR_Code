#include "widget.h"
#include "ui_widget.h"
#include <qdebug.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //data view
    QString tv_str[] = {"States","Range(m)" , "Angle(deg)" , "Range Rate(m/s)" , "Range Accel(m/s^2)" , "Hex Code(8byte)"};
    row = 64;
    col = 6;

    //timer
    TM_Start = new QTimer(this);
    TM_Recode_Start = new QTimer(this);
    TM_Video = new QTimer(this);

    connect(TM_Start, SIGNAL(timeout()), this, SLOT(on_TM_Start()));
    connect(TM_Recode_Start, SIGNAL(timeout()), this, SLOT(on_TM_Recode_Start()));
    connect(TM_Video, SIGNAL(timeout()), this, SLOT(on_TM_Video()));

    //thread
    datathread = new dataThread();

    //fileIO
    file = new fileIO();

    //mode
    ui->Wid_PlanView->setMode(RB_POLAR);
    ui->Wid_SensorView->setMode(RB_POLAR);
    ui->Wid_TableView->setMode(RB_POLAR);

    //
    message_box = new messagebox();
    my_video = new video();

    video_frame_count = 0;
}

Widget::~Widget()
{
    delete ui;
}

//timer
void Widget::on_TM_Start()
{
    track = datathread->get_track();

    ui->Wid_PlanView->setData(track);
    ui->Wid_SensorView->setData(track);
    ui->Wid_TableView->setData(track);
}

void Widget::on_TM_Recode_Start()
{
    track = datathread->get_track();
    file->write(track);
}

void Widget::on_TM_Video(){

    track = file->get_read_track(video_frame_count);

    ui->Wid_PlanView->setData(track);
    ui->Wid_SensorView->setData(track);
    ui->Wid_TableView->setData(track);

    ui->HS_Video_SliderBar->setValue(video_frame_count);
    ui->SB_Frame_Number->setValue(video_frame_count);

    if(video_frame_count >= file->get_frame_count()){
        video_frame_count = 0;
        TM_Video->stop();
        ui->PB_Video_Start_Stop->setText("▶");
    }else{
        video_frame_count+=1;
    }
}

//active event
void Widget::on_PB_Read_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Radar File"), "../", tr("Radar File(*.txt)"));
    file->read(filename);
    video_frame_count = 0;
    ui->HS_Video_SliderBar->setRange(0,file->get_frame_count());
    ui->SB_Frame_Number->setRange(0,file->get_frame_count());
    if(file->get_frame_count() == 0){
        message_box->setMessage("Failed read data");
    }else{
        message_box->setMessage("Completed read data");
    }
    message_box->setVisible(true);
}

void Widget::on_PB_Connect_clicked()
{
    datathread->set_can();

    //QMessageBox message_box;
    //message_box.setText(datathread->get_message());
    //message_box.setStandardButtons(QMessageBox::Ok);
    //message_box.exec();
    message_box->setMessage(datathread->get_message());
    message_box->setVisible(true);
}

void Widget::on_PB_Start_clicked()
{
    message_box->setMessage("Start!!");
    message_box->setVisible(true);

    datathread->start();
    TM_Start->start();

}

void Widget::on_PB_Stop_clicked()
{
    message_box->setMessage("Stop!!");
    message_box->setVisible(true);

    datathread->stop();
    TM_Start->stop();
}

void Widget::on_PB_Recode_Start_clicked()
{
    message_box->setMessage("Recode Start!!");
    message_box->setVisible(true);

    file->set_filename();
    TM_Recode_Start->start();
}

void Widget::on_PB_Recode_Stop_clicked()
{
    message_box->setMessage("Recode Stop!!");
    message_box->setVisible(true);

    TM_Recode_Start->stop();
    file->close();

}

void Widget::on_RB_Polar_clicked()
{
    ui->Wid_PlanView->setMode(RB_POLAR);
    ui->Wid_SensorView->setMode(RB_POLAR);
    ui->Wid_TableView->setMode(RB_POLAR);

    if(datathread->isFinished()){
        ui->Wid_PlanView->setData(track);
        ui->Wid_SensorView->setData(track);
        ui->Wid_TableView->setData(track);
    }

    ui->Wid_PlanView->repaint();
    ui->Wid_SensorView->repaint();
    ui->Wid_TableView->repaint();
}

void Widget::on_RB_Rectangular_clicked()
{
    ui->Wid_PlanView->setMode(RB_RECTANGULAR);
    ui->Wid_SensorView->setMode(RB_RECTANGULAR);
    ui->Wid_TableView->setMode(RB_RECTANGULAR);

    if(datathread->isFinished()){
        ui->Wid_PlanView->setData(track);
        ui->Wid_SensorView->setData(track);
        ui->Wid_TableView->setData(track);
    }
    ui->Wid_PlanView->repaint();
    ui->Wid_SensorView->repaint();
    ui->Wid_TableView->repaint();
}

void Widget::on_PB_Video_Start_Stop_clicked()
{
    QString cstr=ui->PB_Video_Start_Stop->text();
    if(cstr == "▶"){
        ui->PB_Video_Start_Stop->setText("■");
        //시작
        TM_Video->start();
    }

    if(cstr == "■"){
        ui->PB_Video_Start_Stop->setText("▶");
        //중단
        TM_Video->stop();
    }
}

void Widget::on_HS_Video_SliderBar_sliderMoved(int position)
{
    ui->SB_Frame_Number->setValue(position);
    video_frame_count = position;

    track = file->get_read_track(video_frame_count);

    ui->Wid_PlanView->setData(track);
    ui->Wid_SensorView->setData(track);
    ui->Wid_TableView->setData(track);

}

void Widget::on_SB_Frame_Number_valueChanged(int value)
{
    ui->HS_Video_SliderBar->setValue(value);
    video_frame_count = value;

    track = file->get_read_track(video_frame_count);

    ui->Wid_PlanView->setData(track);
    ui->Wid_SensorView->setData(track);
    ui->Wid_TableView->setData(track);
}

void Widget::on_CB_Video_clicked()
{
    if(ui->CB_Video->isChecked()){
        my_video->setVisible(true);
        my_video->set_state(true);
        my_video->start();
    }else{
        my_video->setVisible(false);
        my_video->set_state(false);
        my_video->stop();
    }
}
