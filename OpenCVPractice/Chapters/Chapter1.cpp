//
//  Chapter1.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include "Chapter1.hpp"

Mat image;
string title;
string barName;


void onMouse(int event, int x,  int y, int flags, void * param) {
    if (event == EVENT_LBUTTONDOWN) {
        subtract(image, 10, image);
        setTrackbarPos(barName, title, image.at<uchar>(0));
        imshow(title,image);
    } else if (event == EVENT_RBUTTONDOWN){
        add(image, 10, image);
        setTrackbarPos(barName, title, image.at<uchar>(0));
        setTrackbarPos(barName, title, image.at<uchar>(0));
        imshow(title,image);
    }
}

void onChange(int x, void *) {
    double alpha = (double)(x - 127);
    Mat adjustedImage = Mat::zeros(image.size(), image.type());
    image.convertTo(adjustedImage, -1, 1.0, alpha);
    imshow(title, adjustedImage);
}

Mat getConvertImage(string imagePath) {
    
    Mat image = cv::imread(imagePath);
    
    if (!image.empty()) {
        resize(image, image, cv::Size(400, 400));
        double alpha = 1.0;
        Mat adjustedImage = cv::Mat::zeros(image.size(), image.type());
        image.convertTo(adjustedImage, -1, alpha, 0);
        return adjustedImage;
    } else {
        std::cout << "이미지를 불러오지 못했습니다." << std::endl;
        return Mat();
    }
}
