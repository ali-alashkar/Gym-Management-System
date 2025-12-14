#include "Coach.h"
#include <iostream>

using namespace std;

Coach::Coach(int id, const string& name, const string& password)
    : Staff(id, name, password) {
}

void Coach::display() const {
    Staff::display();
    cout << "Access: Can view member information only." << endl;
}


string Coach::viewMyClasses(int idCoach) {
    ostringstream result;
    result << "\n=== My Assigned Classes ===\n";
    bool hasClasses = false;

    for (const auto& gymClass : GymClass::gymClasses) {
        if (gymClass.assignedcoach && gymClass.assignedcoach->getId() == idCoach) {
            result << "Class Name: " << gymClass.name << "\n";
            result << "Day: " << gymClass.day << "\n";
            result << "Duration: " << gymClass.duration << " minutes\n";
            result << "Capacity: " << gymClass.capacity << "\n";
            result << "Enrolled Members: " << gymClass.enrolledmembers.size() << "/" << gymClass.capacity << "\n";
            result << "Waitlist Size: " << gymClass.waitlist.size() << "\n";
            result << "---------------------------\n";
            hasClasses = true;
        }
    }

    if (!hasClasses) {
        result << "You don't have any assigned classes at the moment.\n";
    }
    return result.str();
}
void Coach::viewAllMembers(QTextEdit* textEdit, const std::vector<Member*>& members) {
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
