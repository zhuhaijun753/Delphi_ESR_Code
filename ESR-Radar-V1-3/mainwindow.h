#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QWheelEvent>
#include <QCloseEvent>
#include <QMessageBox>

#include <data.h>
#include <view.h>
#include <table.h>

//ui
#include <ObjectTrajectory.h>
#include <video.h>

#include <toolradar.h>
#include <toolcamera.h>
#include <toolrecode.h>

#define MOUSE_WHEEL_UP 120
#define MOUSE_WHEEL_DOWN -120

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_AC_Connect_triggered();
    void on_AC_Start_triggered();
    void on_AC_Stop_triggered();
    void on_AC_Table_triggered();
    void on_AC_Information_triggered();
    void on_AC_Recode_Start_triggered();
    void on_AC_Recode_Stop_triggered();
    void on_AC_RADAR_triggered();
    void on_AC_CAMERA_triggered();
    void on_AC_Recode_triggered();
    void on_HSB_Zoom_valueChanged(int value);
    void on_AC_Guide_triggered();
    void on_AC_Clear_triggered();
    void on_AC_Open_triggered();
    void on_AC_Exit_triggered();
    void on_AC_Video_triggered();
    void on_AC_Object_Trajectory_triggered();

    void on_TM_View();

    void closeEvent(QCloseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QMessageBox messagebox;

    ObjectTrajectory *object_trajectory;
    ToolRadar *tool_radar;
    ToolCamera *tool_camera;
    ToolRecode *tool_recode;

    Video *video;
    Data *data;
    View *view;
    Table *table;

    QTimer *TM_View;

    TRACK track[MAX_TRACK_SIZE];
    Limit data_measurement;
    Zoom zoom;
};

#endif // MAINWINDOW_H
