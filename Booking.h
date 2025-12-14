#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
using namespace std;
class Booking {
private:
    string day;
    string time;
    int courtNumber;
    int userID;

public:
    Booking(const string& d, const string& t, int court, const int& userid);
	string getDay() const;
	string getTime() const;
	int getCourtNumber() const;
	int getUserid() const;
	void setUserid(int& userid) ;
     void saveToFile(const string& filename)const ;
	static vector<Booking> loadFromFile(const string& filename);
    static void removeFromFile(const string& filename, const string& day, const string& time, int courtNum, int userID = -1);
};

#endif
