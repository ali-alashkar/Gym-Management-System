#include "Receptionist.h"
#include <iostream>
#include <sstream>
#include<ctime>
#include<string>

using namespace std;

Receptionist::Receptionist(int id, const string& name, const string& password)
    : Staff(id, name, password) {
}
tm Receptionist::getCurrentUTCDate() {
    time_t now = time(0);
    tm utcTime;
    gmtime_s(&utcTime, &now);
    return utcTime;
}


tm Receptionist::addMonthsToDate(tm date, int months) {
    date.tm_mon += months;


    mktime(&date);
    return date;
}

string Receptionist::formatDate(const tm& date) {
    ostringstream oss;
    oss << (date.tm_mday < 10 ? "0" : "") << date.tm_mday << "/"
        << (date.tm_mon + 1 < 10 ? "0" : "") << (date.tm_mon + 1) << "/"
        << (1900 + date.tm_year);
    return oss.str();
}

void Receptionist::display() const {
    Staff::display();
    cout << "Access: Can manage member data.\n";
}


void Receptionist::deleteMember(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp) {
    int id;
    cout << "Enter Member ID to delete: ";
    cin >> id;
    Member::deleteMember(members, id);
    s.cancel(mapp, id); //z
}

void Receptionist::modifyMember(vector<Member>& members) {
    int id;
    cout << "Enter Member ID to modify: ";
    cin >> id;
    Member::modifyMember(members, id);
}

void Receptionist::viewAllMembers(const vector<Member>& members) {
    if (members.empty()) {
        cout << "No members available.\n";
        return;
    }

    cout << "\n=== Members List ===\n";
    for (const auto& member : members) {
        member.display();
        cout << "---------------------\n";
    }
}

void Receptionist::searchMembers(const vector<Member>& members) {
    string searchTerm;
    cin.ignore();
    cout << "Enter name to search: ";
    getline(cin, searchTerm);
    Member::searchMembers(members, searchTerm);
}

//z
void Receptionist::renewMemberSubscription(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp) {
    int id, months;
    cout << "Enter Member ID: ";
    cin >> id;

    Member* m = Member::findMember(members, id);
    if (!m) {
        cout << "Member not found.\n";
        return;
    }

    cout << "Current subscription: " << m->getSubPeriod() << " months\n";
    cout << "Current expiration date: " << m->getSubscription_expiration_date() << "\n";

    cout << "Add months (1, 3, 6, or 12 recommended): ";
    cin >> months;


    if (months <= 0) {
        cout << "Error: Please enter a positive number of months.\n";
        return;
    }

    // Apply renewal
    m->renewSubscription(months);


    Member::saveToFile(members);

    cout << "Subscription updated successfully.\n";
    cout << "New expiration date: " << m->getSubscription_expiration_date() << "\n";

    s.store_to_map(*m, mapp);//z


    if (m->isVip() && m->getSubPeriod() - months < 12) {
        cout << "Member has achieved VIP status!\n";
    }
}
