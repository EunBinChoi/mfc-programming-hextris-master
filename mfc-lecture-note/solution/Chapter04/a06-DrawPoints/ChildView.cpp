
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "DrawPoints.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	for(int x=0; x<256; x++)
		for(int y=0; y<256; y++)
			dc.SetPixelV(x, y, RGB(x, y, 0));
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 	//<= [a06]
{
	CClientDC dc( this );
	COLORREF color = dc.GetPixel( point );

	CString str;
	str.Format( _T("R:%d, G:%d, B:%d"), GetRValue(color), GetGValue(color), GetBValue(color) );
	::AfxMessageBox( str );
	
	CWnd ::OnLButtonUp(nFlags, point);
}
