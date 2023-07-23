#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

void letterBox(cv::Mat& input_img, cv::Mat& output_img, int kernel_h, int kernel_w){
    /*function to pad the image*/

    int top = std::ceil((kernel_h - 1)/2); 
    int bottom = std::floor((kernel_h - 1)/2); 
    int left = std::ceil((kernel_w - 1)/2); 
    int right = std::floor((kernel_w - 1)/2); 

    cv::copyMakeBorder(input_img, output_img, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(0)); 
}

void Conv2D(cv::Mat& input_img, cv::Mat& output_img, std::vector<std::vector<float>>& kernel){
    
    int kernel_h = kernel.size(); 
    int kernel_w = kernel[0].size();
    int num_channel = input_img.channels();

    //padding 
    cv::Mat padded_img; 
    letterBox(input_img, padded_img, kernel_h, kernel_w); 

    //convolution
    for(int k=0; k<num_channel; k++){
        for(int i=0; i<padded_img.rows-kernel_h+1; i++){
            for(int j=0; j<padded_img.cols-kernel_w+1; j++){
                float sum = 0.0;
                for(int m=0; m<kernel_h; m++){
                    for(int n=0; n<kernel_w; n++){
                        sum += padded_img.at<cv::Vec3b>(i+m, j+n)[k] * kernel[m][n];
                    }
                }
                output_img.at<cv::Vec3b>(i, j)[k] = sum;
            }
        }
    }
}

int main(){
    std::string path = "../images/test.jpeg"; 
    cv::Mat image = cv::imread(path); 

    //average blur kernel 
    std::vector<std::vector<float>> kernel
    {
        {1/9.0, 1/9.0, 1/9.0}, 
        {1/9.0, 1/9.0, 1/9.0}, 
        {1/9.0, 1/9.0, 1/9.0}
    }; 

    cv::Mat Output_img(image.rows, image.cols, image.type());
    Conv2D(image, Output_img, kernel);

    cv::imshow("Output Image", Output_img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
