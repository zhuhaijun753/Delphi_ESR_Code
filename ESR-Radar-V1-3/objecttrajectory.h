#ifndef OBJECTTRAJECTORY_H
#define OBJECTTRAJECTORY_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QPixmap>

#include <QDebug>

#include <reversing.h>
#include <defines.h>
#include <view.h>
#include <rule.h>

#include <vector>

#define MOUSE_WHEEL_UP 120
#define MOUSE_WHEEL_DOWN -120

using namespace std;

namespace Ui {
    class ObjectTrajectory;
}

class ObjectTrajectory : public QMainWindow
{
    Q_OBJECT

public:
    explicit ObjectTrajectory(QWidget *parent = 0);
    ~ObjectTrajectory();

    void set_data_measurement(Limit data_measurement);
    void set_track_data(TRACK *track);
    void timer_start();
    void timer_stop();

private slots:
    void on_TM_View();

    void closeEvent(QCloseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void on_AC_BLOB_triggered(bool checked);
    void on_AC_K_NN_triggered(bool checked);
    void on_AC_Basic_triggered(bool checked);
    void on_AC_Trajectory_triggered(bool checked);
    void on_AC_S_CCL_triggered(bool checked);
    void on_AC_RBNN_triggered(bool checked);
    void on_AC_Automatic_Clustering_triggered(bool checked);

    void on_AC_Start_triggered();
    void on_AC_Stop_triggered();
    void on_HSB_Zoom_valueChanged(int value);

private:
    Ui::ObjectTrajectory *ui;

    View *view;
    QTimer *TM_View;
    TRACK *track;

    Limit data_measurement;
    Zoom zoom;

    vector<TRACK> *track_trajectory;//sp matrix = 수정
    int check_clustering_mode;

};

#endif // OBJECTTRAJECTORY_H
