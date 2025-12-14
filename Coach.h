#pragma once
#include "Staff.h"
using namespace std;

class Coach : public Staff {
public:
    Coach(int id = 0, const string& name = "", const string& password = "");


    void display() const override;
    string getRole() const override { return "Coach"; }
    void viewAllMembers(QTextEdit* textEdit, const std::vector<Member*>& members);
    string viewMyClasses(int idCoach);
};
