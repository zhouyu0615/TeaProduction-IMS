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
	int m_ProcessLineId;  //���������ߵ�ID
	CString m_strDescription;
};
