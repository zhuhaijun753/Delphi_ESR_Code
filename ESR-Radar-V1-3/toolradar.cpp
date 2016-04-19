#include "toolradar.h"
#include "ui_toolradar.h"

ToolRadar::ToolRadar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolRadar)
{
    ui->setupUi(this);
    set_SB_value();
}

ToolRadar::~ToolRadar()
{
    delete ui;
}

void ToolRadar::on_PB_Insert_clicked()
{
    click_check = true;
    set_SB_value();
    //this->setVisible(false);
}

void ToolRadar::on_PB_Cancel_clicked()
{
    click_check = false;
    this->setVisible(false);
}

void ToolRadar::closeEvent(QCloseEvent *event){
    click_check = false;
    event->accept();
}

Limit ToolRadar::get_data_measurement(){
    return data_measurement;
}

bool ToolRadar::get_click_check(){
    return click_check;
}

void ToolRadar::set_SB_value(){
    data_measurement.min.Status = ui->SB_Min_Status->value();
    data_measurement.max.Status = ui->SB_Max_Status->value();
    data_measurement.min.Range = ui->SB_Min_Range->value();
    data_measurement.max.Range = ui->SB_Max_Range->value();
    data_measurement.min.Rate = ui->SB_Min_Rate->value();
    data_measurement.max.Rate = ui->SB_Max_Rate->value();
    data_measurement.min.Accel = ui->SB_Min_Accel->value();
    data_measurement.max.Accel = ui->SB_Max_Accel->value();
    data_measurement.min.HBr = ui->SB_Min_HBr->value();
    data_measurement.max.HBr = ui->SB_Max_HBr->value();
    data_measurement.min.Mode = ui->SB_Mode->value();
    data_measurement.max.Mode = ui->SB_Mode->value();
    data_measurement.min.Cohesion = ui->SB_Cohesion->value();
    data_measurement.max.Cohesion = ui->SB_Cohesion->value();
    data_measurement.min.Persistence = ui->SB_Persistence->value();
    data_measurement.max.Persistence = ui->SB_Persistence->value();
    data_measurement.min.CriticalSpeed = (float)ui->DSB_Critical_Speed->value();
    data_measurement.max.CriticalSpeed = (float)ui->DSB_Critical_Speed->value();
    data_measurement.min.Viability = ui->SB_Viability->value();
    data_measurement.max.Viability = ui->SB_Viability->value();
    data_measurement.min.AutomaticClusteringDistance = ui->SB_Automatic_Clustering_Distance->value();
    data_measurement.max.AutomaticClusteringDistance = ui->SB_Automatic_Clustering_Distance->value();
    data_measurement.min.kNN = ui->SB_K->value();
    data_measurement.max.kNN = ui->SB_K->value();
    data_measurement.min.BlobArea = ui->SB_Min_Blob_Area->value();
    data_measurement.max.BlobArea = ui->SB_Max_Blob_Area->value();
    data_measurement.min.BlobDistance = ui->SB_Blob_Distance->value();
    data_measurement.max.BlobDistance = ui->SB_Blob_Distance->value();
    data_measurement.min.BlobMinDistance = ui->SB_Blob_MinDistBlobs->value();
    data_measurement.max.BlobMinDistance = ui->SB_Blob_MinDistBlobs->value();
    data_measurement.min.CCLArea = ui->SB_Min_CCL_Area->value();
    data_measurement.max.CCLArea = ui->SB_Max_CCL_Area->value();
    data_measurement.min.CCLMode = ui->SB_CCL_Mode->value();
    data_measurement.max.CCLMode = ui->SB_CCL_Mode->value();
    data_measurement.min.MaxSPMBuf = ui->SB_MaxSPMBuf->value();
    data_measurement.max.MaxSPMBuf = ui->SB_MaxSPMBuf->value();

}

void ToolRadar::on_HSB_Cohesion_valueChanged(int value)
{
    ui->SB_Cohesion->setValue(value);
}

void ToolRadar::on_HSB_Persistence_valueChanged(int value)
{
    ui->SB_Persistence->setValue(value);
}

void ToolRadar::on_HSB_Critical_Speed_valueChanged(int value)
{
    ui->DSB_Critical_Speed->setValue((double)( (double)value/100.0));
}

void ToolRadar::on_HSB_Viability_valueChanged(int value)
{
    ui->SB_Viability->setValue(value);
}

void ToolRadar::on_SB_Cohesion_valueChanged(int value)
{
    ui->HSB_Cohesion->setValue(value);
}

void ToolRadar::on_SB_Persistence_valueChanged(int value)
{
    ui->HSB_Persistence->setValue(value);
}

void ToolRadar::on_DSB_Critical_Speed_valueChanged(double value)
{
    ui->HSB_Critical_Speed->setValue((int)(value*100));
}

void ToolRadar::on_SB_Viability_valueChanged(int value)
{
    ui->HSB_Viability->setValue(value);
}

void ToolRadar::on_HSB_Automatic_Clustering_Distance_valueChanged(int value)
{
    ui->SB_Automatic_Clustering_Distance->setValue(value);
}

void ToolRadar::on_SB_Automatic_Clustering_Distance_valueChanged(int value)
{
    ui->HSB_Automatic_Clustering_Distance->setValue(value);
}

void ToolRadar::on_HSB_K_valueChanged(int value)
{
    ui->SB_K->setValue(value);
}

void ToolRadar::on_SB_K_valueChanged(int value)
{
    ui->HSB_K->setValue(value);
}

void ToolRadar::on_HSB_Blob_Distance_valueChanged(int value)
{
    ui->SB_Blob_Distance->setValue(value);
}

void ToolRadar::on_SB_Blob_Distance_valueChanged(int value)
{
    ui->HSB_Blob_Distance->setValue(value);
}

void ToolRadar::on_HSB_Blob_MinDistBlobs_valueChanged(int value)
{
    ui->SB_Blob_MinDistBlobs->setValue(value);
}

void ToolRadar::on_SB_Blob_MinDistBlobs_valueChanged(int value)
{
    ui->HSB_Blob_MinDistBlobs->setValue(value);
}

void ToolRadar::on_HSB_MaxSPMBuf_valueChanged(int value)
{
    ui->SB_MaxSPMBuf->setValue(value);
}

void ToolRadar::on_SB_MaxSPMBuf_valueChanged(int value)
{
    ui->HSB_MaxSPMBuf->setValue(value);
}
