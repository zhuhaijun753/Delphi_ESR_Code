#ifndef RULE_H
#define RULE_H

#include <QColor>
#include <reversing.h>
#include <math.h>
#include <mode.h>

class rule
{
private:
    QColor color;
    QString scolor;

    int mode;
    float x,y,p,r;
    int a,b;
public:
    rule();
    void setData(TRACK track);
    void setMode(int mode);
    QColor getColor();
    QString getSColor();
};

#endif // RULE_H
