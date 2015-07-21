// InitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "tbUser.h"
#include "tbProductionLine.h"
#include "tbProcessModule.h"
#include "tbDevice.h"
#include "tbPLc.h"
#include "tbVideo.h"






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

	ON_NOTIFY(NM_CLICK, IDC_LIST_INIT, &InitDlg::OnNMClickListInit)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_INIT, &InitDlg::OnNMRClickListInit)
	ON_BN_CLICKED(IDC_BT_EDIT, &InitDlg::OnBnClickedBtEdit)
	ON_BN_CLICKED(IDC_BT_ADDPLCPARA, &InitDlg::OnBnClickedBtAddplcpara)
END_MESSAGE_MAP()


// InitDlg ��Ϣ�������


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//�����û��������Ӱ�ť��������Ӧ���õ���ʼ������//


	//����Ѿ��������������Ϣ����û����д������������//
	if (!m_dataPorvider.m_vectProductionLine.empty())  {
		((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
		for (int k = 0; k < m_dataPorvider.m_vectProductionLine.size(); k++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_dataPorvider.m_vectProductionLine[k].m_strLineName));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		}
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

	if (!m_dataPorvider.m_vectUser.empty()
		&& !m_dataPorvider.m_vectProductionLine.empty()
		&& !m_dataPorvider.m_vectProcessModule.empty()) //����Ѿ�������û��������ߡ�ģ�飬��ʹ���������ͷ����ť����//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	int temp = 0;

	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	switch (id_init){
	case USER_DATA_EDIT:
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


		temp = m_dataPorvider.m_vectUser.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str));
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectUser[i].m_strUserName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectUser[i].m_strUserPasswd));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectUser[i].m_strUserCode));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectUser[i].m_strNote));
		}
		break;


	case PRODUCTION_LINE_DATA_EDIT:
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


		temp = m_dataPorvider.m_vectProductionLine.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectProductionLine[i].m_strLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectProductionLine[i].m_strCapacity));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectProductionLine[i].m_strDescription));
		}
		break;


	case MODULE_DATA_EDIT:
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
		temp = m_dataPorvider.m_vectProcessModule.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectProcessModule[i].m_strDescription));
		}
		break;


	case DEVICE_DATA_EDIT:
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
			for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
				if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
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
		temp = m_dataPorvider.m_vectDevice.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectDevice[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectDevice[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectDevice[i].m_strDeviceName));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectDevice[i].m_strDeviceType));
		}
		break;

	case PLC_DATA_EDIT:
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
		temp = m_dataPorvider.m_vectPlc.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectPlc[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectPlc[i].m_strPlcName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectPlc[i].m_strPort));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectPlc[i].m_strDescription));
		}
		break;



	case VIDEO_DATA_EDIT:
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
			for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
				if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
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
		temp = m_dataPorvider.m_vectVideo.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //���
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectVideo[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectVideo[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectVideo[i].m_strVideoName));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectVideo[i].m_strPort));
		}
		break;




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


	m_dataPorvider.ReadUserFromDatabase();
	m_dataPorvider.ReadProLineFromDatabase();

	OnPaint();

	m_dataPorvider.ReadProModuleFromDatabase();
	m_dataPorvider.ReadPlcFromDatabase();
	m_dataPorvider.ReadDeviceFromDatabase();
	m_dataPorvider.ReadVideoFromDatabase();

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
	if (m_dataPorvider.m_vectUser.empty())
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
	if (m_dataPorvider.m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
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
	if (m_dataPorvider.m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("������������ߣ�"));
		return;
	}
	if (m_dataPorvider.m_vectProcessModule.empty())
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
	if (m_dataPorvider.m_vectUser.empty())
	{
		AfxMessageBox(_T("��δ�����û�����������û���"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
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

	UserClass tempUser;
	ProductionLineClass tempProLine;
	ProcessModuleClass tempProModule;
	DeviceClass tempDevice;
	PlcClass tempPlc;
	VideoClass tempVideo;


	switch (id_init){
	case USER_DATA_EDIT:
		if (!m_dataPorvider.m_vectUser.empty())            //�ж��Ƿ�����ӹ��û�
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

		tempUser.m_strUserName = text1;
		tempUser.m_strUserPasswd = text2;
		tempUser.m_strUserCode = text3;
		tempUser.m_strNote = text4;

		m_dataPorvider.m_vectUser.push_back(tempUser);

		m_dataPorvider.SaveUserToDatabase();

		break;
	case PRODUCTION_LINE_DATA_EDIT:
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);

		if (!m_dataPorvider.m_vectProductionLine.empty())                 //���������������Ƿ��Ѿ�����//
			for (int q = 0; q < m_dataPorvider.m_vectProductionLine.size(); q++)
				if (text1 == m_dataPorvider.m_vectProductionLine[q].m_strLineName)
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


		tempProLine.m_strLineName = text1;
		tempProLine.m_strCapacity = text2;
		tempProLine.m_strDescription = text3;

		m_dataPorvider.m_vectProductionLine.push_back(tempProLine);




		m_dataPorvider.SaveProLineToDatabase();


		break;
	case MODULE_DATA_EDIT:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		if (text1.IsEmpty() || text2.IsEmpty())                   //�ж���¼�빤��ģ����Ϣ�Ƿ���ȫ//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}

         //�����������¹���ģ�������Ƿ��Ѿ�����//
	     for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)
				if (text2 ==m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName)
				{
					if (text1==m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName)
					{
						AfxMessageBox(_T("�Ƿ����������������µ�ͬ������ģ���Ѵ��ڣ�"));
						return;
					}
					
				}
		 

		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));

		tempProModule.m_strProductionLineName = text1;
		tempProModule.m_strProcessModuleName = text2;
		tempProModule.m_strDescription = text3;


		m_dataPorvider.m_vectProcessModule.push_back(tempProModule);

		m_dataPorvider.SaveProModuleToDatabase();

		break;
	case DEVICE_DATA_EDIT:
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

		tempDevice.m_strProductionLineName = text1;
		tempDevice.m_strProcessModuleName = text2;
		tempDevice.m_strDeviceName = text3;
		tempDevice.m_strDeviceType = text4;

		m_dataPorvider.m_vectDevice.push_back(tempDevice);

		m_dataPorvider.SaveDeviceToDatabase();

		break;
	case PLC_DATA_EDIT:
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

		tempPlc.m_strProductionLineName = text1;
		tempPlc.m_strPlcName = text2;
		tempPlc.m_strPort = text3;
		tempPlc.m_strDescription = text4;

		//����ӵ���Ϣ¼�뵽����//
		m_dataPorvider.m_vectPlc.push_back(tempPlc);

		m_dataPorvider.SavePlcToDatabase();

	
		break;

	case VIDEO_DATA_EDIT:
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

		tempVideo.m_strProductionLineName = text1;
		tempVideo.m_strProcessModuleName = text2;
		tempVideo.m_strVideoName = text3;
		tempVideo.m_strPort = text4;

		//����ӵ���Ϣ¼�뵽����//
		m_dataPorvider.m_vectVideo.push_back(tempVideo);

		m_dataPorvider.SaveVideoToDatabase();

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
	if (!m_dataPorvider.m_vectUser.empty() && !m_dataPorvider.m_vectProductionLine.empty() && !m_dataPorvider.m_vectPlc.empty() && !m_dataPorvider.m_vectProcessModule.empty() && !m_dataPorvider.m_vectDevice.empty())
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
	int temp;
	if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //���COMBO2�������ݣ������//
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	CString str1;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//�õ�COMBO1��ǰѡ����Ŀ//
	for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //��Ӧ��дCOMBO2����//
		if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		}


	//OnPaint();
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








void InitDlg::OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	m_nItem = -1;

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	m_list_init.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CString strText1, strText2, strText3, strText4;   //�ĸ���ʱ�����������ݴ���б���ȡ����Ϣ//
	int nCombo1, nCombo2;     //�б��ѡ����Ŀ����combo1��2������Ӧ��λ��//
	switch (id_init)
	{
	case USER_DATA_EDIT:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		strText4 = m_list_init.GetItemText(m_nItem, 5);
		GetDlgItem(IDC_EDIT1)->SetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strText4);
		break;
	case PRODUCTION_LINE_DATA_EDIT:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		GetDlgItem(IDC_EDIT1)->SetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		break;
	case MODULE_DATA_EDIT:
		strText1 = m_list_init.GetItemText(m_nItem, 2);
		strText2 = m_list_init.GetItemText(m_nItem, 3);
		strText3 = m_list_init.GetItemText(m_nItem, 4);
		GetDlgItem(IDC_EDIT2)->SetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strText3);
		nCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, strText1);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo1);
		break;
	case DEVICE_DATA_EDIT:
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
	case PLC_DATA_EDIT:
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
	case VIDEO_DATA_EDIT:
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


}


void InitDlg::OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int index = pNMItemActivate->iItem;  //�û��һ����б�//
	if (index == -1)
		return;

	std::vector<ProductionLineClass>::iterator pProlineIter;
	std::vector<ProcessModuleClass>::iterator  pModuleIter;
	std::vector<DeviceClass>::iterator        pDeviceIter;
	std::vector<PlcClass>::iterator            pPlcIter;
	std::vector<VideoClass>::iterator		pVideoIter;

	CString tempProLineName, tempModuleName;

	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);//�õ���괦//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	if (nItem1 > 0)
	{
		int nResult;
		int strKey;
		switch (id_init)
		{
		case USER_DATA_EDIT:
			nResult = MessageBox(_T("�ò�����ɾ���û��������������豸���Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
			if (nResult == IDYES)
			{
				m_dataPorvider.DeleteDbTable(CDataProvider::tbUser);
				m_dataPorvider.DeleteDbTable(CDataProvider::tbProductionLine);
				m_dataPorvider.DeleteDbTable(CDataProvider::tbProcessModule);
				m_dataPorvider.DeleteDbTable(CDataProvider::tbDevice);
				m_dataPorvider.DeleteDbTable(CDataProvider::tbPLc);
				m_dataPorvider.DeleteDbTable(CDataProvider::tbVideo);

				m_dataPorvider.m_vectUser.clear();
				m_dataPorvider.m_vectProductionLine.clear();
				m_dataPorvider.m_vectProcessModule.clear();
				m_dataPorvider.m_vectDevice.clear();
				m_dataPorvider.m_vectPlc.clear();
				m_dataPorvider.m_vectVideo.clear();
				m_dataPorvider.m_vectPlcPara.clear();

				GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));

				OnPaint();                                //�ػ洰��//
			}
			break;
		case PRODUCTION_LINE_DATA_EDIT:

			nResult = MessageBox(_T("�ò�����ɾ������������������豸��PLC���豸���Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
			if (nResult == IDYES)
			{
				//ɾ�����ݿ��е�����
				m_dataPorvider.DeleteDbTableItem(CDataProvider::tbProductionLine,
					m_dataPorvider.m_vectProductionLine[m_nItem].m_Id);

				//ɾ�������������ߵĹ���ģ�飬�豸��PLC,����ͷ
				tempProLineName = m_dataPorvider.m_vectProductionLine[m_nItem].m_strLineName;
				m_dataPorvider.DeleteModule(tempProLineName);
				m_dataPorvider.DeleteDevice(tempProLineName);
				m_dataPorvider.DeletePlc(tempProLineName);
				m_dataPorvider.DeleteVideo(tempProLineName);

				//ɾ���������е�����		
				pProlineIter = m_dataPorvider.m_vectProductionLine.begin();
				m_dataPorvider.m_vectProductionLine.erase(pProlineIter + m_nItem);
			}
			   
			break;

		case MODULE_DATA_EDIT:

			nResult = MessageBox(_T("�ò�����ɾ���ù���ģ������������豸�����ݣ��Ƿ������ǰ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
			if (nResult == IDYES)
			{
				//ɾ�����ݿ��е�����
				m_dataPorvider.DeleteDbTableItem(CDataProvider::tbProcessModule,
					m_dataPorvider.m_vectProcessModule[m_nItem].m_Id);

				//ɾ�������������ߵĹ���ģ�飬�豸��PLC,����ͷ
				tempProLineName = m_dataPorvider.m_vectProcessModule[m_nItem].m_strProductionLineName;
				tempModuleName = m_dataPorvider.m_vectProcessModule[m_nItem].m_strProcessModuleName;		
				m_dataPorvider.DeleteDevice(tempProLineName,tempModuleName);
				m_dataPorvider.DeleteVideo(tempProLineName,tempModuleName);


				//ɾ���������е�����		
				pModuleIter = m_dataPorvider.m_vectProcessModule.begin();
				m_dataPorvider.m_vectProcessModule.erase(pModuleIter + m_nItem);
			}

			


			break;
		case DEVICE_DATA_EDIT:
			m_dataPorvider.DeleteDbTableItem(CDataProvider::tbDevice,
				m_dataPorvider.m_vectDevice[m_nItem].m_Id);

			pDeviceIter = m_dataPorvider.m_vectDevice.begin();
			m_dataPorvider.m_vectDevice.erase(pDeviceIter + m_nItem);


			break;
		case PLC_DATA_EDIT:
			m_dataPorvider.DeleteDbTableItem(CDataProvider::tbPLc,
				m_dataPorvider.m_vectPlc[m_nItem].m_Id);

			pPlcIter = m_dataPorvider.m_vectPlc.begin();
			m_dataPorvider.m_vectPlc.erase(pPlcIter + m_nItem);

			break;
		case VIDEO_DATA_EDIT:

			m_dataPorvider.DeleteDbTableItem(CDataProvider::tbVideo,
				m_dataPorvider.m_vectVideo[m_nItem].m_Id);

			pVideoIter = m_dataPorvider.m_vectVideo.begin();
			m_dataPorvider.m_vectVideo.erase(pVideoIter + m_nItem);

			break;
		default:
			break;
		}
		OnPaint();
	}
}


void InitDlg::OnBnClickedBtEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString text1, text2, text3, text4;
	int temp;

	switch (id_init){
	case USER_DATA_EDIT:		
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ�"));
			return;
		}

		m_dataPorvider.m_vectUser[m_nItem].m_strUserName = text1;
		m_dataPorvider.m_vectUser[m_nItem].m_strUserPasswd = text2;
		m_dataPorvider.m_vectUser[m_nItem].m_strUserCode = text3;
		m_dataPorvider.m_vectUser[m_nItem].m_strNote = text4;

		m_dataPorvider.UpdateTableItem(CDataProvider::tbUser, m_dataPorvider.m_vectUser[0].m_UserId);

		break;
	case PRODUCTION_LINE_DATA_EDIT:
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		
		if (text1.IsEmpty() || text2.IsEmpty())
		{
			AfxMessageBox(_T("��Ϣ�����ƣ��޷���ӣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));


		m_dataPorvider.m_vectProductionLine[m_nItem].m_strLineName = text1;
		m_dataPorvider.m_vectProductionLine[m_nItem].m_strCapacity = text2;
		m_dataPorvider.m_vectProductionLine[m_nItem].m_strDescription = text3;
		 
		m_dataPorvider.UpdateTableItem(CDataProvider::tbProductionLine,
			m_dataPorvider.m_vectProductionLine[m_nItem].m_Id);


		break;
	case MODULE_DATA_EDIT:
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

		m_dataPorvider.m_vectProcessModule[m_nItem].m_strProductionLineName = text1;
		m_dataPorvider.m_vectProcessModule[m_nItem].m_strProcessModuleName = text2;
		m_dataPorvider.m_vectProcessModule[m_nItem].m_strDescription = text3;

		m_dataPorvider.UpdateTableItem(CDataProvider::tbProcessModule, 
			m_dataPorvider.m_vectProcessModule[m_nItem].m_Id);



		break;
	case DEVICE_DATA_EDIT:
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
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //�޸ĳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));

		m_dataPorvider.m_vectDevice[m_nItem].m_strProductionLineName = text1;
		m_dataPorvider.m_vectDevice[m_nItem].m_strProcessModuleName = text2;
		m_dataPorvider.m_vectDevice[m_nItem].m_strDeviceName = text3;
		m_dataPorvider.m_vectDevice[m_nItem].m_strDeviceType = text4;

		m_dataPorvider.UpdateTableItem(CDataProvider::tbDevice,
			m_dataPorvider.m_vectDevice[m_nItem].m_Id);

		break;
	case PLC_DATA_EDIT:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ�����ƣ�"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

		m_dataPorvider.m_vectPlc[m_nItem].m_strProductionLineName = text1;
		m_dataPorvider.m_vectPlc[m_nItem].m_strPlcName = text2;
		m_dataPorvider.m_vectPlc[m_nItem].m_strPort = text3;
		m_dataPorvider.m_vectPlc[m_nItem].m_strDescription = text4;

		m_dataPorvider.UpdateTableItem(CDataProvider::tbPLc, m_dataPorvider.m_vectPlc[m_nItem].m_Id);
	
		break;

	case VIDEO_DATA_EDIT:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //���������������Ƹ�ֵ��text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //����������ģ�����Ƹ�ֵ��text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //�ж�¼����Ϣ�Ƿ�����//
		{
			AfxMessageBox(_T("��Ϣ������"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //��ӳɹ�����ձ༭��//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));

		m_dataPorvider.m_vectVideo[m_nItem].m_strProductionLineName = text1;
		m_dataPorvider.m_vectVideo[m_nItem].m_strProcessModuleName = text2;
		m_dataPorvider.m_vectVideo[m_nItem].m_strVideoName = text3;
		m_dataPorvider.m_vectVideo[m_nItem].m_strPort = text4;

		m_dataPorvider.UpdateTableItem(CDataProvider::tbVideo, 
			m_dataPorvider.m_vectVideo[m_nItem].m_Id);			

		break;

	default:
		break;
	}
	OnPaint();




}


void InitDlg::OnBnClickedBtAddplcpara()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	m_InitPlcParaDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}
