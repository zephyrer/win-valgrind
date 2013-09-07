// WinValgrindView.cpp : implementation of the CWinValgrindView class
//

#include "stdafx.h"
#include "WinValgrind.h"

#include "WinValgrindDoc.h"
#include "WinValgrindView.h"
#include ".\WinValgrindview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinValgrindView

IMPLEMENT_DYNCREATE(CWinValgrindView, CColumnTreeView)

BEGIN_MESSAGE_MAP(CWinValgrindView, CColumnTreeView)
	ON_NOTIFY(TVN_SELCHANGED, TreeID, OnTvnSelchanged)
	ON_NOTIFY(NM_DBLCLK, TreeID, OnDblclk)
END_MESSAGE_MAP()

// CWinValgrindView construction/destruction

CWinValgrindView::CWinValgrindView()
{
}

CWinValgrindView::~CWinValgrindView()
{
}

BOOL CWinValgrindView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CColumnTreeView::PreCreateWindow(cs);
}

void CWinValgrindView::OnInitialUpdate()
{
	CColumnTreeView::OnInitialUpdate();

	CTreeCtrl& tree = GetTreeCtrl();
	CHeaderCtrl& header = GetHeaderCtrl();

	DWORD dwStyle = GetWindowLong(tree, GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_FULLROWSELECT | TVS_DISABLEDRAGDROP;
	SetWindowLong(tree, GWL_STYLE, dwStyle);

	//m_ImgList.Create(IDB_IMAGES, 16, 1, RGB(255,0,255));
	//tree.SetImageList(&m_ImgList, TVSIL_NORMAL);

	HDITEM hditem;
	hditem.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT;
	hditem.fmt = HDF_LEFT | HDF_STRING;
	hditem.cxy = 200;
	hditem.pszText = "Process Name";
	header.InsertItem(0, &hditem);
	hditem.cxy = 100;
	hditem.pszText = "PID";
	header.InsertItem(1, &hditem);
	hditem.cxy = 100;
	hditem.pszText = "User Name";
	header.InsertItem(2, &hditem);
	UpdateColumns();

	HTREEITEM hRoot = tree.InsertItem("All Employees", 0, 0, TVI_ROOT);
	HTREEITEM hCat = tree.InsertItem("New York", 0, 0, hRoot);
	tree.InsertItem("John Smith\tA00012\t40,000 USD", 1, 1, hCat);
	tree.InsertItem("Julia Brown\tA00235\t36,000 USD", 1, 1, hCat);
	tree.InsertItem("Kevin Jones\tA00720\t28,000 USD", 1, 1, hCat);
	tree.Expand(hCat, TVE_EXPAND);
	hCat = tree.InsertItem("Warsaw", 0, 0, hRoot);
	tree.InsertItem("Jan Kowalski\tB00241\t50,000 PLN", 1, 1, hCat);
	tree.InsertItem("Maria Nowak\tB00532\t34,000 PLN", 1, 1, hCat);
	tree.InsertItem("Adam Jaworek\tB00855\t31,500 PLN", 1, 1, hCat);
	tree.Expand(hCat, TVE_EXPAND);
	tree.Expand(hRoot, TVE_EXPAND);
}


void CWinValgrindView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;

	// find the label of the selected item
	CString strLabel;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (hItem)
	{
		CTreeCtrl& tree = GetTreeCtrl();
		strLabel = tree.GetItemText(hItem);
		int nPos = strLabel.Find('\t');
		if (nPos >= 0)
			strLabel = strLabel.Left(nPos);
	}

	// display it on the status bar
	GetParentFrame()->SetMessageText(strLabel);

	*pResult = 0;
}

void CWinValgrindView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	AfxMessageBox("NM_DBLCLK Handler");
}
