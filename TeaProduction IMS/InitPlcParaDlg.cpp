// InitPlcParaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitPlcParaDlg.h"
#include "afxdialogex.h"


// CInitPlcParaDlg �Ի���

IMPLEMENT_DYNAMIC(CInitPlcParaDlg, CDialog)

CInitPlcParaDlg::CInitPlcParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitPlcParaDlg::IDD, pParent)
{

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
	m_ListInitPlcPara.InsertColumn(2, _T("��ַ����"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(3, _T("��ַ����"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(4, _T("��������"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(5, _T("����������"), LVCFMT_CENTER, rect1.Width() / 25* 4, -1);
	m_ListInitPlcPara.InsertColumn(6, _T("��������ģ��"), LVCFMT_CENTER, rect1.Width() / 25 * 3.2, -1);
	m_ListInitPlcPara.InsertColumn(7, _T("�����豸"), LVCFMT_CENTER, rect1.Width() / 25 * 3.2, -1);
	m_ListInitPlcPara.InsertColumn(8, _T("����PLC"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);
	m_ListInitPlcPara.InsertColumn(9, _T("�Ƿ�����䷽"), LVCFMT_CENTER, rect1.Width() / 25* 2.5, -1);
	m_ListInitPlcPara.InsertColumn(10, _T("�û��Ƿ�ɼ�"), LVCFMT_CENTER, rect1.Width() /25 * 2.5, -1);

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
			CString str1;
			str1.Format("%d", n+1);
			m_ListInitPlcPara.InsertItem(n , _T(""));
			m_ListInitPlcPara.SetItemText(n , 1, _T(str1));
			m_ListInitPlcPara.SetItemText(n, 2, _T(m_vPlcPara[n].m_strAddressType));
			m_ListInitPlcPara.SetItemText(n, 3, _T(m_vPlcPara[n].m_strAddressIndex));
			m_ListInitPlcPara.SetItemText(n, 4, _T(m_vPlcPara[n].m_strValueType));
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
	    }
	} 
	

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
