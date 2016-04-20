#include "qtmusiceditor.h"
#include "Global.h"
#include "AppDelegate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	CCQApplication::addLibraryPath("./plugins");
	AppDelegate app(argc, argv);
	QTMusicEditor w;
	w.show();
	RECT t;

	logText = dynamic_cast<QPlainTextEdit*>(w.getUI().LogWidgetContents->children().at(0));
	QRect qr = w.getUI().SceneWidget->rect();
	t.left = qr.left();
	t.right = qr.right();
	t.top = qr.top();
	t.bottom = qr.bottom();
	glWidget = w.getUI().SceneWidget;
	app.setParent((HWND)w.getUI().SceneWidget->winId(), t);
	g_app = &app;
	return cocos2d::CCQApplication::getInstance()->run();
}
