//
//  Chapter1.hpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;


void onMouse(int event, int x,  int y, int flaogs, void * param);
void onChange(int x, void *);
Mat getConvertImage(string imagePath);
