
// PaintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Paint.h"
#include "PaintDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPaintDlg dialog




CPaintDlg::CPaintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaintDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isPressed = false;
	IsPressedRight = false;
	shapeFactory = LineFactory::getInstance();
}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_red);
	DDX_Control(pDX, IDC_SLIDER2, m_green);
	DDX_Control(pDX, IDC_SLIDER3, m_blue);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, PenColorC);
}

BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RADIO1, &CPaintDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPaintDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CPaintDlg::OnBnClickedRadio3)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CPaintDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPaintDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO4, &CPaintDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CPaintDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON3, &CPaintDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPaintDlg::OnBnClickedButton4)
	ON_WM_RBUTTONDOWN()
	ON_WM_NCRBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CPaintDlg::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// CPaintDlg message handlers

BOOL CPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
	m_red.SetRangeMax(255);
	m_red.SetRangeMin(0);
	m_green.SetRangeMax(255);
	m_green.SetRangeMin(0);
	m_blue.SetRangeMax(255);
	m_blue.SetRangeMin(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaintDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintDlg::OnPaint()
{
	CPaintDC dc(this);
	for (int i = 0; i < myShapes.GetSize(); ++i)
		myShapes[i]->draw(&dc);

	CBrush brush(RGB(m_red.GetPos(), m_green.GetPos(), m_blue.GetPos()));
	CBrush *old = dc.SelectObject(&brush);

	CPen pen(PS_SOLID,1,CurrentPenColor);
	CPen *oldPen = dc.SelectObject(&pen);

	dc.Rectangle(0, 50, 20, 70);
	dc.SelectObject(old);
	dc.SelectObject(oldPen);

	CurrentBrushColor=BrushColorC.GetColor();
	CurrentPenColor=PenColorC.GetColor();

	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isPressed)
	{
		myShapes[myShapes.GetSize() - 1]->setEnd(point);
		Invalidate();
	}
	else if(IsPressedRight) 
	{
		
		CClientDC dc(this);

		CBrush myBrush,*oldBrush;

		myBrush.CreateSolidBrush(CurrentBrushColor);
		oldBrush=dc.SelectObject( &myBrush );              	                     

		CPen border(PS_SOLID,1, CurrentPenColor);
		CPen* oldBorder;

		oldBorder=dc.SelectObject( &border ); 
		dc.SetROP2(R2_NOTXORPEN);

		moveShape->innerDraw(&dc);
		moveShape->moveShap((point.x-start.x),(point.y-start.y));
		moveShape->innerDraw(&dc);
		start=point;

		dc.SelectObject( oldBorder ); 
		dc.SetROP2(R2_COPYPEN);  
		dc.SelectObject( oldBrush ); 

	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	isPressed = true;
	MyShape *s = shapeFactory->createShape();

	Command *c = new MainShape(myShapes, s);
	c->perform();
	commands.push(c);
	s->setBg(RGB(m_red.GetPos(), m_green.GetPos(), m_blue.GetPos()));
	s->setPen(CurrentPenColor);
	s->setStart(point);
	s->setEnd(point);
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	isPressed = false;
	myShapes[myShapes.GetSize() - 1]->setEnd(point);
	Invalidate();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPaintDlg::OnBnClickedRadio1()
{
	shapeFactory = LineFactory::getInstance();
}


void CPaintDlg::OnBnClickedRadio2()
{
	shapeFactory = RectangleFactory::getInstance();
}


void CPaintDlg::OnBnClickedRadio3()
{
	shapeFactory = EllipseFactory::getInstance();
}


void CPaintDlg::OnOK()
{
}


void CPaintDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CPaintDlg::OnBnClickedButton2()
{
		if (!myShapes.IsEmpty()){
		myShapesUndo.Add(myShapes.GetAt(myShapes.GetSize()-1));
		myShapes.RemoveAt(myShapes.GetSize()-1);
		Invalidate();
	}
}


void CPaintDlg::OnBnClickedButton1()
{
		if (!myShapesUndo.IsEmpty()){
		myShapes.Add(myShapesUndo.GetAt(myShapesUndo.GetSize()-1));
		myShapesUndo.RemoveAt(myShapesUndo.GetSize()-1);
		Invalidate();
	}
}


void CPaintDlg::OnBnClickedRadio4()
{
	shapeFactory = SquareFactory::getInstance();

}


void CPaintDlg::OnBnClickedRadio5()
{
	shapeFactory = CircleFactory::getInstance();
}


void CPaintDlg::OnBnClickedButton3()
{
	CFile file(L"NewFILE.$$", CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&file, CArchive::store);
	myShapes.Serialize(ar);
	ar.Close();
	file.Close();
}



void CPaintDlg::OnBnClickedButton4()
{
	CFile file(_T("NewFile.$$"), CFile::modeRead);
	CArchive archive (&file, CArchive::load);
	myShapes.Serialize(archive);
	archive.Close();
	file.Close();
	Invalidate();
}


void CPaintDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	start=point;
	for(int i=myShapes.GetSize()-1;i>=0;i--){
		if ((myShapes.GetAt(i))->inArea(point)) { 
			if (nFlags==(MK_RBUTTON+MK_CONTROL)){
				myShapes.RemoveAt(i);
				Invalidate();
			}
			else {
				IsPressedRight=true;
				moveShape = myShapes.GetAt(i);
				CClientDC dc(this);
				dc.SetROP2(R2_BLACK);
				moveShape->innerDraw(&dc);
			}
			i=-1;	
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


//void CPaintDlg::OnNcRButtonUp(UINT nHitTest, CPoint point)
//{
//	
//	CDialogEx::OnNcRButtonUp(nHitTest, point);
//}


void CPaintDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (IsPressedRight){
		Invalidate();
		IsPressedRight=false;
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}


void CPaintDlg::OnBnClickedMfccolorbutton1()
{
	CurrentPenColor = PenColorC.GetColor();
}

