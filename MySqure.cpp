#include "StdAfx.h"
#include "MySqure.h"

IMPLEMENT_SERIAL(MySqure,MyRectangle,1)

MySqure::MySqure(void)
{
}


MySqure::~MySqure(void)
{
}

void MySqure::innerDraw(CDC *dc){
	makeEven();
	dc->Rectangle(start.x,start.y,end.x,end.y);
}