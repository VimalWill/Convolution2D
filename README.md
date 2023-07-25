# Implementation of Convolution 2D Layer 

## Overview
In Image Processing, Convolution layers are the basic operator for performing various tasks such as Filtering, Edge Detection, Blurring and Feature Extraction. The process of Convolution 2D layer invloves applying kernel to the input image to obtain the "Convoluted Image". 

## General Steps of Convolution 2D
1. Place the kernel on the input image 
2. Multipe each pixel in the kernel to the corrsponding pixel in the input image 
3. Sum up the element-wise multipled results
4. Slide the kernel to the next pixel and repeat the process until the entire image is covered.
