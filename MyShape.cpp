#include "StdAfx.h"
#include "MyShape.h"

IMPLEMENT_SERIAL(MyShape, CObject, 1)

MyShape::MyShape(void)
{
}


MyShape::~MyShape(void)
{
}

void MyShape::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

    // now do the stuff for our specific class
    if(archive.IsStoring())
		archive << start.x << start.y << end.x << end.y << bgColor << penColor;
    else
        archive >> start.x >> start.y >> end.x >> end.y >> bgColor >> penColor;
}

void MyShape::draw(CDC *dc) { 
	CBrush brush(bgColor);
	CBrush *old = dc->SelectObject(&brush);
	CPen pen(PS_SOLID,1, penColor);
	CPen *oldPen = dc->SelectObject(&pen);
	innerDraw(dc);
	dc->SelectObject(old);
	dc->SelectObject(oldPen);
	
}
void MyShape::makeEven(){
	int DiffX = abs(start.x-end.x);
	int DiffY = abs(start.y-end.y);
	if(DiffX!=DiffY){
		if(DiffX > DiffY){
			if(start.x < end.x){
				end.x = end.x -(DiffX-DiffY);
			}
			else {
				end.x = end.x +(DiffX-DiffY);
			}
		}
		else{
			if(start.y < end.y){
				end.y = end.y -(DiffY-DiffX);
			}
			else{
				end.y = end.y +(DiffY-DiffX);
			}
		}
		
	}
}

bool MyShape::inArea(CPoint& p) const
{
	if (((start.x<p.x && p.x<end.x) || (end.x<p.x && p.x<start.x)) && ((start.y<p.y && p.y<end.y) || (end.y<p.y && p.y<start.y))) {
		return true;
	}
	return false;
}

void MyShape::moveShap(int x,int y)
{
		start.x+=x;
		end.x+=x;
		start.y+=y;
		end.y+=y;
}