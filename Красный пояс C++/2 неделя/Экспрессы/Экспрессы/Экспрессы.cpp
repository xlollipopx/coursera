// Экспрессы.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

class stop_handler {

private:
	map<int, set<int> > routes;
public:
	void add_route(int start, int finish) {
		routes[start].insert(finish);
		routes[finish].insert(start);
	}
	int get_route(int start, int finish){
		int res = abs(finish - start);
		if (start == finish) {
			return 0;
		}
		if (routes[start].empty() == true) {
			return res;
		}
		const set<int>& tmp = routes[start];
		auto finish_pos = tmp.lower_bound(finish);
		if (finish_pos != tmp.end()) {
			res = min(res, abs(finish - *finish_pos));
		}
		if (finish_pos != tmp.begin()) {
			res = min(res, abs(finish - *prev(finish_pos)));
		}
		return res;

	}

};

int main()
{
	int q;
	cin >> q;
	stop_handler sh;
	while (q--) {
		string cmd;
		cin >> cmd;
		pair<int, int> req;
		cin >> req.first >> req.second;
		
		if (cmd == "ADD") {		
			sh.add_route(req.first,req.second);
		}
		else {
			int ans = sh.get_route(req.first,req.second);
			cout << ans << endl;
		}
	}
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
