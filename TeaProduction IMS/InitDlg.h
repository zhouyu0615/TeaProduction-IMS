#pragma once

#include <vector>
#include "afxcmn.h"
#include "UserClass.h"
#include "ProcessModuleClass.h"
#include "ProductionLineClass.h"
#include "PlcClass.h"
#include "DeviceClass.h"
#include "VideoClass.h"
#include  "DataProvider.h"



// InitDlg 对话框

class InitDlg : public CDialog
{
	DECLARE_DYNAMIC(InitDlg)

public:
	InitDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InitDlg();

	static const int USER_DATA_EDIT = 1;
	static const int PRODUCTION_LINE_DATA_EDIT = 2;
	static const int MODULE_DATA_EDIT = 3;
	static const int DEVICE_DATA_EDIT = 4;
	static const int PLC_DATA_EDIT = 5;
	static const int VIDEO_DATA_EDIT = 6;



// 对话框数据
	enum { IDD = IDD_INITDLG };

	int id_init;    //标识当前正在添加的内容，1添加用户；2生产线；3模块；4设备；5PLC;6摄像头//
	int m_userId;

	int m_nItem;            //列表框控件当前选中行的首行序号//
	CDataProvider m_dataPorvider;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtAdduser();
	afx_msg void OnBnClickedBtAddline();
	afx_msg void OnBnClickedBtAddmodule();
	afx_msg void OnBnClickedBtAdddevice();
	afx_msg void OnBnClickedBtAddplc();
	afx_msg void OnBnClickedBtFormula();
	afx_msg void OnBnClickedBtInitadd();


	//添加用于存储用户列表、生产线列表、模块、设备、PLC、摄像头列表的容器//
	std::vector<CString> m_vUser;     
	std::vector<CString> m_vLine;
	std::vector<CString> m_vModule;
	std::vector<CString> m_vDevice;
	std::vector<CString> m_vPlc;
	std::vector<CString> m_vCamera;

   

	


	CListCtrl m_list_init;  //列表控件的关联变量//
	afx_msg void OnBnClickedBtFinish();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedStatic4();

	


	afx_msg void OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtEdit();
};
