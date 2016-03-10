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
    int        channel;
    char       name[100];
    DWORD      hwType;
    canHandle  hnd;
    int        hwIndex;
    int        hwChannel;
    int        isOnBus;
    int        driverMode;
    int        txAck;
} ChannelDataStruct;

typedef struct {
    unsigned int       channelCount;
    ChannelDataStruct  channel[MAX_CHANNELS];
}DriverData;
//hex data
typedef struct{
    long id;
    unsigned char buf[MAX_BUF_SIZE];
    int flag;
}DATA;

//function
void init();
void release();
void search_channel();
void set_Open_Channel();
void set_CANBUS();
void set_CAN_Write(canHandle h , DATA data);
DATA set_CAN_Read(canHandle h);
ChannelDataStruct Integrated();

#endif // CANCONNECT_H
