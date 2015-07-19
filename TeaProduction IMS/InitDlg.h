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



// InitDlg �Ի���

class InitDlg : public CDialog
{
	DECLARE_DYNAMIC(InitDlg)

public:
	InitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InitDlg();

	static const int USER_DATA_EDIT = 1;
	static const int PRODUCTION_LINE_DATA_EDIT = 2;
	static const int MODULE_DATA_EDIT = 3;
	static const int DEVICE_DATA_EDIT = 4;
	static const int PLC_DATA_EDIT = 5;
	static const int VIDEO_DATA_EDIT = 6;



// �Ի�������
	enum { IDD = IDD_INITDLG };

	int id_init;    //��ʶ��ǰ������ӵ����ݣ�1����û���2�����ߣ�3ģ�飻4�豸��5PLC;6����ͷ//
	int m_userId;

	int m_nItem;            //�б��ؼ���ǰѡ���е��������//
	CDataProvider m_dataPorvider;

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
	afx_msg void OnBnClickedBtFinish();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedStatic4();

	


	afx_msg void OnNMClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListInit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtEdit();
};
