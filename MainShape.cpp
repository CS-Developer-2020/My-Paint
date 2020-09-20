#include "StdAfx.h"
#include "MainShape.h"


MainShape::MainShape(CTypedPtrArray<CObArray, MyShape*> &myShapes, MyShape *s)
	: myShapes(myShapes), s(s)
{
}


MainShape::~MainShape(void)
{
}

void MainShape::perform()
{
	myShapes.Add(s);
}

void MainShape::rollback()
{
	for (int i = 0; i < myShapes.GetSize(); ++i)
		if (myShapes[i] == s)
		{
			myShapes.RemoveAt(i);
			return;
		}
}