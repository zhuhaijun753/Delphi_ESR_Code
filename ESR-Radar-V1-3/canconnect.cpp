#include <canconnect.h>

void init(){

    int i;
    DriverData channelData;

    memset(channelData.channel, 0, sizeof(channelData.channel));

    for (i = 0; i < MAX_CHANNELS; i++) {
        channelData.channel[i].isOnBus = 0;
        channelData.channel[i].driverMode = canDRIVER_NORMAL;
        channelData.channel[i].channel = -1;
        channelData.channel[i].hnd = -1;
        channelData.channel[i].txAck = 0; // Default is TxAck off
    }
    channelData.channelCount = 0;

    canInitializeLibrary();

}

void release(){
    canStatus state;
    canHandle h;

    state=canBusOff(h);
    state=canClose(h);
}

void search_channel(){
    canStatus state;
    unsigned int i;
    DriverData channelData;

    state = canGetNumberOfChannels((int*)&channelData.channelCount);

    //printf("사용가능 채널 확인\n");

    for(i = 0 ; i < channelData.channelCount ; i++){
        canGetChannelData(i, canCHANNELDATA_CHANNEL_NAME,channelData.channel[i].name,	sizeof(channelData.channel[i].name));
        canGetChannelData(i, canCHANNELDATA_CARD_TYPE,&channelData.channel[i].hwType,	sizeof(DWORD));

        //printf("%d : %s\n" ,i , m_channelData.channel[i].name );
    }

    //printf("선택할 채널 : ");
    //scanf("%d" , &channel);
}

void set_Open_Channel(){
    canHandle h;
    int channel;
    h = canOpenChannel(channel, canWANT_EXCLUSIVE);
}

void set_CANBUS(){
    canStatus state;
    canHandle h;
    //지역 변수는 입력값으로 설정
    int bitrate = BAUD_500K;//bitrate
    int sps = 5;//sampling point start
    int spe = 2;//sampling point end
    int swf = 0;//synchronization jump width

    state = canIoCtl(h, canIOCTL_FLUSH_TX_BUFFER, NULL, NULL);
    state = canSetBusOutputControl(h , canDRIVER_NORMAL);
    state = canSetBusParams(h, bitrate, sps, spe, swf, 0, 0);
    state = canBusOn(h);

}

void set_CAN_Write(canHandle h , DATA data){
    canWrite(h,data.id , data.buf, sizeof(data.buf) , data.flag);
}

DATA set_CAN_Read(canHandle h){
    long reid;
    int i;
    unsigned char redata[MAX_BUF_SIZE];
    unsigned int redlc;
    unsigned int reflags;
    DWORD retime;
    DATA outdata;

    canStatus state;
    state = canRead(h, &reid, &redata[0], &redlc, &reflags, &retime);
    if(state == canOK){
        outdata.id = reid;
        for(i = 0 ; i < MAX_BUF_SIZE ; i++){
            outdata.buf[i] = redata[i];
        }
        outdata.flag = reflags;
    }else{
        outdata.flag = -1;
    }
    return outdata;
}

ChannelDataStruct Integrated(){

    int i;
    DriverData channelData;
    canHandle h;
    canStatus state;
    ChannelDataStruct output;
    int channel_num =-1;

    int bitrate = BAUD_500K;//bitrate
    int sps = 5;//sampling point start
    int spe = 2;//sampling point end
    int swf = 0;//synchronization jump width

    memset(channelData.channel, 0, sizeof(channelData.channel));

    for (i = 0; i < MAX_CHANNELS; i++) {
        channelData.channel[i].isOnBus = 0;
        channelData.channel[i].driverMode = canDRIVER_NORMAL;
        channelData.channel[i].channel = -1;
        channelData.channel[i].hnd = -1;
        channelData.channel[i].txAck = 0; // Default is TxAck off
    }
    channelData.channelCount = 0;

    canInitializeLibrary();

    state = canGetNumberOfChannels((int*)&channelData.channelCount);

    for(i = 0 ; i < channelData.channelCount ; i++){
        canGetChannelData(i, canCHANNELDATA_CHANNEL_NAME,channelData.channel[i].name,	sizeof(channelData.channel[i].name));
        canGetChannelData(i, canCHANNELDATA_CARD_TYPE,&channelData.channel[i].hwType,	sizeof(DWORD));
        //printf("%s\n" , channelData.channel[i].name);
        if(channelData.channel[i].name[0] == 'K'){
            channelData.channel[i].channel = i;
            channel_num = i;
            break;
        }
    }
    if(channel_num != _DEFAULT){
        channelData.channel[channel_num].hnd = canOpenChannel(channelData.channel[channel_num].channel, canWANT_EXCLUSIVE);

        state = canIoCtl(channelData.channel[channel_num].hnd, canIOCTL_FLUSH_TX_BUFFER, NULL, NULL);
        state = canSetBusOutputControl(channelData.channel[channel_num].hnd , canDRIVER_NORMAL);
        state = canSetBusParams(channelData.channel[channel_num].hnd, bitrate, sps, spe, swf, 0, 0);
        state = canBusOn(channelData.channel[channel_num].hnd);
        channelData.channel[channel_num].isOnBus = _TRUE;

        output = channelData.channel[channel_num];
    }else{
        output.channel = -1;
    }

    return output;
}
