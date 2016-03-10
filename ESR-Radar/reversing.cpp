#include <reversing.h>

void hex_to_bit(unsigned char hexcode, unsigned char* bit){
    //in : 1byte . out : 8bit
    int num = hexcode;
    int i;
    unsigned char tbit[MAX_BUF_SIZE];

    for(i = 0; i < MAX_BUF_SIZE ; i++){
        bit[i] = 0;
        tbit[i] = 0;
    }

    for(i = 0; num > 0 ; i++){
        tbit[i] = (num%2);
        num = num/2;
    }

    for(i = 0 ; i < MAX_BUF_SIZE ; i++){
        bit[i]=tbit[(MAX_BUF_SIZE-1)-i];
    }

    //for(i = 0 ; i < 8 ; i++){	printf("%d" , tbuf[i]);	}printf("\n");

}

void convert_bit_to_complement(unsigned char* bit, int array_size ,unsigned char *out_bit){
    int i;

    for(i = 0; i < array_size ; i++){
        if(bit[i] == 0x00){
            out_bit[i] = 0x01;
        }else{
            out_bit[i] = 0x00;
        }
    }

    if(out_bit[array_size-1] == 0x00){
        out_bit[array_size-1] = 0x01;
    }else{
        out_bit[array_size-1] = 0x00;
        for(i = 1; i < array_size ; i++){
            if(out_bit[(array_size-1)-i] == 0x00){
                out_bit[(array_size-1)-i] = 0x01;
                break;
            }else{
                out_bit[(array_size-1)-i] = 0x00;
            }
        }
    }

}

void convert_hexcode_to_bit(unsigned char* hexcode, unsigned char* bit){//in : 8byte , out : 64bit

    int row = 0;
    int i;
    int j;
    unsigned char tbit[MAX_BUF_SIZE];

    for(i = 0; i < MAX_BUF_SIZE ; i++){
        hex_to_bit(hexcode[i],tbit);
        for(j = 0 ; j < MAX_BUF_SIZE ; j++){
            bit[row] = tbit[j];
            row++;
        }
    }
}

float pow_of_2(float num){

    float output = 1;
    int i;

    if(num == 0){
        return output;
    }else if(num > 0){
        for(i = 0; i < (int)num ; i++){
            output *= 2;
        }
    }else{
        num = num*(-1);
        for(i = 0; i < (int)num ; i++){
            output /= 2;
        }
    }

    return output;

}

float cal_bit_to_float(unsigned char* bit , int array_size){

    int i;
    float output = 0;

    for(i = 0; i < array_size ; i++){
        if(bit[i] == 0x01){
            output += pow_of_2( (float)(array_size-1)-i);
        }
    }

    return output;
}

float convert_bit_to_float(unsigned char* bit , int array_size , int flag){


    //그전에 이진수 소수점 표현(부호 포함)
    //첫번째 태스팅
    float output;
    //for(i = 0; i < array_size ; i++){
    //	printf("%d" , bit[i]);
    //}
    switch(flag){
    case TX_LAT_RATE:
        if(bit[0] == 0x01){
            convert_bit_to_complement(bit,array_size,bit);
            output = cal_bit_to_float(bit,array_size);
            output = output*(-1);
        }else{
            output = cal_bit_to_float(bit,array_size);
        }
        output = output*0.25;
        break;
    case TX_GROUPING:
        output = cal_bit_to_float(bit,array_size);
        break;
    case TX_ONCOMMING:
        output = cal_bit_to_float(bit,array_size);
        break;
    case TX_STATUS:
        output = cal_bit_to_float(bit,array_size);
        break;
    case TX_ANGLE:

        if(bit[0] == 0x01){
            convert_bit_to_complement(bit,array_size,bit);
            output = cal_bit_to_float(bit,array_size);
            output = output*(-1);
        }else{
            output = cal_bit_to_float(bit,array_size);
        }
        output = output*0.1;
        break;
    case TX_RANGE:
        output = cal_bit_to_float(bit,array_size);
        output = output*0.1;
        //output = cal_bit_to_float(bit,array_size);
        break;
    case TX_BRIDGE:
        output = cal_bit_to_float(bit,array_size);
        break;
    case TX_ROLLING:
        output = cal_bit_to_float(bit,array_size);
        break;
    case TX_WIDTH:
        output = cal_bit_to_float(bit,array_size);
        output = output*0.5;
        break;
    case TX_RANGE_ACCEL:
        output = cal_bit_to_float(bit,array_size);
        output = output*0.05;

        break;
    case TX_MED_RANGE_MODE:
        break;
    case TX_RANGE_RATE:
        if(bit[0] == 0x01){
            convert_bit_to_complement(bit,array_size,bit);
            output = cal_bit_to_float(bit,array_size);
            output = output*(-1);
        }else{
            output = cal_bit_to_float(bit,array_size);
        }
        output = output*0.01;
        if( output > 81 || output < -81 ){
            output = 0;
        }
        break;
    default:
        output = cal_bit_to_float(bit,array_size);
        break;
    }

    return output;
}

void split_bit(unsigned char* bit, int start,int end, unsigned char out_bit[]){

    int i = 0;
    int count = 0;
    for(i = start ; i <= end ; i++){
        out_bit[count] = bit[i];
        //printf("%d", out_bit[count]);
        count++;
    }
    //printf("\n");
}

TRACK analysis(unsigned char* bit, unsigned char out_bit[] , TRACK track){

    // LAT_RATE;//CAN_TX_TRACK_LAT_RATE
    split_bit(bit,0,5,out_bit);
    track.LAT_RATE = convert_bit_to_float(out_bit, 6,TX_LAT_RATE);
    //printf("track.LAT_RATE\t\t:\t%f\t" ,track.LAT_RATE);
    //print_bit(out_bit,6);

    // GROUPING;
    split_bit(bit,6,6,out_bit);
    track.GROUPING = convert_bit_to_float(out_bit, 1,TX_GROUPING);
    //printf("track.GROUPING\t\t:\t%f\t" ,track.GROUPING);
    //print_bit(out_bit,1);

    // ONCOMMING;
    split_bit(bit,7,7,out_bit);
    track.ONCOMMING = convert_bit_to_float(out_bit, 1,TX_ONCOMMING);
    //printf("track.ONCOMMING\t\t:\t%f\t" ,track.ONCOMMING);
    //print_bit(out_bit,1);

    // STATUS;
    split_bit(bit,8,10,out_bit);
    track.STATUS = convert_bit_to_float(out_bit, 3,TX_STATUS);
    //printf("track.STATUS\t\t:\t%f\t" ,track.STATUS);
    //print_bit(out_bit,3);

    // ANGLE;//0.1(소수점 첫채짜리 까지)
    split_bit(bit,11,20,out_bit);
    track.ANGLE = convert_bit_to_float(out_bit, 10,TX_ANGLE);
    //printf("track.ANGLE\t\t:\t%f\t" ,track.ANGLE);
    //print_bit(out_bit,10);

    // RANGE;//0.1(소수점 첫채짜리 까지)
    split_bit(bit,21,31,out_bit);
    track.RANGE = convert_bit_to_float(out_bit, 11,TX_RANGE);
    //printf("track.RANGE\t\t:\t%f\t" ,track.RANGE);
    //print_bit(out_bit,11);

    // BRIDGE;
    split_bit(bit,32,32,out_bit);
    track.BRIDGE = convert_bit_to_float(out_bit, 1,TX_BRIDGE);
    //printf("track.BRIDGE\t\t:\t%f\t" ,track.BRIDGE);
    //print_bit(out_bit,1);

    // ROLLING;
    split_bit(bit,33,33,out_bit);
    track.ROLLING = convert_bit_to_float(out_bit, 1,TX_ROLLING);
    //printf("track.ROLLING\t\t:\t%f\t" ,track.ROLLING);
    //print_bit(out_bit,1);

    // WIDTH;
    split_bit(bit,34,37,out_bit);
    track.WIDTH = convert_bit_to_float(out_bit, 4,TX_WIDTH);
    //printf("track.WIDTH\t\t:\t%f\t" ,track.WIDTH);
    //print_bit(out_bit,4);

    // RANGE_ACCEL;
    split_bit(bit,38,47,out_bit);
    track.RANGE_ACCEL = convert_bit_to_float(out_bit, 10,TX_RANGE_ACCEL);
    //printf("track.RANGE_ACCEL\t:\t%f\t" ,track.RANGE_ACCEL);
    //print_bit(out_bit,10);

    // MED_RANGE_MODE;
    split_bit(bit,48,49,out_bit);
    track.MED_RANGE_MODE = convert_bit_to_float(out_bit, 2,TX_MED_RANGE_MODE);
    //printf("track.MED_RANGE_MODE\t:\t%f\t" ,track.MED_RANGE_MODE);
    //print_bit(out_bit,2);

    // RANGE_RATE;
    split_bit(bit,50,63,out_bit);
    track.RANGE_RATE = convert_bit_to_float(out_bit, 14,TX_RANGE_RATE);
    //printf("track.RANGE_RATE\t:\t%f\t" ,track.RANGE_RATE);
    //print_bit(out_bit,14);

    return track;
}
