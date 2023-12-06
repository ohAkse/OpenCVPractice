////
////  Chapter2.hpp
////  OpenCVPractice
////
////  Created by 박유경 on 2023/12/05.
////
//

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void studyBlur();
void studyShapening();
void onMouseMove(int event, int x,  int y, int flags, void * param);
void filterByBlur(int x, int y,  int size);
void filterByEdge(int x, int y, int radius);
void filterByEdgeWithDiff(int x, int y, int radius);
void filterByDifferential(int x, int y, int radius) ;

