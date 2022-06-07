
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "DisableCloseButton.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
	: m_bDirty( FALSE )	//<= [a12]
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// 종료 버튼을 누른 경우에만 특별한 처리를 한다.
	if(nHitTest == HTCLOSE)
		MessageBox(_T("여기를 눌러도 종료할 수 없습니다."), _T("테스트"));
	// 그 밖의 경우에는 운영체제가 자동으로 처리한다.
	else
		CFrameWnd::OnNcLButtonDown(nHitTest, point);
}


void CMainFrame::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if ( nHitTest == HTCLOSE )
	{
		CWindowDC dc( this );

		CDC dcMem;
		dcMem.CreateCompatibleDC( &dc );

		CBitmap bitmap;
		bitmap.LoadBitmap( IDB_BITMAP1 );
		BITMAP bm;
		bitmap.GetBitmap( &bm );

		dcMem.SelectObject( &bitmap );

		CRect rect;
		GetWindowRect( rect );

		int cxFrame = ::GetSystemMetrics( SM_CXFRAME );
		int cyFrame = ::GetSystemMetrics( SM_CYFRAME );
		int cxSize = ::GetSystemMetrics( SM_CXSIZE );
		int cySize = ::GetSystemMetrics( SM_CYSIZE );
		int cxBorder = ::GetSystemMetrics( SM_CXBORDER );
		int cyBorder = ::GetSystemMetrics( SM_CYBORDER );

		dc.StretchBlt( rect.Width() - cxSize - cxFrame,
			cyFrame, cxSize, cySize,
			&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );

		m_bDirty = TRUE;
	}
	else if ( m_bDirty == TRUE )
	{
		m_bDirty = FALSE;
		RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE);
	}

	CFrameWnd::OnNcMouseMove(nHitTest, point);
}
