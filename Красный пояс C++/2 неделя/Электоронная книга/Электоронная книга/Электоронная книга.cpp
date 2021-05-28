// Электоронная книга.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iomanip>
#include <iostream>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

class ReadingManager {
public:
	ReadingManager()
		: user_page_counts_(MAX_USER_COUNT_ + 1, 0),
		sorted_users_(),
		user_positions_(MAX_USER_COUNT_ + 1, -1) {}

	void Read(int user_id, int page_count) {
		if (user_page_counts_[user_id] == 0) {
			AddUser(user_id);
		}
		user_page_counts_[user_id] = page_count;
		int& position = user_positions_[user_id];
		while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
			SwapUsers(position, position - 1);
		}
	}

	double Cheer(int user_id) const {
		if (user_page_counts_[user_id] == 0) {
			return 0;
		}
		const int user_count = GetUserCount();
		if (user_count == 1) {
			return 1;
		}
		const int page_count = user_page_counts_[user_id];
		int position = user_positions_[user_id];
		while (position < user_count &&
			user_page_counts_[sorted_users_[position]] == page_count) {
			++position;
		}
		if (position == user_count) {
			return 0;
		}
		// ÐŸÐ¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ Ð´ÐµÐ»ÐµÐ½Ð¸Ðµ Ñ†ÐµÐ»Ð¾Ñ‡Ð¸ÑÐ»ÐµÐ½Ð½Ð¾Ðµ, Ð¿Ð¾ÑÑ‚Ð¾Ð¼Ñƒ
		// Ð½ÑƒÐ¶Ð½Ð¾ Ð¿Ñ€Ð¸Ð²ÐµÑÑ‚Ð¸ Ñ‡Ð¸ÑÐ»Ð¸Ñ‚ÐµÐ»ÑŒ Ðº Ñ‚Ð¸Ð¿Ñƒ double.
		// ÐŸÑ€Ð¾ÑÑ‚Ð¾Ð¹ ÑÐ¿Ð¾ÑÐ¾Ð± ÑÐ´ÐµÐ»Ð°Ñ‚ÑŒ ÑÑ‚Ð¾ â€” ÑƒÐ¼Ð½Ð¾Ð¶Ð¸Ñ‚ÑŒ ÐµÐ³Ð¾ Ð½Ð° 1.0.
		return (user_count - position) * 1.0 / (user_count - 1);
	}

private:
	// Ð¡Ñ‚Ð°Ñ‚Ð¸Ñ‡ÐµÑÐºÐ¾Ðµ Ð¿Ð¾Ð»Ðµ Ð½Ðµ Ð¿Ñ€Ð¸Ð½Ð°Ð´Ð»ÐµÐ¶Ð¸Ñ‚ ÐºÐ°ÐºÐ¾Ð¼Ñƒ-Ñ‚Ð¾ ÐºÐ¾Ð½ÐºÑ€ÐµÑ‚Ð½Ð¾Ð¼Ñƒ
	// Ð¾Ð±ÑŠÐµÐºÑ‚Ñƒ ÐºÐ»Ð°ÑÑÐ°. ÐŸÐ¾ ÑÑƒÑ‚Ð¸ ÑÑ‚Ð¾ Ð³Ð»Ð¾Ð±Ð°Ð»ÑŒÐ½Ð°Ñ Ð¿ÐµÑ€ÐµÐ¼ÐµÐ½Ð½Ð°Ñ,
	// Ð² Ð´Ð°Ð½Ð½Ð¾Ð¼ ÑÐ»ÑƒÑ‡Ð°Ðµ ÐºÐ¾Ð½ÑÑ‚Ð°Ð½Ñ‚Ð½Ð°Ñ.
	// Ð‘ÑƒÐ´ÑŒ Ð¾Ð½Ð° Ð¿ÑƒÐ±Ð»Ð¸Ñ‡Ð½Ð¾Ð¹, Ðº Ð½ÐµÐ¹ Ð¼Ð¾Ð¶Ð½Ð¾ Ð±Ñ‹Ð»Ð¾ Ð±Ñ‹ Ð¾Ð±Ñ€Ð°Ñ‚Ð¸Ñ‚ÑŒÑÑ ÑÐ½Ð°Ñ€ÑƒÐ¶Ð¸
	// ÑÐ»ÐµÐ´ÑƒÑŽÑ‰Ð¸Ð¼ Ð¾Ð±Ñ€Ð°Ð·Ð¾Ð¼: ReadingManager::MAX_USER_COUNT.
	static const int MAX_USER_COUNT_ = 100'000;

	vector<int> user_page_counts_;
	vector<int> sorted_users_;   // Ð¾Ñ‚ÑÐ¾Ñ€Ñ‚Ð¸Ñ€Ð¾Ð²Ð°Ð½Ñ‹ Ð¿Ð¾ ÑƒÐ±Ñ‹Ð²Ð°Ð½Ð¸ÑŽ ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð° ÑÑ‚Ñ€Ð°Ð½Ð¸Ñ†
	vector<int> user_positions_; // Ð¿Ð¾Ð·Ð¸Ñ†Ð¸Ð¸ Ð² Ð²ÐµÐºÑ‚Ð¾Ñ€Ðµ sorted_users_

	int GetUserCount() const {
		return sorted_users_.size();
	}
	void AddUser(int user_id) {
		sorted_users_.push_back(user_id);
		user_positions_[user_id] = sorted_users_.size() - 1;
	}
	void SwapUsers(int lhs_position, int rhs_position) {
		const int lhs_id = sorted_users_[lhs_position];
		const int rhs_id = sorted_users_[rhs_position];
		swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
		swap(user_positions_[lhs_id], user_positions_[rhs_id]);
	}
};

class request_handler {
private:
	map<int, int> page_rate;
	map<int, int> users;
	int users_amount;
public:
	request_handler() { users_amount = 0; }

	void read(const int& user,const int& page) {
		if (users[user] == 0) {
			users_amount++;
		}
		else {
			page_rate[users[user]]--;
		}
		users[user] = page;
		page_rate[page]++;
	
	}
	double cheer(const int& user) {
		if (users_amount == 0) {
			return 0;
		}
		if (users_amount == 1) {
			return 1;
		}
		if (users[user] == 0) {
			return 0;
		}
		double result = 0;
		int k = users[user];
		for (auto i : page_rate) {
			if (i.first == k) {
				break;
			}
			result += i.second;
		}
		double n = users_amount - 1;
		
		return result / n;
	}


};

int main()
{

	int q;
	cin >> q;
	ReadingManager rq;
	while (q--) {
		string cmd;
		cin >> cmd;
		if (cmd == "READ") {
			int u, p;
			cin >> u >> p;
			rq.Read(u, p);
		}
		else {
			int u;
			cin >> u;
			cout << setprecision(6) << rq.Cheer(u)<<endl;
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
