// InitPlcParaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "InitPlcParaDlg.h"
#include "afxdialogex.h"
#include "DataProvider.h"



// CInitPlcParaDlg 对话框

IMPLEMENT_DYNAMIC(CInitPlcParaDlg, CDialog)

CInitPlcParaDlg::CInitPlcParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitPlcParaDlg::IDD, pParent)
{
	m_nItem = -1;//初始化参数//

	//测试用，可删除，初始化几个vector//
	ProductionLineClass line1;
	line1.m_strLineName = _T("红茶生产线");
	ProductionLineClass line2;
	line2.m_strLineName = _T("绿茶生产线");
	m_vLine.push_back(line1);
	m_vLine.push_back(line2);

	ProcessModuleClass module1;
	module1.m_strProductionLineName = _T("绿茶生产线");
	module1.m_strProcessModuleName = _T("绿茶杀青");
	m_vModule.push_back(module1);

	ProcessModuleClass module2;
	module2.m_strProductionLineName = _T("绿茶生产线");
	module2.m_strProcessModuleName = _T("绿茶风干");
	m_vModule.push_back(module2);

	ProcessModuleClass module3;
	module3.m_strProductionLineName = _T("红茶生产线");
	module3.m_strProcessModuleName = _T("红茶杀青");
	m_vModule.push_back(module3);

	DeviceClass device1;
	device1.m_strProductionLineName = _T("绿茶生产线");
	device1.m_strProcessModuleName = _T("绿茶杀青");
	device1.m_strDeviceName = _T("杀青机");
	m_vDevice.push_back(device1);

	DeviceClass device2;
	device2.m_strProductionLineName = _T("绿茶生产线");
	device2.m_strProcessModuleName = _T("绿茶杀青");
	device2.m_strDeviceName = _T("电机");
	m_vDevice.push_back(device2);

	DeviceClass device3;
	device3.m_strProductionLineName = _T("绿茶生产线");
	device3.m_strProcessModuleName = _T("绿茶风干");
	device3.m_strDeviceName = _T("绿茶风干机");
	m_vDevice.push_back(device3);

	DeviceClass device4;
	device4.m_strProductionLineName = _T("红茶生产线");
	device4.m_strProcessModuleName = _T("红茶杀青");
	device4.m_strDeviceName = _T("杀青机");
	m_vDevice.push_back(device4);

	PlcClass plc1;
	plc1.m_strProductionLineName = _T("红茶生产线");
	plc1.m_strPlcName = _T("红茶一号PLC");
	m_vPlc.push_back(plc1);

	PlcClass plc2;
	plc2.m_strProductionLineName = _T("红茶生产线");
	plc2.m_strPlcName = _T("红茶2号PLC");
	m_vPlc.push_back(plc2);

	PlcClass plc3;
	plc3.m_strProductionLineName = _T("绿茶生产线");
	plc3.m_strPlcName = _T("绿茶一号PLC");
	m_vPlc.push_back(plc3);

	CPlcPara plcpara;
	plcpara.m_bIsConfig = false;
	plcpara.m_bIsVisible = true;
	plcpara.m_strAddressType = _T("I");
	plcpara.m_strAddressIndex = _T("0.0");
	plcpara.m_strLine = _T("绿茶生产线");
	plcpara.m_strModule = _T("绿茶风干");
	plcpara.m_strDevice = _T("绿茶风干机");
	plcpara.m_strPlc = _T("绿茶一号PLC");
	plcpara.m_strValueType = _T("Bool");
	plcpara.m_strNote = _T("启动停止信号");
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
	m_ListInitPlcPara.InsertColumn(2, _T("地址"), LVCFMT_CENTER, rect1.Width() / 25 * 1.6, -1);
	m_ListInitPlcPara.InsertColumn(3, _T("数据类型"), LVCFMT_CENTER, rect1.Width() / 25 * 1.7, -1);
	m_ListInitPlcPara.InsertColumn(4, _T("读写类型"), LVCFMT_CENTER, rect1.Width() / 25 * 1.7, -1);
	m_ListInitPlcPara.InsertColumn(5, _T("所属生产线"), LVCFMT_CENTER, rect1.Width() / 25* 3.3, -1);
	m_ListInitPlcPara.InsertColumn(6, _T("所属工艺模块"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);
	m_ListInitPlcPara.InsertColumn(7, _T("所属设备"), LVCFMT_CENTER, rect1.Width() / 25 * 2.9, -1);
	m_ListInitPlcPara.InsertColumn(8, _T("所属PLC"), LVCFMT_CENTER, rect1.Width() / 25 * 2.9, -1);
	m_ListInitPlcPara.InsertColumn(9, _T("是否进入配方"), LVCFMT_CENTER, rect1.Width() / 25* 2.2, -1);
	m_ListInitPlcPara.InsertColumn(10, _T("用户是否可见"), LVCFMT_CENTER, rect1.Width() /25 * 2.2, -1);
	m_ListInitPlcPara.InsertColumn(11, _T("备注"), LVCFMT_CENTER, rect1.Width() / 25 * 3, -1);

	
	//((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

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
			CString str4;
			int j = n + 1;
			str4.Format("%d", j);
			m_ListInitPlcPara.InsertItem(n , _T(""));
			m_ListInitPlcPara.SetItemText(n , 1, _T(str4));
			m_ListInitPlcPara.SetItemText(n, 2, _T(m_vPlcPara[n].m_strAddressType + m_vPlcPara[n].m_strAddressIndex));
			m_ListInitPlcPara.SetItemText(n, 3, _T(m_vPlcPara[n].m_strValueType));
			if (m_vPlcPara[n].m_bIsReadOnly)
				m_ListInitPlcPara.SetItemText(n, 4, _T("只读"));
			else
				m_ListInitPlcPara.SetItemText(n, 4, _T("读写"));
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
			m_ListInitPlcPara.SetItemText(n, 11, _T(m_vPlcPara[n].m_strNote));
	    }
	} 

	//如果列表框选中了某行，高亮显示//
	if (m_nItem>=0)
	    m_ListInitPlcPara.SetItemState(m_nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	//如果地址类型下拉框为空，则填写地址类型下拉框//
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

	//如果生产线名称下拉框为空，则填写生产线名称到COMBO3//
	if (!m_vLine.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCount()==0)
	{
		for (int n = 0; n < m_vLine.size();n++)            //填写生产线COMBO3//
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T(m_vLine[n].m_strLineName));
		}
	}

	//如果工艺模块下拉框为空，则填写工艺模块名称到COMBO4//	
	if (!m_vModule.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCount() == 0)
   {
	    int nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		if ( nTemp != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, str2);//得到生产线下拉框COMBO3当前选中条目//
			for (int i = 0; i < m_vModule.size();i++)
				if (m_vModule[i].m_strProductionLineName==str2)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(_T(m_vModule[i].m_strProcessModuleName));
					((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(0);
				}	
		}
	}

	//如果设备下拉框为空，则填写设备名称到COMBO5//
	if (!m_vDevice.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCount() == 0)
	{
		int nTemp1 = ((CComboBox*)GetDlgItem(IDC_COMBO4))->GetCurSel();
		if (nTemp1 != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO4))->GetLBText(nTemp1, str2);//得到工艺模块下拉框COMBO4当前选中条目//
			CString str3;
			int nTemp2 = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp2, str3);//得到生产线下拉框COMBO3当前选中条目//
			for (int i = 0; i < m_vDevice.size(); i++)
				if (m_vDevice[i].m_strProcessModuleName==str2 && m_vDevice[i].m_strProductionLineName==str3)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T(m_vDevice[i].m_strDeviceName));
					((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(0);
				}
		}
	}

	//如果PLC下拉框为空，则填写PLC名称到COMBO6//
	if (!m_vPlc.empty() && ((CComboBox*)GetDlgItem(IDC_COMBO6))->GetCount() == 0)
	{
		int nTemp = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		if (nTemp != CB_ERR)
		{
			CString str2;
			((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(nTemp, str2);//得到生产线下拉框COMBO3当前选中条目//
			for (int i = 0; i < m_vPlc.size(); i++)
				if (m_vPlc[i].m_strProductionLineName == str2)
				{
					((CComboBox*)GetDlgItem(IDC_COMBO6))->AddString(_T(m_vPlc[i].m_strPlcName));
					((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(0);
				}
		}
	}
	if (((CComboBox*)GetDlgItem(IDC_COMBO7))->GetCount() == 0)  //填写用户是否可见下拉框//
	{
		((CComboBox*)GetDlgItem(IDC_COMBO7))->AddString(_T("是"));
		((CComboBox*)GetDlgItem(IDC_COMBO7))->AddString(_T("否"));
	}
	if (((CComboBox*)GetDlgItem(IDC_COMBO8))->GetCount() == 0)  //填写是否进入配方下拉框//
	{
		((CComboBox*)GetDlgItem(IDC_COMBO8))->AddString(_T("是"));
		((CComboBox*)GetDlgItem(IDC_COMBO8))->AddString(_T("否"));
	}

	//根据地址类型下拉框的选中条目填写数据类型编辑框//
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

	//根据地址类型下拉框的选中条目填写读写类型下拉框//
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
		    ((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("只读"));
		    ((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		    break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("只读"));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("读写"));
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
			break;
		default:	
			break;
	    }

	// 不为绘图消息调用 CDialog::OnPaint()
}


void CInitPlcParaDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
	OnPaint();
}


void CInitPlcParaDlg::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent();
	OnPaint();
}


void CInitPlcParaDlg::OnCbnSelchangeCombo4()
{
	// TODO:  在此添加控件通知处理程序代码
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent();
	OnPaint();
}

//“添加”按钮的响应函数//
void CInitPlcParaDlg::OnBnClickedBtAddplcpara()
{
	// TODO:  在此添加控件通知处理程序代码
	//获取当前编辑区的内容//
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

	//如果信息填写完整，则写入容器//
	if (strAdressType.IsEmpty() || strAdressIndex.IsEmpty() || strValueType.IsEmpty() || strLine.IsEmpty() || strModule.IsEmpty() || strDevice.IsEmpty() || strPlc.IsEmpty() || strNote.IsEmpty() || nIsConfig == CB_ERR || nIsVisible == CB_ERR||nIsReadWrite ==CB_ERR)
		AfxMessageBox(_T("信息不完善，无法进行添加操作！"));
	else
	{
		m_nItem = -1;     //列表框失去选中行//

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
		m_vPlcPara.push_back(m_PlcPara);//写入容器//
		GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T("")); //清空编辑区//
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

//右击列表框控件的响应函数，实现删除功能//
void CInitPlcParaDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	int index = pNMItemActivate->iItem;  //用户右击的行标//
	if (index == -1)
		return;
	CMenu menu, *pSubMenu;
	menu.LoadMenu(IDR_INITDLG_POP_MENU);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;        //存储鼠标位置的临时变量//
	GetCursorPos(&point1);//得到光标处//
	UINT nItem1 = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD | TPM_TOPALIGN, point1.x, point1.y, GetParent());//确保右键点击在哪菜单出现在哪，并返回所选的菜单项//
	if (nItem1 > 0)
	{
		int nResult;
		nResult = MessageBox(_T("该操作无法恢复，是否继续？"), _T("警告"), MB_ICONEXCLAMATION | MB_YESNO);//警告//
		if (nResult == IDYES)
		{
			m_nItem = -1;     //列表框失去选中行//

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
			OnPaint();                                //重绘窗口//
		}
	}
	*pResult = 0;
}

	


//单击列表框，将该列显示回编辑区//
void CInitPlcParaDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	m_nItem = -1;

	LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	if (lpNMItemActivate != NULL)
	{
		m_nItem = lpNMItemActivate->iItem;
	}
	if (m_nItem == -1)
		return;

	int nCombo;     //列表框选中条目在combo里所对应的位置//

	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO1))->FindStringExact(0, m_vPlcPara[m_nItem].m_strAddressType);//填写地址类型下拉框//
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(nCombo);

	((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();  //填写读写类型下拉框//
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
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("只读"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("只读"));
		((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("读写"));
		if (m_vPlcPara[m_nItem].m_bIsReadOnly)
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
		else
			((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(1);
		break;
	default:
		((CComboBox*)GetDlgItem(IDC_COMBO2))->ResetContent();
		break;
	}
	

	GetDlgItem(IDC_EDIT1)->SetWindowTextA(_T(m_vPlcPara[m_nItem].m_strAddressIndex));//填写地址索引编辑框//

	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO3))->FindStringExact(0, m_vPlcPara[m_nItem].m_strLine);//显示当前条目所属生产线//
	if (nCombo != CB_ERR)
		((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(nCombo);
	else
	{
		AfxMessageBox(_T("未知错误！"));
		return;
	}

	((CComboBox*)GetDlgItem(IDC_COMBO4))->ResetContent(); //重新填写所属模块下拉框，并显示对应条目//
	for (int i = 0; i < m_vModule.size(); i++)
		if (m_vModule[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO4))->AddString(_T(m_vModule[i].m_strProcessModuleName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO4))->FindStringExact(0, m_vPlcPara[m_nItem].m_strModule);
	((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(nCombo);
		
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ResetContent(); //重新填写所属设备下拉框，并显示对应条目//
	for (int i = 0; i < m_vDevice.size(); i++)
		if (m_vDevice[i].m_strProcessModuleName == m_vPlcPara[m_nItem].m_strModule && m_vDevice[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T(m_vDevice[i].m_strDeviceName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO5))->FindStringExact(0, m_vPlcPara[m_nItem].m_strDevice);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(nCombo);
		
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ResetContent(); //重新填写所属PLC下拉框，并显示对应条目//
	for (int i = 0; i < m_vPlc.size(); i++)
		if (m_vPlc[i].m_strProductionLineName == m_vPlcPara[m_nItem].m_strLine)
			((CComboBox*)GetDlgItem(IDC_COMBO6))->AddString(_T(m_vPlc[i].m_strPlcName));
	nCombo = ((CComboBox*)GetDlgItem(IDC_COMBO6))->FindStringExact(0, m_vPlcPara[m_nItem].m_strPlc);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(nCombo);

	GetDlgItem(IDC_EDIT2)->SetWindowTextA(_T(m_vPlcPara[m_nItem].m_strNote));//填写备注编辑框//

	if (m_vPlcPara[m_nItem].m_bIsVisible)              //用户是否可见下拉框显示对应条目//
		((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(0);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO7))->SetCurSel(1);

	if (m_vPlcPara[m_nItem].m_bIsConfig)              //用户是否可见下拉框显示对应条目//
		((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(0);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO8))->SetCurSel(1);

	OnPaint();

	*pResult = 0;
}

//“修改”按钮的响应函数//
void CInitPlcParaDlg::OnBnClickedBtEditplcpara()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nItem == -1)
		return;
	CString strAdressType, strAdressIndex, strValueType, strLine, strModule, strDevice, strPlc, strNote;//用于存储编辑区内容的临时变量//
	int nTemp = -1;
	int nIsConfig = -1, nIsVisible = -1,nIsReadWrite = -1;

	//获取编辑区内容到临时变量//
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

	//若信息完整，则修改对应数据//
	if (strAdressType.IsEmpty() || strAdressIndex.IsEmpty() || strValueType.IsEmpty() || strLine.IsEmpty() || strModule.IsEmpty() || strDevice.IsEmpty() || strPlc.IsEmpty() || strNote.IsEmpty() || nIsConfig == CB_ERR || nIsVisible == CB_ERR || nIsReadWrite ==CB_ERR)
	{
	    
		AfxMessageBox(_T("信息不完善，无法进行该操作！"));
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

//“清空编辑区”按钮响应函数//
void CInitPlcParaDlg::OnBnClickedBtCleareditarea()
{
	// TODO:  在此添加控件通知处理程序代码
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
	m_nItem = -1; //去掉列表框某行的选中状态//
	OnPaint();
}

//清空所有变量，响应函数//
void CInitPlcParaDlg::OnBnClickedBtClearallpara()
{
	// TODO:  在此添加控件通知处理程序代码
	std::vector <CPlcPara>().swap(m_vPlcPara);    //清除容器并最小化它的容量//
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
	m_nItem = -1;//去掉列表框某行的选中状态//
	OnPaint();
}


void CInitPlcParaDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxMessageBox(_T("确认"));

	CDialog::OnCancel();

}





void CInitPlcParaDlg::OnBnClickedBtSaveall()
{
	// TODO:  在此添加控件通知处理程序代码
	m_dataProvider.DeleteDbTable(CDataProvider::tbPLCSymbol);

	m_dataProvider.SaveAllPlcParaToDatabase();


}
