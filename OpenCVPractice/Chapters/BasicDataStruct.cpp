//
//  BasicDataStruct.cpp
//  OpenCVPractice
//
//  Created by 박유경 on 2023/12/04.
//

#include "BasicDataStruct.hpp"

void study2D() {
    Point2f vec1(3.0, -4.0);
    Point2f vec2(-4.0, -3.0);
    
    float magnitude1 = norm(vec1);//sqart((dobule)pt.x*pt.x + (dobule)pt.y*pt.y)
    float magnitude2 = norm(vec2);
    
    float dotProduct = vec1.dot(vec2);
    float angle = std::acos(dotProduct / (magnitude1 * magnitude2));
    float angleInDegrees = angle * 180 / CV_PI;
    cout << "2차원 두 벡터의 내적: " << dotProduct <<" 각도:"<<angleInDegrees << endl; //3*2 + 4*5
    //3차원 두 벡터의 내적:0 각도:90 -> 직교
}

void study3D() {
    
    //오른손 좌표계
    Vec3f vec3(1.0, 1.0, 0.0);
    Vec3f vec4(0.0, 0.0, 1.0);
    
    float magnitude3 = norm(vec3);//sqrt((dobule)pt.x*pt.x + (dobule)pt.y*pt.y + (dobule)pt.z*pt.z)
    float magnitude4 = norm(vec4);
    
    float dotProduct3= vec3.dot(vec4);
    float angle3 = std::acos(dotProduct3 / (magnitude3 * magnitude4));
    float angleInDegrees3 = angle3 * 180 / CV_PI;

    
    cout << "3차원 두 벡터의 내적:" << dotProduct3 <<" 각도:"<<angleInDegrees3 << endl; //1*4 + 2*5 + 3*6
    //3차원 두 벡터의 내적:0 각도:90 -> 직교
}

void studyVector() {
    Vec2d v1(100,200);
    Vec2d v2(200,300);
    cout<<"v1  * 100 = " << v1 * 100<<endl;
    cout<<"v2  * -100 = " << v2 * (-100)<<endl;
    Scalar red(255,0,0); //alpha는 defaul가 0
    cout<<red<<endl;
}

void studyRotateRect() {
    Mat image(300,500, CV_8UC3, Scalar(127,126,127)); //row * col (Matrix와 Point 좌표는 반대로 계산됨), CV_8UC1은 단일채널(흰색 or 검정색)
    Point2f center(image.cols /2.0f, image.rows/2.0f), pts[4];
    //Point2f center(250,150), pts[4]; // x, y
    Size2f size(200,200);
    RotatedRect rotatedRect(center, size, 25);
    
    Rect boundRect = rotatedRect.boundingRect(); //회전된 사각형의 점 좌표
    rectangle(image,boundRect,Scalar(0),1);
    rotatedRect.points(pts); //곡지점 좌표 번환
    
    for( int i=0; i<sizeof(pts)/sizeof(pts[0]); i++) {
        line(image, pts[i], pts[ (i+ 1) % 4 ], Scalar(0), 3);
        circle(image, pts[i], 10, Scalar(0,0,255));
    }
    imshow("회전", image);
}

void studyMat() {
    Mat m1 = Mat::ones(3,5, CV_8UC1); // 모든 원소 1
    Mat m2 = Mat::zeros(3,5, CV_8UC1); // 모든 원소 0
    Mat m3 = Mat::eye(3,5, CV_8UC1); // 3*5 대각선 1
    
    Mat_<int> m4(2,4);
    m4 <<1,2,3,4,5,6,7,8; //n*m 넘어갈시 런타임에러.
    cout<<m1<<endl<<m2<<endl<<m3<<endl<<m4<<endl;
    
    Mat m5 = m1 + m3; // 대입연산자는 얕은복사이기때문에 m5가 바귈시 m1, m2도 같이 바뀜
    Mat m6 = m5;
    m6 = m6 * 100;
    cout<<m6 << endl << m5<<endl; //같음 -> Mat객체도 자동으로 소멸자에서 제거가 되도록 설계되었지만 Strong Reference를 가질 경우 소멸이 안되기 떄문에 주의.(.Release로 릴리즈로 낮출수있으나 권장 X)
    
    Mat m7 = m6.clone(); //깊은복사
    m7 = m7 + 10;
    
    cout<<"m7 ->"<< endl << m7 <<endl <<"m6 ->"<<m6<<endl; //다름
    
    
    m7.resize(1);
    cout<<"m7.resize(1)"<<endl<<m7<<endl;
    m7.resize(4); //복사되기전 행렬의 크기에서 resize할 경우 원본을 유지한체 리사이징(행크기)조절되지만 리사이징되는 크기가 원본행렬의 크기를 넘어설경우 복사되기 전 값만 유지하고 나머지는 0으로 초기화됨
    cout<<"m7.resize(3)"<<endl<< m7<<endl;
    
    cout<<"채널" <<m7.channels() <<endl <<"행 * 열" << m7.rows << "x" << m7.cols<<endl; // 1채널 4* 5
    
    Mat m8 = m7.reshape(2,5);
    cout<<"채널" <<m8.channels() <<endl <<"행 * 열" << m8.rows << "x" << m8.cols<<endl; // 2채널 5 * 2   reshape은 channel * rows * cols 의 값이 복사본의 엘리먼트수와 일치해야댐
    
}


