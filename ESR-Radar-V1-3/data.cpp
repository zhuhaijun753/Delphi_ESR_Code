#include "data.h"

Data::Data(){
    for(int i = 0 ; i < MAX_TRACK_SIZE ; i++){
        m_track[i].AMP = 0;
        m_track[i].ANGLE = 0;
        m_track[i].BRIDGE = 0;
        m_track[i].GROUPING = 0;
        m_track[i].id = 0;
        m_track[i].LAT_RATE = 0;
        m_track[i].MED_RANGE_MODE = 0;
        m_track[i].ONCOMMING = 0;
        m_track[i].RANGE = 0;
        m_track[i].RANGE_ACCEL = 0;
        m_track[i].RANGE_RATE = 0;
        m_track[i].ROLLING = 0;
        m_track[i].STATUS = 0;
        m_track[i].WIDTH = 0;
        m_track[i].X = 0;
        m_track[i].Y = 0;
    }
}

void Data::set_can(){
    //CAN 연결 초기 설정
    m_channel_Data_Struct=Integrated();

    //RX에 전원 제어 입력
    unsigned char ibuf[MAX_HEX_SIZE]= {0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x00};
    for(int i = 0 ; i < MAX_HEX_SIZE ; i++){
        m_data.buf[i] = ibuf[i];
    }
    m_data.flag = 0;
    m_data.id = 0x4F1;

    //연결 여부 확인
    if(m_channel_Data_Struct.channel != _DEFAULT){
        set_CAN_Write(m_channel_Data_Struct.hnd,m_data);
        message = "Successful!!";
    }else{
        message = "Error : Connected CAN Bus Driver";
    }
}

void Data::run(){

    //Thread
    thread_state = true;

    while(thread_state){
        //TX 데이터를 읽어옴
        m_data = set_CAN_Read(m_channel_Data_Struct.hnd);

        //측정된 TRACK일 때만 작업을 수행
        if(m_data.flag != _DEFAULT){
            //트랙의 범위는 0x500~0x53F (64개의 트)
            if( 0x500 <= m_data.id && m_data.id <= 0x53F ){
                //핵사코드 비트로 변
                convert_hexcode_to_bit(m_data.buf,m_bit);

                //비트화된 데이터를 실수형으로 변
                m_track[m_data.id-0x500] = analysis(m_bit,m_out_bit,m_sig_track);

                //Track id를 배열에 맞게끔 설정
                m_track[m_data.id-0x500].id = m_data.id-0x500;

                //Track Hex를 추가 저장(데이터 저장용도로 추가 함 )
                for(int i = 0; i < MAX_HEX_SIZE ; i++){
                    m_track[m_data.id-0x500].hex[i] = m_data.buf[i];
                }
                //msleep(50);
            }
        }
    }
}

void Data::stop(){
    thread_state = false;
}

QString Data::get_message(){
    return message;
}

TRACK* Data::get_track(){
    return m_track;
}
