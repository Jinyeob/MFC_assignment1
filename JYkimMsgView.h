
// JYkimMsgView.h: CJYkimMsgView 클래스의 인터페이스
//

#pragma once


class CJYkimMsgView : public CView
{
protected: // serialization에서만 만들어집니다.
	CJYkimMsgView();
	DECLARE_DYNCREATE(CJYkimMsgView)

// 특성입니다.
public:
	CJYkimMsgDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CJYkimMsgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint m_Pt;
	CSize m_ViewSize;
	COLORREF m_BrushColor = RGB(0, 0, 200);
};

#ifndef _DEBUG  // JYkimMsgView.cpp의 디버그 버전
inline CJYkimMsgDoc* CJYkimMsgView::GetDocument() const
   { return reinterpret_cast<CJYkimMsgDoc*>(m_pDocument); }
#endif

