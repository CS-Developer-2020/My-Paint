#include "StdAfx.h"
#include "MyCircle.h"

IMPLEMENT_SERIAL(MyCircle,MyEllipse,1)

MyCircle::MyCircle(void)
{
}


MyCircle::~MyCircle(void)
{
}

void MyCircle::innerDraw(CDC *dc) {
	makeEven();
	dc->Ellipse(start.x, start.y, end.x, end.y);
}