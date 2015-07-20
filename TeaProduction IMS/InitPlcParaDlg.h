#pragma once
#include "PlcPara.h"
#include <vector>
#include "afxcmn.h"
#include "PlcClass.h"
#include "DeviceClass.h"
#include "ProcessModuleClass.h"
#include "ProductionLineClass.h"
#include  "DataProvider.h"

// CInitPlcParaDlg �Ի���

class CInitPlcParaDlg : public CDialog
{
	DECLARE_DYNAMIC(CInitPlcParaDlg)

public:
	CInitPlcParaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInitPlcParaDlg();

// �Ի�������
	enum { IDD = IDD_INITPLCPARA };
	std::vector<CPlcPara> m_vPlcPara; //���ڴ洢PLC����������//
	CPlcPara m_PlcPara;    //�����ݴ�һ��PLC������¼//
	int m_nItem;//�����ݴ��û������б��ʱ������ڵ��б�//

	std::vector<PlcClass> m_vPlc;
	std::vector<DeviceClass> m_vDevice;
	std::vector<ProcessModuleClass> m_vModule;
	std::vector<ProductionLineClass> m_vLine;
	


	CDataProvider m_dataProvider;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListInitPlcPara;
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedBtAddplcpara();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtEditplcpara();
	afx_msg void OnBnClickedBtCleareditarea();
	afx_msg void OnBnClickedBtClearallpara();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnBnClickedBtSaveall();
};
