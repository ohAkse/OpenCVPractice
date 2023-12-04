//
//  main.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, const char * argv[]) {
    std::string imagePath = "/Users/segassdc/Downloads/a.png";

    // 이미지 읽기
    cv::Mat image = cv::imread(imagePath);

    // 이미지 읽기에 성공한 경우
    if (!image.empty()) {
        cv::imshow("Loaded Image", image);
        cv::waitKey(0);
    } else {
        std::cout << "Failed to load the image!" << std::endl;
    }

    waitKey(0); // 키 입력을 대기합니다.

    return 0;
}
