#include <opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
 
 
void getContours(Mat imgDil, Mat img) {
 
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
 
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area << endl;
		string objectType;
 
              	float peri = arcLength(contours[i], true);
			 approxPolyDP(contours[i], conPoly[i], 0.0002 * peri, true);
			//cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
                    
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(),boundRect[i].br(), Scalar(0, 255, 0), 2);
	
	}
             cout<<(float)boundRect[3].height<<endl;
}



int main()
{ 

Mat imgHSV,mask;
int hmin=0,smin=185,vmin=21;
int hmax=29,smax=255,vmax=93;
 string path="Resources/sample2.jpeg";
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
