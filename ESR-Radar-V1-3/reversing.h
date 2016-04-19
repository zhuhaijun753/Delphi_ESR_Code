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
#define TX_AMP              6413
#define _DEFAULT              -1

#define PIE 3.141592
//track
typedef struct{
    long id;//Hex Code id
    float LAT_RATE;//Lateral rate
    float GROUPING;//그룹 상태(0,1)
    float ONCOMMING;//다가오는 상태인지 아닌지 확인(0,1)
    float STATUS;//현제 샌서 상태(7)
    float ANGLE;//Heading Bearing realtion
    float RANGE;//거리
    float BRIDGE;//브릿지
    float ROLLING;//롤링
    float WIDTH;//가로
    float RANGE_ACCEL;//가속도
    float MED_RANGE_MODE;//융합 트랙 모드(mid-range , long-range) 구
    float RANGE_RATE;//속도
    float AMP;//파워 : dB
    unsigned char hex[MAX_HEX_SIZE];//원시 Hex Code
    float X;//x좌표
    float Y;//y좌표
}TRACK;
//

//function
void hex_to_bit(unsigned char hexcode, unsigned char* bit);//hex code bit로 변환(싱글)
void convert_bit_to_complement(unsigned char* bit, int array_size ,unsigned char *out_bit);//음수 표기를 위한 보수화
void convert_hexcode_to_bit(unsigned char* hexcode, unsigned char* bit);//hex code bit 변환(다수)
float pow_of_2(float num);//제곱 승 : x^2 = pow(x,2)
float cal_bit_to_float(unsigned char* bit , int array_size);//2진수로 표기된 bit를 실수형으로 변환 계산
float convert_bit_to_float(unsigned char* bit , int array_size , int flag);//2진수로 표기된 bit를 실수형으로 변환(측정 볌위 설정)
void split_bit(unsigned char* bit, int start,int end, unsigned char* out_bit);//비트 분할
TRACK analysis(unsigned char* bit, unsigned char out_bit[] , TRACK track);//Track 분석

#endif // REVERSING_H
