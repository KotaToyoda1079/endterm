#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

struct image {
	string fileName;
	string outputName;
	Mat Image;

	vector<Rect> faceRecognize;
	vector<Rect> eyesrecognize;

};

string createPath(string currentDirectory, string betweenPath, string filename);

void loadCascade(CascadeClassifier &Cascade, string path);

void predict_face(image inputImg,CascadeClassifier faceCascade,vector<Rect> &result);
void predict_eyes(image inputImg,CascadeClassifier eyeCascade,vector<Rect> &result);

void putRecognizerResult_face(image inputImg,vector<Rect> &result);
void putRecognizerResult_eyes(image inputImg,vector<Rect> &result);

void warpImage(image *inputImg, Point2f src[4], Point2f dst[4],Point size,float magnify);
void showImg(image& inputImg, float magnify);
void outputImg(image *img,float magnify);
