
// TriggerExplainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TriggerExplain.h"
#include "TriggerExplainDlg.h"
#include "afxdialogex.h"
#include "Des.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTriggerExplainDlg 对话框




CTriggerExplainDlg::CTriggerExplainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTriggerExplainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTriggerExplainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_combo);
}

BEGIN_MESSAGE_MAP(CTriggerExplainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTriggerExplainDlg::OnBnClickedOk)
	ON_WM_CHAR()
	ON_EN_CHANGE(IDC_CIPHER_EDIT, &CTriggerExplainDlg::OnEnChangeCipherEdit)
END_MESSAGE_MAP()


// CTriggerExplainDlg 消息处理程序

BOOL CTriggerExplainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	int Result = GetPrivateProfileInt(FileCount,Count,0,InfoPath);
	if(Result == 0)
	{
		Result = 3;
		IntInfoFile();
		::MessageBox( NULL,_T("欢迎使用触发解析工具！") , TEXT("提示") ,MB_OK);
	}
	InitCombo(Result);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTriggerExplainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTriggerExplainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTriggerExplainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CTriggerExplainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_CHAR)

		if(GetDlgItem(IDC_CIPHER_EDIT)==GetFocus())
		{
			short nks = GetKeyState(VK_CONTROL);
			if (nks & 0x8000)
			{
				return CDialog::PreTranslateMessage(pMsg);
			}

			if ((pMsg->wParam >= 0x30 && pMsg->wParam <= 0x39) 
				||(pMsg->wParam >= 'a' && pMsg->wParam <= 'f') 
				||(pMsg->wParam >= 'A' && pMsg->wParam <= 'F') 
				||(pMsg->wParam == 0x08) ||(pMsg->wParam == 0x20))
			{
				return CDialog::PreTranslateMessage(pMsg);
			}
			else
			{
				MessageBeep(-1);
				pMsg->wParam=NULL;
			}
		}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTriggerExplainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	DES des;
	CString cipher;
	unsigned char data[9];
	unsigned char key[8] = {0x56 ,0x29 ,0x88 ,0x54 ,0x75 ,0x74 ,0x62 ,0x80};
	//unsigned char key[8] = {0x31 ,0x31 ,0x31 ,0x31 ,0x31 ,0x31 ,0x31 ,0x31};

	GetDlgItemText(IDC_CIPHER_EDIT,cipher);
	cipher.Replace(_T(" "),_T(""));//删除字符串中的空格

	if(cipher == "")
	{
		MessageBox( TEXT("请输入终端密文提示信息！") , TEXT("提示") ,MB_OK);
		return;
	}
	else if(cipher.GetLength() != 16)
	{
		MessageBox( TEXT("输入终端密文长度错误！") , TEXT("提示") ,MB_OK);
		return;
	}

	GetCStringHex(cipher,cipher.GetLength(),data);
	des.DataAlgorithm(1,key,8,data,8);

	cipher.Format(_T("%02X%02X%02X%02X %02X%02X%02X%02X\r\n\r\n")
		,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);

	ExplainTriggerInfo(cipher.Left(8),cipher);
	SetDlgItemText(IDC_INFO_EDIT,cipher);
	//CDialogEx::OnOK();
	return;
}

/*
解释触发信息，并返回在字符串显示
in
	data:触发的字符串（8000...）
	info:需要显示的前半部分
out
	info：需要显示的字符串

bit31	bit30	bit29	bit28	bit27	bit26	bit25	bit24   bit23  bit22-bit16	bit15-bit0
MMK丢失	高温	低温	高压	低压	高频	低频	预留    小电池    预留	    mesh相关
*/
int CTriggerExplainDlg::ExplainTriggerInfo(CString data,CString& info)
{
	char i;
	int nSel;
	CString prompt,TypeNum,strType,strType1;
	unsigned int trigger;// = _ttoi(data);
	swscanf_s(data,_T("%08x"),&trigger);

	nSel = m_combo.GetCurSel();//获取combo列表
	TypeNum.Format(_T("Type%d"),nSel);//机器号
	for(i = 0;i < 32;i++)
	{
		strType.Format(_T("Bit%d"),i);//
		::GetPrivateProfileString(TypeNum,strType,_T("NULL"), strType1.GetBuffer(MAX_PATH),MAX_PATH,InfoPath);
		if(((trigger >> i)&0x00000001) != 0)
		{
			info += strType1.GetBuffer(0);
			info += "\r\n";
		}
	}
#if 0
	if(((trigger >> 23)&0x00000001) != 0)
	{
		info += "小电池触发\r\n";
	}
	for(i = 0;i < 16;i++)
	{
		if(((trigger >> i)&0x00000001) != 0)
		{
			prompt.Format(_T("SD%d触发\r\n"),i);
			info += prompt;
		}
	}
	/*bit24、bit16~bit22预留*/
	if((((trigger >> 16)&0x0000007F) != 0)||(((trigger >> 24)&0x00000001) != 0))
	{
		info += "bit24、bit16~bit22预留\r\n";
	}
	if(((trigger >> 25)&0x00000001) != 0)
	{
		info += "低频触发\r\n";
	}
	if(((trigger >> 26)&0x00000001) != 0)
	{
		info += "高频触发\r\n";
	}
	if(((trigger >> 27)&0x00000001) != 0)
	{
		info += "低压触发\r\n";
	}
	if(((trigger >> 28)&0x00000001) != 0)
	{
		info += "高压触发\r\n";
	}
	if(((trigger >> 29)&0x00000001) != 0)
	{
		info += "低温触发\r\n";
	}
	if(((trigger >> 30)&0x00000001) != 0)
	{
		info += "高温触发\r\n";
	}
	if(((trigger >> 31)&0x00000001) != 0)
	{
		info += "MMK丢失\r\n";
	}
#endif
	return 0;
}


/*
获取CString的Hex数据
in
	string:输入的字符串
	stringlen：输入字符串的长度（必须是偶数）
out
	data：输出的data
*/

int CTriggerExplainDlg::GetCStringHex(CString string,int stringlen,unsigned char *data)
{
	int i;
	CString sdata;

	if(stringlen%2 != 0)
		return -1;
	for(i = 0;i < (stringlen/2);i++)
	{
		//data[i] = _ttoi(string.Mid(i*2,2));
		sdata = string.Mid(i*2,2);
		swscanf_s(sdata,_T("%02x"),&data[i]);
	}
	return 0;
}




void CTriggerExplainDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}


void CTriggerExplainDlg::OnEnChangeCipherEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString str;
	GetDlgItemText(IDC_CIPHER_EDIT,str);
	str.Replace(_T(" "),_T(""));
	int len = str.GetLength();
	str.Format(_T("长度:%d"),len);
	SetDlgItemText(IDC_SHOWLEN_STATIC,str);	
	// TODO:  在此添加控件通知处理程序代码
}


/*
初始化配置文件
默认只有G21、K205s和K102s三个

K102s、K205s
bit31	bit30	bit29	bit28	bit27	bit26	bit25	bit24   bit23  bit22-bit16	bit15-bit0
MMK丢失	高温	低温	高压	低压	高频	低频	预留    小电池    预留	    mesh相关

G21
bit31	 bit23    bit9-bit8	       bit7-bit0  other
MMK丢失	 小电池  动态静态总标志	    mesh相关   预留
*/
int CTriggerExplainDlg::IntInfoFile(void)
{
	int nCount=3,i,j;//nCount初始化的机器个数
	CString strTemp,strTemp1,strType;
	CString type[3] = {_T("K102s"),_T("K205s"),_T("G21")};

	for(j = 0; j < 2 ;j++)//初始化K205s、K102s
	{
		strType.Format(_T("Type%d"),j);//机器号
		::WritePrivateProfileString(strType,_T("machine model"),type[j],InfoPath);
		for(i = 0;i < 32 ;i++)
		{
			if(i < 16)
			{
				strTemp.Format(_T("SD%d触发"),i);
			}
			else if(((i >= 16)&&(i <= 22))||(i == 24))
			{
				strTemp = "bit16~bit22、bit24预留";
			}
			else if(i == 23)
			{
				strTemp = "小电池触发";
			}
			else if(i == 25)
			{
				strTemp = "低频触发";
			}
			else if(i == 26)
			{
				strTemp = "高频触发";
			}
			else if(i == 27)
			{
				strTemp = "低压触发";
			}
			else if(i == 28)
			{
				strTemp = "高压触发";
			}
			else if(i == 29)
			{
				strTemp = "低温触发";
			}
			else if(i == 30)
			{
				strTemp = "高温触发";
			}
			else if(i == 31)
			{
				strTemp = "MMK丢失";
			}
			strTemp1.Format(_T("Bit%d"),i);//32字节
			::WritePrivateProfileString(strType,strTemp1,strTemp,InfoPath);
		}
	}

	strType.Format(_T("Type%d"),j);//G21机器号
	::WritePrivateProfileString(strType,_T("machine model"),type[j],InfoPath);
	for(i = 0;i < 32 ;i++)
	{
		if(i < 8)
		{
			strTemp.Format(_T("SD%d触发"),i);
		}
		else if(i == 8)
		{
			strTemp = "有静态触发";
		}
		else if(i == 9)
		{
			strTemp = "有动态触发";
		}
		else if(i == 23)
		{
			strTemp = "小电池触发";
		}
		else if(i == 31)
		{
			strTemp = "MMK丢失";
		}
		else
		{
			strTemp = "未定义";
		}
		strTemp1.Format(_T("Bit%d"),i);//32字节
		::WritePrivateProfileString(strType,strTemp1,strTemp,InfoPath);
	}

	strTemp.Format(_T("%d"),nCount);//32字节
	::WritePrivateProfileString(FileCount,Count,strTemp,InfoPath);
	return 0;
}

/*
初始化combo控件
*/
int CTriggerExplainDlg::InitCombo(int Result)
{
	int i;
	CString TypeNum,strType;

	for(i = 0;i < Result;i++)
	{
		TypeNum.Format(_T("Type%d"),i);//机器号
		::GetPrivateProfileString(TypeNum,_T("machine model"),_T("NULL"), strType.GetBuffer(MAX_PATH),MAX_PATH,InfoPath);
		m_combo.AddString(strType);
	}

	m_combo.SetCurSel(0);// 默认选择第一项   
	return 0;
}

