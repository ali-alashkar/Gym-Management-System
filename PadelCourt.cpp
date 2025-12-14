#include "PadelCourt.h"
using namespace std;

PadelCourt::PadelCourt(int courtNum) : courtNumber(courtNum) {}

int PadelCourt::getCourtNumber() const { return courtNumber; }

bool PadelCourt::isAvailable(const string& day, const string& time) const {
	for (const auto& booking : bookings) {
		if (booking.getDay() == day && booking.getTime() == time) {
			return false;
		}
	}
	return true;
}

bool PadelCourt::addBooking(const Booking& booking) {
	if (isAvailable(booking.getDay(), booking.getTime())) {
		bookings.push_back(booking);
		return true;
	}
	return false;
}

void PadelCourt::removeBooking(const string& day, const string& time) {
	for (auto it = bookings.begin(); it != bookings.end(); ++it) {
		if (it->getDay() == day && it->getTime() == time) {
			bookings.erase(it);
			return;
		}
	}
}

vector<Booking> PadelCourt::getBookings() const {
	return bookings;
}