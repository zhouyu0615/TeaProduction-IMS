
// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

bool LoginDlg::userright = 0;      //��ʼ��ȫ�־�̬����:�û�Ȩ�ޱ�ʶ��//
bool LoginDlg::isinit = false;    //��ʼ������//
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// LoginDlg �Ի���




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


// LoginDlg ��Ϣ�������

BOOL LoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ��Ȩ����Ͽ�
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("����Ա"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->AddString(_T("����Ա"));
	((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void LoginDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR LoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�����¼��ť���ж��û��������뼰Ȩ�ޣ�������Ӧ��һ����������//
void LoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	userright = ((CComboBox*)GetDlgItem(IDC_COMBO_USERRIGHT))->GetCurSel();//���û�Ȩ����Ͽ�ĵ�ǰѡ�����userright//
	
	if (isinit)
	{
	    ShowWindow(SW_HIDE);                //���ص�½����//
		if (maindlg.DoModal()==IDCANCEL)     //���ϵͳ�ѳ�ʼ��������������//
			CDialog::OnOK();   
		else
			ShowWindow(SW_SHOW);
	}
	else
	{
	   if (userright==0)             //ϵͳδ��ʼ�������û�Ȩ��Ϊ��ͨ����Ա//
		   {
			   AfxMessageBox(_T("ϵͳ��δ��ʼ�����޷���¼������ϵ����Ա��"));
	       }
	   else
	   {
		   ShowWindow(SW_HIDE);
		   if (initdlg.DoModal()==IDCANCEL)      //������ʼ�����ý���//
			  CDialog::OnOK();                   //���û�����˳�ʼ������ġ��˳�����ť�����˳�����//
		   else
		   {
			  if(isinit)
			  {
			      GetInitPara();                       //�û����ڳ�ʼ������¼�����Ƶ���Ϣ������Щ��Ϣ����������//
                  if (maindlg.DoModal()==IDCANCEL)     //���ϵͳ�ѳ�ʼ��������������//
			          CDialog::OnOK();                 //���û������������ġ��˳�����ť�����˳�����//
		          else
					  ShowWindow(SW_SHOW);             //���û������������ġ�ע��������ص���½����//
			  }
			  else
				  ShowWindow(SW_SHOW);                //���û�����˳�ʼ������ġ�ע����¼����ť����ص���½����//
		   }
	   }
	}
}

//����ʼ���������õĲ������ݵ�������Ի�����//
void LoginDlg::GetInitPara()
{
   maindlg.Vuser = initdlg.Vuser;
   maindlg.Vline = initdlg.Vline;
   maindlg.Vmudole = initdlg.Vmudole;
   maindlg.Vplc = initdlg.Vplc;
   maindlg.Vdevice = initdlg.Vdevice;
}

LRESULT LoginDlg::PopInitDlg(WPARAM wParam, LPARAM lParam)  //��������ʼ���Ի��򡱵���Ϣ��Ӧ����//
{
   if(initdlg.DoModal()==IDCANCEL)      //������ʼ���Ի���//
	 {                                                 //���û�����˳�ʼ��������˳���ť�����˳�����//
		 maindlg.PostMessageA(WM_CLOSE, 0, 0);
	     AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
      }
   GetInitPara();             //�������޸ĺ�ĳ�ʼ������//
   
    
   return true;
}