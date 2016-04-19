#ifndef DATA_H
#define DATA_H

#include <QThread>
#include <reversing.h>
#include <canconnect.h>

class Data : public QThread
{
    Q_OBJECT

private:
    ChannelDataStruct m_channel_Data_Struct;

    DATA m_data;//데이터 변수
    TRACK m_sig_track,m_track[MAX_TRACK_SIZE];//트렉 관련 변수

    unsigned char m_hex[MAX_HEX_SIZE];//핵사코드
    unsigned char m_bit[MAX_BIT_SIZE];//비트코드
    unsigned char m_out_bit[MAX_BIT_SIZE];//출력 비트 코드
    bool thread_state;//쓰레스 작업여부확인
    QString m_hex_to_string;//핵사코드 스트링 전환
    QString message;//상태 메시지

    void run();

public:
    Data();

    void set_can();
    void stop();

    QString get_message();
    TRACK* get_track();
};
#endif // DATA_H
