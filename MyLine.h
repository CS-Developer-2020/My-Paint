#pragma once
#include "myshape.h"
class MyLine :
	public MyShape
{
public:
	DECLARE_SERIAL(MyLine)
	MyLine(void);
	~MyLine(void);
	void draw(CDC *dc);
};

