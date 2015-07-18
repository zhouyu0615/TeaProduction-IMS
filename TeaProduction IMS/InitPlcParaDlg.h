#pragma once
#include "PlcPara.h"
#include <vector>
#include "afxcmn.h"
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListInitPlcPara;
	afx_msg void OnPaint();
};
