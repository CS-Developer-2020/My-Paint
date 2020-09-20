#pragma once
class MyShape : public CObject
{
public:
	DECLARE_SERIAL(MyShape)
	MyShape(void);
	virtual ~MyShape(void);
	void setStart(CPoint p) { start = p; }
	void setEnd(CPoint p) { end = p; }
	CPoint getStart() const { return start; }
	CPoint getEnd() const { return end; }
	COLORREF getBg() const { return bgColor; }
	COLORREF getPen() const { return penColor; }
	void setBg(COLORREF c) { bgColor = c; }
	void setPen(COLORREF c) {penColor = c;}
	virtual void draw(CDC *dc);
	virtual void innerDraw(CDC *dc) {}
	void Serialize(CArchive& archive);
	void makeEven();
	bool inArea(CPoint&) const;
	void moveShap(int,int);
protected:
	CPoint start, end;
	COLORREF bgColor;
	COLORREF penColor;
};

