#include "toolrecode.h"
#include "ui_toolrecode.h"

ToolRecode::ToolRecode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolRecode)
{
    ui->setupUi(this);
}

ToolRecode::~ToolRecode()
{
    delete ui;
}
