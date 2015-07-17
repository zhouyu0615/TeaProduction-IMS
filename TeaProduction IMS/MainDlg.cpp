// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// MainDlg �Ի���

IMPLEMENT_DYNAMIC(MainDlg, CDialog)

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MainDlg::IDD, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialog)
	ON_COMMAND(IDM_POPINITDLG, &MainDlg::OnPopinitdlg)
	ON_WM_PAINT()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &MainDlg::OnItemclickList1)
END_MESSAGE_MAP()


// MainDlg ��Ϣ�������


BOOL MainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ����Լ��Ĵ���

	//��ʼ���ӶԻ���//
	m_ChildDlg1.Create(IDD_MAINCHILDDLG1,this);
	CRect rect1;
	m_ChildDlg1.GetClientRect(rect1);
	CRect rect2(270,150,rect1.right+270,rect1.bottom+150);
	m_ChildDlg1.MoveWindow(rect2);
	m_ChildDlg1.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	
}


void MainDlg::OnPopinitdlg()
{
	// TODO: �ڴ���������������
	if(LoginDlg::s_bUserRight == 1)
	{
	   HWND m_MacHwnd;
	   CWnd *m_MacCwnd;
	   m_MacCwnd = AfxGetMainWnd();
	   m_MacHwnd = m_MacCwnd->GetSafeHwnd();
	   ::SendMessage(m_MacHwnd,WM_POPINITDLG,0,0);
	   OnPaint();
	}
	else
		AfxMessageBox(_T("��û��Ȩ�޽��иò�����"));
}


void MainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//��ʼ�����οؼ�//
	m_tree.DeleteAllItems();   //������οؼ�//
	HTREEITEM hRoot;       //���ĸ��ڵ���//
	HTREEITEM hFirItem;    //��һһ���ڵ�ľ��//
    HTREEITEM hSecItem;    //��һ�����ڵ�ľ��//
    HTREEITEM hThdItem;    //��һ�����ڵ�ľ��//
	HTREEITEM hFouItem;    //��һ�ļ��ڵ�ľ��//
	hRoot = m_tree.InsertItem(m_vUser[0]);       //������οؼ�����//
	          
	for(int nLine = 0;nLine<m_vLine.size();nLine+=3)             //д����û����µ�����������//
	{
		hFirItem = m_tree.InsertItem((m_vLine[nLine]), NULL, NULL, hRoot, TVI_LAST); 
		hSecItem = m_tree.InsertItem(_T("����ģ��"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nMudole=0; nMudole<m_vModule.size(); nMudole+=3)               //д����������߶�Ӧ�Ĺ���ģ��//
		{
		    if (m_vModule[nMudole]==m_vLine[nLine])
				{
					hThdItem = m_tree.InsertItem((m_vModule[nMudole+1]), NULL, NULL, hSecItem, TVI_LAST);
			        for(int nDevice=0; nDevice<m_vDevice.size(); nDevice+=4)               //д��ù���ģ����µ������豸// 
						if(m_vDevice[nDevice]==m_vModule[nMudole] && m_vDevice[nDevice+1]==m_vModule[nMudole+1])
							hFouItem = m_tree.InsertItem((m_vDevice[nDevice+2]), NULL, NULL, hThdItem, TVI_LAST);
			    }
		}
		hSecItem = m_tree.InsertItem(_T("PLC"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nPlc=0; nPlc<m_vPlc.size(); nPlc+=4)           //д����������µ�����PLC//
			if(m_vPlc[nPlc]==m_vLine[nLine])
		         hThdItem = m_tree.InsertItem((m_vPlc[nPlc+1]), NULL, NULL, hSecItem, TVI_LAST);
	}
	
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}



void MainDlg::OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
