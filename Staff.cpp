#include "Staff.h"
#include "Manager.h"
#include "Coach.h"
#include "Receptionist.h"
#include "PadelSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Staff::Staff(int id, const string& name, const string& password)
    : id(id), name(name), password(password) {
}

int Staff::getId() const { return id; }
string Staff::getName() const { return name; }
string Staff::getPassword() const { return password; }

void Staff::setId(int id) { this->id = id; }
void Staff::setName(const string& name) { this->name = name; }
void Staff::setPassword(const string& password) { this->password = password; }

void Staff::display() const {
    cout << "Staff ID: " << id << "\nName: " << name << "\nRole: " << getRole() << endl;
}

string Staff::serialize() const {
    return to_string(id) + "," + name + "," + password + "," + getRole();
}

void Staff::saveAllStaff(const vector<Staff*>& staffList) {
    ofstream outFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\staff.txt");
    if (!outFile) {
        cerr << "Error: Cannot write to staff.txt" << endl;
        return;
    }

    for (const auto* staff : staffList)
        outFile << staff->serialize() << endl;

    cout << "Staff data saved." << endl;
}

Staff* Staff::login(const vector<Staff*>& staffList, int id, const string& password) {
    for (auto* staff : staffList) {
        if (staff->id == id && staff->password == password) {
            cout << "Login successful. Welcome, " << staff->name << " (" << staff->getRole() << ")" << endl;
            return staff;
        }
    }
    cout << "Login failed. Invalid ID or password." << endl;
    return nullptr;
}

void Staff::viewAllStaff(const vector<Staff*>& staffList, QTextEdit* textEdit) {
    QString output;

    if (staffList.empty()) {
        output = "No staff found.\n";
    } else {
        for (const auto* staff : staffList) {
            output += staff->getInfo();
            output += "--------------------------\n";
        }
    }

    textEdit->setPlainText(output);
}



QString Staff::getInfo() const {
    return QString("Staff ID: %1\nName: %2\nRole: %3\n")
    .arg(QString::number(id))
        .arg(QString::fromStdString(name))
        .arg(QString::fromStdString(getRole()));
}



vector<Staff*> Staff::loadAllStaff() {
    vector<Staff*> staffList;
    ifstream inFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\staff.txt");
    if (!inFile) {
        cout << "No staff file found." << endl;
        return staffList;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, password, role;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, password, ',');
        getline(ss, role, ',');

        int id = stoi(idStr);
        Staff* staff = nullptr;

        if (role == "Manager")
            staff = new Manager(id, name, password);
       else if (role == "Coach")
            staff = new Coach(id, name, password);
        else if (role == "Receptionist")
            staff = new Receptionist(id, name, password);

        if (staff)
            staffList.push_back(staff);
    }

    return staffList;
}
