
#include "test_runner.h"
#include "airline_ticket.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) {map<string, string>::const_iterator it;\
 it = values.find(#field);\
if (it != values.end()) {\
if(#field != "price"){\
         istringstream is(it->second);\
        is>>ticket.field;\
}\
else{\
 istringstream is(it->second);\
is >> ticket.price;\
}\
}\
}
bool operator < (const Time& l, const Time& r) {
	return tie(l.hours, l.minutes) < tie(r.hours, r.minutes);
}
bool operator == (const Time& l, const Time& r) {
	return (l.hours == r.hours && l.minutes == r.minutes);
}
bool operator == (const Date& l, const Date& r) {
	return (l.day == r.day && l.month == r.month && l.year == r.year);
}


ostream& operator << (ostream& os, const Time& obj) {
	os << obj.hours << ' ' << obj.minutes;
	return os;
}
ostream& operator << (ostream& os, const Date& obj) {
	os << obj.day << endl;
	return os;
}
bool operator < (const Date& l, const Date& r) {
	return tie(l.year, l.month, l.day) < tie(r.year, r.month, r.day);
}
istream& operator>>(istream& is, Date& t) {
	string str, d;
	is >> str;
	d = "-:";
	int pos1;
	int da, m, y;
	int pos2;

	str = str + d;
	pos1 = 0;
	int k = 0;
	while ((pos1 = str.find_first_not_of(d, pos1)) != string::npos) {
		pos2 = str.find_first_of(d, pos1);
		string s = str.substr(pos1, pos2 - pos1);
		int a = stoi(s);
		if (k == 0) {
			y = a;
		}
		if (k == 1) {
			m = a;
		}
		if (k == 2) {
			da = a;
		}
		k++;
		pos1 = pos2;
	}
	tie(t.year, t.month, t.day) = tie(y, m, da);
	return is;

}



istream& operator>>(istream& is, Time& t) {
	string str,  d;
	is >> str;
	d = "-:";
	int pos1;
	int ho, mi;
	int pos2;

	str = str + d;
	pos1 = 0;
	int k = 0;
	while ((pos1 = str.find_first_not_of(d, pos1)) != string::npos) {
		pos2 = str.find_first_of(d, pos1);
		string s = str.substr(pos1, pos2 - pos1);
		int a = stoi(s);
		if (k == 0) {
			ho = a;
		}
		if (k == 1) {
			mi = a;
		}
		k++;
		pos1 = pos2;
	}
	tie(t.hours, t.minutes) = tie(ho, mi);
	return is;

}


void TestUpdate() {
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = {
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);

	//UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = {
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
	// значения этих полей не должны измениться
	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}
