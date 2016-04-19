#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //생성자
    TM_View = new QTimer();

    data = new Data();
    view = new View();
    video = new Video();
    table = new Table();

    object_trajectory = new ObjectTrajectory();
    tool_radar = new ToolRadar();
    tool_camera = new ToolCamera();
    tool_recode = new ToolRecode();

    //타이머 설정
    connect(TM_View, SIGNAL(timeout()), this, SLOT(on_TM_View()));

    ui->setupUi(this);

    //줌설정
    zoom.level = ui->HSB_Zoom->value();

    //뷰설정
    view->set_zoom_data(zoom);
    view->paint_init();
    ui->LB_View->setPixmap(view->get_view());

    //크기지정 전부다 define으로 정의
    messagebox.setBaseSize(300,150);
    messagebox.setWindowTitle("Message Box");

    //레이더 데이터 범위 설정
    data_measurement = tool_radar->get_data_measurement();

    //테이블 설정
    table->paint_table();
    //
    tool_radar->setVisible(true);
}

MainWindow::~MainWindow()
{
    TM_View->stop();
    data->stop();//쓰레드 중단
    data->exit();//쓰레드 나가기
    data->quit();//쓰레드 종료
    if(data->isRunning() == true){
        data->msleep(1);//그래도 처리 중일 경우 (sleep)으로 지연
        data->wait();//wait로 남은 데이터 처리 끝날때까지 지연
        data->terminate();//강제 종료(실상 이것만 써도됨)
    }

    delete data;
    delete TM_View;
    delete view;

    delete table;
    delete video;
    delete object_trajectory;

    delete tool_radar;
    delete tool_camera;
    delete tool_recode;

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    object_trajectory->setVisible(false);
    object_trajectory->close();
    video->setVisible(false);
    video->close();
    table->setVisible(false);
    table->close();

    tool_radar->setVisible(false);
    tool_radar->close();
    tool_camera->setVisible(false);
    tool_camera->close();
    tool_recode->setVisible(false);
    tool_recode->close();

    event->accept();
}

void MainWindow::on_TM_View()
{

    if(tool_radar->get_click_check()){
        data_measurement = tool_radar->get_data_measurement();
    }

    //메인 뷰
    view->set_data_measurement(data_measurement);
    view->set_track_data(data->get_track());
    view->set_zoom_data(zoom);

    view->paint_view();
    ui->LB_View->setPixmap(view->get_view());

    //객채 추적 뷰
    object_trajectory->set_data_measurement(data_measurement);
    object_trajectory->set_track_data(data->get_track());

    //비디오
    video->paint_video();

    //테이블
    table->set_data_mesurement(data_measurement);
    table->set_track_data(data->get_track());
    table->paint_table();
}

void MainWindow::on_AC_Connect_triggered()
{
    data->set_can();
    messagebox.setText(data->get_message());
    messagebox.exec();
}

void MainWindow::on_AC_Start_triggered( )
{
    data->start();
    TM_View->start();
}

void MainWindow::on_AC_Stop_triggered( )
{
    data->stop();
    TM_View->stop();
}

void MainWindow::on_AC_Table_triggered( )
{
    table->setVisible(true);
}

void MainWindow::on_AC_Information_triggered( )
{
    //정보는 다 완성되고 나서 작성
}

void MainWindow::on_AC_Recode_Start_triggered( )
{
    //기록관련은 데이터 타입이 명확히 정의될때 사용(개발 태스트용)
}

void MainWindow::on_AC_Recode_Stop_triggered( )
{
    //기록관련은 데이터 타입이 명확히 정의될때 사용(개발 태스트용)
}

void MainWindow::on_AC_RADAR_triggered( )
{
    tool_radar->setVisible(true);
}

void MainWindow::on_AC_CAMERA_triggered( )
{
    tool_camera->setVisible(true);
}

void MainWindow::on_AC_Recode_triggered()
{
    //기록관련은 데이터 타입이 명확히 정의될때 사용(개발 태스트용)
    //여기서는 영상과 데이터 타입 둘다 녹화하는지, 영상만 녹화하는지, 데이터만 녹화하는지 지정
    //확장되서 센서를 2개 이상 사용할 시 맨 뒤에 _Rb(bow), _Rsb(starboard),_Rsp(port)
    tool_recode->setVisible(true);
}

void MainWindow::on_AC_Guide_triggered()
{
    //안내서는 다 완성되고 나서 작성
}

void MainWindow::on_AC_Clear_triggered()
{
    view->paint_init();
    ui->LB_View->setPixmap(view->get_view());
}

void MainWindow::on_AC_Open_triggered()
{
    //기록 명칭 표현 정의 완료된 후 작성
}

void MainWindow::on_AC_Exit_triggered()
{
    this->close();
}

void MainWindow::on_AC_Video_triggered()
{
    video->setVisible(true);
}

void MainWindow::on_AC_Object_Trajectory_triggered()
{
    object_trajectory->setVisible(true);
    //object_trajectory->timer_start();
}

void MainWindow::on_HSB_Zoom_valueChanged(int value)
{
    zoom.level = value;
    view->set_zoom_data(zoom);
    view->paint_view();
    ui->LB_View->setPixmap(view->get_view());
}

void MainWindow::wheelEvent(QWheelEvent *event){
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

void MainWindow::keyPressEvent(QKeyEvent *event){
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
