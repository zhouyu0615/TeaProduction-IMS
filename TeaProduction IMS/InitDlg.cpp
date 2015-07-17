// InitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// InitDlg �Ի���

IMPLEMENT_DYNAMIC(InitDlg, CDialog)

InitDlg::InitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InitDlg::IDD, pParent)
{
	m_IdInit = 1;
}

InitDlg::~InitDlg()
{
}

void InitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INIT, m_list_init);
}


BEGIN_MESSAGE_MAP(InitDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_ADDUSER, &InitDlg::OnBnClickedBtAdduser)
	ON_BN_CLICKED(IDC_BT_ADDLINE, &InitDlg::OnBnClickedBtAddline)
	ON_BN_CLICKED(IDC_BT_ADDMODULE, &InitDlg::OnBnClickedBtAddmodule)
	ON_BN_CLICKED(IDC_BT_ADDDEVICE, &InitDlg::OnBnClickedBtAdddevice)
	ON_BN_CLICKED(IDC_BT_ADDPLC, &InitDlg::OnBnClickedBtAddplc)
	ON_BN_CLICKED(IDC_BT_FORMULA, &InitDlg::OnBnClickedBtFormula)
	ON_BN_CLICKED(IDC_BT_INITADD, &InitDlg::OnBnClickedBtInitadd)
	ON_BN_CLICKED(IDC_BT_FINISH, &InitDlg::OnBnClickedBtFinish)
	ON_BN_CLICKED(IDC_BUTTON3, &InitDlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &InitDlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDCANCEL, &InitDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_INIT, &InitDlg::OnNMClickListInit)
	ON_BN_CLICKED(IDC_BT_EDIT, &InitDlg::OnBnClickedBtEdit)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_INIT, &InitDlg::OnNMRClickListInit)
END_MESSAGE_MAP()


// InitDlg ��Ϣ�������


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	//�����û��������Ӱ�ť��������Ӧ���õ���ʼ������//

	//���������������Ϊ�գ�����д������������//
	int nLineOfCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();   //���COMBO1������ǰ���е�����//
	if (!m_vLine.empty() && nLineOfCombo1 < 1)                                  //����Ѿ��������������Ϣ����û����д������������//
		for (int k = 0; k < m_vLine.size(); k += 3)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_vLine[k]));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		}
	

	//�����б�ؼ����//
	CRect rect1;
	m_list_init.GetWindowRect(&rect1);
	m_list_init.SetExtendedStyle(m_list_init.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE | LVS_SHOWSELALWAYS);

	if (!m_vUser.empty() && !m_vLine.empty() && !m_vModule.empty()) //����Ѿ�������û��������ߡ�ģ�飬��ʹ���������ͷ����ť����//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	//����б�//
	m_list_init.DeleteAllItems();    
	CHeaderCtrl *pmyHeaderCtrl= m_list_init.GetHeaderCtrl();
    int nCount = pmyHeaderCtrl->GetItemCount();
	for(int i=nCount-1;i>=0;i--)
	    m_list_init.DeleteColumn(i);	

	int nTemp = 0;
	switch (m_IdInit){
	case 1:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("����û�"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("�û��б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("�û�����"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("��¼���룺"));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("�ͻ����룺"));		
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("��ע˵����"));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
		//��ʼ���б���//
		//�б�༭//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width()/14, -1);
		m_list_init.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect1.Width()/14*3, -1);
		m_list_init.InsertColumn(3, _T("��¼����"), LVCFMT_CENTER, rect1.Width()/14*3, -1);
		m_list_init.InsertColumn(4, _T("�ͻ�����"), LVCFMT_CENTER, rect1.Width()/14*2, -1);
		m_list_init.InsertColumn(5, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width()/14*5, -1);
		//��д������//
		nTemp = m_vUser.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;    //�б��Ԫ�ص��б�//
		    int nY = 0;    //�б��Ԫ�ص��б�//
			int nLine = nTemp/4;  //������//
			for (int n=1;n<nLine+1;n++)
			{
				CString str;
                str.Format("%d",n);
				m_list_init.InsertItem(n-1, _T(""));
				m_list_init.SetItemText(n-1, 1, _T(str));
			}
			for(int n=0;n<=nTemp-1;n++)
			{
				nX = n/4;
				nY = n%4+2;
				m_list_init.SetItemText(nX, nY, _T(m_vUser[n]));
			}
			break;
		}
		
	case 2:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("���������"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("�������б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("���������ƣ�"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("���ܲ�����"));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("��ע˵����"));

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width()/10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width()/10*4, -1);
		m_list_init.InsertColumn(3, _T("���ܲ���"), LVCFMT_CENTER, rect1.Width()/10*2, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		//��д������//
		nTemp = m_vLine.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;
		    int nY = 0;
			int nLine = nTemp/3;
			for (int n=1;n<nLine+1;n++)
			{
				CString str;
                str.Format("%d",n);
				m_list_init.InsertItem(n-1, _T(""));
				m_list_init.SetItemText(n-1, 1, _T(str));
			}
			for(int n=0;n<=nTemp-1;n++)
			{
				nX = n/3;
				nY = n%3+2;
				m_list_init.SetItemText(nX, nY, _T(m_vLine[n]));
			}
			break;
		}
	case 3:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("��ӹ���ģ��"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("����ģ���б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("���������ߣ�"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("����ģ�����ƣ�"));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("��ע˵����"));

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width()/10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		m_list_init.InsertColumn(3, _T("����ģ������"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width()/10*3, -1);

		//��д������//
		nTemp = m_vModule.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;
		    int nY = 0;
			int nLine = nTemp/3;
			for (int n=1;n<nLine+1;n++)
			{
				CString str;
                str.Format("%d",n);
				m_list_init.InsertItem(n-1, _T(""));
				m_list_init.SetItemText(n-1, 1, _T(str));
			}
			for(int n=0;n<=nTemp-1;n++)
			{
				nX = n/3;
				nY = n%3+2;
				m_list_init.SetItemText(nX, nY, _T(m_vModule[n]));
			}
			break;
		}
	case 4:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("����豸"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("�豸�б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("���������ߣ�"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("��������ģ�飺"));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("�豸���ƣ�"));		
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("�豸���ͣ�"));
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);

		if(((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount()>0)
		{
		    if(((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount()>0)    //���COMBO2�������ݣ������//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		    CString str1;
		    ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,str1);//�õ�COMBO1��ǰѡ����Ŀ//
			for (int i=0; i<m_vModule.size(); i+=3)			           //��Ӧ��дCOMBO2����//
			   if(m_vModule[i]==str1)
			   {
				   ((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vModule[i+1]));
				   ((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
			   }	
		}
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�༭��ͷ//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width()/11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(4, _T("�豸����"), LVCFMT_CENTER, rect1.Width()/11*2, -1);
		m_list_init.InsertColumn(5, _T("�豸����"), LVCFMT_CENTER, rect1.Width()/11*2, -1);

		//��д������//
		nTemp = m_vDevice.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;
		    int nY = 0;
			int nLine = nTemp/4;
			for (int n=1;n<nLine+1;n++)
			{
				CString str;
                str.Format("%d",n);
				m_list_init.InsertItem(n-1, _T(""));
				m_list_init.SetItemText(n-1, 1, _T(str));
			}
			for(int n=0;n<=nTemp-1;n++)
			{
				nX = n/4;
				nY = n%4+2;
				m_list_init.SetItemText(nX, nY, _T(m_vDevice[n]));
			}
			break;
		}
	
	case 5:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("���PLC"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("PLC�б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("���������ߣ�"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("PLC���ƣ�"));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("�˿ڣ�IP����"));		
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("��ע˵����"));
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�б�༭//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width()/11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(3, _T("PLC����"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(4, _T("�˿ڣ�IP��"), LVCFMT_CENTER, rect1.Width()/11*2, -1);
		m_list_init.InsertColumn(5, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width()/11*2, -1);

		//��д������//
		nTemp = m_vPlc.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;
		    int nY = 0;
			int nLine = nTemp/4;
			for (int n=1;n<nLine+1;n++)
			{
				CString str;
                str.Format("%d",n);
				m_list_init.InsertItem(n-1, _T(""));
				m_list_init.SetItemText(n-1, 1, _T(str));
			}
			for(int n=0;n<=nTemp-1;n++)
			{
				nX = n/4;
				nY = n%4+2;
				m_list_init.SetItemText(nX, nY, _T(m_vPlc[n]));
			}
			break;
		}
	case 6:
		//��ʼ���༭��//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("�������ͷ"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("����ͷ�б�"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("���������ߣ�"));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("��������ģ�飺"));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("����ͷ���ƣ�"));
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("�˿ڣ�"));
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);

		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount()>0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount()>0)    //���COMBO2�������ݣ������//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, str1);//�õ�COMBO1��ǰѡ����Ŀ//
			for (int i = 0; i<m_vModule.size(); i += 3)			           //��Ӧ��дCOMBO2����//
				if (m_vModule[i] == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vModule[i + 1]));
					((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
				}
		}
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�༭��ͷ//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("����ͷ����"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("�˿�"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);

		//��д������//
		nTemp = m_vCamera.size();
		if (nTemp == 0)
			break;
		else
		{
			int nX = 0;
			int nY = 0;
			int nLine = nTemp / 4;
			for (int n = 1; n<nLine + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= nTemp - 1; n++)
			{
				nX = n / 4;
				nY = n % 4 + 2;
				m_list_init.SetItemText(nX, nY, _T(m_vCamera[n]));
			}
			break;
		}
		
	default:
		AfxMessageBox(_T("ϵͳ����"));
		CDialog::OnCancel();
		break;
	}



	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


int InitDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


BOOL InitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��




	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void InitDlg::OnBnClickedBtAdduser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_IdInit!=1)
	{
	    GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T("")); 
	}
	m_IdInit = 1;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
    }
	if (m_IdInit!=2)
	{
	    GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T("")); 
	}
	m_IdInit = 2;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddmodule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
    }
	if (m_IdInit!=3)
	{
	    GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T("")); 
	}
	m_IdInit = 3;
	OnPaint();
}


void InitDlg::OnBnClickedBtAdddevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
    }
	if(m_vModule.empty())
	{
	    AfxMessageBox(_T("������ӹ���ģ�飡"));
		return;
	}
	if (m_IdInit!=4)
	{
	    GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T("")); 
	}
	m_IdInit = 4;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddplc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
    }
	if (m_IdInit!=5)
	{
	    GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T("")); 
	}
	m_IdInit = 5;
	OnPaint();
}

//���������ͷ����Ӧ����//
void InitDlg::OnBnClickedBtFormula()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_IdInit != 6)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	
	m_IdInit = 6;
	OnPaint();
}


//��ʼ�����桰��ӡ���ť����Ӧ����//
void InitDlg::OnBnClickedBtInitadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strText1,strText2,strText3,strText4;
	int nTemp;
	switch(m_IdInit){
	case 1:
        if(!m_vUser.empty())            //�ж��Ƿ�����ӹ��û�
			{
				AfxMessageBox(_T("�Ƿ��������û��Ѵ�����"));
				return;
		    }
		GetDlgItem(IDC_EDIT1)->GetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty())
		{ 
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		m_vUser.push_back(strText1);
		m_vUser.push_back(strText2);
		m_vUser.push_back(strText3);
		m_vUser.push_back(strText4);
		break;
	case 2:
		GetDlgItem(IDC_EDIT1)->GetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);

		if(!m_vLine.empty())                 //���������������Ƿ��Ѿ�����//
			for(int q=0;q<m_vLine.size();q+=3)
			   if(strText1==m_vLine[q])
			   {
				   AfxMessageBox(_T("�Ƿ��������������������Ѵ��ڣ�"));
				   return;
			   }

		if (strText1.IsEmpty() || strText2.IsEmpty())
		{ 
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		m_vLine.push_back(strText1);
		m_vLine.push_back(strText2);
		m_vLine.push_back(strText3);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(strText1));//����ӵ�������¼�뵽COMBO1//
	    ((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		break;
	case 3:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		if (strText1.IsEmpty() || strText2.IsEmpty())                   //�ж���¼�빤��ģ����Ϣ�Ƿ���ȫ//
		{ 
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		m_vModule.push_back(strText1);   //��¼�����Ϣд���Ӧ����//
		m_vModule.push_back(strText2);
		m_vModule.push_back(strText3);

		break;
	case 4:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //���������������Ƹ�ֵ��text1//
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(nTemp,strText2);  //����������ģ�����Ƹ�ֵ��text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() || strText4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{ 
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		m_vDevice.push_back(strText1);         //����ӵ���Ϣ¼�뵽����//
		m_vDevice.push_back(strText2);
		m_vDevice.push_back(strText3);
		m_vDevice.push_back(strText4);
		break;
	case 5:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() )  //�ж�¼����Ϣ�Ƿ�����//
		{ 
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		m_vPlc.push_back(strText1);         //����ӵ���Ϣ¼�뵽����//
		m_vPlc.push_back(strText2);
		m_vPlc.push_back(strText3);
		m_vPlc.push_back(strText4);
		break;

	case 6:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, strText1);  //���������������Ƹ�ֵ��text1//
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(nTemp, strText2);  //����������ģ�����Ƹ�ֵ��text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() || strText4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		m_vCamera.push_back(strText1);         //����ӵ���Ϣ¼�뵽����//
		m_vCamera.push_back(strText2);
		m_vCamera.push_back(strText3);
		m_vCamera.push_back(strText4);
		break;

	default:
		break;
	}
	OnPaint();
}

//����ɡ���ť����Ӧ����//
void InitDlg::OnBnClickedBtFinish()
{
	// TODO:
	if(!m_vUser.empty() && !m_vLine.empty() && !m_vPlc.empty() && !m_vModule.empty() && !m_vDevice.empty())
		{
			LoginDlg::s_bIsInit = true;
			CDialog::OnOK();
	    }
	else
		AfxMessageBox(_T("��ʼ����Ϣ�����ƣ��޷�ִ�иò�����"));
}


void InitDlg::OnBnClickedButton3()
{
	// TODO: 

	CDialog::OnOK();
}


void InitDlg::OnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnPaint();
}


void InitDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

//�б��ؼ�������Ӧ����������б��ؼ�ĳ��ʱ����������Ϣ��ʾ�ڱ༭��//
void InitDlg::OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_nItem = -1; 

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	m_list_init.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CString strText1, strText2, strText3, strText4;   //�ĸ���ʱ�����������ݴ���б���ȡ����Ϣ//
	int nCombo1,nCombo2;     //�б��ѡ����Ŀ����combo1��2������Ӧ��λ��//
	switch (m_IdInit)
	{
	case 1:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		strText4 = m_list_init.GetItemText(m_nItem, 5);
		GetDlgItem(IDC_EDIT1)->SetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strText4);
		break;
	case 2:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		GetDlgItem(IDC_EDIT1)->SetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		break;
	case 3:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		nCombo1=((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, strText1);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo1);
		break;
	case 4:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		strText4 = m_list_init.GetItemText(m_nItem, 5);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strText4);
		nCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, strText1);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo1);
		nCombo2 = ((CComboBox*)GetDlgItem(IDC_COMBO2))->FindStringExact(0, strText2);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(nCombo2);
		break;
	case 5:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		strText4 = m_list_init.GetItemText(m_nItem, 5);
		nCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, strText1);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo1);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strText4);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		break;
	case 6:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		strText4 = m_list_init.GetItemText(m_nItem, 5);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strText4);
		nCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, strText1);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo1);
		nCombo2 = ((CComboBox*)GetDlgItem(IDC_COMBO2))->FindStringExact(0, strText2);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(nCombo2);
		break;
	default:
		break;	
	}
	*pResult = 0;
}

//���޸ġ���ť����Ӧ����//
void InitDlg::OnBnClickedBtEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}

//�һ��б�����Ӧ����//
void InitDlg::OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
 	int index = pNMItemActivate->iItem;  //�û��һ����б�//
	if (index == -1)
		return;
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);//�õ���괦//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	if (nItem1>0)
	{
		int nResult;
		switch (m_IdInit)
		{
		case 1:
		    nResult = MessageBox(_T("�ò�����ɾ���û��������������豸���Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
			if (nResult == IDYES)
			{
				std::vector <CString>().swap(m_vUser);    //�����������С����������//
				std::vector <CString>().swap(m_vLine);
				std::vector <CString>().swap(m_vModule);
				std::vector <CString>().swap(m_vDevice);
				std::vector <CString>().swap(m_vPlc);
				std::vector <CString>().swap(m_vCamera);
				GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
				OnPaint();                                //�ػ洰��//
			} 
	        break;
		case 2:
		default:
			break;
		}
	}
	*pResult = 0;
}
