#include "messagebox.h"
#include "ui_messagebox.h"

messagebox::messagebox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messagebox)
{
    ui->setupUi(this);
}

messagebox::~messagebox()
{
    delete ui;
}

void messagebox::setMessage(QString message){
    this->message = message;
    ui->LB_Message->setText(message);
}

void messagebox::on_PB_OK_clicked()
{
    this->setVisible(false);
}
