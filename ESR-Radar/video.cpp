#include "video.h"
#include "ui_video.h"

video::video(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);
    video_thread = new videothread();
    TM_Video_Start = new QTimer();

    video_thread->init();

    connect(TM_Video_Start, SIGNAL(timeout()), this, SLOT(on_TM_Video_Start()));

}

video::~video()
{
    delete ui;
}

void video::set_state(int state){
    this->state = state;
}

void video::start(){
    TM_Video_Start->start();
}

void video::stop(){
    TM_Video_Start->stop();
    video_thread->stop();
}

void video::on_TM_Video_Start(){
    video_thread->set_state(state);
    video_thread->start();
    ui->LB_Video->setPixmap(QPixmap::fromImage(video_thread->get_image()));
}

