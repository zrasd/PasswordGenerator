
// PasswordGeneratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PasswordGenerator.h"
#include "PasswordGeneratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPasswordGeneratorDlg �Ի���



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


// CPasswordGeneratorDlg ��Ϣ�������

BOOL CPasswordGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPasswordGeneratorDlg::OnBnClickedButtonGenerate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	char m;
	char *password = new char[PasswordLength+1];
	if (BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		MessageBox(_T("�빴ѡ��ѡ��"));
		return;
	}


	//1,2,3
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_BigLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SmallLetter) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_Number)
		&& BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK_Symbol))
	{
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
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
		// ��ѡ
		for (int i = 0; i < PasswordLength; i++)
		{
			loop14:m = (rand() % 95) + 33;
			if ((m>32 && m<48||m>58&&m<65||m>90&&m<97||m>122&&m<127))
				password[i] = m;
			else goto loop14;
		}

	}
  	password[PasswordLength] = '\0';                                     //����������Ҫ�ֶ���ӽ������
	PasswordList = password;                                      // char to CString ��ֱ�Ӹ�ֵ
	UpdateData(false);
}
