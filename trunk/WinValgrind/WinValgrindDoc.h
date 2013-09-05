// WinValgrindDoc.h : interface of the CWinValgrindDoc class
//


#pragma once

class CWinValgrindDoc : public CDocument
{
protected: // create from serialization only
	CWinValgrindDoc();
	DECLARE_DYNCREATE(CWinValgrindDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CWinValgrindDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


