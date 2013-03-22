//created by Hu Kun on 29 Nov 2012

#ifndef Market_H
#define Market_H
#include <tuple>
#include "dateUtil.h"
#include "Enums.h"

namespace instruments {

	class Market {

	public:
		Market(){};
		Market(enums::CurrencyEnum);
		~Market(){};

		std::string getNameString();
		void display();

		enums::CurrencyEnum getCurrencyEnum(){return _marketName;}

		void setCurrencyEnum(enums::CurrencyEnum marketName){_marketName = marketName;}


	private:
		enums::CurrencyEnum _marketName;
	};
}
#endif