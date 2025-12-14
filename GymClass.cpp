#include "GymClass.h"
#include<iostream>
#include<list>
#include<queue>
#include"Member.h"
#include"Coach.h"
#include"Staff.h"
#include <fstream>
#include <sstream>

using namespace std;

class Staff;

vector<GymClass> GymClass::gymClasses;
GymClass:: GymClass(){};
GymClass::GymClass(const string& name, Coach* coach, int cap, const string& day, int duration)
    : name(name), assignedcoach(coach), capacity(cap), day(day), duration(duration) {
}

bool GymClass::isFull() {
    return enrolledmembers.size() >= capacity;
}

bool GymClass::isMemberEnrolled(Member* member) {
    auto it = find(enrolledmembers.begin(), enrolledmembers.end(), member);
    return it != enrolledmembers.end();
}
bool GymClass::isMemberInWaitlist(Member* member) {
    queue<Member*> waitlistCopy = waitlist;
    while (!waitlistCopy.empty()) {
        if (waitlistCopy.front() == member) {
            return true;
        }
        waitlistCopy.pop();
    }
    return false;
}


void GymClass::enrollmember(Member* member) {
    if (isMemberEnrolled(member)) {
        cout << "You are already enrolled in this class!" << endl;
        return;
    }

    // Check if member is already in waitlist
    if (isMemberInWaitlist(member)) {
        cout << "You are already on the waitlist for this class!" << endl;
        return;
    }

    if (!isFull()) {
        enrolledmembers.push_back(member);
        cout << member->getName() << " has been enrolled to the class successfully" << endl;
    }
    else {
        waitlist.push(member);
        cout << "Sorry, this class is full. " << member->getName() << " is now on the waitlist for this class." << endl;
    }
}

void GymClass::cancelmember(Member* member) {
    auto it = find(enrolledmembers.begin(), enrolledmembers.end(), member);
    if (it != enrolledmembers.end()) {
        enrolledmembers.erase(it);
        cout << "Your booking for this class has been cancelled." << endl;

        if (!waitlist.empty()) {
            Member* next = waitlist.front();
            waitlist.pop();
            enrolledmembers.push_back(next);
            string message = "You have been enrolled in class " + name + " from the waitlist.";
            next->addNotification(message);


        }
    }
}
void GymClass::saveAllClasses(const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error opening file for saving classes." << endl;
        return;
    }

    out << gymClasses.size() << endl;


    for (const auto& gc : gymClasses) {
        out << gc.name << ","
            << gc.assignedcoach->getName() << ","
            << gc.capacity << ","
            << gc.day << ","
            << gc.duration << endl;

        out << gc.enrolledmembers.size() << endl;
        for (const auto& member : gc.enrolledmembers) {
            out << member->getId() << endl;
        }

        out << gc.waitlist.size() << endl;
        queue<Member*> waitlistCopy = gc.waitlist;
        while (!waitlistCopy.empty()) {
            out << waitlistCopy.front()->getId() << endl;
            waitlistCopy.pop();
        }
    }

    out.close();
}
void GymClass::loadAllClasses(const string& filename, const vector<Coach*>& allCoaches, vector<Member>& allMembers) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error opening file for loading classes." << endl;
        return;
    }

    int classCount;
    in >> classCount;
    in.ignore();

    gymClasses.clear();

    for (int i = 0; i < classCount; ++i) {
        string name, coachName, day;
        int capacity, duration, enrolledCount, waitlistCount;


        getline(in, name, ',');
        getline(in, coachName, ',');
        in >> capacity;
        in.ignore();
        getline(in, day, ',');
        in >> duration;
        in.ignore();


        Coach* coach = nullptr;
        for (auto& c : allCoaches) {
            if (c->getName() == coachName) {
                coach = c;
                break;
            }
        }

        if (!coach) {
            cerr << "Coach not found: " << coachName << endl;
            continue;
        }

        GymClass gc(name, coach, capacity, day, duration);


        in >> enrolledCount;
        in.ignore();
        for (int j = 0; j < enrolledCount; ++j) {
            int memberId;
            in >> memberId;
            in.ignore();
            Member* member = nullptr;
            for (auto& m : allMembers) {
                if (m.getId() == memberId) {
                    member = &m;
                    break;
                }
            }
            if (member) {
                gc.enrolledmembers.push_back(member);
            }
        }

        in >> waitlistCount;
        in.ignore();
        for (int j = 0; j < waitlistCount; ++j) {
            int memberId;
            in >> memberId;
            in.ignore();
            Member* member = nullptr;
            for (auto& m : allMembers) {
                if (m.getId() == memberId) {
                    member = &m;
                    break;
                }
            }
            if (member) {
                gc.waitlist.push(member);
            }
        }

        gymClasses.push_back(gc);
    }

    in.close();
}
void GymClass::showClassesForMember(Member* member) {
    for (const auto& gc : gymClasses) {
        if (find(gc.enrolledmembers.begin(), gc.enrolledmembers.end(), member) != gc.enrolledmembers.end()) {
            cout << gc.name << " on " << gc.day << " with Coach " << gc.assignedcoach->getName() << endl;
        }
    }
}
