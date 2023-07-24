#include "image.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

string createPath(string currentDirectory, string betweenPath, string filename) {
	string path = currentDirectory + betweenPath + filename;

	return path;
}

void loadCascade(CascadeClassifier &Cascade, string path) {
	Cascade.load(path);
}

void warpImage(image *inputImg, Point2f src[4], Point2f dst[4],Point size,float magnify=1) {
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(inputImg->Image, inputImg->Image, matrix, size);
	resize(inputImg->Image, inputImg->Image, Size(), magnify,magnify);
}

void putRecognizerResult_face(image inputImg,vector<Rect> &result) {
	for (int i = 0; i < result.size(); i++) {
		rectangle(inputImg.Image, result[i].tl(), result[i].br(), Scalar(255, 0, 255), 3);
		putText(inputImg.Image, "face", { result[i].x,result[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1);
	}
}

void putRecognizerResult_eyes(image inputImg,vector<Rect> &result) {
	for (int i = 0; i < result.size(); i++) {
		rectangle(inputImg.Image, result[i].tl(), result[i].br(), Scalar(255, 0, 255), 3);

		putText(inputImg.Image, "eyes", { result[i].x,result[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1);
	}
}

void predict_face(image inputImg,CascadeClassifier faceCascade,vector<Rect> &result) {
	faceCascade.detectMultiScale(inputImg.Image,result,1.1,10);
}

void predict_eyes(image inputImg, CascadeClassifier eyeCascade,vector<Rect> &result) {
	eyeCascade.detectMultiScale(inputImg.Image, result, 1.1, 10);
}

void outputImg(image *inputImg, float magnify = 1) {
	resize(inputImg->Image,inputImg->Image,Size(),magnify,magnify);
	imwrite(inputImg->outputName, inputImg->Image);
}

void showImg(image& inputImg, float magnify) {
	Mat img_temp;
	resize(inputImg.Image, img_temp, Size(), magnify, magnify);

	imshow(inputImg.fileName, img_temp);
}