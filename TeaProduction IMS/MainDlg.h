#include "MainChildDlg1.h"
#include <vector>
#pragma once
#define WM_POPINITDLG WM_USER+1

// MainDlg �Ի���

class MainDlg : public CDialog
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainDlg();

// �Ի�������
	enum { IDD = IDD_MAINDLG };

	//������ڴ洢�û��б��������б�ģ�顢�豸��PLC������ͷ�б������//
	std::vector<CString> Vuser;     
	std::vector<CString> Vline;
	std::vector<CString> Vmudole;
	std::vector<CString> Vdevice;
	std::vector<CString> Vplc;
	std::vector<CString> Vcamera;

	//�ӶԻ������//
	MainChildDlg1 childdlg1;

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_tree;
	afx_msg void OnPopinitdlg();
	afx_msg void OnPaint();
	afx_msg void OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
