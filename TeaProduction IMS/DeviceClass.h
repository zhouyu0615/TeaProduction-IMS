#pragma once
class DeviceClass
{
public:
	DeviceClass();
	~DeviceClass();
	int m_Id;
	CString m_strDeviceName;
	int m_ProcessModuleId;
	CString m_strProductionLineName;
	CString m_strProcessModuleName;
	CString m_strDeviceType;
	int m_ProductionLineId;
//	CString m_strModuleName;
};

