#include "MainDlg.h"
#include "InitDlg.h"
// LoginDlg.h : ͷ�ļ�
//
#define WM_POPINITDLG WM_USER+1
#pragma once


// LoginDlg �Ի���
class LoginDlg : public CDialog
{
// ����
public:
	LoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEAPRODUCTIONIMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT PopInitDlg(WPARAM wParam, LPARAM lParam);//������������ʼ���Ի�����Ϣ����Ӧ����//
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	static bool userright;                 //�û�Ȩ�ޱ�ʶ��0�������Ա��1�������Ա//
	static bool isinit;                     //ϵͳ�Ƿ��ʼ����ʶ����true��ʾ�ѳ�ʼ����false��ʾδ��ʼ��//
	MainDlg maindlg;   //������//
	InitDlg initdlg;   //��ʼ�����ý���//
    void GetInitPara();//����ʼ���������õĲ������ݵ�������Ի�����//
};
