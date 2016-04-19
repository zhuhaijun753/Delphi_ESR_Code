#ifndef MATRIX_H
#define MATRIX_H

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

class Matrix
{
private:
    Mat input;
    Mat output;

public:

    Mat create_matrix(int col, int row);
    Mat create_matrix(int col, int row , float *m);

    Mat transpose_matrix(Mat input);
    Mat invert_matrix(Mat input);
    Mat gemm_matrix(Mat input1,Mat input2);
    Mat convert_T(Mat input1, Mat input2 , Mat input3);
    float error(float a,float b, float c , Mat data);
    void print_matrix(Mat input);
    Matrix();
};

#endif // MATRIX_H
