// statusdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// statusdlg dialog

class statusdlg : public CDialog
{
// Construction
public:
	statusdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(statusdlg)
	enum { IDD = IDD_STATUS };
	CListBox	m_ctlStatusList;
	CString	m_statusmsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(statusdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:
	int statusdlg::CheckFileStatus(int *FileFlags, CString *FileTable, int NumFiles);

	// Generated message map functions
	//{{AFX_MSG(statusdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void ProcessFile() ;

// Data members
protected:
	BOOL m_PaintHappened;
};
