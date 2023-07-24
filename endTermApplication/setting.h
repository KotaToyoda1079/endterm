#pragma once
#define CHARBUFF 124

void getCurrentDirectory(char* currentDirectory);
void setAllVariable(char* currentDirectory, char (&section)[CHARBUFF], int sectionNum,char (&fileName)[CHARBUFF], char (&outputFile)[CHARBUFF], char (&settingFile)[CHARBUFF]);
void getVariable(char* currentDirectory, char(&keyValue)[CHARBUFF], char(section)[CHARBUFF], char(fileName)[CHARBUFF], char(settingFile)[CHARBUFF]);
