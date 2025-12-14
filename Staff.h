#pragma once
#include <string>
#include <vector>
#include "Member.h"
#include <map>
#include "SubscribtionManagment.h"//z
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QString>
#include <QTextEdit>

using namespace std;

class Staff {
protected:
    int id;
    string name;
    string password;

public:
    Staff(int id = 0, const string& name = "", const string& password = "");
    virtual ~Staff() = default;


    int getId() const;
    string getName() const;
    string getPassword() const;
    QString getInfo() const;


    void setId(int id);
    void setName(const string& name);
    void setPassword(const string& password);


    virtual void display() const;
    virtual string getRole() const = 0;
    virtual string serialize() const;

    static void saveAllStaff(const vector<Staff*>& staffList);
    static vector<Staff*> loadAllStaff();
    static Staff* login(const vector<Staff*>& staffList, int id, const string& password);
    static void viewAllStaff(const vector<Staff*>& staffList , QTextEdit* textEdit);
};
