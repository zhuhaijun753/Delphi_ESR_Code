#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>

namespace Ui {
class video;
}

class video : public QWidget
{
    Q_OBJECT

public:
    explicit video(QWidget *parent = 0);
    ~video();

    int state;
private:
    Ui::video *ui;

    void set_state();
};

#endif // VIDEO_H
