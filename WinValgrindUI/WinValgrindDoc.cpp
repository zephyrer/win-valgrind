// WinValgrindDoc.cpp : implementation of the CWinValgrindDoc class
//

#include "stdafx.h"
#include "WinValgrind.h"

#include "WinValgrindDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinValgrindDoc

IMPLEMENT_DYNCREATE(CWinValgrindDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinValgrindDoc, CDocument)
END_MESSAGE_MAP()


// CWinValgrindDoc construction/destruction

CWinValgrindDoc::CWinValgrindDoc()
{
	// TODO: add one-time construction code here

}

CWinValgrindDoc::~CWinValgrindDoc()
{
}

BOOL CWinValgrindDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CWinValgrindDoc serialization

void CWinValgrindDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CWinValgrindDoc diagnostics

#ifdef _DEBUG
void CWinValgrindDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinValgrindDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinValgrindDoc commands
