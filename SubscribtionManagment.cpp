#include "SubscribtionManagment.h"
#include <iostream>
using namespace std;

void SubscribtionManagment::write_to_file(map<int, int> mp) {

    ofstream sub{ "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\subs.txt",ios::trunc };

	if (!sub) {
		cerr << "Error writing to file ";
		return;
	}



	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {

		sub << it->first << "|" << it->second << endl;

	}

	sub.close();

	cout << "map saved to file successfully" << endl;

}


void SubscribtionManagment::store_to_map(Member m, map<int, int>& mapp) {


	int key;
	int value;

    days_left_test(m);

	key = m.getId();
	value = m.get_days();

    mapp[key] = value;

	cout << "stored to map successfully" << endl;


}


int SubscribtionManagment::check_expiry(map<int, int>& mp, int id) {



	if (mp[id] < 15 && mp[id]>0) {
		cout << "Your Subscription is about to end !" << endl;

		return 5;
	}

	else if (mp[id] <= 0) {

		cout << "Your Subscribtion has ended !" << endl;
		return 6;
	}

	else
		return 7;

}

bool SubscribtionManagment::offer() {




	cout << "-----Limited Time Offers !-----" << endl;
	cout << "10% Discount on Renewal with 3 months" << endl;
	cout << "20% Discount on Renewal with 6 months" << endl;
	cout << "25% Discount on Renewal with 1 year" << endl;
	cout << "Do you wish to renew ? " << endl;
	cout << "(yes/no)" << endl;

	bool invalid = true;
	string st1;

	while (invalid) {


		cin >> st1;

		transform(st1.begin(), st1.end(), st1.begin(), [](unsigned char c) { return std::tolower(c); });

		if (st1 == "yes" || st1 == "y") {

			invalid = false;
			return true;

		}

		else if (st1 == "no" || st1 == "n") {
			invalid = false;
			return false;
		}
		else {
			cout << "invalid answer" << endl;
			cout << "Write again " << endl;

		}
	}



}

map<int, int> SubscribtionManagment::renew(map<int, int> mp, int id) {
	int period;


	cout << "Enter Period of Subsription: ";

	cin >> period;
	mp[id] += period * 30;

	return mp;
}


void SubscribtionManagment::cancel(map<int, int>& mapp, int id) {

	mapp.erase(id);

	cout << "member deleted from map successfully" << endl;

}

map<int, int> SubscribtionManagment::read_from_file(const string& name) {


	ifstream file(name);
	map<int, int> myMap;

	if (!file) {
		cerr << "Failed to open file: " << name << endl;
		return myMap;
	}

	string line;
	while (getline(file, line)) {
		size_t x = line.find('|');

		if (x != string::npos) {
			string keyStr = line.substr(0, x);
			string valueStr = line.substr(x + 1);

			try {
				int key = stoi(keyStr);
				int value = stoi(valueStr);
				myMap[key] = value;
			}
			catch (const exception& e) {
				cerr << "Error parsing line: " << line << std::endl;
			}
		}

	}
	cout << "map loaded successfully" << endl;
	return myMap;

}

void SubscribtionManagment::days_left_test(Member& mem) {
	string str = mem.getSubscription_expiration_date();
	if (!str.empty()) {
		int d, m, y;
		sscanf_s(str.c_str(), "%d/%d/%d", &d, &m, &y);
		tm parsed{};
		parsed.tm_mday = d;
		parsed.tm_mon = m - 1;
		parsed.tm_year = y - 1900;

		time_t timee = mktime(&parsed);

		if (timee == -1) {
			std::cerr << "Invalid date\n";
			return;
		}

		time_t now = std::time(nullptr);

		double seconds_diff = difftime(timee, now);
		int days_diff = static_cast<int>(seconds_diff / (60 * 60 * 24));


		mem.set_days(days_diff);




	}
	else {
		cout << "string is empty";
		return;
	}

}

void SubscribtionManagment::paymentt(int duration) {
	switch (duration) {
	case 1:
		cout << "The amount to be paid is : 1000 L.E" << endl;
		break;
	case 3:
		cout << "The amount to be paid is : 1800 L.E" << endl;
		break;
	case 6:
		cout << "The amount to be paid is : 3200 L.E" << endl;
		break;
	case 12:
		cout << "The amount to be paid is : 6000 L.E" << endl;
	default:
		cout << "Invalid Period";
		break;
	}
}
