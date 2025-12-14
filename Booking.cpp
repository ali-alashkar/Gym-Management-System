#include "Booking.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

Booking::Booking(const string& d, const string& t, int court, const int& userid)
	: day(d), time(t), courtNumber(court), userID(userid) {}

string Booking::getDay() const { return day; }
string Booking::getTime() const { return time; }
int Booking::getCourtNumber() const { return courtNumber; }
int Booking::getUserid() const { return userID; }
void Booking::setUserid(int& userid) {
	userID = userid;
}


void Booking::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << userID << "," << day << "," << time << "," << courtNumber << "\n";
        file.close();
    }
    else {
        cout << "Error: Unable to open file for saving booking.\n";
    }
}


vector<Booking> Booking::loadFromFile(const string& filename) {
    vector<Booking> bookings;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, day, time;
        int courtNum;

        getline(ss, idStr, ',');
        getline(ss, day, ',');
        getline(ss, time, ',');
        ss >> courtNum;

        int userID = stoi(idStr);
        bookings.emplace_back(day, time, courtNum, userID);
    }

    return bookings;
}

void Booking::removeFromFile(const string& filename, const string& day, const string& time, int courtNum, int userID ) {
    vector<Booking> bookings = Booking::loadFromFile(filename);
    ofstream outFile(filename);  // Truncates the file

    for (const auto& booking : bookings) {
        if (
            !(booking.getDay() == day &&
                booking.getTime() == time &&
                booking.getCourtNumber() == courtNum &&
                (userID == -1 || booking.getUserid() == userID))  // -1 = any user
            ) {
            outFile << booking.getUserid() << "," << booking.getDay() << "," << booking.getTime() << "," << booking.getCourtNumber() << "\n";
        }
    }

    outFile.close();
}

