#include "Member.h"
#include"WorkoutHistory.h"
#include"Workout.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include<ctime>
#include<string>
#include"GymClass.h"
#include"Manager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

Member::Member(int id, const string& name, const string& dob, int subPeriod, const string& Subscription_expiration_date, int days)
    : id(id), name(name), dob(dob), subPeriod(subPeriod), Subscription_expiration_date(Subscription_expiration_date), days(days) {
    history.setMemberID(id);
}


int Member::getSubscriptionRevenueOldMembers(int subPeriod)const {
    if (subPeriod == 1) {
        return 1000;
    }
    if (subPeriod == 3) {
        return 1800;
    }
    if (subPeriod == 6) {
        return 3600;
    }
    if (subPeriod == 12) {
        return 6000;
    }
}

void Member::savePayment(int month, int amount, const string& revenue) {
    ofstream file(revenue, ios::app);
    if (file.is_open()) {
        file << month << "," << amount << "\n";
        file.close();
    }
}

void Member::renewSubscription(int additionalMonths) {
    if (additionalMonths <= 0) {
        cout << "Invalid renewal period." << endl;
        return;
    }

    tm baseDate = getCurrentUTCDate();
    string SD = formatDate(baseDate);
    int day, m, year;
    sscanf_s(SD.c_str(), "%d/%d/%d", &day, &m, &year);
    Member::savePayment(m, Member::getSubscriptionRevenueOldMembers(additionalMonths), "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\revenue");
    if (!Subscription_expiration_date.empty()) {
        int d, m, y;
        sscanf_s(Subscription_expiration_date.c_str(), "%d/%d/%d", &d, &m, &y);
        tm parsed{};
        parsed.tm_mday = d;
        parsed.tm_mon = m - 1;
        parsed.tm_year = y - 1900;
        mktime(&parsed);

        if (mktime(&parsed) > mktime(&baseDate)) {
            baseDate = parsed;
        }
    }

    baseDate = addMonthsToDate(baseDate, additionalMonths);
    Subscription_expiration_date = formatDate(baseDate);
    bool becameVip = !isVip() && (subPeriod + additionalMonths >= 12);
    subPeriod += additionalMonths;

    cout << "Subscription renewed." << endl;
    cout << "New subscription period: " << subPeriod << " months" << endl;

    if (becameVip)
        cout << "Congratulations! You are now a VIP member!" << endl;
}

void Member::display() const {

    cout << "Member ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Date of Birth: " << dob << endl;
    cout << "Subscription Period: " << subPeriod << " months" << endl;
    cout << "Expiration Date is: " << Subscription_expiration_date << endl;
    cout << "Status: " << (isVip() ? "VIP Member" : "Regular Member") << endl;
    cout << "Total Workouts: " << history.getWorkouts().size() << endl;
}

int Member::getSubscriptionRevenue(int subPeriod)const {
    if (subPeriod == 1) {
        return 1000;
    }
    if (subPeriod == 3) {
        return 2000;
    }
    if (subPeriod == 6) {
        return 4000;
    }
    if (subPeriod == 12) {
        return 8000; 
    }
}


void Member::saveToFile(const vector<Member>& members) {
    ofstream outFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\members.txt");
    if (!outFile) {
        throw runtime_error("Error opening members file for writing!");
    }
    for (const auto& member : members) {
        outFile << member.id << ","
            << member.name << ","
            << member.dob << ","
            << member.subPeriod << ","
            << member.Subscription_expiration_date
            << endl;
    }
    outFile.close();
    WorkoutHistory::saveAllWorkouts(members);
    cout << "Members data and workout history saved successfully!" << endl;
}


vector<Member> Member::loadFromFile() {
    vector<Member> members;
    ifstream inFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\members.txt");

    if (!inFile) {
        cout << "Members file not found. Starting with empty list." << endl;
        return members;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            int id = stoi(tokens[0]);
            string name = tokens[1];
            string dob = tokens[2];
            int subPeriod = stoi(tokens[3]);
            string Subscription_expiration_date = tokens[4];

            members.emplace_back(id, name, dob, subPeriod, Subscription_expiration_date);
            members.back().history.loadWorkoutsFromFile(id);
        }
    }

    inFile.close();

    return members;
}


bool Member::deleteMember(vector<Member>& members, int memberId) {
    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i].getId() == memberId) {
            members.erase(members.begin() + i);
            cout << "Member with ID " << memberId << " has been deleted." << endl;
            return true;
        }
    }

    cout << "Member with ID " << memberId << " not found." << endl;
    return false;
}


void Member::modifyMember(vector<Member>& members, int memberId) {
    Member* member = findMember(members, memberId);

    if (!member) {
        cout << "Member with ID " << memberId << " not found." << endl;
        return;
    }

    int choice;
    string newName, newDob;
    int newSubPeriod;

    cout << "\n===== Modify Member =====" << endl;
    cout << "1. Modify Name" << endl;
    cout << "2. Modify Date of Birth" << endl;
    cout << "3. Cancel" << endl;

    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        cout << "Enter new name: ";
        getline(cin, newName);
        member->setName(newName);
        cout << "Name updated successfully." << endl;
        break;
    case 2:
        cout << "Enter new date of birth (DD/MM/YYYY): ";
        getline(cin, newDob);
        member->setDob(newDob);
        cout << "Date of birth updated successfully." << endl;
        break;
    case 3:
        cout << "Modification canceled." << endl;
        break;
    default:
        cout << "Invalid choice." << endl;
        break;
    }
}

Member* Member::findMember(vector<Member>& members, int memberId) {
    for (auto& member : members) {
        if (member.getId() == memberId) {
            return &member;
        }
    }
    return nullptr;
}

void Member::searchMembers(const vector<Member>& members, const string& searchTerm) {
    bool found = false;
    string term = searchTerm;
    transform(term.begin(), term.end(), term.begin(), ::tolower);

    cout << "\n===== Search Results =====" << endl;

    for (const auto& member : members) {
        string name = member.getName();
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(term) != string::npos) {
            member.display();
            cout << "------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No members found matching '" << searchTerm << "'." << endl;
    }
}
tm getCurrentUTCDate() {
    time_t now = time(0);
    tm utcTime;
    gmtime_s(&utcTime, &now);
    return utcTime;
}

tm addMonthsToDate(tm date, int subPeriod) {
    date.tm_mon += subPeriod;


    mktime(&date);
    return date;
}
string formatDate(const tm& date) {
    ostringstream oss;
    oss << (date.tm_mday < 10 ? "0" : "") << date.tm_mday << "/"
        << (date.tm_mon + 1 < 10 ? "0" : "") << (date.tm_mon + 1) << "/"
        << (1900 + date.tm_year);
    return oss.str();
}
void Member::addNotification(const string& message) {
    notifications.push_back(message);
}

void  Member::showNotifications() {
    if (!notifications.empty()) {
        cout << "Notifications:\n";
        for (const string& msg : notifications) {
            cout << "- " << msg << endl;
        }
        notifications.clear();
    }
   
}


string Member:: showAvailableClasses(Member* member) {
    ostringstream result;
    result << "Available Classes:\n\n";

    int index = 1;
    for ( auto& gymClass : GymClass::gymClasses) {
        result << index << ". " << gymClass.name
               << " on " << gymClass.day
               << " (" << gymClass.enrolledmembers.size() << "/"
               << gymClass.capacity << " enrolled)";

        if (gymClass.isMemberEnrolled(member)) {
            result << " [enrolled]";
        } else if (gymClass.isMemberInWaitlist(member)) {
            result << " [On waitlist]";
        }

        result << "\n";
        index++;
    }

    return result.str();
}
string Member::CancelBookingTest() {
    ostringstream result;
    result << "Your current bookings:\n";
    bool foundBooking = false;

    for (size_t i = 0; i < GymClass::gymClasses.size(); ++i) {
        auto& gymClass = GymClass::gymClasses[i];
        for (auto& enrolledMember : gymClass.enrolledmembers) {
            if (enrolledMember == this) {
                foundBooking = true;
                result << (i + 1) << ". " << gymClass.name << "\n";
            }
        }
    }

    if (!foundBooking) {
        result << "You don't have any bookings.\n";
    }

    return result.str();
}



void Member::cancelBookingByIndex(int index) {
    if (index < 1 || index > static_cast<int>(GymClass::gymClasses.size())) return;

    GymClass& gymClass = GymClass::gymClasses[index - 1];
    gymClass.cancelmember(this);
}

QString Member::getInfo() const {
    return QString(
               "Member ID: %1\n"
               "Name: %2\n"
               "Date of Birth: %3\n"
               "Subscription Period: %4 months\n"
               "Expiration Date: %5\n"
               "Status: %6\n"
               "Total Workouts: %7\n"
               )
        .arg(QString::number(id))
        .arg(QString::fromStdString(name))
        .arg(QString::fromStdString(dob))
        .arg(QString::number(subPeriod))
        .arg(QString::fromStdString(Subscription_expiration_date))
        .arg(isVip() ? "VIP Member" : "Regular Member")
        .arg(QString::number(history.getWorkouts().size()));
}

QString Member::getDisplayText() const {
    return QString(" Member ID: %1\n Name: %2\n DOB: %3\n Period: %4 months\n Exp: %5\n Status: %6\n Workouts: %7\n")
    .arg(id)
        .arg(QString::fromStdString(name))
        .arg(QString::fromStdString(dob))
        .arg(subPeriod)
        .arg(QString::fromStdString(Subscription_expiration_date))
        .arg(isVip() ? "VIP" : "Regular")
        .arg(history.getWorkouts().size());
}
