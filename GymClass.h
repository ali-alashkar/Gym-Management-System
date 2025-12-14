#pragma once
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include "Member.h"

class Coach; 
class Staff;

using namespace std;

class GymClass
{
public:
	GymClass(const string& name, Coach* coach, int cap, const string& day, int duration);
    GymClass();
	string name;
	int capacity;
	string day;
	int duration;
	Coach* assignedcoach;

	list<Member*> enrolledmembers;
	queue<Member*> waitlist;
	static vector<GymClass> gymClasses;
    bool isMemberEnrolled(Member* member);
    bool isMemberInWaitlist(Member* member);
    void enrollmember(Member* member);
    void cancelmember(Member* member);
    bool isFull();
	static void saveAllClasses(const string& filename);
	static void loadAllClasses(const string& filename, const vector<Coach*>& allCoaches, vector<Member>& allMembers);
	void showClassesForMember(Member* member);

};
