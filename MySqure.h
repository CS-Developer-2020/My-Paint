#pragma once
#include "myrectangle.h"
#include "MyShape.h"
class MySqure :
	public MyRectangle
{
public:
	DECLARE_SERIAL(MySqure)
	MySqure(void);
	~MySqure(void);
	void innerDraw(CDC *dc);
};

