#include "stdafx.h"
#include "DataProvider.h"

#include "tbUser.h"
#include "tbProductionLine.h"
#include "tbProcessModule.h"
#include "tbDevice.h"
#include "tbPLc.h"
#include "tbVideo.h"
#include "tbPLCSymbol.h"

CDataProvider::CDataProvider()
{

}


CDataProvider::~CDataProvider()
{
}

void CDataProvider::InitDataProvider()
{

	this->ReadUserFromDatabase();
	this->ReadProLineFromDatabase();
	this->ReadProModuleFromDatabase();
	this->ReadDeviceFromDatabase();
	this->ReadPlcFromDatabase();
	this->ReadVideoFromDatabase();
	this->ReadPlcParaFrommDatabase();

}



int CDataProvider::FindProLineId(CString ProducitonLineName)
{
	int ProLineId;
	for (int i = 0; i < m_vectProductionLine.size(); i++)
	{
		if (ProducitonLineName == m_vectProductionLine[i].m_strLineName)
		{
			ProLineId = m_vectProductionLine[i].m_Id;
			return ProLineId;
		}
	}
	return 0;
}


int CDataProvider::FindProModuleId(CString ProductionLineName, CString ModuleName)
{
	int ProModuleId;
	for (int i = 0; i < m_vectProcessModule.size(); i++)
	{
		if (ProductionLineName == m_vectProcessModule[i].m_strProcessModuleName
			&&ModuleName == m_vectProcessModule[i].m_strProductionLineName)
		{
			ProModuleId = m_vectProcessModule[i].m_Id;
			return ProModuleId;
		}
	}
	return 0;
}


int CDataProvider::FindPlcId(CString PlcName)
{
	int PlcId;
	for (int i = 0; i < m_vectPlc.size();i++)
	{
		if (PlcName==m_vectPlc[i].m_strPlcName)
		{
			PlcId = m_vectPlc[i].m_Id;
			return PlcId;
		}
	}
	return 0;

}

int CDataProvider::FindDeviceId(CString ProductionLineName, CString ModuleName, CString DeviceName)
{
	int DeviceId;
	for (int i = 0; i < m_vectDevice.size();i++)
	{
		if (ProductionLineName==m_vectDevice[i].m_strProductionLineName
			&&ModuleName==m_vectDevice[i].m_strProcessModuleName
			&&DeviceName==m_vectDevice[i].m_strDeviceName)
		{
			DeviceId = m_vectDevice[i].m_Id;
			return DeviceId;
		}
	}

	return 0;
}

void CDataProvider::SaveUserToDatabase()
{
	CtbUser m_tbUserSet;
	try{
		if (m_tbUserSet.IsOpen())
			m_tbUserSet.Close();
		if (!m_tbUserSet.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString username, userpasswd, usercode, usernote;

	int userId;
	if (m_vectUser.size() == 1) //设置第一个用户的ID
	{
		userId = 1000;
	}
	else
	{
		userId = m_vectUser[m_vectUser.size() - 2].m_UserId + 1;
	}


	username = m_vectUser[0].m_strUserName;
	userpasswd = m_vectUser[0].m_strUserPasswd;
	usercode = m_vectUser[0].m_strUserCode;
	usernote = m_vectUser[0].m_strNote;

	if (m_tbUserSet.CanUpdate()){
		m_tbUserSet.AddNew();

		CTime time = CTime::GetCurrentTime();
		m_userId = userId;
		m_tbUserSet.m_Id = userId;
		m_tbUserSet.m_CreatedDateTime = time;
		m_tbUserSet.m_LastUpdatedDateTime = time;
		m_tbUserSet.m_UserName = username;
		m_tbUserSet.m_UserPassword = userpasswd;
		m_tbUserSet.m_UserCode = usercode;
		m_tbUserSet.m_Note = usernote;
		m_tbUserSet.Update();

	}
	m_tbUserSet.Close();
}




void CDataProvider::SaveProLineToDatabase()
{

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strlineName, strCapacity, strDescription;


	int lineId;
	int length = m_vectProductionLine.size();

	if (length == 1)//设置第一条生产线的ID
	{
		lineId = 1000;
	}
	else{
		lineId = m_vectProductionLine[length - 2].m_Id + 1;
	}
	m_vectProductionLine[length - 1].m_Id = lineId;

	strlineName = m_vectProductionLine[length - 1].m_strLineName;
	strCapacity = m_vectProductionLine[length - 1].m_strCapacity;
	strDescription = m_vectProductionLine[length - 1].m_strDescription;

	if (tbProductionLine.CanUpdate()){
		tbProductionLine.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProductionLine.m_Id = lineId;
		tbProductionLine.m_CreatedDateTime = time;
		tbProductionLine.m_LastUpdatedDateTime = time;
		tbProductionLine.m_LineName = strlineName;
		tbProductionLine.m_UserId = m_userId; //唯一用户ID
		tbProductionLine.m_Capacity = strCapacity;
		tbProductionLine.m_Description = strDescription;
		tbProductionLine.Update();

	}

	tbProductionLine.Close();

}




void CDataProvider::SaveProModuleToDatabase()
{
	CtbProcessModule tbProcessModule;
	try{
		if (tbProcessModule.IsOpen())
			tbProcessModule.Close();
		if (!tbProcessModule.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strLineName, strModuleName, strDescription;
	int length = m_vectProcessModule.size();
	int Id;
	if (length == 1)//设置第一个模块ID
	{
		Id = 1000;
	}
	else{
		Id = m_vectProcessModule[length - 2].m_Id + 1;
	}

	m_vectProcessModule[length - 1].m_Id = Id;

	strLineName = m_vectProcessModule[length - 1].m_strProductionLineName;
	strModuleName = m_vectProcessModule[length - 1].m_strProcessModuleName;
	strDescription = m_vectProcessModule[length - 1].m_strDescription;
	
	//找出工艺模块所属生产线的ID
	int ProLineId = FindProLineId(strLineName);
	m_vectProcessModule[length - 1].m_ProcessLineId = ProLineId;
	
	if (tbProcessModule.CanUpdate()){
		tbProcessModule.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbProcessModule.m_Id = Id;
		tbProcessModule.m_CreatedDateTime = time;
		tbProcessModule.m_LastUpdatedDateTime = time;
		tbProcessModule.m_ProductionLineName = strLineName;
		tbProcessModule.m_UserId = m_userId; //唯一用户ID
		tbProcessModule.m_ProductionLineId = ProLineId; //所属生产线ID
		tbProcessModule.m_ModuleName = strModuleName;
		tbProcessModule.m_Description = strDescription;
		tbProcessModule.Update();

	}

	tbProcessModule.Close();


}

void CDataProvider::SaveDeviceToDatabase()
{
	CtbDevice tbDevice;
	try{
		if (tbDevice.IsOpen())
			tbDevice.Close();
		if (!tbDevice.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strLineName, strModuleName, strDeviceName, strDeviceType;

	int length = m_vectDevice.size();
	int Id;
	if (length == 1)//设置第一个模块ID
	{
		Id = 1000;
	}
	else{
		Id = m_vectDevice[length - 2].m_Id + 1;
	}
	m_vectDevice[length - 1].m_Id = Id;

	strLineName = m_vectDevice[length - 1].m_strProductionLineName;
	strModuleName = m_vectDevice[length - 1].m_strProcessModuleName;
	strDeviceName = m_vectDevice[length - 1].m_strDeviceName;
	strDeviceType = m_vectDevice[length - 1].m_strDeviceType;

	int ProLineId, ProModuleId;
	//找到该设备所属生产线的ID
	ProLineId = FindProLineId(strLineName);
	//找到设备所属的工艺模块的ID
	ProModuleId == FindProModuleId(strLineName, strModuleName);

	m_vectDevice[length - 1].m_ProductionLineId = ProLineId;
	m_vectDevice[length - 1].m_ProcessModuleId = ProModuleId;

	if (tbDevice.CanUpdate()){
		tbDevice.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbDevice.m_Id = Id;
		tbDevice.m_CreatedDateTime = time;
		tbDevice.m_LastUpdatedDateTime = time;
		tbDevice.m_ProductionLineName = strLineName;
		tbDevice.m_ProcessModuleName = strModuleName;
		tbDevice.m_DeviceName = strDeviceName;
		tbDevice.m_DeviceType = strDeviceType;
		tbDevice.m_ProductionLineId = ProLineId; //所属生产线的ID
		tbDevice.m_ProcessModuleId = ProModuleId;// 所属工艺模块的ID

		tbDevice.Update();

	}

	tbDevice.Close();
}


void CDataProvider::SavePlcToDatabase()
{
	CtbPLc tbPlc;
	try{
		if (tbPlc.IsOpen())
			tbPlc.Close();
		if (!tbPlc.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strLineName, strPlcName, strPort, strDescription;

	int length = m_vectPlc.size();
	int Id;
	if (length == 1)//设置第一个模块ID
	{
		Id = 1000;
	}
	else{
		Id = m_vectPlc[length - 2].m_Id + 1;
	}
	m_vectPlc[length - 1].m_Id = Id;

	strLineName = m_vectPlc[length - 1].m_strProductionLineName;
	strPlcName = m_vectPlc[length - 1].m_strPlcName;
	strPort = m_vectPlc[length - 1].m_strPort;
	strDescription = m_vectPlc[length - 1].m_strDescription;

	int ProlineId = FindProLineId(strLineName); //找出PLC所属生产线的ID
	m_vectPlc[length - 1].m_ProductionLineId = ProlineId;

	if (tbPlc.CanUpdate()){
		tbPlc.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbPlc.m_Id = Id;
		tbPlc.m_CreatedDateTime = time;
		tbPlc.m_LastUpdatedDateTime = time;
		tbPlc.m_ProductionLineName = strLineName;
		tbPlc.m_UserId = m_userId; //唯一用户ID
		tbPlc.m_PLCName = strPlcName;
		tbPlc.m_strPort = strPort;
		tbPlc.m_PortId = atoi(strPort);
		tbPlc.m_Description = strDescription;
		tbPlc.Update();

	}

	tbPlc.Close();
}


void CDataProvider::SaveVideoToDatabase()
{

	CtbVideo tbVideo;
	try{
		if (tbVideo.IsOpen())
			tbVideo.Close();
		if (!tbVideo.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	CString strLineName, strModuleName, strVideoName, strPort;


	int length = m_vectVideo.size();
	int Id;
	if (length == 1)//设置第一个模块ID
	{
		Id = 1000;
	}
	else{
		Id = m_vectVideo[length - 2].m_Id + 1;
	}
	m_vectVideo[length - 1].m_Id = Id;

	strLineName = m_vectVideo[length - 1].m_strProductionLineName;
	strModuleName = m_vectVideo[length - 1].m_strProcessModuleName;
	strVideoName = m_vectVideo[length - 1].m_strVideoName;
	strPort = m_vectVideo[length - 1].m_strPort;

	int ProLineId, ModuleId;
	ProLineId = FindProLineId(strLineName);
	ModuleId = FindProModuleId(strLineName, strModuleName);

	m_vectVideo[length - 1].m_ProductionLineId = ProLineId;
	m_vectVideo[length - 1].m_ModuleId = ModuleId;

	if (tbVideo.CanUpdate()){
		tbVideo.AddNew();

		CTime time = CTime::GetCurrentTime();
		tbVideo.m_Id = Id;
		tbVideo.m_CreatedDateTime = time;
		tbVideo.m_LastUpdatedDateTime = time;
		tbVideo.m_ProductionLineName = strLineName;
		tbVideo.m_ProcessModuleName = strModuleName;
		tbVideo.m_VideoName = strVideoName;
		tbVideo.m_strPort = strPort;

		tbVideo.m_ProductionLineId = ProLineId;
		tbVideo.m_ProcessModuleId = ModuleId;
		tbVideo.Update();

	}

	tbVideo.Close();

}



void CDataProvider::SaveAllPlcParaToDatabase()
{

	CtbPLCSymbol tbPLCSymbol;
	try{
		if (tbPLCSymbol.IsOpen())
			tbPLCSymbol.Close();
		if (!tbPLCSymbol.Open(CRecordset::dynaset)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}



	int Id = 1000;
	int length = m_vectPlcPara.size();
	int ProLineId, ModuleId, DeviceId, PlcId;

	for (int i = 0; i < length; i++)
	{
		m_vectPlcPara[i].m_Id = 1000 + i;

		ProLineId = FindProLineId(m_vectPlcPara[i].m_strLine);
		ModuleId = FindProModuleId(m_vectPlcPara[i].m_strLine, m_vectPlcPara[i].m_strModule);
		DeviceId = FindDeviceId(m_vectPlcPara[i].m_strLine,
								m_vectPlcPara[i].m_strModule,
								m_vectPlcPara[i].m_strDevice);
		PlcId = FindPlcId(m_vectPlcPara[i].m_strPlc);

		m_vectPlcPara[i].m_ProLineId = ProLineId;
		m_vectPlcPara[i].m_ModuleId = ModuleId;
		m_vectPlcPara[i].m_PlcId = PlcId;
		m_vectPlcPara[i].m_DeviceId = DeviceId;

		if (tbPLCSymbol.CanUpdate()){
			tbPLCSymbol.AddNew();
			
			CTime time = CTime::GetCurrentTime();
			tbPLCSymbol.m_Id = m_vectPlcPara[i].m_Id;
			tbPLCSymbol.m_CreatedDateTime = time;
			tbPLCSymbol.m_LastUpdatedDateTime = time;
			tbPLCSymbol.m_AddressType = m_vectPlcPara[i].m_strAddressType;
			tbPLCSymbol.m_AddressIndex = m_vectPlcPara[i].m_strAddressIndex;
			tbPLCSymbol.m_ValueType = m_vectPlcPara[i].m_strValueType;
			tbPLCSymbol.m_Value = m_vectPlcPara[i].m_strValue;
			tbPLCSymbol.m_PlcName = m_vectPlcPara[i].m_strPlc;
			tbPLCSymbol.m_ProductionLineName = m_vectPlcPara[i].m_strLine;
			tbPLCSymbol.m_ProcessModuleName = m_vectPlcPara[i].m_strModule;
			tbPLCSymbol.m_DeviceName = m_vectPlcPara[i].m_strDevice;
			tbPLCSymbol.m_IsVisible = m_vectPlcPara[i].m_bIsVisible;
			tbPLCSymbol.m_IsConfig = m_vectPlcPara[i].m_bIsConfig;
			tbPLCSymbol.m_strNote = m_vectPlcPara[i].m_strNote;
			tbPLCSymbol.m_IsReadOnly = m_vectPlcPara[i].m_bIsReadOnly;

			tbPLCSymbol.m_ProductionLineId = m_vectPlcPara[i].m_ProLineId;
			tbPLCSymbol.m_ProcessModuleId = m_vectPlcPara[i].m_ModuleId;
			tbPLCSymbol.m_PLCId = m_vectPlcPara[i].m_PlcId;
			tbPLCSymbol.m_DeviceId = m_vectPlcPara[i].m_DeviceId;

			tbPLCSymbol.Update();
		}

	}



	tbPLCSymbol.Close();

}

void CDataProvider::ReadPlcParaFrommDatabase()
{

	CString strsql;
	strsql.Format(_T("select * from tbPLCSymbol order by Id"));

	CtbPLCSymbol tbPlcPara;
	try{
		if (tbPlcPara.IsOpen())
			tbPlcPara.Close();
		if (!tbPlcPara.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbPlcPara.IsBOF())
	{
		return;
	}
	CPlcPara tempPlcPara;
	tbPlcPara.MoveFirst();
	while (!tbPlcPara.IsEOF()){
		tempPlcPara.m_Id = tbPlcPara.m_Id;
		tempPlcPara.m_strAddressType = tbPlcPara.m_AddressType;
		tempPlcPara.m_strAddressIndex = tbPlcPara.m_AddressIndex;

		tempPlcPara.m_strValueType = tbPlcPara.m_ValueType;
		tempPlcPara.m_strValue = tbPlcPara.m_Value;
		tempPlcPara.m_strPlc = tbPlcPara.m_PlcName;
		tempPlcPara.m_strLine = tbPlcPara.m_ProductionLineName;
		tempPlcPara.m_strModule = tbPlcPara.m_ProcessModuleName;
		tempPlcPara.m_strDevice = tbPlcPara.m_DeviceName;
		tempPlcPara.m_bIsVisible = tbPlcPara.m_IsVisible;
		tempPlcPara.m_bIsConfig = tbPlcPara.m_IsConfig;
		tempPlcPara.m_strNote = tbPlcPara.m_strNote;
		tempPlcPara.m_bIsReadOnly = tbPlcPara.m_IsReadOnly;

		tempPlcPara.m_ProLineId = tbPlcPara.m_ProductionLineId;
		tempPlcPara.m_ModuleId = tbPlcPara.m_ProcessModuleId;
		tempPlcPara.m_PlcId = tbPlcPara.m_PLCId;
		tempPlcPara.m_DeviceId = tbPlcPara.m_DeviceId;

		m_vectPlcPara.push_back(tempPlcPara);


		tbPlcPara.MoveNext();

	}

	tbPlcPara.Close();


}


void CDataProvider::ReadUserFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbUser order by Id"));

	CtbUser tbUser;
	try{
		if (tbUser.IsOpen())
			tbUser.Close();
		if (!tbUser.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbUser.IsBOF())
	{
		return;
	}

	UserClass tempUser;
	tbUser.MoveFirst();
	while (!tbUser.IsEOF()){
		m_userId = tbUser.m_Id; //获取类成员变量 唯一的 用户ID
		tempUser.m_UserId = tbUser.m_Id;
		tempUser.m_strUserName = tbUser.m_UserName;
		tempUser.m_strUserPasswd = tbUser.m_UserPassword;
		tempUser.m_strUserCode = tbUser.m_UserCode;
		tempUser.m_strNote = tbUser.m_Note;
		m_vectUser.push_back(tempUser);

		tbUser.MoveNext();

	}

	tbUser.Close();

}



void CDataProvider::ReadProLineFromDatabase(){
	CString strsql;
	strsql.Format(_T("select * from tbProductionLine order by Id"));

	CtbProductionLine tbProductionLine;
	try{
		if (tbProductionLine.IsOpen())
			tbProductionLine.Close();
		if (!tbProductionLine.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProductionLine.IsBOF())
	{
		return;
	}

	ProductionLineClass tempProductionLine;
	tbProductionLine.MoveFirst();
	while (!tbProductionLine.IsEOF()){

		tempProductionLine.m_Id = tbProductionLine.m_Id;
		tempProductionLine.m_strLineName = tbProductionLine.m_LineName;
		tempProductionLine.m_strCapacity = tbProductionLine.m_Capacity;
		tempProductionLine.m_strDescription = tbProductionLine.m_Description;

		tempProductionLine.m_UserId = tbProductionLine.m_UserId;

		m_vectProductionLine.push_back(tempProductionLine);
		tbProductionLine.MoveNext();
	}

	tbProductionLine.Close();

}


void CDataProvider::ReadProModuleFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbProcessModule order by Id"));

	CtbProcessModule  tbProcessModule;
	try{
		if (tbProcessModule.IsOpen())
			tbProcessModule.Close();
		if (!tbProcessModule.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbProcessModule.IsBOF())
	{
		return;
	}


	ProcessModuleClass tempModule;
	tbProcessModule.MoveFirst();
	while (!tbProcessModule.IsEOF()){

		tempModule.m_Id = tbProcessModule.m_Id;
		tempModule.m_strProductionLineName = tbProcessModule.m_ProductionLineName;
		tempModule.m_strProcessModuleName = tbProcessModule.m_ModuleName;
		tempModule.m_strDescription = tbProcessModule.m_Description;

		tempModule.m_ProcessLineId = tbProcessModule.m_ProductionLineId;

		m_vectProcessModule.push_back(tempModule);
		tbProcessModule.MoveNext();
	}

	tbProcessModule.Close();

}


void CDataProvider::ReadDeviceFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbDevice order by Id"));

	CtbDevice  tbDevice;
	try{
		if (tbDevice.IsOpen())
			tbDevice.Close();
		if (!tbDevice.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	if (tbDevice.IsEOF())
	{
		return;
	}


	DeviceClass tempDevice;
	tbDevice.MoveFirst();
	while (!tbDevice.IsEOF()){

		tempDevice.m_Id = tbDevice.m_Id;
		tempDevice.m_strProductionLineName = tbDevice.m_ProductionLineName;
		tempDevice.m_strProcessModuleName = tbDevice.m_ProcessModuleName;
		tempDevice.m_strDeviceName = tbDevice.m_DeviceName;
		tempDevice.m_strDeviceType = tbDevice.m_DeviceType;
		tempDevice.m_ProcessModuleId = tbDevice.m_ProcessModuleId;
		tempDevice.m_ProductionLineId = tbDevice.m_ProductionLineId;

		m_vectDevice.push_back(tempDevice);
		tbDevice.MoveNext();
	}

	tbDevice.Close();

}





void CDataProvider::ReadPlcFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbPLc order by Id"));

	CtbPLc  tbPlc;
	try{
		if (tbPlc.IsOpen())
			tbPlc.Close();
		if (!tbPlc.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbPlc.IsEOF())
	{
		return;
	}

	PlcClass tempPlc;
	tbPlc.MoveFirst();
	while (!tbPlc.IsEOF()){

		tempPlc.m_Id = tbPlc.m_Id;
		tempPlc.m_strProductionLineName = tbPlc.m_ProductionLineName;
		tempPlc.m_strPlcName = tbPlc.m_PLCName;
		tempPlc.m_strPort = tbPlc.m_strPort;
		tempPlc.m_strDescription = tbPlc.m_Description;
		tempPlc.m_ProductionLineId = tbPlc.m_ProductionLineId;

		m_vectPlc.push_back(tempPlc);
		tbPlc.MoveNext();
	}

	tbPlc.Close();


}




void CDataProvider::ReadVideoFromDatabase()
{
	CString strsql;
	strsql.Format(_T("select * from tbVideo order by Id"));

	CtbVideo  tbVideo;
	try{
		if (tbVideo.IsOpen())
			tbVideo.Close();
		if (!tbVideo.Open(CRecordset::dynaset, strsql)){
			AfxMessageBox(_T("打开数据库失败！"));
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	if (tbVideo.IsEOF())
	{
		tbVideo.Close();
		return;
	}

	VideoClass tempVideo;
	tbVideo.MoveFirst();
	while (!tbVideo.IsEOF()){

		tempVideo.m_Id = tbVideo.m_Id;
		tempVideo.m_strProductionLineName = tbVideo.m_ProductionLineName;
		tempVideo.m_strProcessModuleName = tbVideo.m_ProcessModuleName;
		tempVideo.m_strPort = tbVideo.m_strPort;
		tempVideo.m_strVideoName = tbVideo.m_VideoName;

		tempVideo.m_ProductionLineId = tbVideo.m_ProductionLineId;
		tempVideo.m_ModuleId = tbVideo.m_ProcessModuleId;

		m_vectVideo.push_back(tempVideo);
		tbVideo.MoveNext();
	}

	tbVideo.Close();


}

/*函数功能：删除枚举类型dbTable类型中提供的各表的所有列
举例：DeleteDbTable(tbProductionLine)删除生产线表格所包含的所有列
*/

int CDataProvider::DeleteDbTable(enumDBTABLE dbTable)
{
	CString strsql;

	switch (dbTable)
	{
	case CDataProvider::tbUser:
		strsql.Format("DELETE FROM tbUser");
		break;
	case CDataProvider::tbProductionLine:
		strsql.Format("DELETE FROM tbProductionLine");
		break;
	case CDataProvider::tbProcessModule:
		strsql.Format("DELETE FROM tbProcessModule");
		break;
	case CDataProvider::tbDevice:
		strsql.Format("DELETE FROM tbDevice");
		break;
	case CDataProvider::tbPLc:
		strsql.Format("DELETE FROM tbPLc");
		break;
	case CDataProvider::tbVideo:
		strsql.Format("DELETE FROM tbVideo");
		break;
	case CDataProvider::tbPLCSymbol:
		strsql.Format("DELETE FROM tbPLCSymbol");
		break;
	default:
		break;
	}

	CtbUser tbUser;
	try{
		if (tbUser.Open(CRecordset::dynaset)){
			tbUser.m_pDatabase->ExecuteSQL(strsql);
		}
		else{
			AfxMessageBox(_T("打开数据库失败！"));
			tbUser.Close();
			return 1;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbUser.Close();
	return 0;
}


/*函数功能：特定删除枚举类型dbTable提供的表中删除特定ID的列*/

int CDataProvider::DeleteDbTableItem(enumDBTABLE dbTable, int Id)
{
	CString strsql;

	switch (dbTable)
	{
	case CDataProvider::tbUser:
		strsql.Format("DELETE FROM tbUser WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbProductionLine:
		strsql.Format("DELETE FROM tbProductionLine WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbProcessModule:
		strsql.Format("DELETE FROM tbProcessModule WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbDevice:
		strsql.Format("DELETE FROM tbDevice WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbPLc:
		strsql.Format("DELETE FROM tbPLc WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbVideo:
		strsql.Format("DELETE FROM tbVideo WHERE Id = '%d'", Id);
		break;
	case CDataProvider::tbPLCSymbol:
		strsql.Format("DELETE FROM tbPLCSymbol WHERE Id = '%d'", Id);
		break;
	default:
		break;
	}

	CtbUser tbUser;
	try{
		if (tbUser.Open(CRecordset::dynaset)){
			tbUser.m_pDatabase->ExecuteSQL(strsql);
		}
		else{
			AfxMessageBox(_T("打开数据库失败！"));
			tbUser.Close();
			return 1;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbUser.Close();
	return 0;
}


/*
函数功能：在枚举类型dbDBTABLE 中的几个表中，修改特定ID的条目
*/
int CDataProvider::UpdateTableItem(enumDBTABLE dbTable, int Id)
{
	CString strsql;
	ProductionLineClass tempProLine;
	ProcessModuleClass tempModule;
	DeviceClass    tempDevice;
	PlcClass      tempPlc;
	VideoClass    tempVideo;
	CPlcPara      tempPlcPara;

	switch (dbTable)
	{
	case CDataProvider::tbUser: //用户仅有一个
		strsql.Format("UPDATE tbUser SET UserName = '%s',UserPassword='%s',UserCode='%s',Note='%s' WHERE Id ='%d'",
			m_vectUser[0].m_strUserName, m_vectUser[0].m_strUserPasswd,
			m_vectUser[0].m_strUserCode, m_vectUser[0].m_strNote, Id);

		break;
	case CDataProvider::tbProductionLine:

		for (int i = 0; i < m_vectProductionLine.size(); i++)
		{
			if (Id == m_vectProductionLine[i].m_Id)
			{
				tempProLine = m_vectProductionLine[i];
				break;
			}

		}
		strsql.Format("UPDATE tbProductionLine SET LineName = '%s',Capacity='%s',Description='%s' WHERE Id = '%d'",
			tempProLine.m_strLineName, tempProLine.m_strCapacity,
			tempProLine.m_strDescription, Id);
		break;
	case CDataProvider::tbProcessModule:
		for (int i = 0; i < m_vectProcessModule.size(); i++)
		{
			if (Id == m_vectProcessModule[i].m_Id)
			{
				tempModule = m_vectProcessModule[i];
				break;
			}

		}
		strsql.Format("UPDATE tbProcessModule SET ModuleName = '%s',ProductionLineName='%s',Description='%s' WHERE Id = '%d'",
			tempModule.m_strProcessModuleName, tempModule.m_strProductionLineName,
			tempModule.m_strDescription, Id);
		break;
	case CDataProvider::tbDevice:
		for (int i = 0; i < m_vectDevice.size(); i++)
		{
			if (Id == m_vectDevice[i].m_Id)
			{
				tempDevice = m_vectDevice[i];
				break;
			}

		}
		strsql.Format("UPDATE tbDevice  SET ProductionLineName='%s',ProcessModuleName = '%s',DeviceName='%s',DeviceType='%s' WHERE Id = '%d'",
			tempDevice.m_strProductionLineName, tempDevice.m_strProcessModuleName,
			tempDevice.m_strDeviceName, tempDevice.m_strDeviceType, Id);

		break;
	case CDataProvider::tbPLc:
		for (int i = 0; i < m_vectPlc.size(); i++)
		{
			if (Id == m_vectPlc[i].m_Id)
			{
				tempPlc = m_vectPlc[i];
				break;
			}

		}
		strsql.Format("UPDATE tbPLc SET ProductionLineName = '%s',PLCName='%s',strPort='%s',Description='%s' WHERE Id = '%d'",
			tempPlc.m_strProductionLineName, tempPlc.m_strPlcName,
			tempPlc.m_strPort, tempPlc.m_strDescription, Id);
		break;
	case CDataProvider::tbVideo:
		for (int i = 0; i < m_vectVideo.size(); i++)
		{
			if (Id == m_vectVideo[i].m_Id)
			{
				tempVideo = m_vectVideo[i];
				break;
			}

		}
		strsql.Format("UPDATE tbVideo SET ProductionLineName = '%s',ProcessModuleName='%s',VideoName='%s',strPort='%s' WHERE Id = '%d'",
			tempVideo.m_strProductionLineName, tempVideo.m_strProcessModuleName,
			tempVideo.m_strVideoName, tempVideo.m_strPort, Id);
		break;
	case CDataProvider::tbPLCSymbol:
		for (int i = 0; i < m_vectPlcPara.size(); i++)
		{
			if (Id == m_vectPlcPara[i].m_Id)
			{
				tempPlcPara = m_vectPlcPara[i];
				break;
			}

		}
		strsql.Format("UPDATE tbPLCSymbol SET AddressType='%s' ,AddressIndex='s',Value=s',ProductionLineName='%s',ProcessModuleName='%s',DeviceName='%s',PlcName='%s',ValueType='%s',strNote='%s',IsVisible='%d',IsConfig='%d',IsReadOnly='%d' WHERE Id = '%d'"
			, tempPlcPara.m_strAddressType,
			tempPlcPara.m_strAddressIndex,
			tempPlcPara.m_strValue,
			tempPlcPara.m_strLine,
			tempPlcPara.m_strModule,
			tempPlcPara.m_strDevice,
			tempPlcPara.m_strPlc,
			tempPlcPara.m_strValueType,
			tempPlcPara.m_strNote,
			(int)tempPlcPara.m_bIsVisible,
			(int)tempPlcPara.m_bIsConfig,
			(int)tempPlcPara.m_bIsReadOnly,
			Id);

		break;
	default:
		break;
	}

	CtbUser tbUser;
	try{
		if (tbUser.Open(CRecordset::dynaset)){
			tbUser.m_pDatabase->ExecuteSQL(strsql);
		}
		else{
			AfxMessageBox(_T("打开数据库失败！"));
			tbUser.Close();
			return 1;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	tbUser.Close();
	return 0;
}

int CDataProvider::DeleteModule(CString ProductionLineName){

	for (pModuleIter = m_vectProcessModule.begin();
		pModuleIter != m_vectProcessModule.end();)
	{
		if (pModuleIter->m_strProductionLineName == ProductionLineName)
		{
			//删除数据库里面的数据
			DeleteDbTableItem(CDataProvider::tbProcessModule, pModuleIter->m_Id);
			//删除内存容器里面的数据
			pModuleIter = m_vectProcessModule.erase(pModuleIter);
		}
		else
		{
			pModuleIter++;
		}

	}
	return 0;
}


int CDataProvider::DeleteDevice(CString ProductionLineName, CString ModuleName){

	for (pDeviceIter = m_vectDevice.begin();
		pDeviceIter != m_vectDevice.end();
		)
	{
		if (pDeviceIter->m_strProductionLineName == ProductionLineName
			&& (ModuleName.IsEmpty() || pDeviceIter->m_strProcessModuleName == ModuleName))
		{
			//删除数据库里面的数据
			DeleteDbTableItem(CDataProvider::tbDevice, pDeviceIter->m_Id);
			//删除内存容器里面的数据
			pDeviceIter = m_vectDevice.erase(pDeviceIter);
		}
		else{
			pDeviceIter++;
		}

	}
	return 0;

}


int CDataProvider::DeletePlc(CString ProductionLineName){

	for (pPlcIter = m_vectPlc.begin();
		pPlcIter != m_vectPlc.end();
		)
	{
		if (pPlcIter->m_strProductionLineName == ProductionLineName)
		{
			//删除数据库里面的数据
			DeleteDbTableItem(CDataProvider::tbPLc, pPlcIter->m_Id);
			//删除内存容器里面的数据
			pPlcIter = m_vectPlc.erase(pPlcIter);
		}
		else
		{
			pPlcIter++;
		}

	}
	return 0;
}

int CDataProvider::DeleteVideo(CString ProductionLineName, CString ModuleName)
{

	for (pVideoIter = m_vectVideo.begin();
		pVideoIter != m_vectVideo.end();
		)
	{
		if (pVideoIter->m_strProductionLineName == ProductionLineName
			&& (ModuleName.IsEmpty() || pVideoIter->m_strProcessModuleName == ModuleName))
		{
			//删除数据库里面的数据
			DeleteDbTableItem(CDataProvider::tbVideo, pVideoIter->m_Id);
			//删除内存容器里面的数据
			pVideoIter = m_vectVideo.erase(pVideoIter);
		}
		else
		{
			pVideoIter++;
		}
	}
	return 0;
}

int CDataProvider::DeletePlcPara(CString ProductionLineName, CString PlcName)
{
	for (pPlcParaIter = m_vectPlcPara.begin();
		pPlcParaIter != m_vectPlcPara.end();
		)
	{
		if (pPlcParaIter->m_strLine == ProductionLineName
			&& (PlcName.IsEmpty() || pPlcParaIter->m_strModule == PlcName))
		{
			//删除数据库里面的数据
			DeleteDbTableItem(CDataProvider::tbPLCSymbol, pPlcParaIter->m_Id);
			//删除内存容器里面的数据
			pPlcParaIter = m_vectPlcPara.erase(pPlcParaIter);
		}
		else
		{
			pPlcParaIter++;
		}
	}
	return 0;

}



/*  根据传入的参数 ProductionLineName ModuleName，
   从m_vectDevice容器中找出相关的Device
   存储到成员变量 m_vTempDevice中

   */
int CDataProvider::SearchDevice(CString ProductionLineName, CString ModuleName)
{
	m_vTempDevice.clear();
	for (pDeviceIter = m_vectDevice.begin(); pDeviceIter != m_vectDevice.end(); pDeviceIter++)
	{
		if (pDeviceIter->m_strProductionLineName==ProductionLineName
			&&pDeviceIter->m_strProcessModuleName==ModuleName)
		{
			m_vTempDevice.push_back(*pDeviceIter);
		}

	}
	return 0;
}


int CDataProvider::SearchPlcPara(CString ProductionLineName, CString ModuleName)
{
	m_vTempPlcPara.clear();
	for (pPlcParaIter = m_vectPlcPara.begin(); pPlcParaIter != m_vectPlcPara.end(); pPlcParaIter++)
	{
		if (pPlcParaIter->m_strLine == ProductionLineName
			&&pPlcParaIter->m_strModule == ModuleName)
		{
			m_vTempPlcPara.push_back(*pPlcParaIter);
		}

	}
	return 0;
}


int CDataProvider::SearchVideo(CString ProductionLineName, CString ModuleName)
{
	m_vTempVideo.clear();
	for (pVideoIter = m_vectVideo.begin(); pVideoIter != m_vectVideo.end(); pVideoIter++)
	{
		if (pVideoIter->m_strProductionLineName == ProductionLineName
			&&pVideoIter->m_strProcessModuleName == ModuleName)
		{
			m_vTempVideo.push_back(*pVideoIter);
		}
	}
	return 0;
}

