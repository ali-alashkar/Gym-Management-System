#ifndef PADEL_COURT_H
#define PADEL_COURT_H

#include <string>
#include <vector>
#include "Booking.h"
using namespace std;
class PadelCourt {
private:
	int courtNumber;
	vector<Booking> bookings;

public:
	PadelCourt(int courtNum);
	int getCourtNumber() const;
	bool isAvailable(const string& day, const string& time) const;
	bool addBooking(const Booking& booking);
	void removeBooking(const string& day, const string& time);
	vector<Booking> getBookings() const;
};

#endif
