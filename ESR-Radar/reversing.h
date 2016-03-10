#ifndef REVERSING_H
#define REVERSING_H

#include <stdlib.h>
#include <canlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_TRACK_SIZE 64
#define MAX_BIT_SIZE 64
#define MAX_BUF_SIZE 8
#define MAX_HEX_SIZE 8

#define TX_LAT_RATE			6401
#define TX_GROUPING			6402
#define TX_ONCOMMING		6403
#define TX_STATUS			6404
#define TX_ANGLE			6405
#define TX_RANGE			6406
#define TX_BRIDGE			6407
#define TX_ROLLING			6408
#define TX_WIDTH			6409
#define TX_RANGE_ACCEL		6410
#define TX_MED_RANGE_MODE	6411
#define TX_RANGE_RATE		6412
#define _DEFAULT              -1

//track
typedef struct{
    long id;
    float LAT_RATE;
    float GROUPING;
    float ONCOMMING;
    float STATUS;
    float ANGLE;
    float RANGE;
    float BRIDGE;
    float ROLLING;
    float WIDTH;
    float RANGE_ACCEL;
    float MED_RANGE_MODE;
    float RANGE_RATE;
    unsigned char hex[MAX_HEX_SIZE];
}TRACK;
//

//function
void hex_to_bit(unsigned char, 	unsigned char *);
void convert_bit_to_complement(unsigned char*, int ,unsigned char*);
void convert_hexcode_to_bit(unsigned char*,unsigned char*);
float pow_of_2(float);
float cal_bit_to_float(unsigned char*,int);
float convert_bit_to_float(unsigned char*,int,int);
void split_bit(unsigned char*,int,int,unsigned char*);
TRACK analysis(unsigned char* bit, unsigned char out_bit[] , TRACK track);

#endif // REVERSING_H
