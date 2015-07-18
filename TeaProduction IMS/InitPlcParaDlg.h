#pragma once
#include "PlcPara.h"
#include <vector>
#include "afxcmn.h"
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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListInitPlcPara;
	afx_msg void OnPaint();
};
