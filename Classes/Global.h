#pragma once
#include <qplaintextedit.h>
#include "cocos2d.h"
#include <QtCore\qobject.h>
#include "AppDelegate.h"

using namespace cocos2d;


extern QWidget* glWidget;
extern Layer* g_scene;
extern QObject* g_editor;
extern AppDelegate* g_app;
extern QPlainTextEdit* logText;
extern HWND g_cocos_HWND;

void addConsoleInfo(std::string str);
void addConsoleInfo(char* fmt, ...);
void clearConsoleInfo();

class Global
{
public:
	Global();
	~Global();
};

