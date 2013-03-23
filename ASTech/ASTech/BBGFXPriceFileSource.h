//created by Wang Jianwei on 01 Dec 2012
#ifndef BBGFXPRICEFILESOURCE_H
#define BBGFXPRICEFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <tuple>
#include "Market.h"
#include "TimeSeries.h"
#include "CandleStick.h"
#include "RecordHelper.h"

using namespace instruments;

namespace DAO {
	class BBGFXPriceFileSource: public AbstractFileSource{
		
	public:
		
		BBGFXPriceFileSource():AbstractFileSource(){};
		BBGFXPriceFileSource(std::string persistDir, std::string fileName):AbstractFileSource(persistDir, fileName){};
		~BBGFXPriceFileSource(){};

		void init(Configuration*);
		
		void retrieveRecord();

	private:

		void insertTimeSeriesIntoCache(TimeSeries* deposit, RecordHelper::TimeSeriesMap* rawTimeSeriesMap);

		CandleStick* createCandleStickObject(CSVDatabase db, int row);

		void updateCandleStickObject(std::string fieldName, std::string fieldVal, CandleStick* candleStick);

	};
}
#endif