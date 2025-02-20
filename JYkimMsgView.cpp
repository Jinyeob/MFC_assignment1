

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "JYkimMsg.h"
#endif

#include "JYkimMsgDoc.h"
#include "JYkimMsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJYkimMsgView

IMPLEMENT_DYNCREATE(CJYkimMsgView, CView)

BEGIN_MESSAGE_MAP(CJYkimMsgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CJYkimMsgView 생성/소멸

CJYkimMsgView::CJYkimMsgView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CJYkimMsgView::~CJYkimMsgView()
{
}

BOOL CJYkimMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CJYkimMsgView 그리기

void CJYkimMsgView::OnDraw(CDC* pDC)
{
	CJYkimMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// 격자 출력
	CRect rect;
	GetClientRect(&rect);	
	int width = rect.Width();
	int height = rect.Height();

	for (int i = width/5; i < width; i+= width / 5) {
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, height);
	}
	for (int i = height / 5; i < height; i += height / 5) {
		pDC->MoveTo(0, i);
		pDC->LineTo(width, i);
	}
	//사각형 생성	
	CBrush myBrush(m_BrushColor);
	CBrush *pOldBrush = pDC->SelectObject(&myBrush);

	pDC->Rectangle(m_Pt.x, m_Pt.y, m_Pt.x +width/5, m_Pt.y +height/5); 

	pDC->SelectObject(pOldBrush);
	myBrush.DeleteObject();
/*
	m_Pt.x = width / 5;
	m_Pt.y = height / 5;
	pDC->Rectangle(m_Pt.x*2, m_Pt.y*2, m_Pt.x*3, m_Pt.y*2);*/


}


// CJYkimMsgView 인쇄

BOOL CJYkimMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CJYkimMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CJYkimMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CJYkimMsgView 진단

#ifdef _DEBUG
void CJYkimMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CJYkimMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJYkimMsgDoc* CJYkimMsgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJYkimMsgDoc)));
	return (CJYkimMsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CJYkimMsgView 메시지 처리기


void CJYkimMsgView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CView::OnSize(nType, cx, cy);
	m_ViewSize = CSize(cx, cy); //클라이언트 영역크기지정
	m_Pt = CPoint(cx *2 / 5, cy *2/ 5); // 출력 위치 화면 가운데로
}


void CJYkimMsgView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	CRect rect;
	GetClientRect(&rect);	
	int width = rect.Width();
	int height = rect.Height();
	switch (nChar) {
	case VK_UP: m_Pt.y -= height/5;
		if (m_Pt.y<0) m_Pt.y = m_ViewSize.cy; break;
	case VK_DOWN: m_Pt.y += height / 5;
		if (m_Pt.y>m_ViewSize.cy) m_Pt.y = 0; break;
	case VK_LEFT: m_Pt.x -= width / 5;
		if (m_Pt.x<0) m_Pt.x = m_ViewSize.cx; break;
	case VK_RIGHT: m_Pt.x += width / 5;
		if (m_Pt.x>m_ViewSize.cx) m_Pt.x = 0; break;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
