#ifndef TABLE_H
#define TABLE_H
#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QCloseEvent>
#include <QMouseEvent>

#include <opencv2/opencv.hpp>
#include <defines.h>
#include <reversing.h>
#include <rule.h>

using namespace cv;

namespace Ui {
class Table;
}

class Table : public QMainWindow
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0);
    ~Table();

    void set_track_data(TRACK* track);
    void set_data_mesurement(Limit data_mesurement);
    void paint_table();

private slots:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:

    Ui::Table *ui;

    Mat mat_table;
    TRACK *track;
    Rule *rule;
    Limit data_mesurement;

    QString table_value_name[6];
    QPoint mouse_click_point[MAX_TRACK_SIZE];

    Scalar background_table_line_color;
    Scalar background_table_text_color;

    void paint_background_table();
    void paint_value_table();
    QPixmap get_table();

};

#endif // TABLE_H
