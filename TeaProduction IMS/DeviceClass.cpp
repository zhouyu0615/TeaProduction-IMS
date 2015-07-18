#include "stdafx.h"
#include "DeviceClass.h"


DeviceClass::DeviceClass()
{
	m_Id = 0;
	m_strDeviceName = _T("");
	m_ProcessModuleId = 0;
	m_strProductionLineName = _T("");
	m_strProcessModuleName = _T("");
	m_strDeviceType = _T("");
	//  m_strModuleName = _T("");
}


DeviceClass::~DeviceClass()
{
}
