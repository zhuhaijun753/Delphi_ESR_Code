#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QWidget>
#include <reversing.h>
#include <mode.h>

#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QDebug>
#include <QFont>

class tableview : public QWidget
{
    Q_OBJECT

private:
    int width,height;
    int mode;

    QLabel *ui_range[64];
    QLabel *ui_angle[64];

    QLabel *ui_x[64];
    QLabel *ui_y[64];

    QLabel *ui_state[64];
    QLabel *ui_range_rate[64];
    QLabel *ui_range_accel[64];

    QFont font;
    QString title[5];
    QString str;
    int title_width[5];
    int title_x[5];

    int label_x,label_y;
    int table_width,table_height;

    float x,y,p;
public:
    tableview(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void setData(TRACK *track);
    void setMode(int mode);
};

#endif // TABLEVIEW_H
