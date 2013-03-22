//created by Wang Jianwei on 01 Dec 2012

#include "RecordHelper.h"
#include "AbstractDao.h"
#include "Configuration.h"
#include "HolidayFileSource.h"
#include "ConfigurationFileSource.h"
#include "MarketFileSource.h"
#include <vector>

using namespace Session;
using namespace DAO;
using namespace std;

RecordHelper* RecordHelper::single = NULL;

RecordHelper* RecordHelper::getInstance()
{
	if(! single)
		single = new RecordHelper();
	return single;
}

void RecordHelper::init(Configuration* cfg){
	dataSourceVector.push_back(new ConfigurationFileSource());
	dataSourceVector.push_back(new MarketFileSource());
	dataSourceVector.push_back(new HolidayFileSource());

	for(unsigned int i = 0; i<dataSourceVector.size(); i++){
		AbstractDAO* dao = dataSourceVector[i];
		dao->init(cfg);
		dao->retrieveRecord();
		dao->printSuccessMsg();
	}
}
