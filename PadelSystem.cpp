#include "PadelSystem.h"
#include "Booking.h"
#include "Member.h"
#include "Staff.h"
#include <iostream>
#include <unordered_set>
#include <limits>
#include<queue>
#include <ctime>
#include <QString>
#include <QTextStream>
using namespace std;
 vector<Booking> bookings = Booking::loadFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
map<pair<string, string>, queue<Booking>> waitlist;
map<pair<string, string>, queue<Booking>> vipWaitlist;
PadelSystem::PadelSystem() {
	courts.emplace_back (1);
}

PadelSystem::PadelSystem(int numCourts) {
	for (int i = 1; i <= numCourts; ++i) {
		courts.emplace_back(i);
	}
}

string PadelSystem::getDayName(int choice) const {
	switch (choice) {
	case 1: return "Wednesday";
	case 2: return "Thursday";
	case 3: return "Friday";
	case 4: return "Saturday";
	case 5: return "Sunday";
	case 6: return "Monday";
	case 7: return "Tuesday";
	default: return "";
	}
}

bool PadelSystem::isValidTime(const string& time) const {

	if (time.length() != 5 || time[2] != ':') return false;
	try {
		int hour = stoi(time.substr(0, 2));
		int minute = stoi(time.substr(3, 2));
		return hour >= 15 && hour <= 23 && minute == 0;
	}
	catch (...) {
		return false;
	}
}

void PadelSystem::displayUserMenu() const {
	cout << "\n=== User Menu ===\n";
	cout << "1. Book a Court\n";
	cout << "2. Check Availability\n";
	cout << "3. View My Bookings\n";
	cout << "4. cancel Booking\n";
	cout << "5. Logout\n";
	cout << "Enter choice: ";
}

void PadelSystem::displayManagerMenu() const {
	cout << "\n=== Manager Menu ===\n";
	cout << "1. View All Bookings\n";
	cout << "2. View Bookings by day\n";
	cout << "3. Delete Booking\n";
	cout << "4. Check Availability\n";
	cout << "5. View the waiting list.\n";
	cout << "6. Logout.\n";
	cout << "Enter choice: ";
}



bool PadelSystem::isInWaitlist(int id, const string& day, const string& time, int courtNum, bool isVip) {
    string filename = isVip ?"C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt" : "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt";
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string idStr, wDay, wTime;
		int wCourt;

		getline(ss, idStr, ',');
		getline(ss, wDay, ',');
		getline(ss, wTime, ',');
		ss >> wCourt;

		if (stoi(idStr) == id && wDay == day && wTime == time && wCourt == courtNum) {
			return true;
		}
	}
	return false;
}

void PadelSystem::viewWaitlist() {
	string day;
	cout << "\nSelect the day to view the waiting list:\n";
	cout << "1. Wednesday\n2. Thursday\n3. Friday\n4. Saturday\n5. Sunday\n6. Monday\n7. Tuesday\n";
	cout << "Enter choice (1-7): ";

	int dayChoice;
	cin >> dayChoice;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	day = getDayName(dayChoice);
	if (day.empty()) {
		cout << "Invalid day choice!\n";
		return;
	}

	cout << "\n " << day << " waitinglist:\n";

	auto showWaitlist = [&](const string& filename, const string& type) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Could not open " << filename << " file.\n";
			return;
		}

		string line;
		bool found = false;
		while (getline(file, line)) {
			stringstream ss(line);
			string idStr, d, time;
			int court;
			getline(ss, idStr, ',');
			getline(ss, d, ',');
			getline(ss, time, ',');
			ss >> court;

			if (d == day) {
				cout << "Member ID: " << idStr
					<< " | Time: " << time
					<< " | Court: " << court 
					<< " | Type: " << type << "\n";
				found = true;
			}
		}
		if (!found) {
			cout << "No " << type << " waitlist on " << day << ".\n";
		}
		file.close();
		};

    showWaitlist("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt", "VIP");
    showWaitlist("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt", "Regular");
}

bool PadelSystem::assignFromWaitlist(const string& day, const string& time, int courtNum) {
	// VIP waitlist
    ifstream vipIn("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt");
	vector<string> updatedVipLines;
	string line;
	bool booked = false;

	while (getline(vipIn, line)) {
		stringstream ss(line);
		string idStr, fileDay, fileTime;
		int fileCourt;
		getline(ss, idStr, ',');
		getline(ss, fileDay, ',');
		getline(ss, fileTime, ',');
		ss >> fileCourt;

		if (!booked && fileDay == day && fileTime == time && fileCourt == courtNum) {
			int waitId = stoi(idStr);
			Booking newBooking(day, time, courtNum, waitId);
            courts[courtNum - 1].addBooking(newBooking);
            //newBooking.saveToFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
			cout << "VIP member ID " << waitId << " has been moved from waitlist and booked.\n";
			booked = true;
		}
		else {
			updatedVipLines.push_back(line);
		}
	}
	vipIn.close();

    ofstream vipOut("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt", ios::trunc);
	for (const auto& l : updatedVipLines) vipOut << l << "\n";
	vipOut.close();

	if (booked) return true;

	// Regular waitlist
    ifstream regIn("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt");
	vector<string> updatedRegLines;

	while (getline(regIn, line)) {
		stringstream ss(line);
		string idStr, fileDay, fileTime;
		int fileCourt;
		getline(ss, idStr, ',');
		getline(ss, fileDay, ',');
		getline(ss, fileTime, ',');
		ss >> fileCourt;

		if (!booked && fileDay == day && fileTime == time && fileCourt == courtNum) {
			int waitId = stoi(idStr);
			Booking newBooking(day, time, courtNum, waitId);
            courts[courtNum - 1].addBooking(newBooking);
            //newBooking.saveToFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
			cout << "Regular member ID " << waitId << " has been moved from waitlist and booked.\n";
			booked = true;
		}
		else {
			updatedRegLines.push_back(line);
		}
	}
	regIn.close();

    ofstream regOut("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt", ios::trunc);
	for (const auto& l : updatedRegLines) regOut << l << "\n";
	regOut.close();

	return booked;
}

void PadelSystem::checkAvailability() const {
	string day, time;

	// Get day input
	cout << "\nSelect a day to check:\n";
	cout << "1. Wednesday\n2. Thursday\n3. Friday\n4. Saturday\n";
	cout << "5. Sunday\n6. Monday\n7. Tuesday\n";
	cout << "Enter choice (1-7): ";

	int dayChoice;
	if (!(cin >> dayChoice) || dayChoice < 1 || dayChoice > 7) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid day choice!\n";
		return;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	day = getDayName(dayChoice);

	// Get time input
	cout << "Enter time (HH:00, 15:00-23:00): ";
	getline(cin, time);

	if (!isValidTime(time)) {
		cout << "Invalid time format! Must be between 15:00 and 23:00 on the hour.\n";
		return;
	}

	bool anyAvailable = false;
	cout << "\n=== Bookings Availability ===\n";
    ifstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
	if (!file.is_open()) {
		cout << "No bookings available\n";
		return;
	}

	// Track booked courts from file
	unordered_set<int> bookedCourts;
	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;

		size_t pos1 = line.find(',');
		size_t pos2 = line.find(',', pos1 + 1);
		size_t pos3 = line.find(',', pos2 + 1);

		if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
			string fileDay = line.substr(pos1 + 1, pos2 - pos1 - 1);
			string fileTime = line.substr(pos2 + 1, pos3 - pos2 - 1);
			int fileCourtNum = stoi(line.substr(pos3 + 1));

			if (fileDay == day && fileTime == time) {
				bookedCourts.insert(fileCourtNum);
			}
		}
	}
	file.close();
	bool anyFileAvailable = false;
	for (int i = 1; i <= static_cast<int>(courts.size()); i++) {
		if (bookedCourts.find(i) == bookedCourts.end()) {
			cout << "Court " << i << " is available.\n";
			anyFileAvailable = true;
		}
	}

	if (!anyFileAvailable) {
		cout << "No courts available at this time!\n";
	}
}

void PadelSystem::viewAllBookings() const {
	struct BookingInfo {
		string day;
		string time;
		string courtNum;
	};

	map<string, vector<BookingInfo>> bookingsByMember;

    ifstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");

	if (!file.is_open()) {
		cout << "No bookings file found or unable to open.\n";
		cout << "No bookings found.\n";
		return;
	}

	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			size_t pos3 = line.find(',', pos2 + 1);

			if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
				string id = line.substr(0, pos1);
				string day = line.substr(pos1 + 1, pos2 - pos1 - 1);
				string time = line.substr(pos2 + 1, pos3 - pos2 - 1);
				string courtNum = line.substr(pos3 + 1);

				bookingsByMember[id].push_back({ day, time, courtNum });
			}
		}
	}
	file.close();

	if (bookingsByMember.empty()) {
		cout << "No bookings found.\n";
		return;
	}

	// Display grouped by member
	for (const auto& pair : bookingsByMember) {
		const string& id = pair.first;
		const vector<BookingInfo>& bookings = pair.second;

		cout << "\nMember ID: " << id << "\n";
		for (size_t i = 0; i < bookings.size(); ++i) {
			const BookingInfo& b = bookings[i];
			cout << i + 1 << ". Court " << b.courtNum << " on " << b.day << " at " << b.time << "\n";
		}
	}

}


void PadelSystem::viewBookingsByDay() {


	if (bookings.empty()) {
		cout << "No bookings found.\n";
		return;
	}

	cout << "\nSelect a day to view bookings:\n";
	cout << "1. Wednesday\n2. Thursday\n3. Friday\n4. Saturday\n";
	cout << "5. Sunday\n6. Monday\n7. Tuesday\n8. Cancel\n";
	cout << "Enter choice (1-8): ";

	int dayChoice;
	if (!(cin >> dayChoice)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input! Returning to main menu.\n";
		return;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (dayChoice == 8) {
		cout << "Operation cancelled.\n";
		return;
	}

	string day = getDayName(dayChoice);
	if (day.empty()) {
		cout << "Invalid day selection.\n";
		return;
	}

	// Filter bookings for the selected day
	vector<Booking> filtered;
	for (const Booking& b : bookings) {
		if (b.getDay() == day) {
			filtered.push_back(b);
		}
	}

	if (filtered.empty()) {
		cout << "No bookings found for " << day << ".\n";
		return;
	}

	// Sort by time then court number
	sort(filtered.begin(), filtered.end(), [](const Booking& a, const Booking& b) {
		if (a.getTime() == b.getTime())
			return a.getCourtNumber() < b.getCourtNumber();
		return a.getTime() < b.getTime();
		});

	cout << "\nBookings for " << day << ":\n";
	for (const Booking& b : filtered) {
		cout << "At " << b.getTime()
			<< ", Court number " << b.getCourtNumber()
			<< ", is booked for Member ID: " << b.getUserid() << "\n";
	}
}

void PadelSystem::viewMyBookings(int memberid) const {
	bool hasBookings = false;
	// Then show bookings from file
	cout << "\n=== My Bookings ===\n";
    ifstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
	if (!file.is_open()) {
		cout << "No bookings file found or unable to open.\n";
		if (!hasBookings) {
			cout << "No bookings found.\n";
		}
		return;
	}

	string line;
	bool fileHasBookings = false;
	while (getline(file, line)) {
		if (!line.empty()) {
			// Parse the line: id,day,time,courtNum
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			size_t pos3 = line.find(',', pos2 + 1);

			if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
				string id = line.substr(0, pos1);
				string day = line.substr(pos1 + 1, pos2 - pos1 - 1);
				string time = line.substr(pos2 + 1, pos3 - pos2 - 1);
				string courtNum = line.substr(pos3 + 1);
				string memberId = to_string(memberid);

				if (memberId == id) {
			fileHasBookings = true;
					cout << "Court " << courtNum
						<< ", Day: " << day
						<< ", Time: " << time<<endl;
				}
			}
		}
	}

	file.close();

	if (!fileHasBookings && !hasBookings) {
		cout << "No bookings found.\n";
	}
}

void PadelSystem::deleteBooking() { //new
	string day, time;
	int courtNum;

	cout << "\nSelect a day:\n";
	cout << "1. Wednesday\n2. Thursday\n3. Friday\n4. Saturday\n";
	cout << "5. Sunday\n6. Monday\n7. Tuesday\n";
	cout << "Enter choice (1-7): ";

	int dayChoice;
	if (!(cin >> dayChoice) || dayChoice < 1 || dayChoice > 7) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid day choice!\n";
		return;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	day = getDayName(dayChoice);
	if (day.empty()) {
		cout << "Invalid day selection!\n";
		return;
	}

	cout << "Enter time (HH:00, 15:00-23:00): ";
	getline(cin, time);

	if (!isValidTime(time)) {
		cout << "Invalid time format! Must be between 15:00 and 23:00 on the hour.\n";
		return;
	}

	cout << "Enter court number (1-" << courts.size() << "): ";
	if (!(cin >> courtNum)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input! Please enter a number.\n";
		return;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (courtNum < 1 || courtNum > static_cast<int>(courts.size())) {
		cout << "Invalid court number!\n";
		return;
	}

	// Remove booking
	bool found = false;

	for (const auto& booking : bookings) {
		if (booking.getDay() == day && booking.getTime() == time && booking.getCourtNumber() == courtNum) {
            Booking::removeFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt", day, time, courtNum, -1);
			courts[courtNum - 1].removeBooking(day, time);
			cout << "Booking deleted successfully!\n";
			found = true;

			// Try assigning someone from the waitlist to this freed slot
			if (!assignFromWaitlist(day, time, courtNum)) {
				cout << "No one in waitlists to assign for this slot.\n";
			}
			break;
		}
	}

	if (!found) {
		cout << "No booking found for this court, day, and time.\n";
	}
}

void PadelSystem::deleteMyBooking(int id) {   //new
    string day, timee;
    int courtNum;

    cout << "\nSelect the day of the booking you want to delete:\n";
    cout << "1. Wednesday\n2. Thursday\n3. Friday\n4. Saturday\n5. Sunday\n6. Monday\n7. Tuesday\n";
    cout << "Enter choice (1-7): ";
    int dayChoice;
    cin >> dayChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    day = getDayName(dayChoice);
    if (day.empty()) {
        cout << "Invalid day choice!\n";
        return;
    }

    cout << "Enter time (HH:00, 15:00-23:00): ";
    cin >> timee;
    if (!isValidTime(timee)) {
        cout << "Invalid time! Must be on the hour between 15:00 and 23:00.\n";
        return;
    }

    cout << "Enter court number (1-" << courts.size() << "): ";
    cin >> courtNum;
    if (courtNum < 1 || courtNum > static_cast<int>(courts.size())) {
        cout << "Invalid court number!\n";
        return;
    }

    bool found = false;
    for (const auto& booking : bookings) {
        if (booking.getDay() == day &&
            booking.getTime() == timee &&
            booking.getCourtNumber() == courtNum &&
            booking.getUserid() == id) {

            Booking::removeFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt", day, timee, courtNum, id);
            courts[courtNum - 1].removeBooking(day, timee);
            cout << "Booking deleted successfully!\n";
            found = true;

            // Try assigning someone from the waitlist to this freed slot
            if (!assignFromWaitlist(day, timee, courtNum)) {
                cout << "No one in waitlists to assign for this slot.\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "No booking found for you on Court " << courtNum << " at " << timee << " on " << day << ".\n";
    }
}


QString PadelSystem::getAllBookingsText() {
    struct BookingInfo {
        string day;
        string time;
        string courtNum;
    };

    map<string, vector<BookingInfo>> bookingsByMember;

    ifstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    QString result;
    QTextStream out(&result);

    if (!file.is_open()) {
        out << "No bookings file found or unable to open.\n";
        out << "No bookings found.\n";
        return result;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                string id = line.substr(0, pos1);
                string day = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string time = line.substr(pos2 + 1, pos3 - pos2 - 1);
                string courtNum = line.substr(pos3 + 1);

                bookingsByMember[id].push_back({ day, time, courtNum });
            }
        }
    }
    file.close();

    if (bookingsByMember.empty()) {
        out << "No bookings found.\n";
        return result;
    }

    for (const auto& pair : bookingsByMember) {
        const string& id = pair.first;
        const vector<BookingInfo>& bookings = pair.second;

        out << "\nMember ID: " << QString::fromStdString(id) << "\n";
        for (size_t i = 0; i < bookings.size(); ++i) {
            const BookingInfo& b = bookings[i];
            out << i + 1 << ". Court " << QString::fromStdString(b.courtNum)
                << " on " << QString::fromStdString(b.day)
                << " at " << QString::fromStdString(b.time) << "\n";
        }
    }

    return result;
}

