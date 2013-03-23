//created by Hu Kun on 29 Nov 2012
#ifndef MarketData_H
#define MarketData_H
#include "Market.h"
#include "Configuration.h"
#include <map>
#include <tuple>
#include "Enums.h"
#include "TimeSeries.h"

using namespace utilities;
using namespace instruments;
using namespace std;
using namespace enums;

namespace Markets {

	// Singlton class for MarketData
	class MarketData {
	public:
		static MarketData* getInstance();

		void buildAll();


	protected:
		//private copy constructor
		MarketData(){};
		~MarketData();
		
	private:
		static bool instanceFlag;
		static MarketData *single;

      map<CcyPair, TimeSeries> _timeSeriesMap;
	};
}
#endif