#pragma once
#include "UserClass.h"
#include "ProcessModuleClass.h"
#include "ProductionLineClass.h"
#include "PlcClass.h"
#include "DeviceClass.h"
#include "VideoClass.h"
#include "PlcPara.h"


class CDataProvider
{
public:
	CDataProvider();
	~CDataProvider();

	int m_userId;

	enum enumDBTABLE {	tbUser, tbProductionLine, tbProcessModule,
		tbDevice, tbPLc, tbVideo, tbPLCSymbol };


	std::vector<UserClass> m_vectUser;
	std::vector<ProductionLineClass> m_vectProductionLine;
	std::vector<ProcessModuleClass> m_vectProcessModule;
	std::vector<DeviceClass>  m_vectDevice;
	std::vector<PlcClass>  m_vectPlc;
	std::vector<VideoClass> m_vectVideo;

	std::vector<CPlcPara>  m_vectPlcPara;


	std::vector<ProductionLineClass>::iterator pProlineIter;
	std::vector<ProcessModuleClass>::iterator  pModuleIter;
	std::vector<DeviceClass>::iterator        pDeviceIter;
	std::vector<PlcClass>::iterator            pPlcIter;
	std::vector<VideoClass>::iterator		pVideoIter;
	std::vector<CPlcPara>::iterator        pPlcParaIter;




	void SaveUserToDatabase();
	void ReadUserFromDatabase();
	void SaveProLineToDatabase();
	void ReadProLineFromDatabase();

	void SaveProModuleToDatabase();
	void ReadProModuleFromDatabase();
	void ReadDeviceFromDatabase();
	void SaveDeviceToDatabase();
	void ReadPlcFromDatabase();
	void SavePlcToDatabase();
	void ReadVideoFromDatabase();
	void SaveVideoToDatabase();


	void SaveAllPlcParaToDatabase();
	void ReadPlcParaFrommDatabase();


	void  InitDataProvider();

	int DeleteDbTable(enumDBTABLE dbTable);
	int DeleteDbTableItem(enumDBTABLE dbTable, int Id);


	
	int UpdateTableItem(enumDBTABLE dbTable, int Id);


	int DeleteModule(CString ProductionLineName);
	int DeleteDevice(CString ProductionLineName, CString ModuleName="");
	int DeletePlc(CString ProductionLineName);
	int DeleteVideo(CString ProductionLineName, CString ModuleName="");
	int DeletePlcPara(CString ProductionLineName, CString PlcName="");

	
	//根据提供的生产线名，返回找到生产线的ID,查找失败则返回0
	int FindProLineId(CString ProducitonLineName);
	//根据提供的生产线名，模块名，返回找到的所属工艺模块的ID,查找失败则返回0
	int FindProModuleId(CString ProductionLineName, CString ModuleName);

	int FindPlcId(CString PlcName);
	int FindDeviceId(CString ProductionLineName, CString ModuleName, CString DeviceName);


	//作为Search Device,PlcPara,Video 方法临时存储的中间容器
	std::vector<DeviceClass> m_vTempDevice;
	std::vector<CPlcPara>  m_vTempPlcPara;
	std::vector<VideoClass> m_vTempVideo;

	int SearchDevice(CString ProductionLineName, CString ModuleName);
	int SearchPlcPara(CString ProductionLineName, CString ModuleName);
	int SearchVideo(CString ProducitonLinaName, CString ModuleName);

};
