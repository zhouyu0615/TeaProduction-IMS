// tbPLc.h : CtbPLc ���ʵ��



// CtbPLc ʵ��

// ���������� 2015��7��18�� ������, 12:05

#include "stdafx.h"
#include "tbPLc.h"
IMPLEMENT_DYNAMIC(CtbPLc, CRecordset)

CtbPLc::CtbPLc(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_PLCName = "";
	m_PortId = 0;
	m_UserId = 0;
	m_Description = "";
	m_ProductionLineName = "";
	m_ProductionLineId = 0;
	m_strPort = "";
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CtbPLc::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbPLc::GetDefaultSQL()
{
	return _T("[dbo].[tbPLc]");
}

void CtbPLc::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Text(pFX, _T("[PLCName]"), m_PLCName);
	RFX_Long(pFX, _T("[PortId]"), m_PortId);
	RFX_Long(pFX, _T("[UserId]"), m_UserId);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);
	RFX_Text(pFX, _T("[strPort]"), m_strPort);

}
/////////////////////////////////////////////////////////////////////////////
// CtbPLc ���

#ifdef _DEBUG
void CtbPLc::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbPLc::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


