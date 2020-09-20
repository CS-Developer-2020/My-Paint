#pragma once
#include "myellipse.h"
class MyCircle :
	public MyEllipse
{
public:
	DECLARE_SERIAL(MyCircle)
	MyCircle(void);
	~MyCircle(void);
	void innerDraw(CDC *dc);
};

