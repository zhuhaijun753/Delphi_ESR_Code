#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>

namespace Ui {
class messagebox;
}

class messagebox : public QWidget
{
    Q_OBJECT
private:
    Ui::messagebox *ui;
    QString message;
public:
    explicit messagebox(QWidget *parent = 0);
    ~messagebox();
    void setMessage(QString message);


private slots:
    void on_PB_OK_clicked();
};

#endif // MESSAGEBOX_H
