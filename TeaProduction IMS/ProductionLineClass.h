#pragma once
class ProductionLineClass
{
public:
	ProductionLineClass();
	~ProductionLineClass();
	int m_Id;
	CString m_strCreateDateTime;
	CString m_strLastUpdateTime;
	CString m_strLineName;
	int m_UserId;
	CString m_strCapacity;
	CString m_strDescription;
};

