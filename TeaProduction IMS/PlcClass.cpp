#include "stdafx.h"
#include "PlcClass.h"


PlcClass::PlcClass()
{
	m_Id = 0;
	m_strPlcName = _T("");
	m_strDescription = _T("");
	m_strProductionLineName = _T("");
	//  Port = _T("");
	m_strPort = _T("");
}


PlcClass::~PlcClass()
{
}
