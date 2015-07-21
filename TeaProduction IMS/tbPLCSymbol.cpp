// tbPLCSymbol.h : CtbPLCSymbol 类的实现



// CtbPLCSymbol 实现

// 代码生成在 2015年7月21日 星期二, 15:48

#include "stdafx.h"
#include "tbPLCSymbol.h"
IMPLEMENT_DYNAMIC(CtbPLCSymbol, CRecordset)

CtbPLCSymbol::CtbPLCSymbol(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_CreatedDateTime;
	m_LastUpdatedDateTime;
	m_AddressType = "";
	m_AddressIndex = "";
	m_PLCId = 0;
	m_ProcessModuleId = 0;
	m_DeviceId = 0;
	m_Value = "";
	m_IsVisible = FALSE;
	m_IsConfig = FALSE;
	m_PlcName = "";
	m_ProductionLineName = "";
	m_ProcessModuleName = "";
	m_DeviceName = "";
	m_ValueType = "";
	m_strNote = "";
	m_IsReadOnly = FALSE;
	m_ProductionLineId = 0;
	m_nFields = 19;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CtbPLCSymbol::GetDefaultConnect()
{
	return _T("DSN=xfcj_SQLSERVER;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=ZHOUYU-PC");
}

CString CtbPLCSymbol::GetDefaultSQL()
{
	return _T("[dbo].[tbPLCSymbol]");
}

void CtbPLCSymbol::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[Id]"), m_Id);
	RFX_Date(pFX, _T("[CreatedDateTime]"), m_CreatedDateTime);
	RFX_Date(pFX, _T("[LastUpdatedDateTime]"), m_LastUpdatedDateTime);
	RFX_Text(pFX, _T("[AddressType]"), m_AddressType);
	RFX_Text(pFX, _T("[AddressIndex]"), m_AddressIndex);
	RFX_Long(pFX, _T("[PLCId]"), m_PLCId);
	RFX_Long(pFX, _T("[ProcessModuleId]"), m_ProcessModuleId);
	RFX_Long(pFX, _T("[DeviceId]"), m_DeviceId);
	RFX_Text(pFX, _T("[Value]"), m_Value);
	RFX_Bool(pFX, _T("[IsVisible]"), m_IsVisible);
	RFX_Bool(pFX, _T("[IsConfig]"), m_IsConfig);
	RFX_Text(pFX, _T("[PlcName]"), m_PlcName);
	RFX_Text(pFX, _T("[ProductionLineName]"), m_ProductionLineName);
	RFX_Text(pFX, _T("[ProcessModuleName]"), m_ProcessModuleName);
	RFX_Text(pFX, _T("[DeviceName]"), m_DeviceName);
	RFX_Text(pFX, _T("[ValueType]"), m_ValueType);
	RFX_Text(pFX, _T("[strNote]"), m_strNote);
	RFX_Bool(pFX, _T("[IsReadOnly]"), m_IsReadOnly);
	RFX_Long(pFX, _T("[ProductionLineId]"), m_ProductionLineId);

}
/////////////////////////////////////////////////////////////////////////////
// CtbPLCSymbol 诊断

#ifdef _DEBUG
void CtbPLCSymbol::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtbPLCSymbol::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


