#ifndef TOOLRECODE_H
#define TOOLRECODE_H

#include <QMainWindow>

namespace Ui {
class ToolRecode;
}

class ToolRecode : public QMainWindow
{
    Q_OBJECT

public:
    explicit ToolRecode(QWidget *parent = 0);
    ~ToolRecode();

private:
    Ui::ToolRecode *ui;
};

#endif // TOOLRECODE_H
