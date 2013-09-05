#pragma once

#include "ColumnTreeView.h"

class CWinValgrindView : public CColumnTreeView
{
	DECLARE_DYNCREATE(CWinValgrindView)
protected:
	CWinValgrindView();
public:
	virtual ~CWinValgrindView();

public:
	CWinValgrindDoc* GetDocument() const;

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();

protected:
	CImageList m_ImgList;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG
inline CWinValgrindDoc* CWinValgrindView::GetDocument() const
   { return reinterpret_cast<CWinValgrindDoc*>(m_pDocument); }
#endif

