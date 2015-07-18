#pragma once
class PlcClass
{
public:
	PlcClass();
	~PlcClass();
	int m_Id;
	CString m_strPlcName;
	CString m_strDescription;
	CString m_strProductionLineName;
//	CString Port;
	CString m_strPort;
};

