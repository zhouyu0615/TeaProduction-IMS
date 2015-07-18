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

	std::vector<UserClass> m_vectUser;
	std::vector<ProductionLineClass> m_vectProductionLine;
	std::vector<ProcessModuleClass> m_vectProcessModule;
	std::vector<DeviceClass>  m_vectDevice;
	std::vector<PlcClass>  m_vectPlc;
	std::vector<VideoClass> m_vectVideo;

	std::vector<CPlcPara>  m_vectPlcPara;

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


	void SavePlcParaToDatabase();
	void ReadPlcParaFrommDatabase();

};

