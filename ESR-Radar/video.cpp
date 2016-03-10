#include "video.h"
#include "ui_video.h"

video::video(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);
    state = 0;
}

video::~video()
{
    delete ui;
}

void video::set_state(){
    this->state = state;
}
