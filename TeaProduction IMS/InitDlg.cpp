// InitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "tbUser.h"
#include "tbProductionLine.h"



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

END_MESSAGE_MAP()


// InitDlg 消息处理程序


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//根据用户点击的添加按钮，加载相应设置到初始化界面//

	//如果生产线下拉框为空，则填写生产线下拉框//
	int lcombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();   //获得COMBO1下拉框当前共有的行数//
	if (!m_vectProductionLine.empty() && lcombo1 < 1)                                  //如果已经添加了生产线信息而又没有填写到下拉框，则导入//
		for (int k = 0; k < m_vectProductionLine.size(); k++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_vectProductionLine[k].m_strLineName));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
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

	if (!m_vectUser.empty() && !m_vectProductionLine.empty() && !m_vectProcessModule.empty()) //如果已经添加了用户、生产线、模块，则使“添加摄像头”按钮可用//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	int temp = 0;

	LV_ITEM litem;
	litem.mask = LVIF_TEXT;
	litem.iSubItem = 0;
	litem.pszText = _T("");

	switch (id_init){
	case 1:
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


		temp = m_vectUser.size();
		for (int i = 0; i < temp; i++)
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


		temp = m_vectProductionLine.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_vectProductionLine[i].m_strLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectProductionLine[i].m_strCapacity));
			m_list_init.SetItemText(i, 4, _T(m_vectProductionLine[i].m_strDescription));
		}
		break;


	case 3:
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
		temp = m_vectProcessModule.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_vectProcessModule[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectProcessModule[i].m_strProcessModuleName));
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
			for (int i = 0; i < m_vectProcessModule.size(); i++)			           //对应填写COMBO2内容//
				if (m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vectProcessModule[i].m_strProcessModuleName));
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
		temp = m_vectDevice.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_vectDevice[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectDevice[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_vectDevice[i].m_strDeviceName));
			m_list_init.SetItemText(i, 5, _T(m_vectDevice[i].m_strDeviceType));
		}
		break;

		/*		temp = Vdevice.size();
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
				*/
	case 5:
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
		temp = m_vectPlc.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_vectPlc[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectPlc[i].m_strPlcName));
			m_list_init.SetItemText(i, 4, _T(m_vectPlc[i].m_strPort));
			m_list_init.SetItemText(i, 5, _T(m_vectPlc[i].m_strDescription));
		}
		break;


		/*		temp = Vplc.size();
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

				*/
	case 6:
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
			for (int i = 0; i < m_vectProcessModule.size(); i++)			           //对应填写COMBO2内容//
				if (m_vectProcessModule[i].m_strProductionLineName == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vectProcessModule[i].m_strProcessModuleName));
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
		temp = m_vectVideo.size();
		for (int i = 0; i < temp; i++)
		{
			litem.iItem = i;
			CString str;
			str.Format("%d", i);
			m_list_init.InsertItem(&litem);
			m_list_init.SetItemText(i, 1, _T(str)); //序号
			m_list_init.SetItemText(i, 2, _T(m_vectVideo[i].m_strProductionLineName));
			m_list_init.SetItemText(i, 3, _T(m_vectVideo[i].m_strProcessModuleName));
			m_list_init.SetItemText(i, 4, _T(m_vectVideo[i].m_strVideoName));
			m_list_init.SetItemText(i, 5, _T(m_vectVideo[i].m_strPort));
		}
		break;



		/*		temp = Vcamera.size();
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
				*/
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


	ReadUserFromDatabase();
	ReadProLineFromDatabase();



	OnPaint();

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
	if (m_vectUser.empty())
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
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_vectProductionLine.empty())
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
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_vectProductionLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
		return;
	}
	if (m_vectProcessModule.empty())
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
	if (m_vectUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
	if (m_vectProductionLine.empty())
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
	case 1:
		if (!m_vectUser.empty())            //判断是否已添加过用户
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

		m_vectUser.push_back(tempUser);

		SaveUserToDatabase();



		break;
	case 2:
		GetDlgItem(IDC_EDIT1)->GetWindowText(text1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(text2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(text3);

		if (!m_vectProductionLine.empty())                 //检测该生产线名称是否已经存在//
			for (int q = 0; q < m_vectProductionLine.size(); q++)
				if (text1 == m_vectProductionLine[q].m_strLineName)
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

		m_vectProductionLine.push_back(tempProLine);

		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(text1));//将添加的生产线录入到COMBO1//
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);


		SaveProLineToDatabase();


		break;
	case 3:
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
		
		tempProModule.m_strProductionLineName = text1;
		tempProModule.m_strProcessModuleName = text2;
		tempProModule.m_strDescription = text3; 

		m_vectProcessModule.push_back(tempProModule);


		/*		Vmudole.push_back(text1);   //将录入的信息写入对应容器//
				Vmudole.push_back(text2);
				Vmudole.push_back(text3);
				*/
		break;
	case 4:
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

		m_vectDevice.push_back(tempDevice);


		/*		Vdevice.push_back(text1);         //将添加的信息录入到容器//
				Vdevice.push_back(text2);
				Vdevice.push_back(text3);
				Vdevice.push_back(text4);
				*/
		break;
	case 5:
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

		m_vectPlc.push_back(tempPlc);


		/*		Vplc.push_back(text1);         //将添加的信息录入到容器//
				Vplc.push_back(text2);
				Vplc.push_back(text3);
				Vplc.push_back(text4);
				*/
		break;

	case 6:
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

		m_vectVideo.push_back(tempVideo);


		/*	Vcamera.push_back(text1);         //将添加的信息录入到容器//
			Vcamera.push_back(text2);
			Vcamera.push_back(text3);
			Vcamera.push_back(text4);
			*/
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
	if (!m_vectUser.empty() && !m_vectProductionLine.empty() && !m_vectPlc.empty() && !m_vectProcessModule.empty() && !m_vectDevice.empty())
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
	OnPaint();
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


void InitDlg::SaveUserToDatabase()
{
	CtbUser m_tbUserSet;
	try{
		if (m_tbUserSet.IsOpen())
			m_tbUserSet.Close();
		if (!m_tbUserSet.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString username, userpasswd, usercode, usernote;

	srand(time(NULL));
	int userId = rand();


	username = m_vectUser[0].m_strUserName;
	userpasswd = m_vectUser[0].m_strUserPasswd;
	usercode = m_vectUser[0].m_strUserCode;
	usernote = m_vectUser[0].m_strNote;

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
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	UserClass tempUser;
	tbUser.MoveFirst();
	while (!tbUser.IsEOF()){
		m_userId = tbUser.m_Id; //获取类成员变量 唯一的 用户ID
		tempUser.m_UserId = tbUser.m_Id;
		tempUser.m_strUserName = tbUser.m_UserName;
		tempUser.m_strUserPasswd = tbUser.m_UserPassword;
		tempUser.m_strUserCode = tbUser.m_UserCode;
		tempUser.m_strNote = tbUser.m_Note;
		m_vectUser.push_back(tempUser);

		tbUser.MoveNext();

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
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strlineName, strCapacity, strDescription;

	srand(time(NULL));
	int lineId = rand();
	int length = m_vectProductionLine.size();

	strlineName = m_vectProductionLine[length - 1].m_strLineName;
	strCapacity = m_vectProductionLine[length - 1].m_strCapacity;
	strDescription = m_vectProductionLine[length - 1].m_strDescription;

	if (tbProductionLine.CanUpdate()){
		tbProductionLine.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProductionLine.m_Id = lineId;
		tbProductionLine.m_CreatedDateTime = time;
		tbProductionLine.m_LastUpdatedDateTime = time;
		tbProductionLine.m_LineName = strlineName;
		tbProductionLine.m_UserId = m_userId; //唯一用户ID
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
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	ProductionLineClass tempProductionLine;
	tbProductionLine.MoveFirst();
	while (!tbProductionLine.IsEOF()){

		tempProductionLine.m_Id = tbProductionLine.m_Id;
		tempProductionLine.m_strLineName = tbProductionLine.m_LineName;
		tempProductionLine.m_strCapacity = tbProductionLine.m_Capacity;
		tempProductionLine.m_strDescription = tbProductionLine.m_Description;

		m_vectProductionLine.push_back(tempProductionLine);
		tbProductionLine.MoveNext();
	}

	tbProductionLine.Close();

}




