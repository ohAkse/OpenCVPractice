//
//  main.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define Chapter_1222

using namespace std;
using namespace cv;

std::string imagePath = "/Users/segassdc/Downloads/a.png";

int main(int argc, const char * argv[]) {
    
#ifdef CV_SETTING
    Mat image = cv::imread(imagePath);

    if (!image.empty()) {
        imshow("이미지 갱신", image);
        waitKey(0);
    } else {
        cout << "이미지 갱신 실패" << endl;
    }
#elifdef Chapter_1
    cout<<"Chapter1"<<endl;
#elifdef Chapter_2
    cout<<"Chapter2"<<endl;
#elifdef Chapter_3
    cout<<"Chapter3"<<endl;
#elifdef Chapter_4
    cout<<"Chapter4"<<endl;
#elifdef Chapter_5
    cout<<"Chapter5"<<endl;
#elifdef Chapter_6
    cout<<"Chapter6"<<endl;
#elifdef Chapter_7
    cout<<"Chapter7"<<endl;
#elifdef Chapter_8
    cout<<"Chapter8"<<endl;
#elifdef Chapter_9
    cout<<"Chapter9"<<endl;
#elifdef Chapter_10
    cout<<"Chapter10"<<endl;
#elifdef Chapter_11
    cout<<"Chapter11"<<endl;
#else
    cout<<"Macro is in the wrong format or not set"<<endl;
#endif

    waitKey(0);

    return 0;
}
