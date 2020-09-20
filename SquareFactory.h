#pragma once
#include "RectangleFactory.h"
#include "MySqure.h"
#include "ShapeFactory.h"
class SquareFactory :
	public ShapeFactory
{
public:
	
	~SquareFactory(void);
	MyShape* createShape(){return new MySqure();};
	static SquareFactory* getInstance(){
		static SquareFactory instance;
		return &instance;
	}
private:
	SquareFactory(void);
};

