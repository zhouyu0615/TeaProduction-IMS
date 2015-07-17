// InitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "tbUser.h"
#include "tbProductionLine.h"



// InitDlg �Ի���

IMPLEMENT_DYNAMIC(InitDlg, CDialog)

InitDlg::InitDlg(CWnd* pParent /*=NULL*/)
: CDialog(InitDlg::IDD, pParent)
{
	id_init = 1;



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
	ON_STN_CLICKED(IDC_STATIC4, &InitDlg::OnStnClickedStatic4)
	
END_MESSAGE_MAP()


// InitDlg ��Ϣ�������


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//�����û��������Ӱ�ť��������Ӧ���õ���ʼ������//

	//���������������Ϊ�գ�����д������������//
	int lcombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();   //���COMBO1������ǰ���е�����//
	if (!m_vectProductionLine.empty() && lcombo1 < 1)                                  //����Ѿ��������������Ϣ����û����д������������//
		for (int k = 0; k < m_vectProductionLine.size(); k++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_vectProductionLine[k].m_strLineName));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		}

	//�����б�ؼ����//
	CRect rect1;
	m_list_init.GetWindowRect(&rect1);
	m_list_init.SetExtendedStyle(m_list_init.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//����б�//
	m_list_init.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_list_init.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_list_init.DeleteColumn(i);

	if (!m_vectUser.empty() && !m_vectProductionLine.empty() && !Vmudole.empty()) //����Ѿ�������û��������ߡ�ģ�飬��ʹ���������ͷ����ť����//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	int temp = 0;

	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	switch (id_init){
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
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 14, -1);
		m_list_init.InsertColumn(2, _T("�û���"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(3, _T("��¼����"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(4, _T("�ͻ�����"), LVCFMT_CENTER, rect1.Width() / 14 * 2, -1);
		m_list_init.InsertColumn(5, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 14 * 5, -1);
		//��д������//

	
		temp = m_vectUser.size();
		for (int i = 0; i < temp;i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str));
			m_list_init.SetItemText(i, 2, _T(m_vectUser[i].m_strUserName));
			m_list_init.SetItemText(i, 3, _T(m_vectUser[i].m_strUserPasswd));
			m_list_init.SetItemText(i, 4, _T(m_vectUser[i].m_strUserCode));
			m_list_init.SetItemText(i, 5, _T(m_vectUser[i].m_strNote));
		}	
		break;

/*		temp = Vuser.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 4;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 4;
				b = n % 4 + 2;
				m_list_init.SetItemText(a, b, _T(Vuser[n]));
			}
			break;
		}
*/

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
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 10 * 4, -1);
		m_list_init.InsertColumn(3, _T("���ܲ���"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		//��д������//


		temp = m_vectProductionLine.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_vectProductionLine[i].m_strLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectProductionLine[i].m_strCapacity));
			m_list_init.SetItemText(i, 4, _T(m_vectProductionLine[i].m_strDescription));			
		}
		break;


	
 /*		temp = Vline.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 3;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 3;
				b = n % 3 + 2;
				m_list_init.SetItemText(a, b, _T(Vline[n]));
			}
			break;
		}
 */

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
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(3, _T("����ģ������"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(4, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);

		//��д������//
		temp = m_vectProcessModule.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			//m_list_init.SetItemText(i, 2, _T(m_vectProcessModule[i].m_s));
			m_list_init.SetItemText(i, 3, _T(m_vectProcessModule[i].m_strModuleName));
			m_list_init.SetItemText(i, 4, _T(m_vectProcessModule[i].m_strDescription));
		}
		break;

/*		temp = Vmudole.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 3;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 3;
				b = n % 3 + 2;
				m_list_init.SetItemText(a, b, _T(Vmudole[n]));
			}
			break;
		}
*/
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

		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //���COMBO2�������ݣ������//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//�õ�COMBO1��ǰѡ����Ŀ//
			for (int i = 0; i < Vmudole.size(); i += 3)			           //��Ӧ��дCOMBO2����//
				if (Vmudole[i] == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(Vmudole[i + 1]));
					((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
				}
		}
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//��ʼ���б���//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //�༭��ͷ//
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("�豸����"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("�豸����"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);

		//��д������//
		temp = Vdevice.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 4;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 4;
				b = n % 4 + 2;
				m_list_init.SetItemText(a, b, _T(Vdevice[n]));
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
		m_list_init.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("����������"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("PLC����"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("�˿ڣ�IP��"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("��ע˵��"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);

		//��д������//
		temp = Vplc.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 4;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 4;
				b = n % 4 + 2;
				m_list_init.SetItemText(a, b, _T(Vplc[n]));
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

		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //���COMBO2�������ݣ������//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//�õ�COMBO1��ǰѡ����Ŀ//
			for (int i = 0; i < Vmudole.size(); i += 3)			           //��Ӧ��дCOMBO2����//
				if (Vmudole[i] == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(Vmudole[i + 1]));
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
		temp = Vcamera.size();
		if (temp == 0)
			break;
		else
		{
			int a = 0;
			int b = 0;
			int c = temp / 4;
			for (int n = 1; n < c + 1; n++)
			{
				CString str;
				str.Format("%d", n);
				m_list_init.InsertItem(n - 1, _T(""));
				m_list_init.SetItemText(n - 1, 1, _T(str));
			}
			for (int n = 0; n <= temp - 1; n++)
			{
				a = n / 4;
				b = n % 4 + 2;
				m_list_init.SetItemText(a, b, _T(Vcamera[n]));
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


	ReadUserFromDatabase();
	ReadProLineFromDatabase();



	OnPaint();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void InitDlg::OnBnClickedBtAdduser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (id_init != 1)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	id_init = 1;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (id_init != 2)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	id_init = 2;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddmodule()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (id_init != 3)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	id_init = 3;
	OnPaint();
}


void InitDlg::OnBnClickedBtAdddevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (Vmudole.empty())
	{
		AfxMessageBox(_T("������ӹ���ģ�飡"));
		return;
	}
	if (id_init != 4)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	id_init = 4;
	OnPaint();
}


void InitDlg::OnBnClickedBtAddplc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (id_init != 5)
	{
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	}
	id_init = 5;
	OnPaint();
}

//���������ͷ����Ӧ����//
void InitDlg::OnBnClickedBtFormula()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	id_init = 6;
	OnPaint();
}


//��ʼ�����桰��ӡ���ť����Ӧ����//
void InitDlg::OnBnClickedBtInitadd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString text1, text2, text3, text4;
	int temp;
	switch (id_init){
	case 1:
		if (!m_vectUser.empty())            //�ж��Ƿ�����ӹ��û�
		{
			AfxMessageBox(_T("�Ƿ��������û��Ѵ�����"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		Vuser.push_back(text1);
		Vuser.push_back(text2);
		Vuser.push_back(text3);
		Vuser.push_back(text4);



		SaveUserToDatabase();


		break;
	case 2:
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);

		if (!m_vectProductionLine.empty())                 //���������������Ƿ��Ѿ�����//
			for (int q = 0; q < m_vectProductionLine.size(); q++)
				if (text1 == m_vectProductionLine[q].m_strLineName)
				{
					AfxMessageBox(_T("�Ƿ��������������������Ѵ��ڣ�"));
					return;
				}

		if (text1.IsEmpty() || text2.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		Vline.push_back(text1);
		Vline.push_back(text2);
		Vline.push_back(text3);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(text1));//����ӵ�������¼�뵽COMBO1//
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);



		SaveProLineToDatabase();


		break;
	case 3:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		if (text1.IsEmpty() || text2.IsEmpty())                   //�ж���¼�빤��ģ����Ϣ�Ƿ���ȫ//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		Vmudole.push_back(text1);   //��¼�����Ϣд���Ӧ����//
		Vmudole.push_back(text2);
		Vmudole.push_back(text3);

		break;
	case 4:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //����������ģ�����Ƹ�ֵ��text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		Vdevice.push_back(text1);         //����ӵ���Ϣ¼�뵽����//
		Vdevice.push_back(text2);
		Vdevice.push_back(text3);
		Vdevice.push_back(text4);
		break;
	case 5:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		Vplc.push_back(text1);         //����ӵ���Ϣ¼�뵽����//
		Vplc.push_back(text2);
		Vplc.push_back(text3);
		Vplc.push_back(text4);
		break;

	case 6:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //����������ģ�����Ƹ�ֵ��text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		Vcamera.push_back(text1);         //����ӵ���Ϣ¼�뵽����//
		Vcamera.push_back(text2);
		Vcamera.push_back(text3);
		Vcamera.push_back(text4);
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
	if (!m_vectUser.empty() && !m_vectProductionLine.empty() && !Vplc.empty() && !m_vectProcessModule.empty() && !Vdevice.empty())
	{
		LoginDlg::isinit = true;
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


void InitDlg::OnStnClickedStatic4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void InitDlg::SaveUserToDatabase()
{
	CtbUser m_tbUserSet;
	try{
		if (m_tbUserSet.IsOpen())
			m_tbUserSet.Close();
		if (!m_tbUserSet.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString username, userpasswd, usercode, usernote;

	srand(time(NULL));
	int userId = rand();

	int offset = Vuser.size() % 4;
	username = Vuser[offset + 0];
	userpasswd = Vuser[offset + 1];
	usercode = Vuser[offset + 2];
	usernote = Vuser[offset + 3];

	if (m_tbUserSet.CanUpdate()){
		m_tbUserSet.AddNew();

		CTime time = CTime::GetCurrentTime();
		m_tbUserSet.m_Id = userId;
		m_tbUserSet.m_CreatedDateTime = time;
		m_tbUserSet.m_LastUpdatedDateTime = time;
		m_tbUserSet.m_UserName = username;
		m_tbUserSet.m_UserPassword = userpasswd;
		m_tbUserSet.m_UserCode = usercode;
		m_tbUserSet.m_Note = usernote;
		m_tbUserSet.Update();

	}
	m_tbUserSet.Close();
}


void InitDlg::ReadUserFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbUser order by Id"));

	CtbUser tbUser;
	try{
		if (tbUser.IsOpen())
			tbUser.Close();
		if (!tbUser.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	UserClass tempUser;



	if (!tbUser.IsEOF()){
		tbUser.MoveFirst();
		m_userId = tbUser.m_Id; //��ȡ���Ա���� Ψһ�� �û�ID
		Vuser.push_back((CString)tbUser.m_UserName);
		Vuser.push_back((CString)tbUser.m_UserPassword);
		Vuser.push_back((CString)tbUser.m_UserCode);
		Vuser.push_back(tbUser.m_Note);

		tempUser.m_UserId = tbUser.m_Id;
		tempUser.m_strUserName = tbUser.m_UserName;
		tempUser.m_strUserPasswd = tbUser.m_UserPassword;
		tempUser.m_strUserCode = tbUser.m_UserPassword;

		m_vectUser.push_back(tempUser);
		
	}

	tbUser.Close();

}


void InitDlg::SaveProLineToDatabase()
{

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strlineName, strCapacity, strDescription;

	srand(time(NULL));
	int lineId = rand();
	int length =(int) Vline.size();


	strlineName = Vline[length-3];
	strCapacity = Vline[length-2];
	strDescription = Vline[length-1];

	if (tbProductionLine.CanUpdate()){
		tbProductionLine.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProductionLine.m_Id = lineId;
		tbProductionLine.m_CreatedDateTime = time;
		tbProductionLine.m_LastUpdatedDateTime = time;
		tbProductionLine.m_LineName = strlineName;
		tbProductionLine.m_UserId = m_userId; //Ψһ�û�ID
		tbProductionLine.m_Capacity = strCapacity;
		tbProductionLine.m_Description = strDescription;
		tbProductionLine.Update();



	}

	tbProductionLine.Close();

}


void InitDlg::ReadProLineFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbProductionLine order by Id"));

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("�����ݿ�ʧ�ܣ�"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	ProductionLineClass tempProductionLine;
	tbProductionLine.MoveFirst();
	while (!tbProductionLine.IsEOF()){
		Vline.push_back((CString)tbProductionLine.m_LineName);
		Vline.push_back((CString)tbProductionLine.m_Capacity);
		Vline.push_back((CString)tbProductionLine.m_Description);

		tempProductionLine.m_Id = tbProductionLine.m_Id;
		tempProductionLine.m_strLineName = tbProductionLine.m_LineName;
		tempProductionLine.m_strCapacity = tbProductionLine.m_Capacity;
		tempProductionLine.m_strDescription = tbProductionLine.m_Description;
		
		m_vectProductionLine.push_back(tempProductionLine);
		tbProductionLine.MoveNext();
	}

	tbProductionLine.Close();

}




