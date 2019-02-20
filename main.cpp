#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {

    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);

    // calc the difference
    Mat diff;
    absdiff(img1, img2, diff);

    // Get the mask if difference greater than th
    int th = 100;  // 0
    Mat mask(img1.size(), CV_8UC1);
    for(int j=0; j<diff.rows; ++j) {
        for(int i=0; i<diff.cols; ++i){
            cv::Vec3b pix = diff.at<cv::Vec3b>(j,i);
            int val = (pix[0] + pix[1] + pix[2]);
            if(val>th){
                mask.at<unsigned char>(j,i) = 255;
            }
        }
    }

    // get the foreground
    Mat image;
    bitwise_and(img1, img2, image, mask);

    // display
    //resize(image, image, Size(image.cols/4, image.rows/4)); // to half size or even smaller
    //namedWindow( "Display frame", WINDOW_AUTOSIZE);
    //imshow("res", image);
    imwrite("resultat_diff.png", image);
    waitKey();
    return 0;
}

