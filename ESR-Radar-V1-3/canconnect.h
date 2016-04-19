#ifndef CANCONNECT_H
#define CANCONNECT_H

#include <stdlib.h>
#include <stdio.h>
#include <canlib.h>

#include <qdebug.h>

#define MAX_CHANNELS 10
#define MAX_BIT_SIZE 64
#define MAX_BUF_SIZE 8

//bool 설정
#define _TRUE 1
#define _FALSE 0
#define _DEFAULT -1

//bool
typedef unsigned int _BOOL;

//can drvierData
typedef struct {
    int        channel;//채널
    char       name[100];//드라이버 명
    DWORD      hwType;//해딩 타입
    canHandle  hnd;//CAN Handler
    int        hwIndex;//CAN 식별 번호
    int        hwChannel;//CAN 체널
    int        isOnBus;//CAN Bus 상태
    int        driverMode;//사용 드라이버 모드
    int        txAck;
}ChannelDataStruct;

typedef struct {
    unsigned int       channelCount;//체널 개수
    ChannelDataStruct  channel[MAX_CHANNELS];//채널 개수에 따른 채널
}DriverData;

//hex data
typedef struct{
    long id;//HEX code ID
    unsigned char buf[MAX_BUF_SIZE];//Hex code
    int flag;//flag
}DATA;

//function
void init();//초기설정
void release();//핸들러 제거(연결 해제)
void search_channel();//채널 검색
void set_Open_Channel();//채널 열기
void set_CANBUS();//CAN Bus 설정
void set_CAN_Write(canHandle h , DATA data);//Rx 입력
DATA set_CAN_Read(canHandle h);//Tx 받기
ChannelDataStruct Integrated();//드라이버 통합

#endif // CANCONNECT_H
