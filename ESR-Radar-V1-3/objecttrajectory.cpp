#include "objecttrajectory.h"
#include "ui_objecttrajectory.h"

ObjectTrajectory::ObjectTrajectory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ObjectTrajectory)
{
    view = new View();
    TM_View = new QTimer();

    track = new TRACK[MAX_TRACK_SIZE];
    track_trajectory = new vector<TRACK>[MAX_TRACK_SIZE];

    connect(TM_View, SIGNAL(timeout()), this, SLOT(on_TM_View()));
    ui->setupUi(this);

    //줌 설정
    zoom.level = ui->HSB_Zoom->value();
    view->set_zoom_data(zoom);

    view->paint_object_trajectory_init();
    ui->LB_View->setPixmap(view->get_view());

    check_clustering_mode = 0;
}

ObjectTrajectory::~ObjectTrajectory()
{
    TM_View->stop();

    delete view;
    delete TM_View;
    delete track;
    delete track_trajectory;

    delete ui;
}

void ObjectTrajectory::closeEvent(QCloseEvent *event){

    event->accept();
}

void ObjectTrajectory::set_track_data(TRACK *track){
    this->track = track;
}

void ObjectTrajectory::set_data_measurement(Limit data_measurement){
    this->data_measurement = data_measurement;
}

void ObjectTrajectory::timer_start(){

    view->set_data_measurement(data_measurement);
    view->set_zoom_data(zoom);

    TM_View->start();

}

void ObjectTrajectory::timer_stop(){
    TM_View->stop();
}

void ObjectTrajectory::on_TM_View(){
    view->set_data_measurement(data_measurement);
    view->set_track_data(track);
    view->set_zoom_data(zoom);

    //qDebug()<<data_measurement.max.State<<" "<<data_measurement.min.State;

    view->paint_object_trajectory_view(check_clustering_mode);
    ui->LB_View->setPixmap(view->get_view());
}

void ObjectTrajectory::wheelEvent(QWheelEvent *event){
    if(event->delta() == MOUSE_WHEEL_UP ){
        if(zoom.level != ui->HSB_Zoom->maximum()){
            zoom.level++;
            ui->HSB_Zoom->setValue(zoom.level);
        }
    }

    if(event->delta() == MOUSE_WHEEL_DOWN ){
        if(zoom.level != ui->HSB_Zoom->minimum()){
            zoom.level--;
            ui->HSB_Zoom->setValue(zoom.level);
        }
    }
    event->accept();
}

void ObjectTrajectory::keyPressEvent(QKeyEvent *event){
    if(event->text() =="+"){
        if(zoom.level != ui->HSB_Zoom->maximum()){
            zoom.level++;
            ui->HSB_Zoom->setValue(zoom.level);
        }
    }
    if(event->text() =="-"){
        if(zoom.level != ui->HSB_Zoom->minimum()){
            zoom.level--;
            ui->HSB_Zoom->setValue(zoom.level);
        }
    }
    event->accept();
}

void ObjectTrajectory::on_AC_Basic_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_BASIC;
    if(checked == true){
        ui->AC_BLOB->setChecked(false);
        ui->AC_K_NN->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_RBNN->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_Trajectory_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_TRAJECTORY;
    if(checked == true){
        ui->AC_BLOB->setChecked(false);
        ui->AC_K_NN->setChecked(false);
        ui->AC_Basic->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_RBNN->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_BLOB_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_BLOB;
    if(checked == true){
        ui->AC_Basic->setChecked(false);
        ui->AC_K_NN->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_RBNN->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_K_NN_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_K_NN;
    if(checked == true){
        ui->AC_BLOB->setChecked(false);
        ui->AC_Basic->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_RBNN->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_S_CCL_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_S_CCL;
    if(checked == true){
        ui->AC_K_NN->setChecked(false);
        ui->AC_BLOB->setChecked(false);
        ui->AC_Basic->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_RBNN->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_RBNN_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_RBNN;
    if(checked == true){
        ui->AC_K_NN->setChecked(false);
        ui->AC_BLOB->setChecked(false);
        ui->AC_Basic->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_Automatic_Clustering->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_AC_Automatic_Clustering_triggered(bool checked)
{
    check_clustering_mode = TRACK_VIEW_AUTOMATIC_CLUSTERING;
    if(checked == true){
        ui->AC_K_NN->setChecked(false);
        ui->AC_BLOB->setChecked(false);
        ui->AC_Basic->setChecked(false);
        ui->AC_Trajectory->setChecked(false);
        ui->AC_S_CCL->setChecked(false);
        ui->AC_RBNN->setChecked(false);
    }
    on_TM_View();
}

void ObjectTrajectory::on_HSB_Zoom_valueChanged(int value)
{
    zoom.level = value;
    view->set_zoom_data(zoom);
    view->paint_object_trajectory_view();
    ui->LB_View->setPixmap(view->get_view());
}

void ObjectTrajectory::on_AC_Start_triggered()
{
    timer_start();
}

void ObjectTrajectory::on_AC_Stop_triggered()
{
    timer_stop();
}


