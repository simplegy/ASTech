#include "CcyPair.h"
#include <regex>
#include "EnumHelper.h"
#include "Configuration.h"

using namespace utilities;
using namespace std;

void CcyPair::setCcyPairStr(std::string ccyPairStr){
	std::regex ccyPairRegex ("[A-Za-z]{6}");
	if (std::regex_match (ccyPairStr,ccyPairRegex)){
		_ccy1 = ccyPairStr.substr(0,3);
		_ccy2 = ccyPairStr.substr(3,3);
		_ccyPairStr = ccyPairStr;
	}else{
		throw "currency pair not recognized!";
	}
}

bool CcyPair::isEqual(CcyPair ccyPair){
	if (getCCY1() == ccyPair.getCCY1() && getCCY2() == ccyPair.getCCY2())
		return true;
	else
		return false;
}

enums::CurrencyEnum CcyPair::getCCY1Enum(){
	return EnumHelper::getCcyEnum(_ccy1);
}

enums::CurrencyEnum CcyPair::getCCY2Enum(){
	return EnumHelper::getCcyEnum(_ccy2);
}

enums::CurrencyEnum CcyPair::getDomesticCCYEnum(){
	return EnumHelper::getCcyEnum(getDomesticCCY());
}

enums::CurrencyEnum CcyPair::getForeignCCYEnum(){
	return EnumHelper::getCcyEnum(getForeignCCY());
}
