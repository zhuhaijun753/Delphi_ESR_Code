#include "toolcamera.h"
#include "ui_toolcamera.h"

ToolCamera::ToolCamera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolCamera)
{
    ui->setupUi(this);
}

ToolCamera::~ToolCamera()
{
    delete ui;
}
