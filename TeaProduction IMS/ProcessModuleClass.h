#pragma once
class ProcessModuleClass
{
public:
	ProcessModuleClass();
	~ProcessModuleClass();
	int m_Id;
	CString m_strCreateDateTime;
	CString m_strLastUpdateTime;
	CString m_strModuleName;
	int m_ProcessLineId;  //所属生产线的ID
	CString m_strProductionLineName;
	CString m_strDescription;
	CString m_strProcessModuleName;
	
};

