#pragma once
class VideoClass
{
public:
	VideoClass();
	~VideoClass();
	int m_Id;
	CString m_strVideoName;
	CString m_strProcessModuleName;
	CString m_strProductionLineName;
	CString m_strPort;

	int m_ProductionLineId;
	int m_ModuleId;
};

