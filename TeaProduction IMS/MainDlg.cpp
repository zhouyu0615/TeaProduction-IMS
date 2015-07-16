// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TeaProduction IMS.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "LoginDlg.h"

// MainDlg 对话框

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


// MainDlg 消息处理程序


BOOL MainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  添加自己的代码

	//初始化子对话框//
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
	// TODO: 在此添加命令处理程序代码
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
		AfxMessageBox(_T("您没有权限进行该操作！"));
}


void MainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	//初始化树形控件//
	m_tree.DeleteAllItems();   //清空树形控件//
	HTREEITEM hRoot;       //树的根节点句柄//
	HTREEITEM hFirItem;    //任一一级节点的句柄//
    HTREEITEM hSecItem;    //任一二级节点的句柄//
    HTREEITEM hThdItem;    //任一三级节点的句柄//
	HTREEITEM hFouItem;    //任一四级节点的句柄//
	hRoot = m_tree.InsertItem(Vuser[0]);       //添加树形控件内容//
	          
	for(int nline = 0;nline<Vline.size();nline+=3)             //写入该用户名下的所有生产线//
	{
		hFirItem = m_tree.InsertItem((Vline[nline]), NULL, NULL, hRoot, TVI_LAST); 
		hSecItem = m_tree.InsertItem(_T("工艺模块"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nmudole=0; nmudole<Vmudole.size(); nmudole+=3)               //写入该条生产线对应的工艺模块//
		{
		    if (Vmudole[nmudole]==Vline[nline])
				{
					hThdItem = m_tree.InsertItem((Vmudole[nmudole+1]), NULL, NULL, hSecItem, TVI_LAST);
			        for(int ndevice=0; ndevice<Vdevice.size(); ndevice+=4)               //写入该工艺模块底下的所有设备// 
						if(Vdevice[ndevice]==Vmudole[nmudole] && Vdevice[ndevice+1]==Vmudole[nmudole+1])
							hFouItem = m_tree.InsertItem((Vdevice[ndevice+2]), NULL, NULL, hThdItem, TVI_LAST);
			    }
		}
		hSecItem = m_tree.InsertItem(_T("PLC"), NULL, NULL, hFirItem, TVI_LAST);
		for (int nplc=0; nplc<Vplc.size(); nplc+=4)           //写入该生产线下的所有PLC//
			if(Vplc[nplc]==Vline[nline])
		         hThdItem = m_tree.InsertItem((Vplc[nplc+1]), NULL, NULL, hSecItem, TVI_LAST);
	}
	
	// 不为绘图消息调用 CDialog::OnPaint()
}



void MainDlg::OnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
