#include "stdafx.h"
#include "ProductionLineClass.h"


ProductionLineClass::ProductionLineClass()
{
	m_Id = 0;
	m_strCreateDateTime = _T("");
	m_strLastUpdateTime = _T("");
	m_strLineName = _T("");
	m_UserId = 0;
	m_strCapacity = _T("");
	m_strDescription = _T("");
}


ProductionLineClass::~ProductionLineClass()
{
}
