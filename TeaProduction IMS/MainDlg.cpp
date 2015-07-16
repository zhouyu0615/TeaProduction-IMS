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
	childdlg1.Create(IDD_MAINCHILDDLG1,this);
	CRect rect1;
	childdlg1.GetClientRect(rect1);
	CRect rect2(270,150,rect1.right+270,rect1.bottom+150);
	childdlg1.MoveWindow(rect2);
	childdlg1.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	
}


void MainDlg::OnPopinitdlg()
{
	// TODO: �ڴ���������������
	if(LoginDlg::userright == 1)
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
	hRoot = m_tree.InsertItem(Vuser[0]);       //������οؼ�����//
	          
	for(int nline = 0;nline<Vline.size();nline+=3)             //д����û����µ�����������//
	{
		hFirItem = m_tree.InsertItem((Vline[nline]), NULL, NULL, hRoot, TVI_LAST); 
		hSecItem = m_tree.InsertItem(_T("����ģ��"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nmudole=0; nmudole<Vmudole.size(); nmudole+=3)               //д����������߶�Ӧ�Ĺ���ģ��//
		{
		    if (Vmudole[nmudole]==Vline[nline])
				{
					hThdItem = m_tree.InsertItem((Vmudole[nmudole+1]), NULL, NULL, hSecItem, TVI_LAST);
			        for(int ndevice=0; ndevice<Vdevice.size(); ndevice+=4)               //д��ù���ģ����µ������豸// 
						if(Vdevice[ndevice]==Vmudole[nmudole] && Vdevice[ndevice+1]==Vmudole[nmudole+1])
							hFouItem = m_tree.InsertItem((Vdevice[ndevice+2]), NULL, NULL, hThdItem, TVI_LAST);
			    }
		}
		hSecItem = m_tree.InsertItem(_T("PLC"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nplc=0; nplc<Vplc.size(); nplc+=4)           //д����������µ�����PLC//
			if(Vplc[nplc]==Vline[nline])
		         hThdItem = m_tree.InsertItem((Vplc[nplc+1]), NULL, NULL, hSecItem, TVI_LAST);
	}
	
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}



void MainDlg::OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
