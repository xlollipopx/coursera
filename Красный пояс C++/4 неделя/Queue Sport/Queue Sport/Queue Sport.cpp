// Queue Sport.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<map>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include<set>
using namespace std;

class sport_queue {
public:
	void add(int number, int order) {
		if (l.size() == 0) {
			l.push_back(number);
			position_[number] = l.begin();
			mp[number]++;
		}
		else {
			if (mp[order] == 0) {
				l.push_back(number);
				position_[number] = --l.end();
				mp[number]++;
			}
			else {
				auto it = l.emplace(position_[order], number);
				position_[number] = it;
				mp[number]++;
			}
		}
	}
	void print() {
		for (auto i : l) {
			cout << i << ' ';
		}
		cout << endl;
	}
private: 
	list<int> l;
	map<int, list<int> ::iterator> position_;
	map<int, int> mp;
	
};

int main()
{
	int n;
	sport_queue sq;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int order, num;
		cin >> num >> order;
		sq.add(num, order);
	}
	sq.print();


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
