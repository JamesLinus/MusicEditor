#include "CCQGLWidget.h"
#include "CCQGLView.h"
#include "Global.h"
#include <QDesktopWidget>
#include <QApplication>

NS_CC_BEGIN

static CCQGLView* s_pMainWindow = nullptr;

CCQGLView::CCQGLView(QWidget *parent)
	:QGLWidget(parent)
{
	setMouseTracking(true);
}

CCQGLView::~CCQGLView()
{

}

CCQGLView* CCQGLView::create(const std::string& viewName, float width, float height, HWND mParentHwnd)
{
	auto ret = new (std::nothrow) CCQGLView;
	if (ret && ret->initWithRect(viewName, Rect(0, 0, width, height), 1, mParentHwnd)) {
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

void CCQGLView::mousePressEvent(QMouseEvent *e)
{
	addConsoleInfo("mousePressEvent");
}

void CCQGLView::mouseMoveEvent(QMouseEvent *e)
{
	addConsoleInfo("mouseMoveEvent");
}
NS_CC_END