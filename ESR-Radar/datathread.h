#ifndef DATATHREAD_H
#define DATATHREAD_H

#include <QThread>
#include <reversing.h>
#include <canconnect.h>

class dataThread : public QThread
{
    Q_OBJECT

private:
    ChannelDataStruct m_channel_Data_Struct;

    DATA m_data;
    TRACK m_sig_track,m_track[MAX_TRACK_SIZE];

    unsigned char m_hex[MAX_HEX_SIZE];
    unsigned char m_bit[MAX_BIT_SIZE];
    unsigned char m_out_bit[MAX_BIT_SIZE];
    bool thread_state;
    QString m_hex_to_string;

    QString message;
    void run();

public:
    void set_can();
    void stop();

    QString get_message();
    TRACK* get_track();
};

#endif // DATATHREAD_H
