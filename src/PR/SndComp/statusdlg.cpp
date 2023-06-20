// statusdlg.cpp : implementation file
//

#include "stdafx.h"
#include "sndcomp.h"
#include "statusdlg.h"
#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void		AddDefaultExtension (char *SourceName, char *DestFile, char *ext) ;
extern CString	FileTable[];
extern int		FileFlags[];
extern int		NumFiles;


/////////////////////////////////////////////////////////////////////////////
// statusdlg dialog


statusdlg::statusdlg(CWnd* pParent /*=NULL*/)
	: CDialog(statusdlg::IDD, pParent)
{
	m_PaintHappened = FALSE;

	//{{AFX_DATA_INIT(statusdlg)
	m_statusmsg = _T("");
	//}}AFX_DATA_INIT
}


void statusdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(statusdlg)
	DDX_Control(pDX, IDC_STATUSLIST, m_ctlStatusList);
	DDX_Text(pDX, ID_PROMPT, m_statusmsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(statusdlg, CDialog)
	//{{AFX_MSG_MAP(statusdlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// statusdlg member functions

int statusdlg::CheckFileStatus(int *FileFlags, CString *FileTable, int NumFiles)
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
		//AddDefaultExtension (temp, DestName, "n64");
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
		}
	}

	return 0;
}	 


/////////////////////////////////////////////////////////////////////////////
// statusdlg message handlers



BOOL statusdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void statusdlg::OnPaint() 
{
	// TODO: Add your message handler code here
		
		// Do not call CDialog::OnPaint() for painting messages

	BOOL prevPaintHappened = m_PaintHappened;
	m_PaintHappened = TRUE;
	if (!prevPaintHappened)
		ProcessFile();
}

void statusdlg::ProcessFile() 
{
	static int CurrentFile = 0;
	CFileStatus		rStatus1;
	CFileStatus		rStatus2; 
	CFile				AIFFfile;
	CFile				CompFile;
	char 				DestName[128];
	char 				CompName[128];
	char				FileName[128];
	char 				temp[128];
	int				result, Sum1, Sum2;
	int				i;

#if 0
	for (i=0; i<10; i++)
	{
		char string[100];
		sprintf(string, "Rob %d", i);

		m_ctlStatusList.AddString(string);
		m_ctlStatusList.SetTopIndex(max(0, i - 5));
		UpdateWindow();

		Sleep(100);

	}
	
	
	OnCancel();

#else

	for(i = 0; i <  NumFiles; i++)
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
		}

		if(FileFlags[i] & FILE_MODIFIED)
		{	
			char string[256];
			sprintf(string, "%s:  MODIFIED", FileTable[i]);
			m_ctlStatusList.AddString(string);
			m_ctlStatusList.SetTopIndex(max(0, i - 5));
		}

		UpdateWindow();

	}

	Sleep(5000);
	OnCancel();

#endif
	
}

