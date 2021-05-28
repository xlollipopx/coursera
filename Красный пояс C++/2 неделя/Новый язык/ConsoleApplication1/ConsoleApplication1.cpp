// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include<iostream>
#include<ostream>
#include<map>
#include<set>
using namespace std;
//insert(returrn value):
//The single element versions(1) return a pair, with its member pair::first set to an 
//iterator pointing to either the newly inserted element or to the equivalent 
//element already in the set.The pair::second element in the pair is set to true if a new 
//element was inserted or false if an equivalent element already existed.
class Learner {
private:
	set<string> dict;
	
public:
	int Learn(const vector<string>& words) {
		int newWords = 0;
		for (const auto& word : words) {
			auto it = dict.insert(word);
			if (it.second == true) {
				newWords++;
			}
		}
		return newWords;
	}

	vector<string> KnownWords() {
		
		vector<string> di;
		for (const auto& i : dict) {
			di.push_back(i);
		}
		return di;
	}
};
int main() {
	Learner learner;
	string line;
	while (getline(cin, line)) {
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
		}
		cout << learner.Learn(words) << "\n";
	}
	cout << "=== known words ===\n";
	for (auto word : learner.KnownWords()) {
		cout << word << "\n";
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
