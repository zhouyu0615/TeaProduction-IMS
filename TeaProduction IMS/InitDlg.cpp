// InitDlg.cpp : 实现文件
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






// InitDlg 对话框

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


// InitDlg 消息处理程序


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//根据用户点击的添加按钮，加载相应设置到初始化界面//


	//如果已经添加了生产线信息而又没有填写到下拉框，则导入//
	if (!m_dataPorvider.m_vectProductionLine.empty())  {
		((CComboBox*)GetDlgItem(IDC_COMBO1))->ResetContent();
		for (int k = 0; k < m_dataPorvider.m_vectProductionLine.size(); k++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_dataPorvider.m_vectProductionLine[k].m_strLineName));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		}
	}                                
		

	//设置列表控件风格//
	CRect rect1;
	m_list_init.GetWindowRect(&rect1);
	m_list_init.SetExtendedStyle(m_list_init.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LBS_OWNERDRAWVARIABLE);

	//清空列表//
	m_list_init.DeleteAllItems();
	CHeaderCtrl *pmyHeaderCtrl = m_list_init.GetHeaderCtrl();
	int nCount = pmyHeaderCtrl->GetItemCount();
	for (int i = nCount - 1; i >= 0; i--)
		m_list_init.DeleteColumn(i);

	if (!m_dataPorvider.m_vectUser.empty()
		&& !m_dataPorvider.m_vectProductionLine.empty()
		&& !m_dataPorvider.m_vectProcessModule.empty()) //如果已经添加了用户、生产线、模块，则使“添加摄像头”按钮可用//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	int temp = 0;

	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	switch (id_init){
	case USER_DATA_EDIT:
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加用户"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("用户列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("用户名："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("登录密码："));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("客户编码："));
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("备注说明："));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
		//初始化列表区//
		//列标编辑//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 14, -1);
		m_list_init.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(3, _T("登录密码"), LVCFMT_CENTER, rect1.Width() / 14 * 3, -1);
		m_list_init.InsertColumn(4, _T("客户编码"), LVCFMT_CENTER, rect1.Width() / 14 * 2, -1);
		m_list_init.InsertColumn(5, _T("备注说明"), LVCFMT_CENTER, rect1.Width() / 14 * 5, -1);
		//填写表单内容//


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
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加生产线"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("生产线列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("生产线名称："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("产能产量："));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("备注说明："));

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //列标编辑//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("生产线名称"), LVCFMT_CENTER, rect1.Width() / 10 * 4, -1);
		m_list_init.InsertColumn(3, _T("产能产量"), LVCFMT_CENTER, rect1.Width() / 10 * 2, -1);
		m_list_init.InsertColumn(4, _T("备注说明"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		//填写表单内容//


		temp = m_dataPorvider.m_vectProductionLine.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectProductionLine[i].m_strLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectProductionLine[i].m_strCapacity));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectProductionLine[i].m_strDescription));
		}
		break;


	case MODULE_DATA_EDIT:
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加工艺模块"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("工艺模块列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("所属生产线："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("工艺模块名称："));
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("备注说明："));

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //列标编辑//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 10, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(3, _T("工艺模块名称"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);
		m_list_init.InsertColumn(4, _T("备注说明"), LVCFMT_CENTER, rect1.Width() / 10 * 3, -1);




		//填写表单内容//
		temp = m_dataPorvider.m_vectProcessModule.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectProcessModule[i].m_strDescription));
		}
		break;


	case DEVICE_DATA_EDIT:
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加设备"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("设备列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("所属生产线："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("所属工艺模块："));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("设备名称："));
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("设备类型："));
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);



		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //如果COMBO2已有内容，先清空//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//得到COMBO1当前选中条目//
			for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //对应填写COMBO2内容//
				if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
					((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
				}
		}

		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //编辑表头//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("所属工艺模块"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("设备名称"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("设备类型"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);



		//填写表单内容//
		temp = m_dataPorvider.m_vectDevice.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectDevice[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectDevice[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectDevice[i].m_strDeviceName));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectDevice[i].m_strDeviceType));
		}
		break;

	case PLC_DATA_EDIT:
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加PLC"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("PLC列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("所属生产线："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("PLC名称："));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("端口（IP）："));
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("备注说明："));
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //列标编辑//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("PLC名称"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("端口（IP）"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("备注说明"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);

		//填写表单内容//
		temp = m_dataPorvider.m_vectPlc.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectPlc[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectPlc[i].m_strPlcName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectPlc[i].m_strPort));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectPlc[i].m_strDescription));
		}
		break;



	case VIDEO_DATA_EDIT:
		//初始化编辑区//
		GetDlgItem(IDC_STATIC_SET)->SetWindowText(_T("添加摄像头"));
		GetDlgItem(IDC_STATIC_LIST)->SetWindowText(_T("摄像头列表"));
		GetDlgItem(IDC_STATIC1)->SetWindowText(_T("所属生产线："));
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("所属工艺模块："));
		GetDlgItem(IDC_STATIC3)->SetWindowText(_T("摄像头名称："));
		GetDlgItem(IDC_STATIC4)->SetWindowText(_T("端口："));
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);

		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount() > 0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //如果COMBO2已有内容，先清空//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//得到COMBO1当前选中条目//
			for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //对应填写COMBO2内容//
				if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
					((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
				}
		}
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //编辑表头//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width() / 11, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(3, _T("所属工艺模块"), LVCFMT_CENTER, rect1.Width() / 11 * 3, -1);
		m_list_init.InsertColumn(4, _T("摄像头名称"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);
		m_list_init.InsertColumn(5, _T("端口"), LVCFMT_CENTER, rect1.Width() / 11 * 2, -1);

		//填写表单内容//
		temp = m_dataPorvider.m_vectVideo.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i+1);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_dataPorvider.m_vectVideo[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_dataPorvider.m_vectVideo[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_dataPorvider.m_vectVideo[i].m_strVideoName));
			m_list_init.SetItemText(i, 5, _T(m_dataPorvider.m_vectVideo[i].m_strPort));
		}
		break;




	default:
		AfxMessageBox(_T("系统错误！"));
		CDialog::OnCancel();
		break;
	}



	// 不为绘图消息调用 CDialog::OnPaint()
}


int InitDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL InitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


	m_dataPorvider.ReadUserFromDatabase();
	m_dataPorvider.ReadProLineFromDatabase();

	OnPaint();

	m_dataPorvider.ReadProModuleFromDatabase();
	m_dataPorvider.ReadPlcFromDatabase();
	m_dataPorvider.ReadDeviceFromDatabase();
	m_dataPorvider.ReadVideoFromDatabase();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void InitDlg::OnBnClickedBtAdduser()
{
	// TODO: 在此添加控件通知处理程序代码
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
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
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
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_dataPorvider.m_vectUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
		return;
	}
	if (m_dataPorvider.m_vectProcessModule.empty())
	{
		AfxMessageBox(_T("请先添加工艺模块！"));
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
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_dataPorvider.m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
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

//“添加摄像头”响应函数//
void InitDlg::OnBnClickedBtFormula()
{
	// TODO: 在此添加控件通知处理程序代码

	id_init = 6;
	OnPaint();
}


//初始化界面“添加”按钮的响应函数//
void InitDlg::OnBnClickedBtInitadd()
{
	// TODO: 在此添加控件通知处理程序代码
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
		if (!m_dataPorvider.m_vectUser.empty())            //判断是否已添加过用户
		{
			AfxMessageBox(_T("非法操作，用户已创建！"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
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

		if (!m_dataPorvider.m_vectProductionLine.empty())                 //检测该生产线名称是否已经存在//
			for (int q = 0; q < m_dataPorvider.m_vectProductionLine.size(); q++)
				if (text1 == m_dataPorvider.m_vectProductionLine[q].m_strLineName)
				{
					AfxMessageBox(_T("非法操作，该生产线名称已存在！"));
					return;
				}

		if (text1.IsEmpty() || text2.IsEmpty())
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		if (text1.IsEmpty() || text2.IsEmpty())                   //判断所录入工艺模块信息是否完全//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}

         //检测该生产线下工艺模块名称是否已经存在//
	     for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)
				if (text2 ==m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName)
				{
					if (text1==m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName)
					{
						AfxMessageBox(_T("非法操作，该生产线下的同名工艺模块已存在！"));
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));

		tempPlc.m_strProductionLineName = text1;
		tempPlc.m_strPlcName = text2;
		tempPlc.m_strPort = text3;
		tempPlc.m_strDescription = text4;

		//将添加的信息录入到容器//
		m_dataPorvider.m_vectPlc.push_back(tempPlc);

		m_dataPorvider.SavePlcToDatabase();

	
		break;

	case VIDEO_DATA_EDIT:
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));

		tempVideo.m_strProductionLineName = text1;
		tempVideo.m_strProcessModuleName = text2;
		tempVideo.m_strVideoName = text3;
		tempVideo.m_strPort = text4;

		//将添加的信息录入到容器//
		m_dataPorvider.m_vectVideo.push_back(tempVideo);

		m_dataPorvider.SaveVideoToDatabase();

		break;

	default:
		break;
	}
	OnPaint();
}

//“完成”按钮的响应函数//
void InitDlg::OnBnClickedBtFinish()
{
	// TODO:
	if (!m_dataPorvider.m_vectUser.empty() && !m_dataPorvider.m_vectProductionLine.empty() && !m_dataPorvider.m_vectPlc.empty() && !m_dataPorvider.m_vectProcessModule.empty() && !m_dataPorvider.m_vectDevice.empty())
	{
		LoginDlg::s_bIsInit = true;
		CDialog::OnOK();
	}
	else
		AfxMessageBox(_T("初始化信息不完善，无法执行该操作！"));
}


void InitDlg::OnBnClickedButton3()
{
	// TODO: 

	CDialog::OnOK();
}


void InitDlg::OnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int temp;
	if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount() > 0)    //如果COMBO2已有内容，先清空//
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	temp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	CString str1;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, str1);//得到COMBO1当前选中条目//
	for (int i = 0; i < m_dataPorvider.m_vectProcessModule.size(); i++)			           //对应填写COMBO2内容//
		if (m_dataPorvider.m_vectProcessModule[i].m_strProductionLineName == str1)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_dataPorvider.m_vectProcessModule[i].m_strProcessModuleName));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		}


	//OnPaint();
}


void InitDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void InitDlg::OnStnClickedStatic4()
{
	// TODO:  在此添加控件通知处理程序代码
}








void InitDlg::OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	m_nItem = -1;

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	m_list_init.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CString strText1, strText2, strText3, strText4;   //四个临时变量，用于暂存从列标框读取的信息//
	int nCombo1, nCombo2;     //列表框选中条目，在combo1和2里所对应的位置//
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
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	int index = pNMItemActivate->iItem;  //用户右击的行标//
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
	CPoint point1;        //存储鼠标位置的临时变量//
	GetCursorPos(&point1);//得到光标处//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//确保右键点击在哪菜单出现在哪，并返回所选的菜单项//
	if (nItem1 > 0)
	{
		int nResult;
		int strKey;
		switch (id_init)
		{
		case USER_DATA_EDIT:
			nResult = MessageBox(_T("该操作将删除用户及其名下所有设备，是否继续当前操作？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
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

				OnPaint();                                //重绘窗口//
			}
			break;
		case PRODUCTION_LINE_DATA_EDIT:

			nResult = MessageBox(_T("该操作将删除该生产线所有相关设备，PLC等设备，是否继续当前操作？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
			if (nResult == IDYES)
			{
				//删除数据库中的数据
				m_dataPorvider.DeleteDbTableItem(CDataProvider::tbProductionLine,
					m_dataPorvider.m_vectProductionLine[m_nItem].m_Id);

				//删除包含该生产线的工艺模块，设备，PLC,摄像头
				tempProLineName = m_dataPorvider.m_vectProductionLine[m_nItem].m_strLineName;
				m_dataPorvider.DeleteModule(tempProLineName);
				m_dataPorvider.DeleteDevice(tempProLineName);
				m_dataPorvider.DeletePlc(tempProLineName);
				m_dataPorvider.DeleteVideo(tempProLineName);

				//删除该容器中的数据		
				pProlineIter = m_dataPorvider.m_vectProductionLine.begin();
				m_dataPorvider.m_vectProductionLine.erase(pProlineIter + m_nItem);
			}
			   
			break;

		case MODULE_DATA_EDIT:

			nResult = MessageBox(_T("该操作将删除该工艺模块下所有相关设备等数据，是否继续当前操作？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
			if (nResult == IDYES)
			{
				//删除数据库中的数据
				m_dataPorvider.DeleteDbTableItem(CDataProvider::tbProcessModule,
					m_dataPorvider.m_vectProcessModule[m_nItem].m_Id);

				//删除包含该生产线的工艺模块，设备，PLC,摄像头
				tempProLineName = m_dataPorvider.m_vectProcessModule[m_nItem].m_strProductionLineName;
				tempModuleName = m_dataPorvider.m_vectProcessModule[m_nItem].m_strProcessModuleName;		
				m_dataPorvider.DeleteDevice(tempProLineName,tempModuleName);
				m_dataPorvider.DeleteVideo(tempProLineName,tempModuleName);


				//删除该容器中的数据		
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
	// TODO:  在此添加控件通知处理程序代码
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
			AfxMessageBox(_T("信息不完善！"));
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
			AfxMessageBox(_T("信息不完善，无法添加！"));
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		if (text1.IsEmpty() || text2.IsEmpty())                   //判断所录入工艺模块信息是否完全//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //修改成功，清空编辑框//
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
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
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(temp, text1);  //将所属生产线名称赋值给text1//
		temp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(temp, text2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(text4);
		if (text1.IsEmpty() || text2.IsEmpty() || text3.IsEmpty() || text4.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
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
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	m_InitPlcParaDlg.DoModal();
	this->ShowWindow(SW_SHOW);
}
