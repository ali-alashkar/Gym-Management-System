#pragma once
#include "Staff.h"
#include<ctime>
#include "SubscribtionManagment.h" //z
using namespace std;

class Receptionist : public Staff {
public:
    Receptionist(int id = 0, const string& name = "", const string& password = "");
    tm getCurrentUTCDate();
    tm addMonthsToDate(tm date, int months);
    string formatDate(const tm& date);

    void display() const override;
    string getRole() const override { return "Receptionist"; }

    void deleteMember(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp); //z
    void modifyMember(vector<Member>& members);
    void viewAllMembers(const vector<Member>& members);
    void searchMembers(const vector<Member>& members);
    void renewMemberSubscription(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp); //z
};
