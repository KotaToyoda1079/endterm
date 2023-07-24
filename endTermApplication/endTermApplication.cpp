// endTermApplication.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <Windows.h>
#include "image.h"
#include "setting.h"

#define CHARBUFF 124
#define REAL_ASPECT_WIDTH 250;
#define REAL_ASPECT_HEIGHT 350;

using namespace std;
using namespace cv;

////////////////////////////////////////////// declare variables /////////////////////////////////////////
char section[CHARBUFF];
char inputFile[CHARBUFF];
char outputFile[CHARBUFF];
char xmlFile_face[CHARBUFF];
char xmlFile_eyes[CHARBUFF];
char settingFile[CHARBUFF];

char inputFileName[CHARBUFF];
char outputFileName[CHARBUFF];
char xmlFileName_face[CHARBUFF];
char xmlFileName_eyes[CHARBUFF];


float w = REAL_ASPECT_WIDTH;
float h = REAL_ASPECT_HEIGHT;

CascadeClassifier faceCascade;
CascadeClassifier eyeCascade;

image Img_sampleGirl;
image img_samplePic;
image img_sampleMan;

Point2f src[4] = { {849,383},{966,371},{854,516},{976,506} };
Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

////////////////////////////////////////////// declare variables end /////////////////////////////////////////

void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}


int main()
{

	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	string current = currentDirectory;

	////////////////////////////////////////////// sample 1 preprocess/////////////////////////////////////////

	setAllVariable(currentDirectory, section,1,inputFile,outputFile, settingFile);

	getVariable(currentDirectory, inputFileName, section, inputFile, settingFile);
	getVariable(currentDirectory, outputFileName, section, outputFile, settingFile);

	Img_sampleGirl.fileName = (string)inputFileName;
	Img_sampleGirl.outputName = (string)outputFileName;

	string path_sampleGirl = createPath(currentDirectory, "\\sampleImages\\", Img_sampleGirl.fileName);

	Img_sampleGirl.Image = imread(path_sampleGirl);

	///////////////////////////////////////////// sample 2 preprocess///////////////////////////////////////

	setAllVariable(currentDirectory, section, 2, inputFile, outputFile, settingFile);

	getVariable(currentDirectory, inputFileName, section, inputFile, settingFile);
	getVariable(currentDirectory, outputFileName, section, outputFile, settingFile);

	img_samplePic.fileName = (string)inputFileName;
	img_samplePic.outputName = (string)outputFileName;

	string path_samplePic = createPath(currentDirectory, "\\sampleImages\\", img_samplePic.fileName);

	img_samplePic.Image = imread(path_samplePic);

	///////////////////////////////////////////// sample 3 preprocess//////////////////////////////////////////

	setAllVariable(currentDirectory, section, 3, inputFile, outputFile, settingFile);

	getVariable(currentDirectory, inputFileName, section, inputFile, settingFile);
	getVariable(currentDirectory, outputFileName, section, outputFile, settingFile);

	img_sampleMan.fileName = (string)inputFileName;
	img_sampleMan.outputName = (string)outputFileName;

	string path_sampleMan = createPath(currentDirectory, "\\sampleImages\\", img_sampleMan.fileName);
	img_sampleMan.Image = imread(path_sampleMan);
	
	/////////////////////////////////////////////sample preprocess end//////////////////////////////////////////


	/////////////////////////////////////////////load Classifier////////////////////////////////////////////////

	setAllVariable(currentDirectory, section, 0, xmlFile_face, xmlFile_eyes, settingFile);

	getVariable(currentDirectory, xmlFileName_face,section,xmlFile_face,settingFile);
	getVariable(currentDirectory, xmlFileName_eyes, section, xmlFile_eyes, settingFile);

	string path_faceCascade = createPath(currentDirectory,"\\xmlfile\\",xmlFileName_face);
	string path_eyeCascade = createPath(currentDirectory,"\\xmlfile\\",xmlFileName_eyes);

	loadCascade(faceCascade, path_faceCascade);
	loadCascade(eyeCascade, path_eyeCascade);
	
	if (faceCascade.empty() || eyeCascade.empty()) { fprintf(stdout, "failed to load"); }

	/////////////////////////////////////////////load Classifier complete ////////////////////////////////////////////////
	
	////////////////////////////////////////////Sample 1 prediction and outPut////////////////////////////////////////////////
	
	predict_face(Img_sampleGirl, faceCascade,Img_sampleGirl.faceRecognize);
	predict_eyes(Img_sampleGirl, eyeCascade,Img_sampleGirl.eyesrecognize);

	putRecognizerResult_face(Img_sampleGirl, Img_sampleGirl.faceRecognize);
	putRecognizerResult_eyes(Img_sampleGirl, Img_sampleGirl.eyesrecognize);

	showImg(Img_sampleGirl, 1);

	outputImg(&Img_sampleGirl, 2);

	////////////////////////////////////////////Sample 2 prediction and outPut////////////////////////////////////////////////

	warpImage(&img_samplePic, src, dst, Point(w, h), 1);

	predict_face(img_samplePic, faceCascade, img_samplePic.faceRecognize);
	predict_eyes(img_samplePic, eyeCascade, img_samplePic.eyesrecognize);

	putRecognizerResult_face(img_samplePic, img_samplePic.faceRecognize);
	putRecognizerResult_eyes(img_samplePic, img_samplePic.eyesrecognize);

	showImg(img_samplePic, 2);

	outputImg(&img_samplePic, 2);

	////////////////////////////////////////////Sample 3 prediction and outPut////////////////////////////////////////////////

	predict_face(img_sampleMan, faceCascade, img_sampleMan.faceRecognize);
	predict_eyes(img_sampleMan, eyeCascade, img_sampleMan.eyesrecognize);

	putRecognizerResult_face(img_sampleMan, img_sampleMan.faceRecognize);
	putRecognizerResult_eyes(img_sampleMan, img_sampleMan.eyesrecognize);

	showImg(img_sampleMan, 0.5);

	outputImg(&img_sampleMan, 1);

	////////////////////////////////////////////finish all////////////////////////////////////////////////

	cv::waitKey(0);
}

