//created by Jianwei on 30 Nov\

#include "EnumHelper.h"
#include "Enums.h"

using namespace utilities;

enums::CurrencyEnum EnumHelper::getCcyEnum(std::string ccyName){
	if (ccyName =="EUR" || ccyName == "EU")
		return EUR;
	else if (ccyName == "USD" || ccyName == "US")
		return USD;
	else if (ccyName == "THB")
		return THB;
	else if (ccyName == "KRW")
		return KRW;
	else if (ccyName == "SGD")
		return SGD;
	else if (ccyName == "JPY")
		return JPY;
	throw "Market name not foud: "+ccyName;
}
