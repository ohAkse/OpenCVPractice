//////
//////  Chapter2.cpp
//////  OpenCVPractice
//////
//////  Created by 박유경 on 2023/12/05.
//////
//
#include "Chapter2.hpp"

Mat image;
string title;
string barName;

void studyBlur() {

    Mat origin = imread("/Users/segassdc/Downloads/background.png", IMREAD_COLOR);
    Mat dest = Mat(origin.size(), CV_32FC3, Scalar(0, 0, 0)); 
    float data[] = {
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f,
        1/9.f, 1/9.f, 1/9.f
    };
    Mat mask = Mat(3, 3, CV_32F, data);

    cout<<mask.size()<<endl;
    Point center = mask.size() / 2;
    

    for (int i = center.y; i < origin.rows - center.y; i++) {
        for (int j = center.x; j < origin.cols - center.x; j++) {
            Vec3f sum(0, 0, 0);
            for (int u = 0; u < mask.rows; u++) {
                for (int v = 0; v < mask.cols; v++) {
                    int y = i + u - center.y;
                    int x = j + v - center.x;
                    Vec3b pixel = origin.at<Vec3b>(y, x);
                    sum += mask.at<float>(u, v) * Vec3f(pixel[0], pixel[1], pixel[2]);
                }
            }
            dest.at<Vec3f>(i, j) = sum;
        }
    }
    dest.convertTo(dest,CV_8U);

    imshow("origin", origin);
    imshow(title, dest);
 }

void studyShapening() {

    Mat origin = imread("/Users/segassdc/Downloads/background.png", IMREAD_COLOR);
    cout<<origin<<endl;
    Mat dest = Mat(origin.size(), CV_32FC3, Scalar(0, 0, 0));
//    float data[] = {
//        3,-2, 1,
//        0, 5, -4,
//        -1,0,-1
//    };
    float data[] = {
        -1, -1, -1,
        -1, 9 , -1,
        -1, -1, -1
    };
    Mat mask = Mat(3, 3, CV_32F, data);

    Point center = mask.size() / 2;

    for (int i = center.y; i < origin.rows - center.y; i++) {
        for (int j = center.x; j < origin.cols - center.x; j++) {
            Vec3f sum(0, 0, 0);
            for (int u = 0; u < mask.rows; u++) {
                for (int v = 0; v < mask.cols; v++) {
                    int y = i + u - center.y;
                    int x = j + v - center.x;
                    Vec3b pixel = origin.at<Vec3b>(y, x);
                    sum += mask.at<float>(u, v) * Vec3f(pixel[0], pixel[1], pixel[2]);
                }
            }
            dest.at<Vec3f>(i, j) = sum;
        }
    }
    dest.convertTo(dest,CV_8U);

    imshow("origin", origin);
    imshow("dest", dest);
 }

void onMouseMove(int event, int x,  int y, int flags, void * param) {
    
    int radius = 50;
    if (event == EVENT_LBUTTONDOWN) {
    
        // *************************다른솔루션**************************************
        //        Rect roi_rect = Rect(max(0, x - radius), max(0, y - radius), min(2 * radius, image.cols - x + radius), min(2 * radius, image.rows - y + radius));
        //        Mat roi = image(roi_rect); // 클릭한 위치 주변의 ROI
        //        Mat result;
        //        filter2D(roi, result, -1, mask, Point(-1, -1), 0, BORDER_DEFAULT);
        //        result.copyTo(roi); // 블러 처리된 결과를 원본 ROI에 복사
        //        imshow(title, image);
        // **********************************************************************
         //filterByBlur(x,y,radius);
         //filterByEdge(x,y,radius);;
         //filterByEdgeWithDiff(x,y,radius);
        filterByDifferential(x,y,radius);

    } else if (event == EVENT_RBUTTONDOWN){
        //원보
        image = imread( "/Users/segassdc/Downloads/background.png");
        resize(image, image, Size(500,500));
        imshow(title, image);
    } else if (event == EVENT_MOUSEMOVE) {
        Mat circleDraw = image.clone();
        circle(circleDraw, Point(x, y), radius, Scalar(0, 0, 255), 1);
        imshow(title, circleDraw);
    }
}

void filterByBlur(int x, int y, int radius)
{
    Mat mask = Mat::ones(3, 3, CV_32F) / 9.0; // 3x3 블러링 마스크
    Rect roi_rect = Rect(max(0, x - radius), max(0, y - radius), min(2 * radius, image.cols - x + radius), min(2 * radius, image.rows - y + radius));
    Mat roi = image(roi_rect).clone(); // roi의 좌표는 다시 roi_rect만큼 0,0부터 시작
    
    for (int y = 1; y < roi.rows - 1; ++y) {
        for (int x = 1; x < roi.cols - 1; ++x) {
            Vec3f sum(0, 0, 0);
            for (int u = -1; u <= 1; ++u) {
                for (int v = -1; v <= 1; ++v) {
                    int yy = y + u;
                    int xx = x + v;
                    Vec3b pixel = roi.at<Vec3b>(yy, xx);
                    sum += mask.at<float>(u + 1, v + 1) * Vec3f(pixel[0], pixel[1], pixel[2]);
                }
            }
            roi.at<Vec3b>(y, x) = Vec3b(sum[0], sum[1], sum[2]);
        }
    }
    roi.copyTo(image(roi_rect));
    imshow(title, image);
}


//유사연산자 에지 max(C-1, C-2,C-3 ...C-N)
// 1 2 3
// 4 C 5
// 6 7 8
void filterByEdge(int x, int y, int radius) {
    
    Rect roi_rect = Rect(max(0, x - radius), max(0, y - radius), min(2 * radius, image.cols - x + radius), min(2 * radius, image.rows - y + radius));
    Mat roi = image(roi_rect).clone();
    Mat grayRoi;
    cvtColor(roi, grayRoi, COLOR_BGR2GRAY);
    // 유사연산 엣지 검출
    for (int y = 1; y < grayRoi.rows - 1; ++y) {
        for (int x = 1; x < grayRoi.cols - 1; ++x) {
            int maxDiff = 0;
            for (int u = -1; u <= 1; ++u) {
                for (int v = -1; v <= 1; ++v) {
                    int diff = abs(grayRoi.at<uchar>(y, x) - grayRoi.at<uchar>(y + u, x + v));
                    if (diff > maxDiff) {
                        maxDiff = diff;
                    }
                }
            }
            roi.at<Vec3b>(y, x) = Vec3b(maxDiff, maxDiff, maxDiff);
        }
    }
    roi.copyTo(image(roi_rect));
    imshow(title, image);
}


void filterByEdgeWithDiff(int x, int y, int radius) {
    Rect roi_rect = Rect(max(0, x - radius), max(0, y - radius), min(2 * radius, image.cols - x + radius), min(2 * radius, image.rows - y + radius));
    Mat roi = image(roi_rect).clone();
    
    Mat grayRoi;
    cvtColor(roi, grayRoi, COLOR_BGR2GRAY);
    // 차연산 엣지 검출
    for (int j = 1; j < grayRoi.rows - 1; ++j) {
        for (int i = 1; i < grayRoi.cols - 1; ++i) {
            vector<uchar> mask;
            for (int u = -1; u <= 1; ++u) {
                for (int v = -1; v <= 1; ++v) {
                    int yy = j + u;
                    int xx = i + v;
                    mask.emplace_back(grayRoi.at<uchar>(yy, xx));
                }
            }
            uchar max = 0;
            for(int idx = 0; idx < mask.size() / 2; idx++) {
                int start = mask.at(idx);
                int end = mask.at(mask.size() - 1 - idx);
                uchar diff = abs(start - end);
                if (diff > max) max = diff;
            }
            roi.at<Vec3b>(j, i) = Vec3b(max, max, max);
        }
    }
    
    roi.copyTo(image(roi_rect));
    imshow(title, image);
}

void filterByDifferential(int x, int y, int radius) {
    float verticalMask[] = {
        -1, 0 , 1,
        -1, 0 , 1,
        -1, 0 , 1
    };
    
    
    float horizontalMask[] = {
        -1, -1 , -1,
         0, 0 , 0,
         1, 1 , 1
    };
    
    Mat verticalMat,verticalMaskMat(3,3,CV_32F, verticalMask);
    Mat horizontalMat,horizontalMaskMat(3,3,CV_32F, horizontalMask);
    Mat diffrenceMat;
    filter2D(image, verticalMat, CV_32F, verticalMaskMat); //수직으로 콘볼루션
    filter2D(image, horizontalMat, CV_32F, horizontalMaskMat); //수평으로 콘볼루션
    magnitude(verticalMat, horizontalMat, diffrenceMat); //수평+수직 콘볼루션한 행렬값을 differenceMat으로 출력
    
    diffrenceMat.convertTo(diffrenceMat,CV_8U);
    verticalMat.convertTo(verticalMat,CV_8U);
    horizontalMat.convertTo(horizontalMat,CV_8U);
    
    imshow("미분하여 얻은결과",diffrenceMat);
    //imshow("수직filter2D 얻은결과",verticalMat);
    //imshow("수평filter2D 얻은결과",horizontalMat);
}

