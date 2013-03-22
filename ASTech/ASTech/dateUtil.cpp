//created by Hu Kun 30 Nov 2012
#include "dateUtil.h"
#include "date.h"
#include <math.h>
#include <iostream>
#include "RecordHelper.h"
#include <ctime>
#include "Constants.h"

using namespace utilities;
using namespace Session;
using namespace std;

long dateUtil::getJudianDayNumber(unsigned short year, unsigned short month, unsigned short day){
	int	_a=(14-month)/12;
	int _y=year+4800-_a;
	int _m=month+12*_a-3;
	//if (_calendarType==Gregorian){
	return day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-(int)(_y/100)+(int)(_y/400)-32045;
	/*}else if (_calendarType==Judian){
		_judianDayNumber=_day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-32083;
	}*/
}

long dateUtil::getDaysBetween(date startDate, date endDate){
	return getDaysBetween
		(endDate.getJudianDayNumber(),startDate.getJudianDayNumber());
}

long dateUtil::getDaysBetween(long startJDN, long endJDN){
	return startJDN-endJDN;
}

signed long dateUtil::getBizDaysBetween(date startDate, date endDate){
	return getBizDaysBetween
		(startDate.getJudianDayNumber(),endDate.getJudianDayNumber());
}

signed long dateUtil::getBizDaysBetween(long startJDN, long endJDN){
	
	long numBizDay=0;
	for (long i = 0; i<abs(endJDN-startJDN); i++){
		if (isBizDay(i)) numBizDay++;
	}
	if (startJDN>endJDN) {
		return -numBizDay;
	}
	else {
		return numBizDay;
	}
}

bool dateUtil::isBizDay(date date0){
	return isBizDay(date0.getJudianDayNumber());
}

bool dateUtil::isBizDay(long JDN){
	int dayOfWeek = 1 + (int)fmod(JDN+1,7.0);
	if (dayOfWeek==1||dayOfWeek==7){
		return false;
	}
	return true;
}

bool dateUtil::isHoliday(long JDN, enums::CurrencyEnum market){
	RecordHelper::HolidayMap holidayMap= RecordHelper::getInstance()->getHolidayMap();
	if (holidayMap.find(market)== holidayMap.end()){
		cout<< "Market not found in Holiday Map: "+market<<endl;
		return false;
	}

	set<long> holidaySet = holidayMap[market];
	if (holidaySet.find(JDN) != holidaySet.end())
		return true;
	return false;
}

bool dateUtil::isHoliday(date aDate, enums::CurrencyEnum market){
	return isHoliday(aDate.getJudianDayNumber(),market);
}

date dateUtil::getToday(){
	date today(getTodayYear(),getTodayMonth(),getTodayDay());
	return today;
}

int dateUtil::getTodayDay() {
	time_t     rawtime;
	struct tm* timeinfo;

	time( &rawtime );
	timeinfo = localtime( &rawtime );
	return timeinfo->tm_mday;		
}

int dateUtil::getTodayMonth() {
	time_t     rawtime;
	struct tm* timeinfo;

	time( &rawtime );
	timeinfo = localtime( &rawtime );
	return 1+timeinfo->tm_mon;	
}
	
int dateUtil::getTodayYear() {
	time_t     rawtime;
	struct tm* timeinfo;

	time( &rawtime );
	timeinfo = localtime( &rawtime );
	return 1900+timeinfo->tm_year;
}

unsigned short* dateUtil::getYearMonthDay(long JDN){
	long _year, _month, _day;
	JDN = JDN - 1721119 ;
	_year = (4 * JDN - 1) / 146097 ; 
	JDN = 4 * JDN - 1 - 146097 * _year ; 
	_day = JDN / 4 ;
	JDN = (4 * _day + 3) / 1461 ; 
	_day = 4 * _day + 3 - 1461 * JDN ; 
	_day = (_day + 4) / 4 ;
	_month = (5 * _day - 3) / 153 ; 
	_day = 5 * _day - 3 - 153 * _month ; 
	_day = (_day + 5) / 5 ;
	_year = 100 * _year + JDN ;
	if (_month < 10){
		_month = _month + 3;
	}
	else{
		_month = _month - 9 ; 
		_year = _year + 1;
	}
	unsigned short* returnArray = new unsigned short[3]();
	returnArray[0]=(unsigned short) _year;
	returnArray[1]=(unsigned short) _month;
	returnArray[2]=(unsigned short) _day;
	return returnArray;
}


date dateUtil::getEndDateMonthIncrement(date startDate, int numMonth){
	if (numMonth==0) return startDate;
	short startMonth = startDate.getMonth();
	short endMonth = (startMonth + numMonth);
	bool isEndMonthPow12 = (startMonth + numMonth)%12==0?true:false;
	endMonth = isEndMonthPow12 ? 12 : (startMonth + numMonth)%12;
	int yearIncrement = abs((startMonth + numMonth)/12) - (isEndMonthPow12 ? 1 : 0);
	if (startMonth + numMonth<0)
		yearIncrement = -abs((startMonth + numMonth)/12) - 1 - (isEndMonthPow12 ? 1 : 0);
	endMonth = endMonth<=0 ? endMonth+12 : endMonth;
	short endYear= startDate.getYear()+ yearIncrement;	
	date endDate(endYear, endMonth, startDate.getDay());

	// Adjust the return day to the end of month if the start date is also end of month
	//if (startDate.getDay() == getMonthLastDay(startDate.getYear(), startDate.getMonth()))
   //endDate.setDay(getMonthLastDay(endDate.getYear(), endDate.getMonth()));
	return endDate;
}

date dateUtil::getBizDateOffSet(date refDate, long offset, enums::CurrencyEnum market) {
	long JDN = refDate.getJudianDayNumber();
	bool forward = offset>=0?true:false;
	for (long i=0; i<abs(offset); i++){
		forward?JDN++:JDN--;
		while(!isBizDay(JDN) || isHoliday(JDN,market)){
			forward?JDN++:JDN--;
		}
	}
	date offsetDate(JDN);
	return offsetDate; 
}
		
int dateUtil::getMonthLastDay(int year, int month){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (isleapyear(year) && month==2)
		monthlen[1]++;

	int lastDay = monthlen[month-1];
	return lastDay;
}

date dateUtil::adjustInvalidateDate(date aDate, bool forwardAdjust){
	int monthLastDay = getMonthLastDay(aDate.getYear(), aDate.getMonth());
	if (aDate.getDay()>monthLastDay){
		if (forwardAdjust){
			aDate.setMonth(aDate.getMonth()%12+1);
			aDate.setDay(1);
		}	else{
			aDate.setDay(monthLastDay);
		}
	}
	return aDate;
}

bool dateUtil::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

long dateUtil::getPrecedingJDN(date refDate, enums::CurrencyEnum market){
	//date adjustedDate = adjustInvalidateDate(refDate,false);
	long JDN = refDate.getJudianDayNumber();
	while(!isBizDay(JDN) || isHoliday(JDN,market)){
		JDN--;
	}
	return JDN;
}

long dateUtil::getFolloingJDN(date refDate, enums::CurrencyEnum market){
	//date adjustedDate = adjustInvalidateDate(refDate,true);
	long JDN = refDate.getJudianDayNumber();
	while(!isBizDay(JDN) || isHoliday(JDN,market)){
		JDN++;
	}
	return JDN;
}

double dateUtil::thirty_360(date startDate, date endDate){
	int yearFactor = 360*(endDate.getYear()-startDate.getYear());
	int monthFactor = 30*(endDate.getMonth()-startDate.getMonth());
	int dayFactor = endDate.getDay()-startDate.getDay();
	return (yearFactor+monthFactor+dayFactor)/360.0;
}

dateUtil::DateUnit dateUtil::getDateUnit(char letterDateUnit){
	switch(letterDateUnit){
	case 'BD':
		return BIZDAY;
	case 'D':
		return DAY;
	case 'N':
		return DAY;
	case 'M':
		return MONTH;
	case 'W':
		return WEEK;
	case 'Y':
		return YEAR;
	}
	throw "DateUnit not found: "+letterDateUnit;
}