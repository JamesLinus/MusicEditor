#include "BaseRoute.h"


BaseRoute::BaseRoute()
{
	drawNode = DrawNode::create();
	addChild(drawNode);
}


BaseRoute::~BaseRoute()
{
}

void BaseRoute::drawBezier()
{
	drawNode->clear();
	drawNode->drawCubicBezier(startPos, control1, control2, endPos, 10, _color);
}

void BaseRoute::drawLine()
{

}