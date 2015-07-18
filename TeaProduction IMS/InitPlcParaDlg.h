#pragma once
#include "PlcPara.h"
#include <vector>
#include "afxcmn.h"
#include "PlcClass.h"
#include "DeviceClass.h"
#include "ProcessModuleClass.h"
#include "ProductionLineClass.h"
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

	std::vector<PlcClass> m_Plc;
	std::vector<DeviceClass> m_Device;
	std::vector<ProcessModuleClass> m_Module;
	std::vector<ProductionLineClass> m_Line;
	


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
};
