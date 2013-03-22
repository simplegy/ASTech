//created by Wang Jianwei on 01 Dec 2012
#ifndef FXPRICEFILESOURCE_H
#define FXPRICEFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <tuple>
#include "Market.h"

using namespace instruments;

namespace DAO {
	class FXPriceFileSource: public AbstractFileSource{
		
	public:
		
		FXPriceFileSource():AbstractFileSource(){};
		FXPriceFileSource(std::string persistDir, std::string fileName):AbstractFileSource(persistDir, fileName){};
		~FXPriceFileSource(){};

		void init(Configuration*);
		
		void retrieveRecord();
	};
}
#endif