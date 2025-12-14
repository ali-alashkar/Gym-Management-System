#ifndef PADEL_SYSTEM_H
#define PADEL_SYSTEM_H

#include <vector>
#include <string>
#include<queue>
#include "PadelCourt.h"
#include <QString>
#include <QTextStream>
using namespace std;
class PadelSystem {
private:
    //vector<PadelCourt> courts;
	void displayUserMenu() const;
	void displayManagerMenu() const;
	void bookCourt(int id);

	string getDayName(int choice) const;


public:
    bool isValidTime(const string& time) const;
    vector<PadelCourt> courts;
	void checkAvailability() const;
	void viewAllBookings() const;
	void viewMyBookings(int id) const;
 static  QString getAllBookingsText();
	void deleteBooking();
    void deleteMyBooking(int id);
	 PadelSystem(int numCourts);
     PadelSystem();
	 void viewBookingsByDay();
     bool assignFromWaitlist(const std::string& day, const std::string& time, int courtNum);
	 void viewWaitlist();
     bool isInWaitlist(int id, const std::string& day, const std::string& time, int courtNum, bool isVip);
	void Menu(int id);
	void Menu2();
	
};

#endif
