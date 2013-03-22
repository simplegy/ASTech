//created by Wang Jianwei on 01 Dec 2012
#ifndef RecordHelper_H
#define RecordHelper_H
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <tuple>
#include <vector>
#include "AbstractDao.h"
#include "AbstractSession.h"
#include "Enums.h"
#include "Market.h"
#include "CcyPair.h"

using namespace utilities;
using namespace DAO;
using namespace enums;
using namespace instruments;
using namespace std;

namespace Session {
	class RecordHelper: public AbstractSession{
	
	public:
		
		static RecordHelper* getInstance();

		void init(Configuration*);

		// Type Definition
		typedef std::map<enums::CurrencyEnum, std::set<long>> HolidayMap;	
		typedef std::map<enums::CurrencyEnum, Market> MarketMap;
		typedef std::map<string, CcyPair> CcyPairMap;

		// Getters
		HolidayMap getHolidayMap(){return _holidayMap;}
		MarketMap getMarketMap(){return _MarketMap;}
		CcyPairMap* getCcyPairMap(){ return &_CcyPairMap; }

		// Setters
		void setHolidayMap(HolidayMap map){_holidayMap=map;}
		void setMarketMap(MarketMap map){_MarketMap=map;}
		void setCcyPairMap(CcyPairMap map){_CcyPairMap=map;}

		// Methods

	private:		
		
		RecordHelper(){};
		~RecordHelper(){};

		static RecordHelper* single;
		std::vector<AbstractDAO*> dataSourceVector;

		HolidayMap _holidayMap;			
		MarketMap _MarketMap;
		CcyPairMap _CcyPairMap;
	};
}

#endif