//created by Hu Kun 30 Nov 2012
#include "MarketData.h"
#include "Configuration.h"
#include "RecordHelper.h"
#include "Configuration.h"

using namespace Markets;
using namespace utilities;
using namespace enums;
bool MarketData::instanceFlag = false;
MarketData* MarketData::single = NULL;

MarketData* MarketData::getInstance()
{
	if(! instanceFlag)
	{
		single = new MarketData();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

MarketData::~MarketData() {
	delete single;
	instanceFlag = false;
}

void MarketData::buildAll(){
}
