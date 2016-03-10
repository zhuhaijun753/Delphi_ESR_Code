#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QTimer>
#include <videothread.h>
#include <QDebug>

namespace Ui {
class video;
}

class video : public QWidget

{
    Q_OBJECT
private:
    Ui::video *ui;
    videothread *video_thread;
    QTimer *TM_Video_Start;
    int state;

public:
    explicit video(QWidget *parent = 0);
    ~video();
    void set_state(int state);
    void start();
    void stop();
private slots:
    void on_TM_Video_Start();
};

#endif // VIDEO_H
