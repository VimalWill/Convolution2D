#automation script for underlying 3 convolution 2D executables
import os 
import time 
import sys
import cv2
import subprocess


def automated_execution(command):
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode == 0:
        print("Executed Successfully")
        print("Ouput:")
        print(result.stdout)

    else:
        print("Execution Failed")
        print("Error Message:")
        print(result.stderr)

#get input image parameters 
path = sys.argv[1]
image = cv2.imread(path)
BASE_DIR = str(os.getcwd())

img_height, img_width, channel = image.shape
pixel_depth = image.dtype

print("---Convolution 2D Unit---\n")
print("---INPUT IMAGE PARAMS---")
print("\n")
print("INPUT IMAGE HEIGHT :", img_height)
print("INPUT IMAGE WIDTH  :", img_width)
print("INPUT IMAGE CHANNEL:", channel)
print("INPUT IMAGE DEPTH  :", pixel_depth)
print("\n")


#executing convolution layers 
print("performing convolution...\n")
print("Threaded Convolution 2D(C++):")
exe1 = BASE_DIR + "/c++/build/thread_conv2d"
command = [exe1, path]
automated_execution(command)
print("\n")


print("Convolution 2D(C++):")
exe2 = BASE_DIR + "/c++/build/conv2d"
command = [exe2, path]
automated_execution(command)
print("\n")


print("Convolution 2D(Python):")
exe3 = BASE_DIR + "/python/conv2d.py"
command = ["python3", exe3, path]
automated_execution(command)




