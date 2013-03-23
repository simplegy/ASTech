#include "BBGFXPriceFileSource.h"

using namespace DAO;
using namespace utilities;

void BBGFXPriceFileSource::init(Configuration* cfg){
	 _name = "BBG FX Price";
	_fileName = cfg->getProperty("FXPrice.BloomBerg.file",true,"");
	_persistDir = cfg->getProperty("data.path",false,"");
	_enabled = cfg->getProperty("FXPrice.BloomBerg.enabled",true,"")=="true"?true:false;
	AbstractFileSource::init(cfg);
}

void BBGFXPriceFileSource::retrieveRecord(){
	if (!_enabled) return;	

	CSVDatabase db = readCSV(_persistDir+_fileName);
	int numOfRows=db.size();
	int numOfCols=db.at(0).size();

	RecordHelper::TimeSeriesMap* map = RecordHelper::getInstance()->getBBGRawTimeSeriesMap();
	TimeSeries * timeSeries = new TimeSeries();

	for (int i=1;i<numOfRows;i++) {
		CandleStick* tempCandleStick = createCandleStickObject(db, i);
		timeSeries->insertCandleStick(tempCandleStick);
	}
		insertTimeSeriesIntoCache(timeSeries, map);
}

void BBGFXPriceFileSource::insertTimeSeriesIntoCache(TimeSeries* timeSeries, RecordHelper::TimeSeriesMap* rawTimeSeriesMap){
	string ccyPair = timeSeries->getCcyPair()->getCcyPairStr();
	if (rawTimeSeriesMap->find(ccyPair) == rawTimeSeriesMap->end()){
		rawTimeSeriesMap->insert(std::make_pair(ccyPair, *timeSeries));
	}else{
		auto tempMap = &(rawTimeSeriesMap->find(ccyPair)->second);
		tempMap=timeSeries;
	}
}

CandleStick* BBGFXPriceFileSource::createCandleStickObject(CSVDatabase db, int row){
	int numOfCols=db.at(0).size();
	CandleStick* tempCandleStick = new CandleStick();

	for (int i=0;i<numOfCols;i++) {
		String fieldName = db.at(0).at(i);
		String fieldVal = db.at(row).at(i);
		updateCandleStickObject(fieldName, fieldVal, tempCandleStick);
	}		
	return tempCandleStick;
}

void BBGFXPriceFileSource::updateCandleStickObject(std::string fieldName, std::string fieldVal, CandleStick* candleStick){
	if(fieldName=="<TICKER>"){
	}
}