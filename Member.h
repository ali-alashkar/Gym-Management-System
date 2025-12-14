#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "WorkoutHistory.h"
#include<list>
#include"GymClass.h"
#include<QMessageBox>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include<QApplication>

using namespace std;

class Member {
private:
    int id;
    string name;
    string dob;
    int subPeriod;
    string Subscription_expiration_date;
    string start_date; 
    int days; //z
    list<string> notifications;

public:
    WorkoutHistory history;
    Member(int id = 0, const string& name = "", const string& dob = "", int subPeriod = 0, const string& Subscription_expiration_date = "", int days = 0); 

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getDob() const { return dob; }
    int getSubPeriod()  { return subPeriod; }
    bool isVip() const {
        return subPeriod >= 12; 
    }
    string getSubscription_expiration_date() {
        return Subscription_expiration_date;
    }
    string getStart_date() {
        return start_date;
    }
    int get_days() { return days; }//z

    // Setters
    void setId(int id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void setDob(const string& dob) { this->dob = dob; }
    void setSubPeriod(int subPeriod) { this->subPeriod = subPeriod; }
    void setSubscription_expiration_date(string& Subscription_expiration_date) {
        this->Subscription_expiration_date = Subscription_expiration_date;
    }
    void setStart_date(string& start_date) {
        this->start_date = start_date; 
    }
    void set_days(int days) { this->days = days; }//z


    void renewSubscription(int additionalMonths);
    void display() const;
    int getSubscriptionRevenue(int subPeriod) const;



    static void saveToFile(const vector<Member>& members);
    static vector<Member> loadFromFile();


    static bool deleteMember(vector<Member>& members, int memberId);
    static void modifyMember(vector<Member>& members, int memberId);
    static Member* findMember(vector<Member>& members, int memberId);
    static void searchMembers(const vector<Member>& members, const string& searchTerm);
    void savePayment(int month, int amount, const string& revenue); //monthly revenue
    int getSubscriptionRevenueOldMembers(int subPeriod) const;
    void addNotification(const string& message);
    void  showNotifications();
   // void showAvailableClassesAndBook(Member* member);
    string showAvailableClasses(Member* member);
    string CancelBookingTest();
    //void CancelBooking();
    void cancelBookingByIndex(int index);
    QString getInfo() const;
    QString getDisplayText() const;
};

tm getCurrentUTCDate();
tm addMonthsToDate(tm date, int subPeriod);
string formatDate(const tm& date);
