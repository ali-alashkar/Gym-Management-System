#pragma once
#include "Staff.h"
#include "PadelSystem.h"
#include <vector>
#include"GymClass.h"

using namespace std;

class Manager : public Staff {
public:
    Manager(int id = 0, const string& name = "", const string& password = "");


    void display() const override;
    string getRole() const override { return "Manager"; }

    static QString addStaff(vector<Staff*>& staffList, QString idStr, QString name, QString password, bool isCoachSelected, bool isReceptionistSelected);
    void showMenu(vector<Member>& members, vector<Staff*>& staffList, PadelSystem& ps);
    static int getMonthlyRevenue(int Mmonth, const string& revenue);
   static QString addGymClass(vector<Staff*>& staffList,vector<GymClass>& gymClasses,QString name,QString day,QString durationStr,QString capacityStr,QString coachIndexStr);
    static string showGymClasses(const vector<GymClass>& gymClasses);
  static QString addGymClass2(vector<Staff*>& staffList,vector<GymClass>& gymClasses,QString name,QString day,QString durationStr, QString capacityStr,QString coachIndexStr);
    void clearGymClasses() const;
    void viewAllMembers(QTextEdit* textEdit, const vector<Member*>& members);
};
