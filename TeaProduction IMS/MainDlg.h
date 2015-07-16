#include "MainChildDlg1.h"
#include <vector>
#pragma once
#define WM_POPINITDLG WM_USER+1

// MainDlg 对话框

class MainDlg : public CDialog
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainDlg();

// 对话框数据
	enum { IDD = IDD_MAINDLG };

	//添加用于存储用户列表、生产线列表、模块、设备、PLC、摄像头列表的容器//
	std::vector<CString> Vuser;     
	std::vector<CString> Vline;
	std::vector<CString> Vmudole;
	std::vector<CString> Vdevice;
	std::vector<CString> Vplc;
	std::vector<CString> Vcamera;

	//子对话框变量//
	MainChildDlg1 childdlg1;

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_tree;
	afx_msg void OnPopinitdlg();
	afx_msg void OnPaint();
	afx_msg void OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
