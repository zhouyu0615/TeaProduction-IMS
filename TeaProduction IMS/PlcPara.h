#pragma once
#include <vector>
class CPlcPara
{
public:
	CPlcPara();
	~CPlcPara();
	CString m_strAddressType;    //��ַ����//
	CString m_strValueType;      //��������//
	CString m_strAddressIndex;   //��ֵַ//
	CString m_strValue;     //ֵ//
	CString m_strPlc;       //����PLC//
	CString m_strLine;      //����������//
	CString m_strModule;    //����ģ������//
	CString m_strDevice;    //�����豸����//
	bool m_bIsVisible;    //�û��Ƿ�ɼ�//
	bool m_bIsConfig;     //�Ƿ�����䷽//
	CString m_strNote;    //��ע˵��//
	bool m_bIsReadOnly;    //�Ƿ�ֻ��//
};

