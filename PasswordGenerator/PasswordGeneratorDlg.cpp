
// PasswordGeneratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PasswordGenerator.h"
#include "PasswordGeneratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPasswordGeneratorDlg 对话框



CPasswordGeneratorDlg::CPasswordGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PASSWORDGENERATOR_DIALOG, pParent)
	, PasswordLength(0)
	, PasswordList(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PassWordLength, PasswordLength);
	DDX_Text(pDX, IDC_EDIT_PasswordList, PasswordList);
}

BEGIN_MESSAGE_MAP(CPasswordGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Generate, &CPasswordGeneratorDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()


// CPasswordGeneratorDlg 消息处理程序

BOOL CPasswordGeneratorDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPasswordGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPasswordGeneratorDlg::OnPaint()
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
HCURSOR CPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPasswordGeneratorDlg::OnBnClickedButtonGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	char m;
	char *password = new char[PasswordLength+1];
	if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		MessageBox(_T("请勾选复选框！"));
		return;
	}


	//1,2,3
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop: m = (rand() % 95) + 33;
			if ((m>47 && m<58 || m>64 && m<91 || m>96 && m<123))
				password[i] = m;
			else goto loop;
		}

	}


	//1,2,3,4
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter)&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter)&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
				loop1:    m = (rand() % 95) + 33;
				if ((m>32&&m<127))
				password[i] = m;
				else goto loop1;
		}
			
	}

	
	//1,2,4
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop2: m = (rand() % 95) + 33;
			if ((m>32 && m<47 || m>57 && m<127))
				password[i] = m;
			else goto loop2;
		}

	}

	//2,3,4
	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop3: m = (rand() % 95) + 33;
			if ((m>32 && m<65 || m>90 && m<127))
				password[i] = m;
			else goto loop3;
		}

	}

	//1,3,4
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop4: m = (rand() % 95) + 33;
			if ((m>32 && m<97 || m>122 && m<127))
				password[i] = m;
			else goto loop4;
		}

	}


	//1,2

	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop5: m = (rand() % 95) + 33;
			if ((m>64 && m<91 || m>96 && m<123))
				password[i] = m;
			else goto loop5;
		}

	}

	//1,3

	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop6: m = (rand() % 95) + 33;
			if ((m>47 && m<58 || m>64 && m<91))
				password[i] = m;
			else goto loop6;
		}

	}

	//1,4

	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop7: m = (rand() % 95) + 33;
			if ((m>32 && m<48 || m>57 && m<97||m>122&&m<127))
				password[i] = m;
			else goto loop7;
		}

	}

	//2,3
	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop8: m = (rand() % 95) + 33;
			if ((m>47 && m<58 || m>96 && m<123))
				password[i] = m;
			else goto loop8;
		}

	}

	//2,4

	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop9:m = (rand() % 95) + 33;
			if ((m>32 && m<48 || m>57 && m<65 || m>90 && m<127))
				password[i] = m;
			else goto loop9;
		}

	}

	//3,4

	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop10:m = (rand() % 95) + 33;
			if ((m>32 && m<65 || m>90 && m<97 || m>122 && m<127))
				password[i] = m;
			else goto loop10;
		}

	}

	//1

	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop11:m = (rand() % 95) + 33;
			if ((m>64 && m<91))
				password[i] = m;
			else goto loop11;
		}

	}


	//2

	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop12:m = (rand() % 95) + 33;
			if ((m>96 && m<123))
				password[i] = m;
			else goto loop12;
		}

	}

	//3

	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop13:m = (rand() % 95) + 33;
			if ((m>47 && m<58))
				password[i] = m;
			else goto loop13;
		}

	}

	//4

	else if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// 勾选
		for (int i = 0; i < PasswordLength; i++)
		{
			loop14:m = (rand() % 95) + 33;
			if ((m>32 && m<48||m>58&&m<65||m>90&&m<97||m>122&&m<127))
				password[i] = m;
			else goto loop14;
		}

	}
  	password[PasswordLength] = '\0';                                     //编码问题需要手动添加结束标记
	PasswordList = password;                                      // char to CString 可直接赋值
	UpdateData(false);
}
