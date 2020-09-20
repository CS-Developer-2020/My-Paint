#pragma once

#include "MyShape.h"

class ShapeFactory
{
public:
	ShapeFactory(void);
	~ShapeFactory(void);
	virtual MyShape* createShape() = 0;
};

