//created by Hu Kun on 30 Nov
//updated by Hu Kun on 5 Dec

#include "Market.h"
#include "Enums.h"
#include "EnumHelper.h"
#include "RecordHelper.h"

using namespace instruments;
using namespace utilities;
using namespace Session;

Market::Market(enums::CurrencyEnum market) {
	_marketName = market;
	RecordHelper::MarketMap marketMap = RecordHelper::getInstance()->getMarketMap();
	*this = marketMap[market];
}

std::string Market::getNameString(){
	switch(_marketName){
	case::USD:
		return "USD";
	case::EUR:
		return "EUR";
	case::THB:
		return "THB";
	case::KRW:
		return "KRW";
	case::SGD:
		return "SGD";
	case::JPY:
		return "JPY";
	}
	return NULL;
}

void Market::display(){
}