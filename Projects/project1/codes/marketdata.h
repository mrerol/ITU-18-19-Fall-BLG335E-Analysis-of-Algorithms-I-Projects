using namespace std;

class MarketDataTimeStamp {
public:
	int index_file_line;

	int year;
	int month_day;
	int hour_minute_second;
	int milisecond;

	MarketDataTimeStamp(){};
	~MarketDataTimeStamp() {};

	bool operator>(const MarketDataTimeStamp&)const;
	bool operator<=(const MarketDataTimeStamp&)const;
};

class MarketDataLastPrice {
public:
	int index_file_line;

	float last_price;

	MarketDataLastPrice(){};
	~MarketDataLastPrice() {};

	bool operator>(const MarketDataLastPrice&)const;
	bool operator<=(const MarketDataLastPrice&)const;
};

