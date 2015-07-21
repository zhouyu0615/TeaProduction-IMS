// tbPLCSymbol.h : CtbPLCSymbol ������

#pragma once

// ���������� 2015��7��21�� ���ڶ�, 15:48

class CtbPLCSymbol : public CRecordset
{
public:
	CtbPLCSymbol(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CtbPLCSymbol)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_Id;
	CTime	m_CreatedDateTime;
	CTime	m_LastUpdatedDateTime;
	CStringA	m_AddressType;
	CStringA	m_AddressIndex;
	long	m_PLCId;
	long	m_ProcessModuleId;
	long	m_DeviceId;
	CStringA	m_Value;
	BOOL	m_IsVisible;
	BOOL	m_IsConfig;
	CStringA	m_PlcName;
	CStringA	m_ProductionLineName;
	CStringA	m_ProcessModuleName;
	CStringA	m_DeviceName;
	CStringA	m_ValueType;
	CStringA	m_strNote;
	BOOL	m_IsReadOnly;
	long	m_ProductionLineId;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


