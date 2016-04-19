#include "matrix.h"

Matrix::Matrix()
{

}

Mat Matrix::create_matrix(int col, int row){
    Mat output = Mat::zeros(row,col,CV_32F);
    return output;
}

Mat Matrix::create_matrix(int col, int row , float *m){
    Mat output = Mat(row,col,CV_32F,m);
    return output;
}

Mat Matrix::transpose_matrix(Mat input){
    Mat output;
    transpose(input,output);
    return output;
}

Mat Matrix::invert_matrix(Mat input){
    Mat output;
    invert(input,output);
    return output;
}

Mat Matrix::gemm_matrix(Mat input1,Mat input2){
    Mat output;
    gemm(input1,input2,1,0,0,output,0);
    //multiply(input1,input2,output);
    return output;
}

Mat Matrix::convert_T(Mat input1, Mat input2, Mat input3){

    Mat output;
    output = Mat::zeros(3,3,CV_32F);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3 ; j++){
            if(i == 0){
                output.at<float>(i,j) = input1.at<float>(j);
                //output_data[0][j] = input1.at<float>(j);
                //printf("%f ",output_data[0][j]);
            }
            if(i == 1){
                output.at<float>(i,j) = input2.at<float>(j);
                //output_data[1][j] = input2.at<float>(j);
                //printf("%f ",output_data[1][j]);
            }
            if(i == 2){
                output.at<float>(i,j)= input3.at<float>(j);
                //output_data[2][j] = input3.at<float>(j);
                //printf("%f ",output_data[2][j]);
            }
        }
        //printf("\n");
    }

    return output;
}

float Matrix::error(float a, float b, float c, Mat data){

    float error = 0;
    float e;
    for(int i = 0; i <data.cols ; i++){
        e = (
                data.at<float>(3,i) -
                a*data.at<float>(1,i) -
                b*data.at<float>(2,i) -
                c
            );
        e = e*e;
        error += e;
    }

    return error;
}

void Matrix::print_matrix(Mat input){
    for(int i = 0; i< input.rows ; i++){
        for(int j = 0; j < input.cols ; j++){
            printf("%f " , input.at<float>(i,j));
        }
        printf("\n");
    }
    printf("\n");
}
