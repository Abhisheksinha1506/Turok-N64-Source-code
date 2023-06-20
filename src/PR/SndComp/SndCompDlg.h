// SndCompDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSndCompDlg dialog





class CSndCompDlg : public CDialog
{
// Construction
public:
	CSndCompDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSndCompDlg)
	enum { IDD = IDD_SNDCOMP_DIALOG };
	CString	m_ErrorMsg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSndCompDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   void TypeString(CWnd *pTarget, CString String);
	int CSndCompDlg::CheckFileStatus(int *FileFlags, CString *FileTable, int NumFiles);
	int DoTableDesign(CWnd *pTelnetWnd, CString *FileTable, int NumFiles, int *FileFlags);
	void CSndCompDlg::CompressSoundFiles(CWnd *pTelnetWnd, CString *FileTable, int NumFiles, int *FileFlags);
	void CSndCompDlg::ComplieSounds(CWnd *pTelnetWnd);

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSndCompDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



