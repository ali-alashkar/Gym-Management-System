#include <iostream>
#include "Manager.h"
#include "Coach.h"
#include "Receptionist.h"
#include "PadelSystem.h"
#include "GymClass.h"
#include <vector>

using namespace std;

Manager::Manager(int id, const string& name, const string& password)
    : Staff(id, name, password) {}

void Manager::display() const {
    Staff::display();
    cout << "Access: Full system access.\n";
}

int Manager::getMonthlyRevenue(int Mmonth, const string& revenue) {
   ifstream file(revenue);
    int totalRevenue = 0;

    if (file.is_open()) {
       string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string monthStr, amountStr;
            getline(ss, monthStr, ',');
            getline(ss, amountStr);

            int month = stoi(monthStr);
            int amount = stoi(amountStr);

            if (month == Mmonth) {
                totalRevenue += amount;
            }
        }
        file.close();
    }
    cout << "Total revenue in " << Mmonth << " = ";
    return totalRevenue;
}


QString Manager::addStaff(vector<Staff*>& staffList, QString idStr, QString name, QString password, bool isCoachSelected, bool isReceptionistSelected) {

    if (idStr.trimmed().isEmpty() || name.trimmed().isEmpty() || password.trimmed().isEmpty()) {
        return "Error: All fields (ID, Name, Password) must be filled.";
    }


    bool ok;
    int id = idStr.toInt(&ok);
    if (!ok) {
        return "Error: Invalid ID format.";
    }


    for (const auto& staff : staffList) {
        if (staff->getId() == id) {
            return "Error: The entered ID already exists.";
        }
    }


    if (!isCoachSelected && !isReceptionistSelected) {
        return "Error: Please select a role (Coach or Receptionist).";
    }


    Staff* newStaff = nullptr;
    if (isCoachSelected) {
        newStaff = new Coach(id, name.toStdString(), password.toStdString());
    } else if (isReceptionistSelected) {
        newStaff = new Receptionist(id, name.toStdString(), password.toStdString());
    }


    staffList.push_back(newStaff);
    return "Staff added successfully.";
}



void Manager::clearGymClasses() const {
    GymClass::gymClasses.clear();
    ofstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\gym_classes.txt", ios::trunc);
    file.close();
    cout << "All gym classes cleared for the new month.\n";
}
void Manager::viewAllMembers(QTextEdit* textEdit, const std::vector<Member*>& members) {
    QString output;

    if (members.empty()) {
        output = "No members found.\n";
    } else {
        output = "=== Members List ===\n";
        for (const auto* member : members) {
            output += member->getInfo();
            output += "---------------------\n";
        }
    }

    textEdit->setPlainText(output);
}
string Manager::showGymClasses(const vector<GymClass>& gymClasses) {
    ostringstream result;

    if (gymClasses.empty()) {
        result << "No gym classes available.\n";
        return result.str();
    }

    result << "\n=== Gym Classes ===\n";
    int i = 1;
    for (const auto& gymClass : gymClasses) {
        result << i << ". Class Name: " << gymClass.name << "\n";

        if (gymClass.assignedcoach)
            result << "Coach: " << gymClass.assignedcoach->getName() << "\n";
        else
            result << "Coach: (Unassigned)\n";

        result << "Day: " << gymClass.day << "\n"
               << "Duration: " << gymClass.duration << " minutes\n"
               << "Capacity: " << gymClass.capacity << "\n"
               << "Enrolled Members: " << gymClass.enrolledmembers.size() << "\n"
               << "Waitlist Size: " << gymClass.waitlist.size() << "\n"
               << "---------------------------\n";
        i++;
    }

    return result.str();
}

QString Manager::addGymClass(
    vector<Staff*>& staffList,
    vector<GymClass>& gymClasses,
    QString name,
    QString day,
    QString durationStr,
    QString capacityStr,
    QString coachIndexStr
    ) {

    name = name.trimmed();
    day = day.trimmed();
    durationStr = durationStr.trimmed();
    capacityStr = capacityStr.trimmed();
    coachIndexStr = coachIndexStr.trimmed();


    if (name.isEmpty() || day.isEmpty() || durationStr.isEmpty() || capacityStr.isEmpty()) {
        return "Error: All fields must be filled.";
    }


    bool durationOk, capacityOk, coachIndexOk;
    int duration = durationStr.toInt(&durationOk);
    int capacity = capacityStr.toInt(&capacityOk);
    int coachIndex = coachIndexStr.toInt(&coachIndexOk);

    if (!durationOk || duration <= 0) {
        return "Error: Invalid duration entered.";
    }
    if (!capacityOk || capacity <= 0) {
        return "Error: Invalid capacity entered.";
    }
    vector<Coach*> availableCoaches;
    for (Staff* s : staffList) {
        if (Coach* coach = dynamic_cast<Coach*>(s)) {
            availableCoaches.push_back(coach);
        }
    }

    if (availableCoaches.empty()) {
        return "Error: No available coaches found. Cannot add class.";
    }
    else if(!availableCoaches.empty()){
        QString result;
        for (const auto& coach : availableCoaches) {
            result += "Coach ID: " + QString::number(coach->getId()) +
                      ", Name: " + QString::fromStdString(coach->getName()) + "\n";
        }
        return result;


    }
}
QString Manager::addGymClass2(  vector<Staff*>& staffList,vector<GymClass>& gymClasses,QString name,QString day,QString durationStr,QString capacityStr,QString coachIndexStr) {

    bool durationOk, capacityOk, coachIndexOk;
    int duration = durationStr.toInt(&durationOk);
    int capacity = capacityStr.toInt(&capacityOk);
    int coachIndex = coachIndexStr.toInt(&coachIndexOk);

    vector<Coach*> availableCoaches;
    for (Staff* s : staffList) {
        if (Coach* coach = dynamic_cast<Coach*>(s)) {
            availableCoaches.push_back(coach);
        }
    }
    if (!coachIndex || coachIndex <= 0) {
        return "Error: Invalid coach number.";
    }

    if (coachIndex > static_cast<int>(availableCoaches.size())) {
        return "Error: Coach number out of range.";
    }

    Coach* selectedCoach = availableCoaches[coachIndex - 1];
    GymClass newClass(name.toStdString(), selectedCoach, capacity, day.toStdString(), duration);
    GymClass::gymClasses.push_back(newClass);

    return "Class added successfully.";
}



