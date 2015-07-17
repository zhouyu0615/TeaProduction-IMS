// InitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// InitDlg 对话框

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


// InitDlg 消息处理程序


void InitDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	//根据用户点击的添加按钮，加载相应设置到初始化界面//

	//如果生产线下拉框为空，则填写生产线下拉框//
	int nLineOfCombo1 = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();   //获得COMBO1下拉框当前共有的行数//
	if (!m_vLine.empty() && nLineOfCombo1 < 1)                                  //如果已经添加了生产线信息而又没有填写到下拉框，则导入//
		for (int k = 0; k < m_vLine.size(); k += 3)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(m_vLine[k]));
			((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		}
	

	//设置列表控件风格//
	CRect rect1;
	m_list_init.GetWindowRect(&rect1);
	m_list_init.SetExtendedStyle(m_list_init.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SINGLESEL | LBS_OWNERDRAWVARIABLE | LVS_SHOWSELALWAYS);

	if (!m_vUser.empty() && !m_vLine.empty() && !m_vModule.empty()) //如果已经添加了用户、生产线、模块，则使“添加摄像头”按钮可用//
		GetDlgItem(IDC_BT_FORMULA)->EnableWindow(TRUE);

	//清空列表//
	m_list_init.DeleteAllItems();    
	CHeaderCtrl *pmyHeaderCtrl= m_list_init.GetHeaderCtrl();
    int nCount = pmyHeaderCtrl->GetItemCount();
	for(int i=nCount-1;i>=0;i--)
	    m_list_init.DeleteColumn(i);	

	int nTemp = 0;
	switch (m_IdInit){
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
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width()/14, -1);
		m_list_init.InsertColumn(2, _T("用户名"), LVCFMT_CENTER, rect1.Width()/14*3, -1);
		m_list_init.InsertColumn(3, _T("登录密码"), LVCFMT_CENTER, rect1.Width()/14*3, -1);
		m_list_init.InsertColumn(4, _T("客户编码"), LVCFMT_CENTER, rect1.Width()/14*2, -1);
		m_list_init.InsertColumn(5, _T("备注说明"), LVCFMT_CENTER, rect1.Width()/14*5, -1);
		//填写表单内容//
		nTemp = m_vUser.size();
		if(nTemp==0)
		    break;
		else
		{
		    int nX = 0;    //列表框元素的行标//
		    int nY = 0;    //列表框元素的列标//
			int nLine = nTemp/4;  //总行数//
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
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width()/10, -1);
		m_list_init.InsertColumn(2, _T("生产线名称"), LVCFMT_CENTER, rect1.Width()/10*4, -1);
		m_list_init.InsertColumn(3, _T("产能产量"), LVCFMT_CENTER, rect1.Width()/10*2, -1);
		m_list_init.InsertColumn(4, _T("备注说明"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		//填写表单内容//
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
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width()/10, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		m_list_init.InsertColumn(3, _T("工艺模块名称"), LVCFMT_CENTER, rect1.Width()/10*3, -1);
		m_list_init.InsertColumn(4, _T("备注说明"), LVCFMT_CENTER, rect1.Width()/10*3, -1);

		//填写表单内容//
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

		if(((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount()>0)
		{
		    if(((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount()>0)    //如果COMBO2已有内容，先清空//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		    CString str1;
		    ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,str1);//得到COMBO1当前选中条目//
			for (int i=0; i<m_vModule.size(); i+=3)			           //对应填写COMBO2内容//
			   if(m_vModule[i]==str1)
			   {
				   ((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vModule[i+1]));
				   ((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
			   }	
		}
		GetDlgItem(IDC_COMBO2)->ShowWindow(SW_SHOW);

		//初始化列表区//
		m_list_init.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);       //编辑表头//
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width()/11, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(3, _T("所属工艺模块"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(4, _T("设备名称"), LVCFMT_CENTER, rect1.Width()/11*2, -1);
		m_list_init.InsertColumn(5, _T("设备类型"), LVCFMT_CENTER, rect1.Width()/11*2, -1);

		//填写表单内容//
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
		m_list_init.InsertColumn(1, _T("序号"), LVCFMT_CENTER, rect1.Width()/11, -1);
		m_list_init.InsertColumn(2, _T("所属生产线"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(3, _T("PLC名称"), LVCFMT_CENTER, rect1.Width()/11*3, -1);
		m_list_init.InsertColumn(4, _T("端口（IP）"), LVCFMT_CENTER, rect1.Width()/11*2, -1);
		m_list_init.InsertColumn(5, _T("备注说明"), LVCFMT_CENTER, rect1.Width()/11*2, -1);

		//填写表单内容//
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

		if (((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount()>0)
		{
			if (((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCount()>0)    //如果COMBO2已有内容，先清空//
				((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
			nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
			CString str1;
			((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, str1);//得到COMBO1当前选中条目//
			for (int i = 0; i<m_vModule.size(); i += 3)			           //对应填写COMBO2内容//
				if (m_vModule[i] == str1)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T(m_vModule[i + 1]));
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




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void InitDlg::OnBnClickedBtAdduser()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
		return;
    }
	if(m_vModule.empty())
	{
	    AfxMessageBox(_T("请先添加工艺模块！"));
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
	// TODO: 在此添加控件通知处理程序代码
	if(m_vUser.empty())
	{
		AfxMessageBox(_T("尚未创建用户，请先添加用户！"));
		return;
	}
    if(m_vLine.empty())
	{
		AfxMessageBox(_T("请先添加生产线！"));
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

//“添加摄像头”响应函数//
void InitDlg::OnBnClickedBtFormula()
{
	// TODO: 在此添加控件通知处理程序代码
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


//初始化界面“添加”按钮的响应函数//
void InitDlg::OnBnClickedBtInitadd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strText1,strText2,strText3,strText4;
	int nTemp;
	switch(m_IdInit){
	case 1:
        if(!m_vUser.empty())            //判断是否已添加过用户
			{
				AfxMessageBox(_T("非法操作，用户已创建！"));
				return;
		    }
		GetDlgItem(IDC_EDIT1)->GetWindowText(strText1);
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty())
		{ 
			AfxMessageBox(_T("信息不完善，无法添加！"));
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

		if(!m_vLine.empty())                 //检测该生产线名称是否已经存在//
			for(int q=0;q<m_vLine.size();q+=3)
			   if(strText1==m_vLine[q])
			   {
				   AfxMessageBox(_T("非法操作，该生产线名称已存在！"));
				   return;
			   }

		if (strText1.IsEmpty() || strText2.IsEmpty())
		{ 
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		m_vLine.push_back(strText1);
		m_vLine.push_back(strText2);
		m_vLine.push_back(strText3);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T(strText1));//将添加的生产线录入到COMBO1//
	    ((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
		break;
	case 3:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		if (strText1.IsEmpty() || strText2.IsEmpty())                   //判断所录入工艺模块信息是否完全//
		{ 
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		m_vModule.push_back(strText1);   //将录入的信息写入对应容器//
		m_vModule.push_back(strText2);
		m_vModule.push_back(strText3);

		break;
	case 4:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //将所属生产线名称赋值给text1//
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(nTemp,strText2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() || strText4.IsEmpty())  //判断录入信息是否完整//
		{ 
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		m_vDevice.push_back(strText1);         //将添加的信息录入到容器//
		m_vDevice.push_back(strText2);
		m_vDevice.push_back(strText3);
		m_vDevice.push_back(strText4);
		break;
	case 5:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp,strText1);  //将所属生产线名称赋值给text1//
		GetDlgItem(IDC_EDIT2)->GetWindowText(strText2);
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() )  //判断录入信息是否完整//
		{ 
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
		m_vPlc.push_back(strText1);         //将添加的信息录入到容器//
		m_vPlc.push_back(strText2);
		m_vPlc.push_back(strText3);
		m_vPlc.push_back(strText4);
		break;

	case 6:
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nTemp, strText1);  //将所属生产线名称赋值给text1//
		nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
		((CComboBox*)GetDlgItem(IDC_COMBO2))->GetLBText(nTemp, strText2);  //将所属工艺模块名称赋值给text2//
		GetDlgItem(IDC_EDIT3)->GetWindowText(strText3);
		GetDlgItem(IDC_EDIT4)->GetWindowText(strText4);
		if (strText1.IsEmpty() || strText2.IsEmpty() || strText3.IsEmpty() || strText4.IsEmpty())  //判断录入信息是否完整//
		{
			AfxMessageBox(_T("信息不完善，无法添加！"));
			return;
		}
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T("")); //添加成功，清空编辑框//
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		m_vCamera.push_back(strText1);         //将添加的信息录入到容器//
		m_vCamera.push_back(strText2);
		m_vCamera.push_back(strText3);
		m_vCamera.push_back(strText4);
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
	if(!m_vUser.empty() && !m_vLine.empty() && !m_vPlc.empty() && !m_vModule.empty() && !m_vDevice.empty())
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

//列表框控件单击响应函数，点击列表框控件某行时，将该行信息显示在编辑区//
void InitDlg::OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	m_nItem = -1; 

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	m_list_init.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	CString strText1, strText2, strText3, strText4;   //四个临时变量，用于暂存从列标框读取的信息//
	int nCombo1,nCombo2;     //列表框选中条目，在combo1和2里所对应的位置//
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

//“修改”按钮的响应函数//
void InitDlg::OnBnClickedBtEdit()
{
	// TODO:  在此添加控件通知处理程序代码

}

//右击列表框的响应函数//
void InitDlg::OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
 	int index = pNMItemActivate->iItem;  //用户右击的行标//
	if (index == -1)
		return;
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //存储鼠标位置的临时变量//
	GetCursorPos(&point1);//得到光标处//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//确保右键点击在哪菜单出现在哪，并返回所选的菜单项//
	if (nItem1>0)
	{
		int nResult;
		switch (m_IdInit)
		{
		case 1:
		    nResult = MessageBox(_T("该操作将删除用户及其名下所有设备，是否继续当前操作？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
			if (nResult == IDYES)
			{
				std::vector <CString>().swap(m_vUser);    //清除容器并最小化它的容量//
				std::vector <CString>().swap(m_vLine);
				std::vector <CString>().swap(m_vModule);
				std::vector <CString>().swap(m_vDevice);
				std::vector <CString>().swap(m_vPlc);
				std::vector <CString>().swap(m_vCamera);
				GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT2)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
				GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
				OnPaint();                                //重绘窗口//
			} 
	        break;
		case 2:
		default:
			break;
		}
	}
	*pResult = 0;
}
