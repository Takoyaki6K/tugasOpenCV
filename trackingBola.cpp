#include <bits/stdc++.h>
#include <opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

int main(int argc, char** argv){
    VideoCapture vid("bolabola.mp4");

    Mat gambar, gambar_kecil, gambar_hsv, aturThreshold;

    int min_H = 0;
    int max_H = 179;
    int min_S = 0;
    int max_S = 255;
    int min_V = 0;
    int max_V = 255;

    namedWindow("threshold", WINDOW_AUTOSIZE);

    createTrackbar("min_H", "threshold", &min_H, 179);
    createTrackbar("max_H", "threshold", &max_H, 179);
    createTrackbar("min_S", "threshold", &min_S, 255);
    createTrackbar("max_S", "threshold", &max_S, 255);
    createTrackbar("min_V", "threshold", &min_V, 255);
    createTrackbar("max_V", "threshold", &max_V, 255);

    while (true) {
        vid.read(gambar);

        resize(gambar, gambar_kecil, Size(), 0.5, 0.5);
        cvtColor(gambar_kecil, gambar_hsv, COLOR_BGR2HSV);

        inRange(gambar_hsv, Scalar(min_H,min_S,min_V), Scalar(max_H,max_S,max_V), aturThreshold);

        vector<vector<Point>>counturs;
        findContours(aturThreshold, counturs, RETR_TREE, CHAIN_APPROX_NONE);

        for (int i = 0; i < counturs.size(); i++)
        {
            vector<Point>counturs_new;
            Point2f center;
            float radius;
            counturs_new = counturs[i];
            minEnclosingCircle(counturs_new, center, radius);
            if (radius> 20 && radius < 78){
                circle(gambar_kecil , center, radius, Scalar(255, 0, 0), 3 );
                printf("x: %2f y: %2f radius: %2f\n", center.x, center.y, radius);
            }
        }
        
        imshow("video", gambar_kecil);
        imshow("ngatur threshold", aturThreshold);

        if ((char)27 == (char) waitKey(300)) 
        break; 


    }
    return 0;

}