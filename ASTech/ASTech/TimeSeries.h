//created by Hu Kun on 29 Nov 2012

#ifndef TIMESERIES_H
#define TIMESERIES_H
#include <map>
#include "dateUtil.h"
#include "Enums.h"
#include "date.h"
#include "CcyPair.h"
#include "CandleStick.h"


namespace utilities {

	class TimeSeries {

	public:
		TimeSeries(){};
		TimeSeries(CcyPair ccyPair){
			_ccyPair = ccyPair;
		}
		~TimeSeries(){};

		// Methods
		TimeSeries cross(TimeSeries timeSeries);
		TimeSeries aggregate(enums::ResolutionEnum targetResolution);
		void insertCandleStick(CandleStick* candleStick);

		// Getters and Setters;
		CcyPair* getCcyPair(){ return &_ccyPair; }


	private:

		CcyPair _ccyPair;
		std::map<long, CandleStick> _candleStickMap;
	};
}
#endif