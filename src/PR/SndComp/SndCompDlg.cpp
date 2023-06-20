// SndCompDlg.cpp : implementation file
//
#include "stdafx.h"
#include "SndComp.h"
#include "SndCompDlg.h"
#include "makeinst.h"
#include "statusdlg.h"
#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CString	FileTable[MAX_ELEMENT_FILES];
int		FileFlags[MAX_ELEMENT_FILES];
int		NumFiles = 0;

extern void		AddDefaultExtension (char *SourceName, char *DestFile, char *ext) ;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSndCompDlg dialog

CSndCompDlg::CSndCompDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSndCompDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSndCompDlg)
	m_ErrorMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSndCompDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSndCompDlg)
	DDX_Text(pDX, IDC_ERRORMSG, m_ErrorMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSndCompDlg, CDialog)
	//{{AFX_MSG_MAP(CSndCompDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSndCompDlg message handlers

BOOL CSndCompDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	statusdlg		statusdlg; 

	
	int		ErrorCode;

	//int		NumFiles = 0;
	//CString	FileTable[MAX_ELEMENT_FILES];
	//int		FileFlags[MAX_ELEMENT_FILES];

#if 1

   CString	sgiName = GetCommandLine();
	int		pos = sgiName.Find(' ');

	if (pos == -1)
      return TRUE;
   else
      sgiName = sgiName.Mid(pos + 1);

   if (sgiName.IsEmpty())
      return TRUE;
   else if (sgiName[0] == ' ')
      return TRUE;
#else


	//CString sgiName = "chorltonsgi";
	//CString sgiName = "foghorn";
	//CString sgiName = "marvin";
	CString sgiName = "hobbes";
#endif

	CWnd *pTelnetWnd = FindWindow("TelnetWClass", "Telnet - " + sgiName + ".iguana-us.com");
	if (!pTelnetWnd)
	{
		WinExec("c:\\windows\\telnet.exe " + sgiName + ".iguana-us.com", SW_SHOW);

		pTelnetWnd = FindWindow("TelnetWClass", "Telnet - " + sgiName + ".iguana-us.com");
		if (pTelnetWnd)
		{
			TypeString(pTelnetWnd, "root\ndaffy\n");
			TypeString(pTelnetWnd, "fixdir\n");
			TypeString(pTelnetWnd, "cd tengine/sounds\n");
		}
	}
	
   if (pTelnetWnd)
   {
		TypeString(pTelnetWnd, "fixdir\n");
		TypeString(pTelnetWnd, "cd tengine/sounds\n");
		
		CString fileName = "e:\\src\\PR\\tengine\\sounds\\elements";
		FILE *pFile = fopen(fileName, "r");

		if (pFile)
		{
	
			for(int i = 0; i < MAX_ELEMENT_FILES; i++)
				FileFlags[i] = 0;

			NumFiles = MakeInst(pFile, FileTable);

			ErrorCode = NumFiles & 0x0000ffff;

			if( NumFiles > MAX_ELEMENT_FILES)
			{
				m_ErrorMsg = "ERROR:\n\nMaximum number of elements has been exceeded";
				UpdateData(FALSE);
				return TRUE;  // return TRUE  unless you set the focus to a control
			}

			if( NumFiles < 0)
			{
				switch (NumFiles)
				{
					case OUTPUT_ERROR:
						m_ErrorMsg = "ERROR:\n\nCould not open output file";
						break;

					case HEADER_ERROR:
						m_ErrorMsg = "ERROR:\n\nUnable to read AIFF header";
						break;

					default:
						char		numstr[3];

						_itoa(abs(NumFiles), numstr, 10);
						m_ErrorMsg = "ERROR:\n\nCould not find element ";
						m_ErrorMsg += numstr;
						break;
				}			

				UpdateData(FALSE);
				return TRUE;  // return TRUE  unless you set the focus to a control
			}


			statusdlg.DoModal();
			//CheckFileStatus(FileFlags, FileTable, NumFiles);
			DoTableDesign(pTelnetWnd, FileTable, NumFiles, FileFlags);
			Sleep(10);
			CompressSoundFiles(pTelnetWnd, FileTable, NumFiles, FileFlags);
			ComplieSounds(pTelnetWnd);
			fclose(pFile);
		   OnOK();
		}
		else
		{
			// display error message

			m_ErrorMsg = "ERROR:\n\nCould not open \"" + fileName + "\"";
			UpdateData(FALSE);
		}
		
   }
	return TRUE;  // return TRUE  unless you set the focus to a control
}


///////////////////////////////////////////////////////////////////////////////////
//		Function: int CSndCompDlg::CheckFileStatus(int *FileFlags, CString *FileTable, int NumFiles)
///////////////////////////////////////////////////////////////////////////////////
//		Description:	This Funcition will check the dates of the files to see 
//							which files need to be compressed. If so, the FLAG_MODIFIED
//							is set.
///////////////////////////////////////////////////////////////////////////////////
int CSndCompDlg::CheckFileStatus(int *FileFlags, CString *FileTable, int NumFiles)
{

	CFileStatus		rStatus1;
	CFileStatus		rStatus2; 
	CFile				AIFFfile;
	CFile				CompFile;
	char 				DestName[128];
	char 				CompName[128];
	char				FileName[128];
	char 				temp[128];
	int				result, Sum1, Sum2;
	




	for(int i = 0; i <  NumFiles; i++)
	{
		strcpy(FileName, "e:\\src\\PR\\tengine\\sounds\\");		
		strcat(FileName, FileTable[i]);		

		strcpy(temp, FileTable[i]);
		AddDefaultExtension (temp, DestName, "n64");
		strcpy(CompName, "e:\\src\\PR\\tengine\\sounds\\");		
		strcat(CompName, DestName);		


		result = AIFFfile.Open(FileName, CFile::modeRead, NULL); 
		if(!result)
		{
			//afxDump << "Error in opening file\n";
		}
		else
		{
			AIFFfile.GetStatus(FileName, rStatus1);
			AIFFfile.Close();
		}

		result = CompFile.Open(CompName, CFile::modeRead, NULL); 
		if(!result)
		{
			FileFlags[i] |= FILE_MODIFIED;
		}
		else
		{
			CompFile.GetStatus(CompName, rStatus2);
			CompFile.Close();
		}



		if((FileFlags[i] & FILE_MODIFIED) == 0)
		{
			Sum1 = rStatus1.m_mtime.GetYear() +
						rStatus1.m_mtime.GetMonth();

			Sum2 = rStatus2.m_mtime.GetYear() +
						rStatus2.m_mtime.GetMonth();	

			if(Sum1 == Sum2)
			{
				if(rStatus1.m_mtime.GetDay() == rStatus2.m_mtime.GetDay())
				{

					if(rStatus1.m_mtime.GetHour() == rStatus2.m_mtime.GetHour())
					{
						if(rStatus1.m_mtime.GetMinute() == rStatus2.m_mtime.GetMinute())
						{
							if(rStatus1.m_mtime.GetSecond() > rStatus2.m_mtime.GetSecond())
							{
								FileFlags[i] |= FILE_MODIFIED;
							}
						}
						else
						{
							if(rStatus1.m_mtime.GetMinute() > rStatus2.m_mtime.GetMinute())
							{
								FileFlags[i] |= FILE_MODIFIED;
							}
						}
					}	
					else
					{
						if(rStatus1.m_mtime.GetHour() > rStatus2.m_mtime.GetHour())
						{
							FileFlags[i] |= FILE_MODIFIED;
						}
					}
				}
				else
				{
					if(rStatus1.m_mtime.GetDay() > rStatus2.m_mtime.GetDay())
					{
						FileFlags[i] |= FILE_MODIFIED;
					}
				}
			}
			else
			{
				if(Sum1 > Sum2)
				{
					FileFlags[i] |= FILE_MODIFIED;
				}
			}

	#if 0
			afxDump << "Set " << i << "\n";
			afxDump << "GetYear  " << rStatus1.m_mtime.GetYear() << ", " << rStatus2.m_mtime.GetYear() << "\n"; 
			afxDump << "GetMonth  " << rStatus1.m_mtime.GetMonth() << ", " << rStatus2.m_mtime.GetMonth() << "\n"; 
			afxDump << "GetDay  " << rStatus1.m_mtime.GetDay() << ", " << rStatus2.m_mtime.GetDay() << "\n"; 
			afxDump << "GetHour  " << rStatus1.m_mtime.GetHour() << ", " << rStatus2.m_mtime.GetHour() << "\n"; 
			afxDump << "GetMinute  " << rStatus1.m_mtime.GetMinute() << ", " << rStatus2.m_mtime.GetMinute() << "\n"; 
			afxDump << "GetSecond  " << rStatus1.m_mtime.GetSecond() << ", " << rStatus2.m_mtime.GetSecond() << "\n"; 
	#endif

		}
	}

	//statusdlg.DoModal();

	return 0;
}	 


///////////////////////////////////////////////////////////////////////////////////
//		Function: void DoTableDesign(CString *FileTable, int NumFiles)
///////////////////////////////////////////////////////////////////////////////////
//		Description:	This Funcition will invoke the SGI utility "tabledesign"
//							with each of the files in the file table		
///////////////////////////////////////////////////////////////////////////////////
int CSndCompDlg::DoTableDesign(CWnd *pTelnetWnd, CString *FileTable, int NumFiles, int *FileFlags)
{

	CString		CommandStr;


	CommandStr.GetBuffer(1024);
	for(int	i = 0; i < NumFiles; i++)
	{
		CString newName;
		
		int pos = FileTable[i].ReverseFind('.');
		if(pos == -1)
		{
			TypeString(pTelnetWnd, "Error in table design");
			// problem
		}
		else
		{
			if(FileFlags[i] & FILE_MODIFIED)
			{
				newName = FileTable[i].Left(pos + 1) + "tbl";
				CommandStr = "./table-aif " + FileTable[i] + " " + newName + "\n";
				TypeString(pTelnetWnd, CommandStr);
			}
		}
	}

	return 0;
}



///////////////////////////////////////////////////////////////////////////////////
//		Function: void CompressSoundFiles(CString *FileTable, int NumFiles)
///////////////////////////////////////////////////////////////////////////////////
//		Description:	This Funcition will invoke the SGI utility "vadpcm_enc"
//							with each of the files in the file table		
///////////////////////////////////////////////////////////////////////////////////
void CSndCompDlg::CompressSoundFiles(CWnd *pTelnetWnd, CString *FileTable, int NumFiles, int *FileFlags)
{
	CString		CommandStr, TblName, DestName;

	CommandStr.GetBuffer(1024);
	for(int	i = 0; i < NumFiles; i++)
	{
		int pos = FileTable[i].ReverseFind('.');
		if(pos == -1)
		{
			TypeString(pTelnetWnd, "Error in sound compression");
		}
		else
		{
			if(FileFlags[i] & FILE_MODIFIED)
			{
				TblName = FileTable[i].Left(pos + 1) + "tbl ";
				DestName = FileTable[i].Left(pos + 1) + "n64\n";
				CommandStr = "./encode-aif " + TblName + FileTable[i] + " " +DestName;
				TypeString(pTelnetWnd, CommandStr);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////
//		Function: void CSndCompDlg::ComplieSounds(CWnd *pTelnetWnd)
///////////////////////////////////////////////////////////////////////////////////
//		Description:	This Funcition will invoke the SGI utility "ic"
///////////////////////////////////////////////////////////////////////////////////
void CSndCompDlg::ComplieSounds(CWnd *pTelnetWnd)
{
	CString		CommandStr;
	TypeString(pTelnetWnd, "make\n");
	TypeString(pTelnetWnd, "cp sfx.tbl .. \n");
	TypeString(pTelnetWnd, "cp sfx.ctl .. \n");

}

///////////////////////////////////////////////////////////////////////////////////
//		Function: void CSndCompDlg::TypeString(CWnd *pTargetWnd, CString String)
///////////////////////////////////////////////////////////////////////////////////
//		Description:	
///////////////////////////////////////////////////////////////////////////////////
void CSndCompDlg::TypeString(CWnd *pTargetWnd, CString String)
{
   int i, numb = String.GetLength();
   for (i=0; i<numb; i++)
   {
      Sleep(7);

      char ch = String[i];

      if (ch == ' ')
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_SPACE, 0);
      }
		else if (ch == '-')
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_SUBTRACT, 0);
      }
      else if (ch == '/')
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_DIVIDE, 0);
      }
      else if (ch == '.')
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_DECIMAL, 0);
      }
      else if (ch == '\n')
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_RETURN, 0);
         Sleep(500);
      }
      else if ((ch >= 'a') && (ch <= 'z'))
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, ((WPARAM) ch) + ('A' - 'a'), 0);
      }
      else if ((ch >= 'A') && (ch <= 'Z'))
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) VK_SHIFT, 0);
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) ch, 0);
         pTargetWnd->PostMessage(WM_KEYUP, (WPARAM) VK_SHIFT, (1UL << 30) | (1UL << 31));
      }
      else
      {
         pTargetWnd->PostMessage(WM_KEYDOWN, (WPARAM) ch, 0);
      }
   }
}



void CSndCompDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSndCompDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSndCompDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
