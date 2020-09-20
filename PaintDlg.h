
// PaintDlg.h : header file
//

#pragma once

#include "MyShape.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyLine.h"
#include "EllipseFactory.h"
#include "LineFactory.h"
#include "RectangleFactory.h"
#include <vector>
#include "MainShape.h"
#include <stack>
#include "MySqure.h"
#include "SquareFactory.h"
#include "ShapeFactory.h"
#include "MyCircle.h"
#include "CircleFactory.h"

using namespace std;

// CPaintDlg dialog
class CPaintDlg : public CDialogEx
{
// Construction
public:
	CPaintDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_PAINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	bool isPressed;
	CPoint start;
	CPoint end;
	CTypedPtrArray<CObArray, MyShape*> myShapes;
	CTypedPtrArray<CObArray, MyShape*> myShapesUndo;
	stack<Command*> commands, undoes;
	CMFCColorButton BrushColorC;
	CMFCColorButton PenColorC;
	COLORREF CurrentBrushColor;
	COLORREF CurrentPenColor;
	bool IsPressedRight;
	MyShape* moveShape;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
private:
	ShapeFactory* shapeFactory;
	virtual void OnOK();
public:
	CSliderCtrl m_red;
	CSliderCtrl m_green;
	CSliderCtrl m_blue;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	/*afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);*/
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
