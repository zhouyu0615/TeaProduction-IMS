#pragma once

#include <vector>
#include "afxcmn.h"
#include "InitPlcParaDlg.h"

// InitDlg �Ի���

class InitDlg : public CDialog
{
	DECLARE_DYNAMIC(InitDlg)

public:
	InitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InitDlg();

// �Ի�������
	enum { IDD = IDD_INITDLG };

	int m_IdInit;    //��ʶ��ǰ������ӵ����ݣ�1����û���2�����ߣ�3ģ�飻4�豸��5PLC;6����ͷ//

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
	std::vector<CString> m_vUser;     
	std::vector<CString> m_vLine;
	std::vector<CString> m_vModule;
	std::vector<CString> m_vDevice;
	std::vector<CString> m_vPlc;
	std::vector<CString> m_vCamera;

	CListCtrl m_list_init;  //�б�ؼ��Ĺ�������//
	int m_nItem;            //�б��ؼ���ǰѡ���е��������//
	CInitPlcParaDlg m_InitPlcParaDlg;      //��ʼ��PLC�����Ľ���//
	afx_msg void OnBnClickedBtFinish();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtEdit();
	afx_msg void OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtAddplcpara();
};
