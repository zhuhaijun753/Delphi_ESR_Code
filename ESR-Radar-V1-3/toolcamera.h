#ifndef TOOLCAMERA_H
#define TOOLCAMERA_H

#include <QMainWindow>

namespace Ui {
class ToolCamera;
}

class ToolCamera : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolCamera(QWidget *parent = 0);
    ~ToolCamera();

private:
    Ui::ToolCamera *ui;
};

#endif // TOOLCAMERA_H
