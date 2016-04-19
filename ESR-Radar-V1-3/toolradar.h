#ifndef TOOLRADAR_H
#define TOOLRADAR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDebug>

#include <defines.h>

namespace Ui {
class ToolRadar;
}

class ToolRadar : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolRadar(QWidget *parent = 0);
    ~ToolRadar();

    Limit get_data_measurement();
    bool get_click_check();

private slots:
    void on_PB_Insert_clicked();
    void on_PB_Cancel_clicked();
    void closeEvent(QCloseEvent *event);

    void on_HSB_Cohesion_valueChanged(int value);
    void on_SB_Cohesion_valueChanged(int value);

    void on_HSB_Persistence_valueChanged(int value);
    void on_SB_Persistence_valueChanged(int value);

    void on_HSB_Critical_Speed_valueChanged(int value);
    void on_DSB_Critical_Speed_valueChanged(double value);

    void on_HSB_Viability_valueChanged(int value);
    void on_SB_Viability_valueChanged(int value);

    void on_HSB_Automatic_Clustering_Distance_valueChanged(int value);
    void on_SB_Automatic_Clustering_Distance_valueChanged(int value);

    void on_HSB_K_valueChanged(int value);
    void on_SB_K_valueChanged(int value);

    void on_HSB_Blob_Distance_valueChanged(int value);
    void on_SB_Blob_Distance_valueChanged(int value);

    void on_HSB_Blob_MinDistBlobs_valueChanged(int value);
    void on_SB_Blob_MinDistBlobs_valueChanged(int value);

    void on_HSB_MaxSPMBuf_valueChanged(int value);
    void on_SB_MaxSPMBuf_valueChanged(int value);

private:
    Ui::ToolRadar *ui;
    Limit data_measurement;
    bool click_check;

    void set_SB_value();
};

#endif // TOOLRADAR_H
