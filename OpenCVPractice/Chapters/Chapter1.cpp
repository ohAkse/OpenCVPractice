//
//  Chapter1.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include "Chapter1.hpp"
extern Mat image;
extern string title;
extern string barName;


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

void studyMatFncs() {
    Mat m1(3, 5, CV_32SC1); //32bit signed int with 1 channel
    Mat m2(3, 5, CV_32FC1); //32bit floating points with 1 channel
    Mat m3(3, 5, CV_8UC2); //8bit unsigned char with 2 channel
    Mat m4(3, 5, CV_32SC3); //32bit signed int with 3 channel
    
    for (int i = 0,  j = 0;  i<m1.rows; i++) {
        for(int k = 0; k<m1.cols; k++, j++){
            m1.at<int>(i, k) = j;
            Point pt(k,i);
            m2.at<float>(pt) = (float)k;
            m3.at<Vec2b>(i,k) = Vec2b(0,2);
            m4.at<Vec3i>(i,j) = Vec3s(0,1,2);
            
        }
    }
    cout<<"m1" << endl << m1<<endl;
    cout<<"m2" << endl << m2<<endl;
    cout<<"m3" << endl << m3<<endl;
    cout<<"m4" << endl << m4<<endl;
}

void estimateLoopResult() {
    const int rows = 200;
    const int cols = 200;

    Mat m1(rows, cols, CV_32FC3);
    Mat m2(rows, cols, CV_32FC3);
    Mat m3(rows, cols, CV_32FC3);

    // mat iterator
    auto start1 = chrono::high_resolution_clock::now();
    for (MatIterator_<Vec3f> it = m1.begin<Vec3f>(); it != m1.end<Vec3f>(); ++it) {
        (*it)[0] *= 0.3f;
        (*it)[1] *= 0.5f;
        (*it)[2] *= 0.6f;
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;
    cout << "Elapsed time for iterator: " << duration1.count() << " seconds" << endl;

    // for문 at
    auto start2 = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < m2.rows; i++) {
        for (int j = 0; j < m2.cols; j++) {
            m2.at<Vec3f>(i, j) = Vec3f(0.3f, 0.5f, 0.6f);
        }
    }
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration2 = end2 - start2;
    cout << "Elapsed time for at function: " << duration2.count() << " seconds" << endl;
    
    auto start3 = chrono::high_resolution_clock::now();

    m3.forEach<Vec3f>([](Vec3f &pixel, const int  position[]) -> void {
        pixel = Vec3f(0.3f, 0.5f, 0.6f);
    });

    auto end3 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration3 = end3 - start3;
    cout << "Elapsed time for forEach function: " << duration3.count() << " seconds" << endl;
}

void studyBandingEffect() {
    
    Mat image(50,512, CV_8UC1, Scalar(0));
    Mat changedImage(50,512, CV_8UC1, Scalar(0));
    
    for(int i=0; i<image.rows; i++) {
        for(int j=0; j<image.cols; j++) {
            image.at<uchar>(i,j) = j;
            changedImage.at<uchar>(i,j) = (j/10)*20;
        }
    }
    imshow("origin",image);
    imshow("changed",changedImage);
}

void studyBrightnessScroll() {
    int TrackBarPosvalue = 127;
    namedWindow(title,WINDOW_AUTOSIZE);
    createTrackbar(barName,title,&TrackBarPosvalue, 255, onChange);
    setMouseCallback(title, onMouse,0);
    imshow(title,image);
}

void  studyMatMeanBrightness() {
    Mat darkImage = image.clone() * 0.5;
    Mat meanDarkImage = image.clone() * 0.5 + (mean(image) / 2.0)[0];
    Mat brightImage = image.clone() * 2.0;
    Mat brightMeanImage = image.clone() * 2.0 - (mean(image) / 2.0)[0];
    imshow("image", image);
    imshow("darkImage", darkImage);
    imshow("brightImage", brightImage);
    imshow("meanDarkImage", meanDarkImage); // 평균 대비 감소
    imshow("brightMeanImage", brightMeanImage); //평균 이용 증가
    
}
