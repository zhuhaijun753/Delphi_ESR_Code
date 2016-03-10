#include "datathread.h"

void dataThread::set_can(){
    m_channel_Data_Struct=Integrated();
    unsigned char ibuf[8]= {0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x00};
    for(int i = 0 ; i < 8 ; i++){
        m_data.buf[i] = ibuf[i];
    }
    m_data.flag = 0;
    m_data.id = 0x4F1;
    if(m_channel_Data_Struct.channel != _DEFAULT){
        set_CAN_Write(m_channel_Data_Struct.hnd,m_data);
        message = "Successful!!";
    }else{
        message = "Error : Connected CAN Bus Driver";
    }

}

void dataThread::run(){
    thread_state = true;

    while(thread_state){
        m_data = set_CAN_Read(m_channel_Data_Struct.hnd);

        if(m_data.flag != -1){
            if( 0x500 <= m_data.id && m_data.id <= 0x53F ){
                convert_hexcode_to_bit(m_data.buf,m_bit);
                m_track[m_data.id-0x500] = analysis(m_bit,m_out_bit,m_sig_track);
                m_track[m_data.id-0x500].id = m_data.id-0x500;
                for(int i = 0; i < 8 ; i++){
                    m_track[m_data.id-0x500].hex[i] = m_data.buf[i];
                }
                //msleep(50);
            }
        }
    }
}

void dataThread::stop(){
    thread_state = false;
}

QString dataThread::get_message(){
    return message;
}

TRACK* dataThread::get_track(){
    return m_track;
}

