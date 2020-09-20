#pragma once
#include "ellipsefactory.h"
#include "MyCircle.h"
class CircleFactory :
	public ShapeFactory
{
public:
	~CircleFactory(void);
	MyShape* createShape() { return new MyCircle(); }
	static CircleFactory* getInstance() {
		static CircleFactory instance;
		return &instance;
	}
private:
	CircleFactory(void);
};

