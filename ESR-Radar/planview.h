#ifndef PLANVIEW_H
#define PLANVIEW_H

#include <QWidget>
#include <reversing.h>
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QDebug>
#include <rule.h>
#include <mode.h>

class planview : public QWidget
{
    Q_OBJECT
private:
    int width;
    int height;

    long id;
    int state;
    float range;
    float angle;
    float range_rate;

    QLabel *ui_track[64];

    int count;
    int ui_range,ui_angle;
    int ui_x,ui_y;
    float x,y,p;
    int ui_track_size;

    int mode;
    rule radar_rule;
public:
    planview(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void setData(long id , int state ,float range, float angle , float range_rate);
    void setData(TRACK* track);
    void setMode(int mode);
};

#endif // PLANVIEW_H
