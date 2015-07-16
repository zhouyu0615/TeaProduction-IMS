
// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

bool LoginDlg::userright = 0;      //初始化全局静态变量:用户权限标识符//
bool LoginDlg::isinit = false;    //初始化变量//
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


// LoginDlg 对话框




LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &LoginDlg::OnBnClickedOk)
	ON_MESSAGE(WM_POPINITDLG,PopInitDlg)
END_MESSAGE_MAP()


// LoginDlg 消息处理程序

BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	//初始化权限组合框
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("操作员"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("管理员"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void LoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void LoginDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR LoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击登录按钮后判断用户名、密码及权限，弹出对应下一步操作界面//
void LoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	userright = ((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->GetCurSel();//将用户权限组合框的当前选择读入userright//
	
	if (isinit)
	{
	    ShowWindow(SW_HIDE);                //隐藏登陆界面//
		if (maindlg.DoModal()==IDCANCEL)     //如果系统已初始化，弹出主界面//
			CDialog::OnOK();   
		else
			ShowWindow(SW_SHOW);
	}
	else
	{
	   if (userright==0)             //系统未初始化，且用户权限为普通操作员//
		   {
			   AfxMessageBox(_T("系统尚未初始化，无法登录，请联系技术员！"));
	       }
	   else
	   {
		   ShowWindow(SW_HIDE);
		   if (initdlg.DoModal()==IDCANCEL)      //弹出初始化设置界面//
			  CDialog::OnOK();                   //若用户点击了初始化界面的“退出”按钮，则退出程序//
		   else
		   {
			  if(isinit)
			  {
			      GetInitPara();                       //用户已在初始化界面录入完善的信息，将这些信息传给主界面//
                  if (maindlg.DoModal()==IDCANCEL)     //如果系统已初始化，弹出主界面//
			          CDialog::OnOK();                 //若用户点击了主界面的“退出”按钮，则退出程序//
		          else
					  ShowWindow(SW_SHOW);             //若用户点击了主界面的“注销”，则回到登陆界面//
			  }
			  else
				  ShowWindow(SW_SHOW);                //若用户点击了初始化界面的“注销登录”按钮，则回到登陆界面//
		   }
	   }
	}
}

//将初始化界面设置的参数传递到主界面对话框类//
void LoginDlg::GetInitPara()
{
   maindlg.Vuser = initdlg.Vuser;
   maindlg.Vline = initdlg.Vline;
   maindlg.Vmudole = initdlg.Vmudole;
   maindlg.Vplc = initdlg.Vplc;
   maindlg.Vdevice = initdlg.Vdevice;
}

LRESULT LoginDlg::PopInitDlg(WPARAM wParam, LPARAM lParam)  //“弹出初始化对话框”的消息响应函数//
{
   if(initdlg.DoModal()==IDCANCEL)      //弹出初始化对话框//
	 {                                                 //若用户点击了初始化界面的退出按钮，则退出程序//
		 maindlg.PostMessageA(WM_CLOSE, 0, 0);
	     AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
      }
   GetInitPara();             //传递新修改后的初始化参数//
   
    
   return true;
}