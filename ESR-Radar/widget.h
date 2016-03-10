#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>

#include <qtimer.h>
#include <datathread.h>
#include <fileio.h>
#include <mode.h>
#include <messagebox.h>
#include <video.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_PB_Read_clicked();
    void on_PB_Connect_clicked();
    void on_PB_Start_clicked();
    void on_PB_Stop_clicked();
    void on_PB_Recode_Start_clicked();
    void on_PB_Recode_Stop_clicked();

    void on_TM_Start();
    void on_TM_Recode_Start();
    void on_TM_Video();

    void on_RB_Polar_clicked();
    void on_RB_Rectangular_clicked();
    void on_PB_Video_Start_Stop_clicked();
    void on_HS_Video_SliderBar_sliderMoved(int position);
    void on_SB_Frame_Number_valueChanged(int value);

    void on_CB_Video_clicked();

private:
    Ui::Widget *ui;

    //
    QTimer *TM_Start,*TM_Recode_Start,*TM_Video;
    //
    dataThread *datathread;
    fileIO *file;
    TRACK *track;
    //
    int mode;
    int col,row;
    int video_frame_count;

    messagebox *message_box;
    video *my_video;
};

#endif // WIDGET_H
