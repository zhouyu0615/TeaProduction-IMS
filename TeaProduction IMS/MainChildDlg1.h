#pragma once


// MainChildDlg1 �Ի���

class MainChildDlg1 : public CDialog
{
	DECLARE_DYNAMIC(MainChildDlg1)

public:
	MainChildDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainChildDlg1();

// �Ի�������
	enum { IDD = IDD_MAINCHILDDLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
