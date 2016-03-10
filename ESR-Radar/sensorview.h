#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <QWidget>
#include <reversing.h>
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QDebug>
#include <rule.h>
#include <mode.h>

class sensorview : public QWidget
{
    Q_OBJECT
private:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    int width,height;
    QLabel *ui_track[64];
    int mode;
    rule radar_rule;
    int label_width;
    int label_height;
public:
    sensorview(QWidget *parent = 0);
    void setData(TRACK *track);

    void setMode(int mode);
};

#endif // SENSORVIEW_H
