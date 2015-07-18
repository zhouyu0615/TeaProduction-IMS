// InitPlcParaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitPlcParaDlg.h"
#include "afxdialogex.h"


// CInitPlcParaDlg 对话框

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


// CInitPlcParaDlg 消息处理程序


BOOL CInitPlcParaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置列表控件风格及添加表头//
	CRect rect1;
	m_ListInitPlcPara.GetWindowRect(&rect1);
	m_ListInitPlcPara.SetExtendedStyle(m_ListInitPlcPara.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE | LVS_SHOWSELALWAYS);
	m_ListInitPlcPara.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_ListInitPlcPara.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 25, -1);
	m_ListInitPlcPara.InsertColumn(2, _T("地址类型"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(3, _T("地址索引"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(4, _T("数据类型"), LVCFMT_CENTER, rect1.Width() / 25 * 2, -1);
	m_ListInitPlcPara.InsertColumn(5, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 25* 4, -1);
	m_ListInitPlcPara.InsertColumn(6, _T("所属工艺模块"), LVCFMT_CENTER, rect1.Width() / 25 * 3.2, -1);
	m_ListInitPlcPara.InsertColumn(7, _T("所属设备"), LVCFMT_CENTER, rect1.Width() / 25 * 3.2, -1);
	m_ListInitPlcPara.InsertColumn(8, _T("所属PLC"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);
	m_ListInitPlcPara.InsertColumn(9, _T("是否进入配方"), LVCFMT_CENTER, rect1.Width() / 25* 2.5, -1);
	m_ListInitPlcPara.InsertColumn(10, _T("用户是否可见"), LVCFMT_CENTER, rect1.Width() /25 * 2.5, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CInitPlcParaDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	
	m_ListInitPlcPara.DeleteAllItems();          //清空列表//
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
				m_ListInitPlcPara.SetItemText(n, 9, _T("是")); 
			else			
				m_ListInitPlcPara.SetItemText(n, 9, _T("否"));
			
			if (m_vPlcPara[n].m_bIsVisible)
				m_ListInitPlcPara.SetItemText(n, 10, _T("是"));
			else
				m_ListInitPlcPara.SetItemText(n, 10, _T("否"));
	    }
	} 
	

	// 不为绘图消息调用 CDialog::OnPaint()
}
