// ssort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "test_runner.h"
#include <algorithm>
#include<vector>
#include <numeric>
#include "airline_ticket.h"
#include<tuple>
using namespace std;

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
	os << obj.hours <<  ' '<<obj.minutes;
	return os;
}
ostream& operator << (ostream& os, const Date& obj) {
	os << obj.day << endl;
	return os;
}
bool operator < (const Date& l, const Date& r) {
	return tie(l.year, l.month, l.day) < tie(r.year, r.month, r.day);
}
#define SORT_BY(field)[](const AirlineTicket& lhs, const AirlineTicket& rhs) {\
return lhs.field < rhs.field;\
}

void SortTickets(vector<AirlineTicket>& tixs) {
	stable_sort(begin(tixs), end(tixs), SORT_BY(to));
	stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
	stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
void TestSortBy() {
	vector<AirlineTicket> tixs = {
	  {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
	  {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
	  {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
	  {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
	  {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
	};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{ 2018, 2, 9 }));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{ 2018, 3, 5 }));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
