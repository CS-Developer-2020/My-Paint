#pragma once
#include "command.h"
#include "MyShape.h"

class MainShape :
	public Command
{
public:
	MainShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s);
	~MainShape(void);
	virtual void perform();
	virtual void rollback();
private:
	CTypedPtrArray<CObArray, MyShape*> &myShapes;
	MyShape *s;
};

