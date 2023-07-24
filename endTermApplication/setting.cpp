#include "setting.h"
#include <Windows.h>
#include <iostream>
#define CHARBUFF 124

void setAllVariable(char* currentDirectory, char (&section)[CHARBUFF],int sectionNum, char (& fileName)[CHARBUFF], char (&outputFile)[CHARBUFF], char (&settingFile)[CHARBUFF]) {
	
	if (sectionNum == 0) {
		sprintf_s(section, CHARBUFF, "section%d", sectionNum);
		sprintf_s(fileName, CHARBUFF, "xmlFileFace");
		sprintf_s(outputFile, CHARBUFF, "xmlFileEyes");
		sprintf_s(settingFile, CHARBUFF, "%s\\setting.ini", currentDirectory);
	}
	else {
		sprintf_s(section, CHARBUFF, "section%d", sectionNum);
		sprintf_s(fileName, CHARBUFF, "inputFile%d", sectionNum);
		sprintf_s(outputFile, CHARBUFF, "outputFile%d", sectionNum);
		sprintf_s(settingFile, CHARBUFF, "%s\\setting.ini", currentDirectory);
	}

}

void getVariable(char* currentDirectory, char(&keyValue)[CHARBUFF], char(section)[CHARBUFF], char(fileName)[CHARBUFF], char(settingFile)[CHARBUFF]) {
	
	if (GetPrivateProfileString(section, fileName, "new key word", keyValue, CHARBUFF, settingFile) != 0) {
		fprintf(stdout, "%s,%s\n", settingFile, keyValue);
	}
	else {
		fprintf(stdout, "%s doesnt contain [$s] %s\n", settingFile, section, fileName);
	}

}

