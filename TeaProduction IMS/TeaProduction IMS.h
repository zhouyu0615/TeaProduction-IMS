
// TeaProduction IMS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTeaProIMSApp:
// �йش����ʵ�֣������ TeaProduction IMS.cpp
//

class CTeaProIMSApp : public CWinApp
{
public:
	CTeaProIMSApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTeaProIMSApp theApp;