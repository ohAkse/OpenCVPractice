//
//  Chapter1.hpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>
using namespace std;
using namespace cv;

void onMouse(int event, int x,  int y, int flaogs, void * param);
void onChange(int x, void *);
Mat getConvertImage(string imagePath);
void studyMatFncs();
void estimateLoopResult();
void studyBandingEffect();
void studyBrightnessScroll();
void studyMatMeanBrightness();

// Mats
//CV_8U - 8-bit unsigned char (0~255)
//CV_8S - 8-bit signed char (-128~127)
//CV_16U - 16-bit unsigned short (0~65535)
//CV_16S - 16-bit signed short (-32768~32767)
//CV_32S - 32-bit signed integers (-2147483648~2147483647)
//CV_32F - 32-bit floating-point numbers
//CV_64F - 64-bit double-precision floating-point numbers

// Vectors
//Vec2b - 2-element vector of 8-bit unsigned integers
//Vec3b - 3-element vector of 8-bit unsigned integers
//Vec4b - 4-element vector of 8-bit unsigned integers
//Vec2s - 2-element vector of 16-bit signed short
//Vec3s - 3-element vector of 16-bit signed short
//Vec4s - 4-element vector of 16-bit signed short
//Vec2i - 2-element vector of 32-bit signed integers
//Vec3i - 3-element vector of 32-bit signed integers
//Vec4i - 4-element vector of 32-bit signed integers
//Vec2f - 2-element vector of 32-bit floating-point numbers
//Vec3f - 3-element vector of 32-bit floating-point numbers
//Vec4f - 4-element vector of 32-bit floating-point numbers
//Vec2d - 2-element vector of 64-bit floating-point numbers
//Vec3d - 3-element vector of 64-bit floating-point numbers
//Vec4d - 4-element vector of 64-bit floating-point numbers
