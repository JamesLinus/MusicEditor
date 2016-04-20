#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class BaseRoute : public Sprite
{
public:
	BaseRoute();
	~BaseRoute();
	void drawBezier();
	void drawLine();
private:
	Point startPos;
	DrawNode* drawNode;
	Point control1;
	Point control2;
	Point endPos;
	Color4F _color;
};

