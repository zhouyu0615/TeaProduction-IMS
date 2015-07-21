// InitPlcParaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitPlcParaDlg.h"
#include "afxdialogex.h"
#include "DataProvider.h"



// CInitPlcParaDlg �Ի���

IMPLEMENT_DYNAMIC(CInitPlcParaDlg, CDialog)

CInitPlcParaDlg::CInitPlcParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitPlcParaDlg::IDD, pParent)
{
	m_nItem = -1;//��ʼ������//

	//�����ã���ɾ������ʼ������vector//
	ProductionLineClass line1;
	line1.m_strLineName = _T("���������");
	ProductionLineClass line2;
	line2.m_strLineName = _T("�̲�������");
	m_vLine.push_back(line1);
	m_vLine.push_back(line2);

	ProcessModuleClass module1;
	module1.m_strProductionLineName = _T("�̲�������");
	module1.m_strProcessModuleName = _T("�̲�ɱ��");
	m_vModule.push_back(module1);

	ProcessModuleClass module2;
	module2.m_strProductionLineName = _T("�̲�������");
	module2.m_strProcessModuleName = _T("�̲���");
	m_vModule.push_back(module2);

	ProcessModuleClass module3;
	module3.m_strProductionLineName = _T("���������");
	module3.m_strProcessModuleName = _T("���ɱ��");
	m_vModule.push_back(module3);

	DeviceClass device1;
	device1.m_strProductionLineName = _T("�̲�������");
	device1.m_strProcessModuleName = _T("�̲�ɱ��");
	device1.m_strDeviceName = _T("ɱ���");
	m_vDevice.push_back(device1);

	DeviceClass device2;
	device2.m_strProductionLineName = _T("�̲�������");
	device2.m_strProcessModuleName = _T("�̲�ɱ��");
	device2.m_strDeviceName = _T("���");
	m_vDevice.push_back(device2);

	DeviceClass device3;
	device3.m_strProductionLineName = _T("�̲�������");
	device3.m_strProcessModuleName = _T("�̲���");
	device3.m_strDeviceName = _T("�̲��ɻ�");
	m_vDevice.push_back(device3);

	DeviceClass device4;
	device4.m_strProductionLineName = _T("���������");
	device4.m_strProcessModuleName = _T("���ɱ��");
	device4.m_strDeviceName = _T("ɱ���");
	m_vDevice.push_back(device4);

	PlcClass plc1;
	plc1.m_strProductionLineName = _T("���������");
	plc1.m_strPlcName = _T("���һ��PLC");
	m_vPlc.push_back(plc1);

	PlcClass plc2;
	plc2.m_strProductionLineName = _T("���������");
	plc2.m_strPlcName = _T("���2��PLC");
	m_vPlc.push_back(plc2);

	PlcClass plc3;
	plc3.m_strProductionLineName = _T("�̲�������");
	plc3.m_strPlcName = _T("�̲�һ��PLC");
	m_vPlc.push_back(plc3);

	CPlcPara plcpara;
	plcpara.m_bIsConfig = false;
	plcpara.m_bIsVisible = true;
	plcpara.m_strAddressType = _T("I");
	plcpara.m_strAddressIndex = _T("0.0");
	plcpara.m_strLine = _T("�̲�������");
	plcpara.m_strModule = _T("�̲���");
	plcpara.m_strDevice = _T("�̲��ɻ�");
	plcpara.m_strPlc = _T("�̲�һ��PLC");
	plcpara.m_strValueType = _T("Bool");
	plcpara.m_strNote = _T("����ֹͣ�ź�");
	plcpara.m_bIsReadOnly = true;
	m_vPlcPara.push_back(plcpara);



	m_dataProvider.ReadPlcParaFrommDatabase();

	m_vPlcPara.push_back(m_dataProvider.m_vectPlcPara[0]);

}

CInitPlcParaDlg::~CInitPlcParaDlg()
{
}

void CInitPlcParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListInitPlcPara);
}


BEGIN_MESSAGE_MAP(CInitPlcParaDlg, CDialog)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CInitPlcParaDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CInitPlcParaDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CInitPlcParaDlg::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BT_ADDPLCPARA, &CInitPlcParaDlg::OnBnClickedBtAddplcpara)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CInitPlcParaDlg::OnNMRClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CInitPlcParaDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BT_EDITPLCPARA, &CInitPlcParaDlg::OnBnClickedBtEditplcpara)
	ON_BN_CLICKED(IDC_BT_CLEAREDITAREA, &CInitPlcParaDlg::OnBnClickedBtCleareditarea)
	ON_BN_CLICKED(IDC_BT_CLEARALLPARA, &CInitPlcParaDlg::OnBnClickedBtClearallpara)
	ON_BN_CLICKED(IDCANCEL, &CInitPlcParaDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BT_SAVEALL, &CInitPlcParaDlg::OnBnClickedBtSaveall)
END_MESSAGE_MAP()


// CInitPlcParaDlg ��Ϣ�������


BOOL CInitPlcParaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//�����б�ؼ������ӱ�ͷ//
	CRect rect1;
	m_ListInitPlcPara.GetWindowRect(&rect1);
	m_ListInitPlcPara.SetExtendedStyle(m_ListInitPlcPara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE | LVS_SHOWSELALWAYS);
	m_ListInitPlcPara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_ListInitPlcPara.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect1.Width() / 25, -1);
	m_ListInitPlcPara.InsertColumn(2, _T("��ַ"), LVCFMT_CENTER, rect1.Width() / 25 * 1.6, -1);
	m_ListInitPlcPara.InsertColumn(3, _T("��������"), LVCFMT_CENTER, rect1.Width() / 25 * 1.7, -1);
	m_ListInitPlcPara.InsertColumn(4, _T("��д����"), LVCFMT_CENTER, rect1.Width() / 25 * 1.7, -1);
	m_ListInitPlcPara.InsertColumn(5, _T("����������"), LVCFMT_CENTER, rect1.Width() / 25* 3.3, -1);
	m_ListInitPlcPara.InsertColumn(6, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);
	m_ListInitPlcPara.InsertColumn(7, _T("�����豸"), LVCFMT_CENTER, rect1.Width() / 25 * 2.9, -1);
	m_ListInitPlcPara.InsertColumn(8, _T("����PLC"), LVCFMT_CENTER, rect1.Width() / 25 * 2.9, -1);
	m_ListInitPlcPara.InsertColumn(9, _T("�Ƿ�����䷽"), LVCFMT_CENTER, rect1.Width() / 25* 2.2, -1);
	m_ListInitPlcPara.InsertColumn(10, _T("�û��Ƿ�ɼ�"), LVCFMT_CENTER, rect1.Width() /25 * 2.2, -1);
	m_ListInitPlcPara.InsertColumn(11, _T("��ע"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);

	
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CInitPlcParaDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	
	m_ListInitPlcPara.DeleteAllItems();          //����б�//
	int nSizeOfVector = m_vPlcPara.size();
	if (nSizeOfVector>0)
	{
		for (int n = 0; n < nSizeOfVector;n++)
	    {
			CString str4;
			int j = n + 1;
			str4.Format("%d", j);
			m_ListInitPlcPara.InsertItem(n , _T(""));
			m_ListInitPlcPara.SetItemText(n , 1, _T(str4));
			m_ListInitPlcPara.SetItemText(n, 2, _T(m_vPlcPara[n].m_strAddressType + m_vPlcPara[n].m_strAddressIndex));
			m_ListInitPlcPara.SetItemText(n, 3, _T(m_vPlcPara[n].m_strValueType));
			if (m_vPlcPara[n].m_bIsReadOnly)
				m_ListInitPlcPara.SetItemText(n, 4, _T("ֻ��"));
			else
				m_ListInitPlcPara.SetItemText(n, 4, _T("��д"));
			m_ListInitPlcPara.SetItemText(n, 5, _T(m_vPlcPara[n].m_strLine));
			m_ListInitPlcPara.SetItemText(n, 6, _T(m_vPlcPara[n].m_strModule));
			m_ListInitPlcPara.SetItemText(n, 7, _T(m_vPlcPara[n].m_strDevice));
			m_ListInitPlcPara.SetItemText(n, 8, _T(m_vPlcPara[n].m_strPlc));
			if (m_vPlcPara[n].m_bIsConfig)
				m_ListInitPlcPara.SetItemText(n, 9, _T("��")); 
			else			
				m_ListInitPlcPara.SetItemText(n, 9, _T("��"));
			
			if (m_vPlcPara[n].m_bIsVisible)
				m_ListInitPlcPara.SetItemText(n, 10, _T("��"));
			else
				m_ListInitPlcPara.SetItemText(n, 10, _T("��"));
			m_ListInitPlcPara.SetItemText(n, 11, _T(m_vPlcPara[n].m_strNote));
	    }
	} 

	//����б��ѡ����ĳ�У�������ʾ//
	if (m_nItem>=0)
	    m_ListInitPlcPara.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	//�����ַ����������Ϊ�գ�����д��ַ����������//
	if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() == 0)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("I"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("IX"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("IB"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("IW"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("ID"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("Q"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("QX"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("QB"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("QW"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("QD"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("M"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("MX"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("MB"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("MW"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("MD"));
	}

	//�������������������Ϊ�գ�����д���������Ƶ�COMBO3//
	if (!m_vLine.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCount()==0)
	{
		for (int n = 0; n < m_vLine.size();n++)            //��д������COMBO3//
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T(m_vLine[n].m_strLineName));
		}
	}

	//�������ģ��������Ϊ�գ�����д����ģ�����Ƶ�COMBO4//	
	if (!m_vModule.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCount() == 0)
   {
	    int nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		if ( nTemp != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, str2);//�õ�������������COMBO3��ǰѡ����Ŀ//
			for (int i = 0; i < m_vModule.size();i++)
				if (m_vModule[i].m_strProductionLineName==str2)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(_T(m_vModule[i].m_strProcessModuleName));
					((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(0);
				}	
		}
	}

	//����豸������Ϊ�գ�����д�豸���Ƶ�COMBO5//
	if (!m_vDevice.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCount() == 0)
	{
		int nTemp1 = ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel();
		if (nTemp1 != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO4))->GetLBText(nTemp1, str2);//�õ�����ģ��������COMBO4��ǰѡ����Ŀ//
			CString str3;
			int nTemp2 = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp2, str3);//�õ�������������COMBO3��ǰѡ����Ŀ//
			for (int i = 0; i < m_vDevice.size(); i++)
				if (m_vDevice[i].m_strProcessModuleName==str2 && m_vDevice[i].m_strProductionLineName==str3)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T(m_vDevice[i].m_strDeviceName));
					((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(0);
				}
		}
	}

	//���PLC������Ϊ�գ�����дPLC���Ƶ�COMBO6//
	if (!m_vPlc.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCount() == 0)
	{
		int nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		if (nTemp != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, str2);//�õ�������������COMBO3��ǰѡ����Ŀ//
			for (int i = 0; i < m_vPlc.size(); i++)
				if (m_vPlc[i].m_strProductionLineName == str2)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO6))->AddString(_T(m_vPlc[i].m_strPlcName));
					((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(0);
				}
		}
	}
	if (((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCount() == 0)  //��д�û��Ƿ�ɼ�������//
	{
		((CComboBox*)GetDlgItem(IDC_COMBO7))->AddString(_T("��"));
		((CComboBox*)GetDlgItem(IDC_COMBO7))->AddString(_T("��"));
	}
	if (((CComboBox*)GetDlgItem(IDC_COMBO8))->GetCount() == 0)  //��д�Ƿ�����䷽������//
	{
		((CComboBox*)GetDlgItem(IDC_COMBO8))->AddString(_T("��"));
		((CComboBox*)GetDlgItem(IDC_COMBO8))->AddString(_T("��"));
	}

	//���ݵ�ַ�����������ѡ����Ŀ��д�������ͱ༭��//
	switch (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel())
	{
	case 0:
	case 1:
	case 5:
	case 6:
	case 10:
	case 11:
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("Bool"));
		break;
	case 2:
	case 7:
	case 12:
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("Byte"));
		break;
	case 3:
	case 8:
	case 13:
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("Word"));
		break;
	case 4:
	case 9:
	case 14:
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("DWord"));
		break;
	default:
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		break;
	}

	//���ݵ�ַ�����������ѡ����Ŀ��д��д����������//
	if ( ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() == 0)
	    switch (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel())
	    {
	    case 0:
	    case 1:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	    case 6:
	    case 7:
	    case 8:
	    case 9:
		    ((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("ֻ��"));
		    ((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		    break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("ֻ��"));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("��д"));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
			break;
		default:	
			break;
	    }

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


void CInitPlcParaDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	OnPaint();
}


void CInitPlcParaDlg::OnCbnSelchangeCombo3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
	OnPaint();
}


void CInitPlcParaDlg::OnCbnSelchangeCombo4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	OnPaint();
}

//����ӡ���ť����Ӧ����//
void CInitPlcParaDlg::OnBnClickedBtAddplcpara()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰ�༭��������//
	CString strAdressType, strAdressIndex, strValueType, strLine, strModule, strDevice, strPlc, strNote;
	int nTemp = -1,nIsReadWrite = -1;
	int nIsConfig = -1, nIsVisible = -1;
	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, strAdressType);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, strLine);

	GetDlgItem(IDC_EDIT1)->GetWindowText(strAdressIndex);
	GetDlgItem(IDC_EDIT3)->GetWindowText(strValueType);
	GetDlgItem(IDC_EDIT2)->GetWindowText(strNote);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO4))->GetLBText(nTemp, strModule);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(nTemp, strDevice);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->GetLBText(nTemp, strPlc);

	nIsVisible = ((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel();
	nIsConfig = ((CComboBox*)GetDlgItem(IDC_COMBO8))->GetCurSel();
	nIsReadWrite = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();

	//�����Ϣ��д��������д������//
	if (strAdressType.IsEmpty() || strAdressIndex.IsEmpty() || strValueType.IsEmpty() || strLine.IsEmpty() || strModule.IsEmpty() || strDevice.IsEmpty() || strPlc.IsEmpty() || strNote.IsEmpty() || nIsConfig == CB_ERR || nIsVisible == CB_ERR||nIsReadWrite ==CB_ERR)
		AfxMessageBox(_T("��Ϣ�����ƣ��޷�������Ӳ�����"));
	else
	{
		m_nItem = -1;     //�б��ʧȥѡ����//

		m_PlcPara.m_strAddressType = strAdressType;
		m_PlcPara.m_strAddressIndex = strAdressIndex;
		m_PlcPara.m_strValueType = strValueType;
		m_PlcPara.m_strLine = strLine;
		m_PlcPara.m_strModule = strModule;
		m_PlcPara.m_strDevice = strDevice;
		m_PlcPara.m_strPlc = strPlc;
		m_PlcPara.m_strNote = strNote;
		if (nIsReadWrite == 0)
			m_PlcPara.m_bIsReadOnly = true;
		else
			m_PlcPara.m_bIsReadOnly = false;
		if (nIsVisible == 1)
			m_PlcPara.m_bIsVisible = false;
		else
			m_PlcPara.m_bIsVisible = true;
		if (nIsConfig == 1)
			m_PlcPara.m_bIsConfig = false;
		else
			m_PlcPara.m_bIsConfig = true;
		m_vPlcPara.push_back(m_PlcPara);//д������//
		GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T("")); //��ձ༭��//
		GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(""));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO3))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO7))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO8))->ResetContent();
		OnPaint();
	}
}

//�һ��б��ؼ�����Ӧ������ʵ��ɾ������//
void CInitPlcParaDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int index = pNMItemActivate->iItem;  //�û��һ����б�//
	if (index == -1)
		return;
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //�洢���λ�õ���ʱ����//
	GetCursorPos(&point1);//�õ���괦//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//ȷ���Ҽ�������Ĳ˵��������ģ���������ѡ�Ĳ˵���//
	if (nItem1 > 0)
	{
		int nResult;
		nResult = MessageBox(_T("�ò����޷��ָ����Ƿ������"), _T("����"), MB_ICONEXCLAMATION | MB_YESNO);//����//
		if (nResult == IDYES)
		{
			m_nItem = -1;     //�б��ʧȥѡ����//

			m_vPlcPara.erase(m_vPlcPara.begin() + index);
			GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T(""));
			GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(""));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO3))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO7))->ResetContent();
			((CComboBox*)GetDlgItem(IDC_COMBO8))->ResetContent();
			OnPaint();                                //�ػ洰��//
		}
	}
	*pResult = 0;
}

	


//�����б�򣬽�������ʾ�ر༭��//
void CInitPlcParaDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_nItem = -1;

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	if (m_nItem == -1)
		return;

	int nCombo;     //�б��ѡ����Ŀ��combo������Ӧ��λ��//

	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, m_vPlcPara[m_nItem].m_strAddressType);//��д��ַ����������//
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo);

	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();  //��д��д����������//
	switch (nCombo)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("ֻ��"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("ֻ��"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("��д"));
		if (m_vPlcPara[m_nItem].m_bIsReadOnly)
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		else
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(1);
		break;
	default:
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
		break;
	}
	

	GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T(m_vPlcPara[m_nItem].m_strAddressIndex));//��д��ַ�����༭��//

	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO3))->FindStringExact(0, m_vPlcPara[m_nItem].m_strLine);//��ʾ��ǰ��Ŀ����������//
	if (nCombo != CB_ERR)
		((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(nCombo);
	else
	{
		AfxMessageBox(_T("δ֪����"));
		return;
	}

	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent(); //������д����ģ�������򣬲���ʾ��Ӧ��Ŀ//
	for (int i = 0; i < m_vModule.size(); i++)
		if (m_vModule[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(_T(m_vModule[i].m_strProcessModuleName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO4))->FindStringExact(0, m_vPlcPara[m_nItem].m_strModule);
	((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(nCombo);
		
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent(); //������д�����豸�����򣬲���ʾ��Ӧ��Ŀ//
	for (int i = 0; i < m_vDevice.size(); i++)
		if (m_vDevice[i].m_strProcessModuleName == m_vPlcPara[m_nItem].m_strModule && m_vDevice[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T(m_vDevice[i].m_strDeviceName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO5))->FindStringExact(0, m_vPlcPara[m_nItem].m_strDevice);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(nCombo);
		
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent(); //������д����PLC�����򣬲���ʾ��Ӧ��Ŀ//
	for (int i = 0; i < m_vPlc.size(); i++)
		if (m_vPlc[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO6))->AddString(_T(m_vPlc[i].m_strPlcName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO6))->FindStringExact(0, m_vPlcPara[m_nItem].m_strPlc);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(nCombo);

	GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(m_vPlcPara[m_nItem].m_strNote));//��д��ע�༭��//

	if (m_vPlcPara[m_nItem].m_bIsVisible)              //�û��Ƿ�ɼ���������ʾ��Ӧ��Ŀ//
		((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(0);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(1);

	if (m_vPlcPara[m_nItem].m_bIsConfig)              //�û��Ƿ�ɼ���������ʾ��Ӧ��Ŀ//
		((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(0);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(1);

	OnPaint();

	*pResult = 0;
}

//���޸ġ���ť����Ӧ����//
void CInitPlcParaDlg::OnBnClickedBtEditplcpara()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nItem == -1)
		return;
	CString strAdressType, strAdressIndex, strValueType, strLine, strModule, strDevice, strPlc, strNote;//���ڴ洢�༭�����ݵ���ʱ����//
	int nTemp = -1;
	int nIsConfig = -1, nIsVisible = -1,nIsReadWrite = -1;

	//��ȡ�༭�����ݵ���ʱ����//
	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, strAdressType);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, strLine);

	GetDlgItem(IDC_EDIT1)->GetWindowText(strAdressIndex);
	GetDlgItem(IDC_EDIT3)->GetWindowText(strValueType);
	GetDlgItem(IDC_EDIT2)->GetWindowText(strNote);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO4))->GetLBText(nTemp, strModule);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(nTemp, strDevice);

	nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->GetLBText(nTemp, strPlc);

	nIsVisible = ((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCurSel();
	nIsConfig = ((CComboBox*)GetDlgItem(IDC_COMBO8))->GetCurSel();
	nIsReadWrite = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();

	//����Ϣ���������޸Ķ�Ӧ����//
	if (strAdressType.IsEmpty() || strAdressIndex.IsEmpty() || strValueType.IsEmpty() || strLine.IsEmpty() || strModule.IsEmpty() || strDevice.IsEmpty() || strPlc.IsEmpty() || strNote.IsEmpty() || nIsConfig == CB_ERR || nIsVisible == CB_ERR || nIsReadWrite ==CB_ERR)
	{
	    
		AfxMessageBox(_T("��Ϣ�����ƣ��޷����иò�����"));
		return;
	}
	else
	{
		m_vPlcPara[m_nItem].m_strAddressType = strAdressType;
		m_vPlcPara[m_nItem].m_strAddressIndex = strAdressIndex;
		m_vPlcPara[m_nItem].m_strValueType = strValueType;
		m_vPlcPara[m_nItem].m_strLine = strLine;
		m_vPlcPara[m_nItem].m_strModule = strModule;
		m_vPlcPara[m_nItem].m_strDevice = strDevice;
		m_vPlcPara[m_nItem].m_strNote = strNote;
		m_vPlcPara[m_nItem].m_strPlc = strPlc;
		if (nIsVisible)
			m_vPlcPara[m_nItem].m_bIsVisible = false;
		else
			m_vPlcPara[m_nItem].m_bIsVisible = true;
		if (nIsConfig)
			m_vPlcPara[m_nItem].m_bIsConfig = false;
		else
			m_vPlcPara[m_nItem].m_bIsConfig = true;
		if (nIsReadWrite)
			m_vPlcPara[m_nItem].m_bIsReadOnly = false;
		else
			m_vPlcPara[m_nItem].m_bIsReadOnly = true;
	}

	OnPaint();

}

//����ձ༭������ť��Ӧ����//
void CInitPlcParaDlg::OnBnClickedBtCleareditarea()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T(""));
	GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(""));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO3))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO7))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO8))->ResetContent();
	m_nItem = -1; //ȥ���б��ĳ�е�ѡ��״̬//
	OnPaint();
}

//������б�������Ӧ����//
void CInitPlcParaDlg::OnBnClickedBtClearallpara()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	std::vector <CPlcPara>().swap(m_vPlcPara);    //�����������С����������//
	GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T(""));
	GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(""));
	((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO3))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO7))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO8))->ResetContent();
	m_nItem = -1;//ȥ���б��ĳ�е�ѡ��״̬//
	OnPaint();
}


void CInitPlcParaDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("ȷ��"));

	CDialog::OnCancel();

}





void CInitPlcParaDlg::OnBnClickedBtSaveall()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_dataProvider.DeleteDbTable(CDataProvider::tbPLCSymbol);

	m_dataProvider.SaveAllPlcParaToDatabase();


}
