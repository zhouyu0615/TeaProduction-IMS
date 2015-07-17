#pragma once

#include <vector>
#include "afxcmn.h"

// InitDlg �Ի���

class InitDlg : public CDialog
{
	DECLARE_DYNAMIC(InitDlg)

public:
	InitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InitDlg();

// �Ի�������
	enum { IDD = IDD_INITDLG };

	int id_init;    //��ʶ��ǰ������ӵ����ݣ�1����û���2�����ߣ�3ģ�飻4�豸��5PLC;6����ͷ//
	int m_userId;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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


	//������ڴ洢�û��б��������б�ģ�顢�豸��PLC������ͷ�б������//
	std::vector<CString> Vuser;     
	std::vector<CString> Vline;
	std::vector<CString> Vmudole;
	std::vector<CString> Vdevice;
	std::vector<CString> Vplc;
	std::vector<CString> Vcamera;

	CListCtrl m_list_init;  //�б�ؼ��Ĺ�������//
	afx_msg void OnBnClickedBtFinish();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedStatic4();


	void SaveUserToDatabase();
	void ReadUserFromDatabase();
	void SaveProLineToDatabase();
	void ReadProLineFromDatabase();






};
