#include "marketdata.h"


bool MarketDataTimeStamp::operator>(const MarketDataTimeStamp& in_obj)const {
	if (this->year > in_obj.year)
		return true;
	else if (this->year == in_obj.year && this->month_day > in_obj.month_day)
		return true;
	else if (this->year == in_obj.year && this->month_day == in_obj.month_day && this->hour_minute_second > in_obj.hour_minute_second)
		return true;
	else if (this->year == in_obj.year && this->month_day == in_obj.month_day && this->hour_minute_second == in_obj.hour_minute_second && this->milisecond > in_obj.milisecond)
		return true;
	else
		return false;
}
bool MarketDataTimeStamp::operator<=(const MarketDataTimeStamp& in_obj)const {
	if (this->year <= in_obj.year)
		return true;
	else if (this->year == in_obj.year && this->month_day <= in_obj.month_day)
		return true;
	else if (this->year == in_obj.year && this->month_day == in_obj.month_day && this->hour_minute_second <= in_obj.hour_minute_second)
		return true;
	else if (this->year == in_obj.year && this->month_day == in_obj.month_day && this->hour_minute_second == in_obj.hour_minute_second && this->milisecond <= in_obj.milisecond)
		return true;
	else return false;
}



bool MarketDataLastPrice::operator>(const MarketDataLastPrice& in_obj)const{
	if (this->last_price > in_obj.last_price)
		return true;
	else
		return false;
}
bool MarketDataLastPrice::operator<=(const MarketDataLastPrice& in_obj)const {
	if (this->last_price <= in_obj.last_price)
		return true;
	else
		return false;
}