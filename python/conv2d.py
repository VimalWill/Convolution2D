import cv2 
import math
import numpy as np 
import sys
import time

def nanoseconds_to_seconds(nanoseconds):
    seconds = nanoseconds / 1_000_000_000
    return seconds

def Conv2D(img, kernel):
    cvt_img = img
    #padding 
    kernel_h, kernel_w = kernel.shape
    top    = math.ceil((kernel_h - 1) / 2)
    bottom = math.floor((kernel_h - 1) / 2)
    left   = math.ceil((kernel_w - 1) / 2)
    right  = math.floor((kernel_w - 1) / 2)

    padded_img = cv2.copyMakeBorder(cvt_img, top, bottom, left, right, cv2.BORDER_CONSTANT, value=0)
    output_img = np.zeros_like(cvt_img)
    kernel = np.flipud(np.fliplr(kernel))

    #convolution
    for i in range(cvt_img.shape[0]):
        for j in range(cvt_img.shape[1]):
            for k in range(cvt_img.shape[2]):
                output_img[i, j, k] = np.sum(padded_img[i:i + kernel_h, j:j + kernel_w, k] * kernel)
    
    return output_img


def main():
    path = sys.argv[1]
    image = cv2.imread(path)

    kernel = np.array([
        [1/9, 1/9, 1/9], 
        [1/9, 1/9, 1/9], 
        [1/9, 1/9, 1/9]
    ])

    n1 = time.time_ns()
    conv_img = Conv2D(image, kernel)
    n2 = time.time_ns()
    n = n2 - n1
    sec = nanoseconds_to_seconds(n)
    # cv2.imshow("frame", conv_img)
    # cv2.waitKey(-1)
    # cv2.destroyAllWindows()
    output_path = "../Convolution/outputs/python_conv2d.png"
    cv2.imwrite(output_path, conv_img)
    print("Convoluted Image at", output_path)
    print("Total Run-Time:", sec)
    

if __name__ == "__main__":
    main()

    

