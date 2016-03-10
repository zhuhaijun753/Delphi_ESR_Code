#ifndef FILEIO_H
#define FILEIO_H

#include <QFile>
#include <reversing.h>
#include <QDate>
#include <QTextStream>
#include <iostream>
#include <QDataStream>
#include <QDebug>

class fileIO
{
private:
    QFile file;
    QString filename;

    unsigned int frame_count;
    unsigned int file_num;

    int count;

    TRACK read_track[30000][64];
public:
    fileIO();

    void set_filename(QString str);
    void set_filename();

    void write(TRACK *track);
    void close();

    void read(QString filename);

    TRACK* get_read_track(int count);
    int get_frame_count();
};

#endif // FILEIO_H
