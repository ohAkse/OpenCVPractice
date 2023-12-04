//
//  main.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include <iostream>
#include "Chapters/Chapter1.hpp"
#define BasicDataStruct

#ifdef BasicDataStruct
#include "Chapters/BasicDataStruct.hpp"
#endif

#ifdef Chapter_1
#include "Chapters/Chapter1.hpp"
#endif


using namespace std;
using namespace cv;

//공통으로 쓰일 전역변수
extern string title;
extern string barName;
extern Mat image;

//Main에서 경로 혹은 하드코딩으로 넘겨줄값.
string imagePath = "/Users/segassdc/Downloads/a.png";
int TrackBarPosvalue = 127;

int main(int argc, const char * argv[]) {
    title = "Practice";
    barName = "brightness";
    
#ifdef CV_SETTING
    image = cv::imread(imagePath);
    if (!image.empty()) {
        imshow("이미지 갱신", image);
    } else {
        cout << "이미지 갱신 실패" << endl;
    }
    
#elifdef BasicDataStruct
    study2D();
    study3D();
    studyVector();
    studyRotateRect();
    studyMat();
#elifdef Chapter_1
    //image = Mat(300,500,CV_16UC1, Scalar(25555));
    image = getConvertImage(imagePath);
    namedWindow(title,WINDOW_AUTOSIZE);
    createTrackbar(barName,title,&TrackBarPosvalue, 255, onChange);
    setMouseCallback(title, onMouse,0);
    imshow(title,image);
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
