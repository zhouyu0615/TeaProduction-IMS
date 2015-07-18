#include "stdafx.h"
#include "ProcessModuleClass.h"


ProcessModuleClass::ProcessModuleClass()
{
	m_Id = 0;
	m_strCreateDateTime = _T("");
	m_strLastUpdateTime = _T("");
	//  m_strModuleName = _T("");
	m_ProcessLineId = 0;
	m_strDescription = _T("");
	m_strProcessModuleName = _T("");
	m_strProductionLineName = _T("");
}


ProcessModuleClass::~ProcessModuleClass()
{
}
