#pragma once
#include <vector>
class CPlcPara
{
public:
	CPlcPara();
	~CPlcPara();
	CString m_AddressType; //地址类型//
	CString m_ValueType;//数据类型//
	CString m_AddressIndex;//地址值//
	CString m_Value;//值//
	CString m_Plc;//所属PLC//
	CString m_Line;//所属生产线//
	CString m_Module; ////
};

