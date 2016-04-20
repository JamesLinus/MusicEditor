#include "Global.h"
#include "FontChina.h"
#include <cstdarg>
#include <qtextcursor.h>
#include <atlstr.h>
#include <QTextStream>
#include <QJsonDocument>

QWidget* glWidget = NULL;
Layer* g_scene = NULL;
QObject* g_editor = NULL;
AppDelegate* g_app = NULL;
HWND g_cocos_HWND = NULL;
QPlainTextEdit* logText = NULL;

void addConsoleInfo(std::string str)
{
	QTextCursor cursor = logText->textCursor();
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
	logText->insertPlainText(FontChina::G2U((str + "\n").c_str()));
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
	logText->ensureCursorVisible();
}

void addConsoleInfo(char* fmt, ...)
{
	char buf[4096] = { 0 };
	char* p = buf;
	std::string str;
	va_list args;
	std::string pattern = fmt;
	int count = 0;
	size_t pos = 0;
	while (pos != std::string::npos){
		pos = pattern.find("%", pos);
		if (pos != std::string::npos){
			count++;
			pos += (pattern.size() + 1);
		}
	}
	if (count != 0){
		va_start(args, fmt);
		vsprintf(p, fmt, args);
		va_end(args);
		str = buf;
		str += "\n";
	}
	else{
		str = fmt;
		str += "\n";
	}
	QTextCursor cursor = logText->textCursor();
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
	logText->insertPlainText(FontChina::G2U(str.c_str()));
	cursor.movePosition(QTextCursor::End);
	logText->setTextCursor(cursor);
}

void clearConsoleInfo()
{
	logText->clear();
}
