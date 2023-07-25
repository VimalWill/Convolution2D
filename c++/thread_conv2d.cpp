#include <omp.h>
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <chrono>

void letterBox(cv::Mat& input_img, cv::Mat& output_image, const int kernel_h, const int kernel_w){

    int top = std::ceil((kernel_h - 1)/2); 
    int bottom = std::floor((kernel_h - 1)/2); 
    int left = std::ceil((kernel_w - 1)/2); 
    int right = std::floor((kernel_w - 1)/2);

    cv::copyMakeBorder(input_img, output_image, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(0)); 
}

void ThreadedConv2D(cv::Mat& input_image, cv::Mat& output_img, std::vector<std::vector<float>>& kernel){

    const int kernel_h = kernel.size(); 
    const int kernel_w = kernel[0].size(); 
    const int num_channel = input_image.channels(); 
    //threads will be assigned based on the hardware architecture
    int num_threads = std::thread::hardware_concurrency();

    /*padding*/
    cv::Mat padded_img; 
    letterBox(input_image, padded_img, kernel_h, kernel_w); 

    /*parallelized convolution*/
    //https://stackoverflow.com/questions/13357065/how-does-openmp-handle-nested-loops
    #pragma omp parallel for collapse(2) num_threads(num_threads)
    for(int k=0; k<num_channel; k++){
        for(int i=0; i<padded_img.rows-kernel_h+1; i++){
            for(int j=0; j<padded_img.cols-kernel_w+1; j++){
                //printf("threadId = %d \n", omp_get_thread_num());
                float sum = 0.0;
                for(int m=0; m<kernel_h; m++){
                    for(int n=0; n<kernel_w; n++){
                        //printf("threadId = %d \n", omp_get_thread_num());
                        sum += padded_img.at<cv::Vec3b>(i+m, j+n)[k] * kernel[m][n];
                    }
                }
                output_img.at<cv::Vec3b>(i, j)[k] = sum;
            }
        }
    }

}

int main(int argc, char* argv[]){
    std::string path = argv[1]; 
    cv::Mat image = cv::imread(path); 

    //average blur kernel 
    std::vector<std::vector<float>> kernel
    {
        {1/9.0, 1/9.0, 1/9.0}, 
        {1/9.0, 1/9.0, 1/9.0}, 
        {1/9.0, 1/9.0, 1/9.0}
    }; 

    cv::Mat Output_img(image.rows, image.cols, image.type());

    auto start_time = std::chrono::high_resolution_clock::now();
    ThreadedConv2D(image, Output_img, kernel);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> latency = end_time - start_time; 

    // cv::imshow("Output Image", Output_img);
    // cv::waitKey(0);
    // cv::destroyAllWindows();

    /*write the output as .jpg image*/
    std::string output_path = "../Convolution/outputs/threadconv2d.png";
    cv::imwrite(output_path, Output_img);
    std::cout << "Convoluted image saved at" << output_path << std::endl;
    std::cout << "Total Run-Time:" << latency.count() << std::endl;

    return 0;
}
