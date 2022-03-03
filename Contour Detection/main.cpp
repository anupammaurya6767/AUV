#include <opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
 
void getContours(Mat mask,Mat img)
{

  vector<vector<Point>>contours; 
  vector<Vec4i>hierarchy;
  

  findContours(mask,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
  drawContours(img,contours,-1,Scalar(255,0,255),2);
}




int main()
{
Mat imgHSV,mask;
int hmin=78,smin=176,vmin=125;
int hmax=82,smax=217,vmax=138;

 string path="Resources/sample.jpeg";
 Mat img = imread(path);
cvtColor(img,imgHSV,COLOR_BGR2HSV);
 Mat imgGray;
Scalar lower(hmin,smin,vmin);
Scalar upper(hmax,smax,vmax);
 inRange(imgHSV,lower,upper,mask);
Mat imgBlur,imgCanny,imgDil;
  cvtColor(img,imgGray,COLOR_BGR2GRAY);
  GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
  Canny(imgBlur,imgCanny,25,75);

Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
dilate(imgCanny,imgDil,kernel);

getContours(mask,img);

imshow("Image",img);
/*
imshow("Image Gray",imgGray);
imshow("Image Blur",imgBlur);
imshow("Image Canny",imgCanny);
imshow("Image Dilation",imgDil);
*/
waitKey(0);
   
   
   

   return 0;
}
