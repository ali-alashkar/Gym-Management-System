#ifndef SubscribtionManagment_h
#define SubscribtionManagment_h

#include "member.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

class SubscribtionManagment
{

private:

	vector <Member> m;

public:



	void write_to_file(map<int, int> mp);



	void store_to_map(Member m, map<int, int>& mapp);

    int check_expiry(map<int, int>& mp, int id);

	bool offer();


	map<int, int> read_from_file(const std::string& name);

    map<int, int> renew(map<int, int> mp, int id);
	void cancel(map<int, int>& mapp, int id);


	void days_left_test(Member& m);
	void paymentt(int p);
};




#endif
