#include "TimeSeries.h"

using namespace utilities;

void TimeSeries::insertCandleStick(CandleStick* candleStick){
	_candleStickMap.insert(std::pair<long,CandleStick>(candleStick->getDate().getJudianDayNumber(),*candleStick));
}