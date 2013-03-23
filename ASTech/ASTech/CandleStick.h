//created by Hu Kun on 29 Nov 2012

#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#include <map>
#include "Enums.h"
#include "CcyPair.h"
#include "boost\date_time\gregorian\gregorian.hpp"

using namespace boost::gregorian;

namespace utilities {

	class CandleStick {

	public:
		CandleStick(){};
		~CandleStick(){};

      // Methods


      // Getters and Setters;
		CcyPair* getCcyPair(){ return &_ccyPair; }
		date getDate(){ return _date; }

	private:

      CcyPair _ccyPair;
      double _open;
      double _high;
      double _low;
      double _close;
      double _last;
      date _date;
      enums::ResolutionEnum _resolutionEnum;
	};
}
#endif