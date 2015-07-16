#pragma once


// MainChildDlg1 对话框

class MainChildDlg1 : public CDialog
{
	DECLARE_DYNAMIC(MainChildDlg1)

public:
	MainChildDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainChildDlg1();

// 对话框数据
	enum { IDD = IDD_MAINCHILDDLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
