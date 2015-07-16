#include "MainDlg.h"
#include "InitDlg.h"
// LoginDlg.h : 头文件
//
#define WM_POPINITDLG WM_USER+1
#pragma once


// LoginDlg 对话框
class LoginDlg : public CDialog
{
// 构造
public:
	LoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEAPRODUCTIONIMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT PopInitDlg(WPARAM wParam, LPARAM lParam);//声明“弹出初始化对话框”消息的响应函数//
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	static bool userright;                 //用户权限标识，0代表操作员，1代表管理员//
	static bool isinit;                     //系统是否初始化标识符，true表示已初始化，false表示未初始化//
	MainDlg maindlg;   //主界面//
	InitDlg initdlg;   //初始化设置界面//
    void GetInitPara();//将初始化界面设置的参数传递到主界面对话框类//
};
