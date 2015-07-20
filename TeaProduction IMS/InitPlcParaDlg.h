#pragma once
#include "PlcPara.h"
#include <vector>
#include "afxcmn.h"
#include "PlcClass.h"
#include "DeviceClass.h"
#include "ProcessModuleClass.h"
#include "ProductionLineClass.h"
#include  "DataProvider.h"

// CInitPlcParaDlg 对话框

class CInitPlcParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitPlcParaDlg)

public:
	CInitPlcParaDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInitPlcParaDlg();

// 对话框数据
	enum { IDD = IDD_INITPLCPARA };
	std::vector<CPlcPara> m_vPlcPara; //用于存储PLC变量的容器//
	CPlcPara m_PlcPara;    //用于暂存一条PLC变量记录//
	int m_nItem;//用于暂存用户单击列表框时鼠标所在的行标//

	std::vector<PlcClass> m_vPlc;
	std::vector<DeviceClass> m_vDevice;
	std::vector<ProcessModuleClass> m_vModule;
	std::vector<ProductionLineClass> m_vLine;
	


	CDataProvider m_dataProvider;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListInitPlcPara;
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedBtAddplcpara();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtEditplcpara();
	afx_msg void OnBnClickedBtCleareditarea();
	afx_msg void OnBnClickedBtClearallpara();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnBnClickedBtSaveall();
};
