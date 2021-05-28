// Система бронирования.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*#include <iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;

struct Request{
	long long time;
	string hotel_name;
	int client_id;
	int room_count;
	Request(long long t,string h,int c,int r) : time(t), hotel_name(h), client_id(c), room_count(r){}

};
class Requst_handler {
public:
	void Book(long long _time, string _hotel_name, int id, int _rooms) {
		Request q(_time, _hotel_name, id, _rooms);
		event_queue.push(q);
		while (!event_queue.empty() && q.time - event_queue.front().time >= 86400ll)
		{
			clients[event_queue.front().hotel_name][event_queue.front().client_id] -= event_queue.front().room_count;
			if (clients[event_queue.front().hotel_name][event_queue.front().client_id] == 0) {
				clients[event_queue.front().hotel_name].erase(event_queue.front().client_id);
			}
			rooms[event_queue.front().hotel_name] -= event_queue.front().room_count;
			event_queue.pop();
		}
		clients[_hotel_name][id] += _rooms;
		rooms[_hotel_name] += _rooms;
	}
	int Rooms(string _hotel_name) {
		return rooms[_hotel_name];
	}
	int Clients(string _hotel_name) {
		int res = clients[_hotel_name].size();
		return res;
	}

private:
	queue<Request>  event_queue;
	map<string, map<int, int>> clients;
	map<string, int> rooms;
};

int main()
{
   
	int q;
	cin >> q;
	Requst_handler rq;
	while (q--) {
		string req;
		cin >> req;
		if (req == "CLIENTS") {
			string name;
			cin >> name;
			cout << rq.Clients(name) << endl;
		}
		if (req == "BOOK") {
			string name;
			int t, id, r;
			cin >> t >> name >> id >> r;
			rq.Book(t, name, id, r);
		}
		if (req == "ROOMS") {
			string name;
			cin >> name;
			cout << rq.Rooms(name)<<endl;
		}
	}
	

	
}*/
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class HotelManager {
public:
	void Book(int64_t time, const string& hotel_name,
		int client_id, int room_count) {
		current_time_ = time;
		hotels_[hotel_name].Book({ time, client_id, room_count });
	}
	int ComputeClientCount(const string& hotel_name) {
		return hotels_[hotel_name].ComputeClientCount(current_time_);
	}
	int ComputeRoomCount(const string& hotel_name) {
		return hotels_[hotel_name].ComputeRoomCount(current_time_);
	}

private:
	struct Booking {
		int64_t time;
		int client_id;
		int room_count;
	};

	class HotelInfo {
	public:
		void Book(const Booking& booking) {
			last_bookings_.push(booking);
			room_count_ += booking.room_count;
			++client_booking_counts_[booking.client_id];
		}
		int ComputeClientCount(int64_t current_time) {
			RemoveOldBookings(current_time);
			return client_booking_counts_.size();
		}
		int ComputeRoomCount(int64_t current_time) {
			RemoveOldBookings(current_time);
			return room_count_;
		}
	private:
		static const int TIME_WINDOW_SIZE = 86400;
		queue<Booking> last_bookings_;
		int room_count_ = 0;
		map<int, int> client_booking_counts_;

		void PopBooking() {
			const Booking& booking = last_bookings_.front();
			room_count_ -= booking.room_count;
			const auto client_stat_it =
				client_booking_counts_.find(booking.client_id);
			if (--client_stat_it->second == 0) {
				client_booking_counts_.erase(client_stat_it);
			}
			last_bookings_.pop();
		}
		void RemoveOldBookings(int64_t current_time) {
			while (
				!last_bookings_.empty()
				&& last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
				) {
				PopBooking();
			}
		}
	};

	int64_t current_time_ = 0;
	map<string, HotelInfo> hotels_;
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;

		if (query_type == "BOOK") {
			int64_t time;
			cin >> time;
			string hotel_name;
			cin >> hotel_name;
			int client_id, room_count;
			cin >> client_id >> room_count;
			manager.Book(time, hotel_name, client_id, room_count);
		}
		else {
			string hotel_name;
			cin >> hotel_name;
			if (query_type == "CLIENTS") {
				cout << manager.ComputeClientCount(hotel_name) << "\n";
			}
			else if (query_type == "ROOMS") {
				cout << manager.ComputeRoomCount(hotel_name) << "\n";
			}
		}
	}

	return 0;
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
