#pragma once

#include "cocos2d.h"

#include <QMouseEvent>
#include <QWidget>
#include <QtOpenGL/QGLWidget>


NS_CC_BEGIN

class CCQGLView : public QGLWidget, public GLViewImpl
{
	Q_OBJECT
public:
	CCQGLView(QWidget *parent = 0);
	~CCQGLView();
	static CCQGLView* create(const std::string& viewName, float width, float height, HWND mParentHwnd);
protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
    
};

NS_CC_END

