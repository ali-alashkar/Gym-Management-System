#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Member.h"
#include "Staff.h"
#include "Manager.h"
#include "Coach.h"
#include "Booking.h"
#include "PadelSystem.h"
#include "SubscribtionManagment.h"
#include "GymClass.h"
#include <QApplication>
using namespace std;

Member* member;
QString timeBooking;
QString timeChecking;
QString timeCancelling;
QString timedeleting;
Staff* loggedInStaff;
string day_to_book;
string day_to_view;
string day_to_view_by_day;
string day_to_Check;
string day_to_Cancel;
string day_to_delete;
int staff_id ;
string staff_pass;
int member_id;
Workout w;
PadelSystem systemm(3);
GymClass *gymm;
Coach *coach2;
SubscribtionManagment s;
vector<Member> members ;
vector<Staff*> staffList ;
//list<Member*> enrolledmembers;
//queue<Member*> waitlist;
//vector<GymClass> gymClasses;
map<int, int> mapp;
map<const int, Member> memberMap;
vector<Booking> loadedBookings = Booking::loadFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    members = Member::loadFromFile();
    staffList = Staff::loadAllStaff();
 mapp = s.read_from_file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\subs.txt");
    vector<Coach*> allCoaches;
    for (Staff* s : staffList) {
        Coach* c = dynamic_cast<Coach*>(s);
        if (c != nullptr) {
            allCoaches.push_back(c);
        }
    }
    GymClass::loadAllClasses("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\gymClasses.txt", allCoaches, members);

    ui->setupUi(this);
      ui->stackedWidget->setCurrentWidget(ui->start);
    ui->staffid->setValidator(new QIntValidator(0, 9999, this));
     ui->recent->setValidator(new QIntValidator(0, 9999, this));
     ui->duration->setValidator(new QIntValidator(0, 9999, this));
    QRegularExpression rx("[A-Za-z ]+");
    ui->type->setValidator(new QRegularExpressionValidator(rx, this));
    ui->staffName->setValidator(new QRegularExpressionValidator(rx, this));
    ui->dayDate->setInputMask("00/00/0000;_");
    ui->staffid2->setValidator(new QIntValidator(0, 9999, this));
    ui->id_member_2->setValidator(new QIntValidator(0, 9999, this));
    ui->id_member->setValidator(new QIntValidator(0, 9999, this));
    ui->addMon->setValidator(new QIntValidator(1, 12, this));
    ui->staffpass2->setEchoMode(QLineEdit::Password);
    ui->StaffPass->setEchoMode(QLineEdit::Password);
    ui->staffpass->setEchoMode(QLineEdit::Password);
    ui->total_mins->setValidator(new QIntValidator(0, 999999999, this));
    ui->time_to_check->setInputMask("00:00;_");
    ui->book_class->setValidator(new QIntValidator(0, 99, this));
    ui->time_to_book->setInputMask("00:00;_");
    ui->year->setValidator(new QIntValidator(1990, 2025, this));
    ui->time_to_cancel->setInputMask("00:00;_");
    ui->mon->setValidator(new QIntValidator(1, 12, this));
    ui->mon_2->setValidator(new QIntValidator(1, 12, this));
    ui->mon_3->setValidator(new QIntValidator(1, 12, this));
    ui->mon_4->setValidator(new QIntValidator(1, 12, this));
    ui->mon_5->setValidator(new QIntValidator(1, 12, this));
    ui->time_to_check_2->setInputMask("00:00;_");
    ui->total_works->setValidator(new QIntValidator(0, 9999, this));
    ui->time_to_delete->setInputMask("00:00;_");
    ui->cancelling->setValidator(new QIntValidator(0, 9999, this));
    ui->staffId->setValidator(new QIntValidator(0, 9999, this));
    ui->dob->setInputMask("00/00/0000;_");
    ui->Day->setValidator(new QRegularExpressionValidator(rx, this));
    ui->memName->setValidator(new QRegularExpressionValidator(rx, this));
    ui->memID->setValidator(new QIntValidator(0, 9999, this));
    ui->memID_2->setValidator(new QIntValidator(0, 9999, this));
    ui->memID_3->setValidator(new QIntValidator(0, 9999, this));
    ui->newModifying->setValidator(new QRegularExpressionValidator(rx, this));
    ui->memName_3->setValidator(new QRegularExpressionValidator(rx, this));
    ui->ClassName->setValidator(new QRegularExpressionValidator(rx, this));
    ui->memID_4->setValidator(new QIntValidator(0, 9999, this));
    ui->Capacity->setValidator(new QIntValidator(1, 9999, this));
    ui->CoachChosen->setValidator(new QIntValidator(1, 10, this));
    ui->Duration->setValidator(new QIntValidator(0, 9999, this));

}

MainWindow::~MainWindow()
{
     s.write_to_file(mapp);
    Member::saveToFile(members);
    Staff::saveAllStaff(staffList);
    GymClass::saveAllClasses("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\gymClasses.txt");
    delete ui;
}

void MainWindow::on_gymbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_padelbt_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->padelsys);

}


void MainWindow::on_exit1_clicked()
{
    connect(ui->exit1, &QPushButton::clicked, this, &QWidget::close);

}


void MainWindow::on_loginmembt_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->loginmemgym);
}


void MainWindow::on_back_to_startbtn_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->start);
}


void MainWindow::on_back_to_startbtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->start);
}


void MainWindow::on_loginstaffbtn_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->loginstaffgym);
}


void MainWindow::on_loginmembt_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginmempadel);
}


void MainWindow::on_loginstaffbtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginstaffpadel);
}


void MainWindow::on_back_to_gymsys_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_back_to_gymsys_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_back_to_padelsys_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->padelsys);
}


void MainWindow::on_backtopadelsys_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->padelsys);
}


void MainWindow::on_back_to_gymsys_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_logmembtn_clicked()
{
    member_id=ui->id_member->text().toInt();
    Member*  member = Member::findMember(members,member_id);

    if (!member) {
        QMessageBox::critical(this, "Login Failed",
                              "Id not found");
        ui->id_member->clear();
        ui->id_member->setFocus();
    }
    else{
        if(s.check_expiry(mapp,member_id)==5){
            QMessageBox::information(this,"For you to know","Your subscription is about to end");
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Renew now!!!", "Would you like to renew?",
                                          QMessageBox::Yes | QMessageBox::No);
            if(reply==QMessageBox::Yes){
                Member *mem= Member::findMember(members,member_id);
                ui->current_subscription_2->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
                ui->stackedWidget->setCurrentWidget(ui->renew_subs);
            }
            else{
                 ui->stackedWidget->setCurrentWidget(ui->member_menu);
            }
        }
        else if(s.check_expiry(mapp,member_id)==6){
            QMessageBox::information(this,"For you to know","Your subscription has ended");
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Renew now!!!", "Would you like to renew?",
                                          QMessageBox::Yes | QMessageBox::No);
            if(reply==QMessageBox::Yes){
                Member *mem= Member::findMember(members,member_id);
                ui->current_subscription_2->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
                ui->stackedWidget->setCurrentWidget(ui->renew_subs);
            }
            else{
                ui->stackedWidget->setCurrentWidget(ui->start);
            }
        }
        else{
             ui->stackedWidget->setCurrentWidget(ui->member_menu);
        }

        ui->id_member->clear();
        ui->id_member->setFocus();
    }
}



void MainWindow::on_view_info_btn_clicked()
{
   Member *mem= Member::findMember(members,member_id);
    ui->stackedWidget->setCurrentWidget(ui->view_info);
    ui->memberId->setText(QString::number(mem->getId()));
       ui->memberName->setText(QString::fromStdString(mem->getName()));
        ui->memberDob->setText(QString::fromStdString(mem->getDob()));
        ui->sub_per->setText(QString::number(mem->getSubPeriod()) + " months");
        ui->exp_date->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
        ui->stat->setText(QString::fromStdString(mem->isVip() ? "VIP Member" : "Regular Member"));
        ui->total_workouts_2->setText(QString::number(mem->history.totalWorkouts()));



}


void MainWindow::on_back_to_memmenue_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::on_back_to_memmenue_2_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::on_submit_2_clicked()
{

    ui->dayDate->setFocus();
    Member *mem= Member::findMember(members,member_id);
    if(!ui->dayDate->text().isEmpty()||!ui->duration->text().isEmpty()||!ui->type->text().isEmpty()){
        ui->duration->clear();
        ui->dayDate->clear();
        ui->type->clear();
        QMessageBox::warning(this,"Error","Fill all fields ,please");
        return;
    }
    else{
    w.dateOfTheDay=ui->dayDate->text().toStdString();
    w.durationInMinutes=ui->duration->text().toInt();
    w.typeOfWorkout=ui->type->text().toStdString();
    mem->history.addWorkout(w);
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
    ui->duration->clear();
    ui->dayDate->clear();
    ui->type->clear();
    }
}


void MainWindow::on_back_to_memmenue_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
    ui->viewing_recent->clear();
    ui->recent->clear();
    ui->recent->setFocus();
}


void MainWindow::on_back_to_memmenue_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
    ui->total_works->clear();
}


void MainWindow::on_submit_3_clicked()
{
    Member* mem = Member::findMember(members, member_id);
    if(ui->book_class->text().toInt()<=0 ||ui->book_class->text().isEmpty()){
        ui->book_class->clear();
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid class number to book ");
        return;
    }
   else if (ui->book_class->text().toInt() >= 1 && ui->book_class->text().toInt() <= GymClass::gymClasses.size()) {
      GymClass::gymClasses[ui->book_class->text().toInt() - 1].enrollmember(mem);
      ui->stackedWidget->setCurrentWidget(ui->member_menu);
      ui->book_class->clear();
    }

}


void MainWindow::on_back_to_memmenue_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);  
    ui->yearlymins->clear();
    ui->year->clear();
    ui->year->setFocus();
}


void MainWindow::on_back_to_memmenue_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
    ui->monthlymins->clear();
    ui->mon->clear();
    ui->mon->setFocus();

}


void MainWindow::on_back_to_memmenue_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::on_submit_6_clicked()
{
    QString inputText = ui->cancelling->text();
    bool ok;
    int index = inputText.toInt(&ok);

    if (!ok || index <= 0 || index > static_cast<int>(GymClass::gymClasses.size())) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid class number to cancel.");
        return;
    }

    Member* member = Member::findMember(members, member_id);
    if (!member) {
        QMessageBox::warning(this, "Error", "Member not found.");
        return;
    }

    member->cancelBookingByIndex(index);
    QMessageBox::information(this, "Booking Cancelled", "Your class booking has been cancelled.");
    //GymClass::saveAllClasses("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\gymclasses.txt");
    ui->cancelling->clear();
     ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::on_renew_sub_clicked()
{

    Member *mem= Member::findMember(members,member_id);
    ui->current_subscription_2->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
     ui->stackedWidget->setCurrentWidget(ui->renew_subs);
}


void MainWindow::on_add_workout_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->add_Workout);
}


void MainWindow::on_view_recent_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->view_recent_2);
}


void MainWindow::on_all_mins_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->total_Mins);
    Member *mem= Member::findMember(members,member_id);
    ui->total_mins->setText(QString::number(mem->history.getAllWorkoutMinutes()));

}


void MainWindow::on_yearly_mins_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->yearly);
}


void MainWindow::on_monthly_mins_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->monthly);
}


void MainWindow::on_total_workouts_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->totalWorkouts);
    Member *mem= Member::findMember(members,member_id);
    ui->total_works->setText(QString::number(mem->history.totalWorkouts()));
}


void MainWindow::on_submit_clicked()
{
        ui->addMon->setFocus();

        Member *mem = Member::findMember(members, member_id);

        if (!mem) {
            ui->addMon->clear();
            QMessageBox::warning(this, "Error", "Member not found.");
            return;
        }
        else {
        int monthsToAdd = ui->addMon->text().toInt();
        if (monthsToAdd==1 || monthsToAdd==3||monthsToAdd==6||monthsToAdd==12 ) {
            mem->renewSubscription(monthsToAdd);
            ui->afterrenew->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
            s.store_to_map(*mem,mapp);
        }
        else{
            ui->addMon->clear();
            QMessageBox::warning(this, "Invalid Input", "Please enter 1  ,3 , 6 or 12 months.");
            return;
        }
        }

}


void MainWindow::on_cancelBooking_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->cancel_Booking);
    Member *mem= Member::findMember(members,member_id);
     ui->viewtocancel->setText(QString::fromStdString(mem->CancelBookingTest()));
}


void MainWindow::on_bookClass_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->booking);
     Member *mem= Member::findMember(members,member_id);
    ui->viewandbookclasses->setText(QString::fromStdString(mem->showAvailableClasses(mem)));
}


void MainWindow::on_back_to_check_clicked()
{

    timeChecking = ui->time_to_check->text();
    QRegularExpression timeRegex("^([1]?[5-9]|2[0-3]):00$");
    if (!timeRegex.match(timeChecking).hasMatch()) {
        QMessageBox::warning(this, "Error", "Time must be between 15:00 and 23:00, format HH:00.");
        return;
    }


    if (ui->monday->isChecked()) day_to_Check = "Monday";
    else if (ui->tuesday->isChecked())  day_to_Check = "Tuesday";
    else if (ui->wednesday->isChecked()) day_to_Check = "Wednesday";
    else if (ui->thursday->isChecked()) day_to_Check = "Thursday";
    else if (ui->friday->isChecked()) day_to_Check = "Friday";
    else if (ui->saturday->isChecked()) day_to_Check = "Saturday";
    else if (ui->sunday->isChecked()) day_to_Check = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->view_availability);
    view_availability(day_to_Check,timeChecking);
    ui->time_to_check->clear();
    ui->time_to_check->setFocus();
    ui->monday->setAutoExclusive(false);
    ui->tuesday->setAutoExclusive(false);
    ui->wednesday->setAutoExclusive(false);
    ui->thursday->setAutoExclusive(false);
    ui->friday->setAutoExclusive(false);
    ui->saturday->setAutoExclusive(false);
    ui->sunday->setAutoExclusive(false);
    ui->monday->setChecked(false);
    ui->tuesday->setChecked(false);
    ui->wednesday->setChecked(false);
    ui->thursday->setChecked(false);
    ui->friday->setChecked(false);
    ui->saturday->setChecked(false);
    ui->sunday->setChecked(false);
    ui->monday->setAutoExclusive(true);
    ui->tuesday->setAutoExclusive(true);
    ui->wednesday->setAutoExclusive(true);
    ui->thursday->setAutoExclusive(true);
    ui->friday->setAutoExclusive(true);
    ui->saturday->setAutoExclusive(true);
    ui->sunday->setAutoExclusive(true);
}


void MainWindow::on_checkAvailability_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->choosetocheck);
}


void MainWindow::on_back_to_padelsys_2_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->padelsys);
}


void MainWindow::on_back_to_membermenu_padel_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
}


void MainWindow::on_back_to_member_menu_padel_clicked()
{
   //vector<Member> members = Member::loadFromFile();
    vector<Booking> loadedBookings2 = Booking::loadFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    Member* currentMember = Member::findMember(members, member_id);
    bool isVip = currentMember ? currentMember->isVip() : false;
    int courtNum = -1;
    if (ui->court1->isChecked()) courtNum = 1;
    else if (ui->court2->isChecked()) courtNum = 2;
    else if (ui->court3->isChecked()) courtNum = 3;
    else {
        QMessageBox::warning(this, "Error", "Please select a court.");
        return;
    }
    for (const Booking& b : loadedBookings2) {
        if (b.getUserid() == member_id && b.getDay() == day_to_book && b.getTime() == timeBooking.toStdString() && b.getCourtNumber() == courtNum) {

            QMessageBox::warning(this, "Error", "You have already booked this court at this time.");
            ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
            ui->court1->setAutoExclusive(false);
            ui->court2->setAutoExclusive(false);
            ui->court3->setAutoExclusive(false);
            ui->court1->setChecked(false);
            ui->court2->setChecked(false);
            ui->court3->setChecked(false);
            ui->court1->setAutoExclusive(true);
            ui->court2->setAutoExclusive(true);
            ui->court3->setAutoExclusive(true);
            return;



        }
        else if(b.getDay() == day_to_book && b.getTime() == timeBooking.toStdString() && b.getCourtNumber() == courtNum){

            int hour = timeBooking.mid(0, 2).toInt();
            QString nextTime;
            bool found = false;

            for (int h = hour + 1; h <= 23; ++h) {
                nextTime = QString("%1:00").arg(h, 2, 10, QChar('0'));
                if (systemm.courts[courtNum - 1].isAvailable(day_to_book, nextTime.toStdString())) {
                    found = true;
                    QString msg = QString("Court %1 is already booked at %2 on %3.\n"
                                          "Next available time: %4.\n\n"
                                          "Do you want to be added to the waitlist for %2?\n"
                                          "or do you want to book at %4?")

                                      .arg(courtNum)
                                      .arg(timeBooking)
                                      .arg(QString::fromStdString(day_to_book))
                                      .arg(nextTime);
                    QMessageBox msgBox(this);
                    msgBox.setWindowTitle("Court Unavailable");
                    msgBox.setText(msg);
                    msgBox.setIcon(QMessageBox::Question);
                    QPushButton *waitlistButton = msgBox.addButton("Stay on the Waitlist", QMessageBox::YesRole);
                    QPushButton *bookLaterButton = msgBox.addButton("Book this new slot", QMessageBox::NoRole);
                    msgBox.addButton("Cancel", QMessageBox::RejectRole);


                    msgBox.setDefaultButton(bookLaterButton);

                    msgBox.exec();

                    if (msgBox.clickedButton() == waitlistButton) {
                        QString filename = isVip ? "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt" : "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt";
                        if (systemm.isInWaitlist(member_id, day_to_book, timeBooking.toStdString(), courtNum, isVip)) {
                            QMessageBox::information(this, "Info", "You are already on the waitlist for this slot.");
                            ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);

                        } else {
                            QFile file(filename);
                            if (file.open(QIODevice::Append | QIODevice::Text)) {
                                QTextStream out(&file);
                                out << member_id << "," << QString::fromStdString(day_to_book) << "," << timeBooking << "," << courtNum << "\n";
                                file.close();
                                QMessageBox::information(this, "Success", "Added to waitlist.");
                                ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
                            }
                        }
                    } else if (msgBox.clickedButton() == bookLaterButton) {
                        Booking booking(day_to_book, nextTime.toStdString(), courtNum, member_id);
                        if (systemm.courts[courtNum - 1].addBooking(booking)) {
                            booking.saveToFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
                            QMessageBox::information(this, "Success", "Booking successful at " + nextTime);
                        } else {
                            QMessageBox::warning(this, "Error", "Failed to book at suggested time.");
                        }
                        ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);


                    }
                    else{
                        ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
                    }

                    ui->court1->setAutoExclusive(false);
                    ui->court2->setAutoExclusive(false);
                    ui->court3->setAutoExclusive(false);
                    ui->court1->setChecked(false);
                    ui->court2->setChecked(false);
                    ui->court3->setChecked(false);
                    ui->court1->setAutoExclusive(true);
                    ui->court2->setAutoExclusive(true);
                    ui->court3->setAutoExclusive(true);

                    return;
                }
            }
            if (!found) {
                QString msg2 = QString("Court %1 is already booked at %2 on %3.\n"
                                      "Do you want to be added to the waitlist for %2?\n"
                                       "Or Check the Next day available slots.\n"
                                      )

                                  .arg(courtNum)
                                  .arg(timeBooking)
                                   .arg(QString::fromStdString(day_to_book));

                QMessageBox msgBox(this);
                msgBox.setWindowTitle("Court Unavailable");
                msgBox.setText(msg2);
                msgBox.setIcon(QMessageBox::Question);


                QPushButton *waitlistButton = msgBox.addButton("Stay on the Waitlist", QMessageBox::YesRole);
                msgBox.addButton("Check next day", QMessageBox::RejectRole);

                msgBox.exec();

                if (msgBox.clickedButton() == waitlistButton) {
                    QString filename = isVip ? "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt" : "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt";
                    if (systemm.isInWaitlist(member_id, day_to_book, timeBooking.toStdString(), courtNum, isVip)) {
                        QMessageBox::information(this, "Info", "You are already on the waitlist for this slot.");
                        ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);

                    } else {
                        QFile file(filename);
                        if (file.open(QIODevice::Append | QIODevice::Text)) {
                            QTextStream out(&file);
                            out << member_id << "," << QString::fromStdString(day_to_book) << "," << timeBooking << "," << courtNum << "\n";
                            file.close();
                            QMessageBox::information(this, "Success", "Added to waitlist.");
                            ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
                        }
                    }
                }
                else{
                    ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
                }

                ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
            }
            ui->court1->setAutoExclusive(false);
            ui->court2->setAutoExclusive(false);
            ui->court3->setAutoExclusive(false);
            ui->court1->setChecked(false);
            ui->court2->setChecked(false);
            ui->court3->setChecked(false);
            ui->court1->setAutoExclusive(true);
            ui->court2->setAutoExclusive(true);
            ui->court3->setAutoExclusive(true);
            return;




        }
    }

    if (systemm.courts[courtNum - 1].isAvailable(day_to_book, timeBooking.toStdString())) {
        Booking booking(day_to_book, timeBooking.toStdString(), courtNum, member_id);
        if (systemm.courts[courtNum - 1].addBooking(booking)) {
            booking.saveToFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
            QMessageBox::information(this, "Success", "Booking successful!");
        }
    }
    else {
        QMessageBox::warning(this, "Unavailable", "Court is already booked at that time.");


    }
    ui->court1->setAutoExclusive(false);
    ui->court2->setAutoExclusive(false);
    ui->court3->setAutoExclusive(false);
    ui->court1->setChecked(false);
    ui->court2->setChecked(false);
    ui->court3->setChecked(false);
    ui->court1->setAutoExclusive(true);
    ui->court2->setAutoExclusive(true);
    ui->court3->setAutoExclusive(true);
    ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);

}


void MainWindow::on_back_to_bookingCourt_clicked()
{


     timeBooking = ui->time_to_book->text();
    QRegularExpression timeRegex("^([1]?[5-9]|2[0-3]):00$");
    if (!timeRegex.match(timeBooking).hasMatch()) {
        QMessageBox::warning(this, "Error", "Time must be between 15:00 and 23:00, format HH:00.");
        return;
    }


    if (ui->monday_2->isChecked()) day_to_book = "Monday";
    else if (ui->tuesday_2->isChecked()) day_to_book = "Tuesday";
    else if (ui->wednesday_2->isChecked()) day_to_book = "Wednesday";
    else if (ui->thursday_2->isChecked()) day_to_book = "Thursday";
    else if (ui->friday_2->isChecked()) day_to_book = "Friday";
    else if (ui->saturday_2->isChecked()) day_to_book = "Saturday";
    else if (ui->sunday_2->isChecked()) day_to_book = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->choosecourttobook);
    ui->time_to_book->clear();
    ui->time_to_book->setFocus();
    ui->monday_2->setAutoExclusive(false);
    ui->tuesday_2->setAutoExclusive(false);
    ui->wednesday_2->setAutoExclusive(false);
    ui->thursday_2->setAutoExclusive(false);
    ui->friday_2->setAutoExclusive(false);
    ui->saturday_2->setAutoExclusive(false);
    ui->sunday_2->setAutoExclusive(false);
    ui->monday_2->setChecked(false);
    ui->tuesday_2->setChecked(false);
    ui->wednesday_2->setChecked(false);
    ui->thursday_2->setChecked(false);
    ui->friday_2->setChecked(false);
    ui->saturday_2->setChecked(false);
    ui->sunday_2->setChecked(false);
    ui->monday_2->setAutoExclusive(true);
    ui->tuesday_2->setAutoExclusive(true);
    ui->wednesday_2->setAutoExclusive(true);
    ui->thursday_2->setAutoExclusive(true);
    ui->friday_2->setAutoExclusive(true);
    ui->saturday_2->setAutoExclusive(true);
    ui->sunday_2->setAutoExclusive(true);
}

void MainWindow::on_bookCourt_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->bookCourt_2);
}


void MainWindow::on_back_to_membermenu_padel_2_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
}


void MainWindow::on_viewmybookings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mybookings);
    viewMyBookings(member_id);
}


void MainWindow::on_cancelbooking_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->cancel);
}


void MainWindow::on_back_to_member_menu_padel_2_clicked()
{
    int courtNum = -1;
    if (ui->court1_2->isChecked()) courtNum = 1;
    else if (ui->court2_2->isChecked()) courtNum = 2;
    else if (ui->court3_2->isChecked()) courtNum = 3;
    else {
        QMessageBox::warning(this, "Error", "Please select a court.");
        return;
    }
  vector<Booking> bookings = Booking::loadFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    bool found = false;

    for (const Booking& b : bookings) {
        if (b.getUserid() == member_id && b.getDay() == day_to_Cancel &&
            b.getTime() == timeCancelling.toStdString() && b.getCourtNumber() == courtNum) {

            // Booking match found
            Booking::removeFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt", day_to_Cancel, timeCancelling.toStdString(), courtNum, member_id);
            systemm.courts[courtNum - 1].removeBooking(day_to_Cancel, timeCancelling.toStdString());

            QMessageBox::information(this, "Deleted", "Your booking was successfully deleted.");
            found = true;
            // Try assigning someone from the waitlist to this freed slot
            if (!systemm.assignFromWaitlist(day_to_Cancel, timeCancelling.toStdString(), courtNum)) {
                cout << "No one in waitlists to assign for this slot.\n";
            }
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Not Found", "No matching booking found for this time, court, and day.");
    }
    ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
    ui->court1_2->setAutoExclusive(false);
    ui->court2_2->setAutoExclusive(false);
    ui->court3_2->setAutoExclusive(false);
    ui->court1_2->setChecked(false);
    ui->court2_2->setChecked(false);
    ui->court3_2->setChecked(false);
    ui->court1_2->setAutoExclusive(true);
    ui->court2_2->setAutoExclusive(true);
    ui->court3_2->setAutoExclusive(true);


}


void MainWindow::on_back_to_cancelCourt_clicked()
{

    timeCancelling = ui->time_to_cancel->text();
    QRegularExpression timeRegex("^([1]?[5-9]|2[0-3]):00$");
    if (!timeRegex.match(timeCancelling).hasMatch()) {
        QMessageBox::warning(this, "Error", "Time must be between 15:00 and 23:00, format HH:00.");
        return;
    }
    if (ui->monday_3->isChecked()) day_to_Cancel = "Monday";
    else if (ui->tuesday_3->isChecked()) day_to_Cancel = "Tuesday";
    else if (ui->wednesday_3->isChecked()) day_to_Cancel = "Wednesday";
    else if (ui->thursday_3->isChecked()) day_to_Cancel = "Thursday";
    else if (ui->friday_3->isChecked()) day_to_Cancel = "Friday";
    else if (ui->saturday_3->isChecked()) day_to_Cancel = "Saturday";
    else if (ui->sunday_3->isChecked()) day_to_Cancel = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->courtCancel);
    ui->time_to_cancel->clear();
    ui->time_to_cancel->setFocus();
    ui->monday_3->setAutoExclusive(false);
    ui->tuesday_3->setAutoExclusive(false);
    ui->wednesday_3->setAutoExclusive(false);
    ui->thursday_3->setAutoExclusive(false);
    ui->friday_3->setAutoExclusive(false);
    ui->saturday_3->setAutoExclusive(false);
    ui->sunday_3->setAutoExclusive(false);
    ui->monday_3->setChecked(false);
    ui->tuesday_3->setChecked(false);
    ui->wednesday_3->setChecked(false);
    ui->thursday_3->setChecked(false);
    ui->friday_3->setChecked(false);
    ui->saturday_3->setChecked(false);
    ui->sunday_3->setChecked(false);
    ui->monday_3->setAutoExclusive(true);
    ui->tuesday_3->setAutoExclusive(true);
    ui->wednesday_3->setAutoExclusive(true);
    ui->thursday_3->setAutoExclusive(true);
    ui->friday_3->setAutoExclusive(true);
    ui->saturday_3->setAutoExclusive(true);
    ui->sunday_3->setAutoExclusive(true);

}


void MainWindow::on_logmembtn_2_clicked()
{
    member_id=ui->id_member_2->text().toInt();
    Member*  member = Member::findMember(members,member_id);

    if (!member) {
        QMessageBox::critical(this, "Login Failed",
                              "Id not found");
        ui->id_member_2->clear();
        ui->id_member_2->setFocus();
    }
    else{
     ui->stackedWidget->setCurrentWidget(ui->member_menu_padel);
         ui->id_member_2->clear();
     ui->id_member_2->setFocus();
    }
}


void MainWindow::on_viewthemostactive_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->activeCoach);
}


void MainWindow::on_back_to_gymsys_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_back_to_coachmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->coach_menu);
}


void MainWindow::on_back_to_coachmenu_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->coach_menu);
}


void MainWindow::on_viewmyclasses_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->viewmyclasses_2);
    ui->view_assigned_classes->setText(QString::fromStdString(coach2->viewMyClasses(staff_id)));
}


void MainWindow::on_viewallmembers_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->memberList);
    viewAllMemberss(members);
}


void MainWindow::on_logstaffbtn_clicked()
{
     staff_id = ui->staffid->text().toInt();
     staff_pass = ui->staffpass->text().toStdString();

    Staff* loggedIn = Staff::login(staffList, staff_id, staff_pass);

    if (loggedIn) {
        QString role = QString::fromStdString(loggedIn->getRole());

        if (role == "Coach") {
            ui->stackedWidget->setCurrentWidget(ui->coach_menu);
        }
        else if (role == "Receptionist") {
            ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
        }
        else if (role == "Manager") {
            ui->stackedWidget->setCurrentWidget(ui->managerMenu);
        }
        else {
            QMessageBox::warning(this, "Login", "Unknown staff role.");
        }

        ui->staffid->clear();
        ui->staffpass->clear();
        ui->staffid->setFocus();
    }
    else {
        QMessageBox::critical(this, "Login Failed", "Incorrect ID or password.");
        ui->staffid->clear();
        ui->staffpass->clear();
        ui->staffid->setFocus();
    }
}



void MainWindow::on_cheackavailabilityadmin_clicked()
{
        ui->stackedWidget->setCurrentWidget(ui->checkavailabilityadmin);
}


void MainWindow::on_back_to_padelsys_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->padelsys);
}


void MainWindow::on_back_to_adminmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminmenu);
}


void MainWindow::on_viewallbookings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewallBookings);
    QString output =PadelSystem::getAllBookingsText();
    ui->view_my_bookings_2->setPlainText(output);
}


void MainWindow::on_logstaffbtn_2_clicked(){
    int staff_id=ui->staffid2->text().toInt();
   string staff_pass=ui->staffpass2->text().toStdString();
      Staff::login(staffList, staff_id, staff_pass);

    if (Staff::login(staffList, staff_id, staff_pass)) {

          ui->stackedWidget->setCurrentWidget(ui->adminmenu);
        ui->staffid2->clear();
        ui->staffid2->setFocus();
        ui->staffpass2->clear();
       // ui->staffpass2->setFocus();
    }
else
{
        QMessageBox::critical(this, "Login Failed",
                              "Incorrect Id/password");
        ui->staffid2->clear();
        ui->staffid2->setFocus();
        ui->staffpass2->clear();
        //ui->staffpass2->setFocus();
}

}
void MainWindow::on_back_to_adminmenu_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminmenu);
}


void MainWindow::on_viewbookingsbyday_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->choosedaytoviewbooking);
}


void MainWindow::on_back_to_adminmenu_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminmenu);
}


void MainWindow::on_back_to_view_waitinglist_clicked()
{



    if (ui->monday_4->isChecked()) day_to_view = "Monday";
    else if (ui->tuesday_4->isChecked()) day_to_view = "Tuesday";
    else if (ui->wednesday_4->isChecked()) day_to_view = "Wednesday";
    else if (ui->thursday_4->isChecked()) day_to_view = "Thursday";
    else if (ui->friday_4->isChecked()) day_to_view = "Friday";
    else if (ui->saturday_4->isChecked()) day_to_view = "Saturday";
    else if (ui->sunday_4->isChecked()) day_to_view = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }
     ui->stackedWidget->setCurrentWidget(ui->view_waitigList);
    displayWaitlist(QString::fromStdString(day_to_view));
    ui->monday_4->setAutoExclusive(false);
    ui->tuesday_4->setAutoExclusive(false);
    ui->wednesday_4->setAutoExclusive(false);
    ui->thursday_4->setAutoExclusive(false);
    ui->friday_4->setAutoExclusive(false);
    ui->saturday_4->setAutoExclusive(false);
    ui->sunday_4->setAutoExclusive(false);
    ui->monday_4->setChecked(false);
    ui->tuesday_4->setChecked(false);
    ui->wednesday_4->setChecked(false);
    ui->thursday_4->setChecked(false);
    ui->friday_4->setChecked(false);
    ui->saturday_4->setChecked(false);
    ui->sunday_4->setChecked(false);
    ui->monday_4->setAutoExclusive(true);
    ui->tuesday_4->setAutoExclusive(true);
    ui->wednesday_4->setAutoExclusive(true);
    ui->thursday_4->setAutoExclusive(true);
    ui->friday_4->setAutoExclusive(true);
    ui->saturday_4->setAutoExclusive(true);
    ui->sunday_4->setAutoExclusive(true);


}


void MainWindow::on_viewwaitinglist_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->daytowaitinglist);
}


void MainWindow::on_deletebooking_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->deletebooking_2);
}


void MainWindow::on_back_to_adminmenu_padel_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->adminmenu);
}


void MainWindow::on_back_to_chechavailadmin_clicked()
{
    timeChecking = ui->time_to_check_2->text();
    QRegularExpression timeRegex("^([1]?[5-9]|2[0-3]):00$");
    if (!timeRegex.match(timeChecking).hasMatch()) {
        QMessageBox::warning(this, "Error", "Time must be between 15:00 and 23:00, format HH:00.");
        return;
    }


    if (ui->monday_5->isChecked()) day_to_Check = "Monday";
    else if (ui->tuesday_5->isChecked())  day_to_Check = "Tuesday";
    else if (ui->wednesday_5->isChecked()) day_to_Check = "Wednesday";
    else if (ui->thursday_5->isChecked()) day_to_Check = "Thursday";
    else if (ui->friday_5->isChecked()) day_to_Check = "Friday";
    else if (ui->saturday_5->isChecked()) day_to_Check = "Saturday";
    else if (ui->sunday_5->isChecked()) day_to_Check = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->viewAvailadmin);
    view_availability_admin(day_to_Check,timeChecking);
    ui->time_to_check_2->clear();
    ui->time_to_check_2->setFocus();
    ui->monday_5->setAutoExclusive(false);
    ui->tuesday_5->setAutoExclusive(false);
    ui->wednesday_5->setAutoExclusive(false);
    ui->thursday_5->setAutoExclusive(false);
    ui->friday_5->setAutoExclusive(false);
    ui->saturday_5->setAutoExclusive(false);
    ui->sunday_5->setAutoExclusive(false);
    ui->monday_5->setChecked(false);
    ui->tuesday_5->setChecked(false);
    ui->wednesday_5->setChecked(false);
    ui->thursday_5->setChecked(false);
    ui->friday_5->setChecked(false);
    ui->saturday_5->setChecked(false);
    ui->sunday_5->setChecked(false);
    ui->monday_5->setAutoExclusive(true);
    ui->tuesday_5->setAutoExclusive(true);
    ui->wednesday_5->setAutoExclusive(true);
    ui->thursday_5->setAutoExclusive(true);
    ui->friday_5->setAutoExclusive(true);
    ui->saturday_5->setAutoExclusive(true);
    ui->sunday_5->setAutoExclusive(true);

}



void MainWindow::on_back_to_admin_menu_padel_clicked()
{   
        int courtNum = -1;
    if (ui->court1_3->isChecked()) courtNum = 1;
    else if (ui->court2_3->isChecked()) courtNum = 2;
    else if (ui->court3_3->isChecked()) courtNum = 3;
    else {
        QMessageBox::warning(this, "Error", "Please select a court.");
        return;
    }

    bool found = false;

    for (const Booking& b : loadedBookings) {
        if (b.getDay() == day_to_delete && b.getTime() == timedeleting && b.getCourtNumber() == courtNum) {
            Booking::removeFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt", day_to_delete, timedeleting.toStdString(), courtNum, -1);
            systemm.courts[courtNum - 1].removeBooking(day_to_delete, timedeleting.toStdString());
            QMessageBox::information(this, "Deleted", "Booking was successfully deleted.");
            found = true;

            // Try assigning someone from the waitlist to this freed slot
            if (!systemm.assignFromWaitlist(day_to_delete,  timedeleting.toStdString(), courtNum)) {
                cout << "No one in waitlists to assign for this slot.\n";
            }
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Not Found", "No booking found for that court, time, and day.");
    }


    ui->stackedWidget->setCurrentWidget(ui->adminmenu);
    ui->court1_3->setAutoExclusive(false);
    ui->court2_3->setAutoExclusive(false);
    ui->court3_3->setAutoExclusive(false);
    ui->court1_3->setChecked(false);
    ui->court2_3->setChecked(false);
    ui->court3_3->setChecked(false);
    ui->court1_3->setAutoExclusive(true);
    ui->court2_3->setAutoExclusive(true);
    ui->court3_3->setAutoExclusive(true);

}


void MainWindow::on_back_to_deleteCourt_clicked()
{
         timedeleting = ui->time_to_delete->text();
     QRegularExpression timeRegex("^([1]?[5-9]|2[0-3]):00$");
     if (!timeRegex.match(timedeleting).hasMatch()) {
         QMessageBox::warning(this, "Error", "Time must be between 15:00 and 23:00, format HH:00.");
         return;
     }
     if (ui->monday_6->isChecked()) day_to_delete = "Monday";
     else if (ui->tuesday_6->isChecked()) day_to_delete = "Tuesday";
     else if (ui->wednesday_6->isChecked()) day_to_delete = "Wednesday";
     else if (ui->thursday_6->isChecked()) day_to_delete = "Thursday";
     else if (ui->friday_6->isChecked()) day_to_delete = "Friday";
     else if (ui->saturday_6->isChecked()) day_to_delete = "Saturday";
     else if (ui->sunday_6->isChecked()) day_to_delete = "Sunday";
     else {
         QMessageBox::warning(this, "Error", "Please select a day.");
         return;
     }
    ui->stackedWidget->setCurrentWidget(ui->courtDelete);
     ui->time_to_cancel->clear();
     ui->time_to_cancel->setFocus();
     ui->monday_6->setAutoExclusive(false);
     ui->tuesday_6->setAutoExclusive(false);
     ui->wednesday_6->setAutoExclusive(false);
     ui->thursday_6->setAutoExclusive(false);
     ui->friday_6->setAutoExclusive(false);
     ui->saturday_6->setAutoExclusive(false);
     ui->sunday_6->setAutoExclusive(false);
     ui->monday_6->setChecked(false);
     ui->tuesday_6->setChecked(false);
     ui->wednesday_6->setChecked(false);
     ui->thursday_6->setChecked(false);
     ui->friday_6->setChecked(false);
     ui->saturday_6->setChecked(false);
     ui->sunday_6->setChecked(false);
     ui->monday_6->setAutoExclusive(true);
     ui->tuesday_6->setAutoExclusive(true);
     ui->wednesday_6->setAutoExclusive(true);
     ui->thursday_6->setAutoExclusive(true);
     ui->friday_6->setAutoExclusive(true);
     ui->saturday_6->setAutoExclusive(true);
     ui->sunday_6->setAutoExclusive(true);
}


void MainWindow::on_back_to_coachmenue_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->coach_menu);
    ui->mon_2->clear();
    ui->activememberforthecoach->clear();
}


void MainWindow::on_back_to_gymsys_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_back_to_recepmenue_clicked()
{
    ui->mon_3->clear();
    ui->activememberforthereceptionist->clear();
    ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}


void MainWindow::on_activereceptionist_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->activereceptionist_2);
}


void MainWindow::on_back_to_recepmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}


void MainWindow::on_viewALLmembers_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->memlistrecep);
    viewAllMembersss(members);
}


void MainWindow::on_addmember_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addMember);
}


void MainWindow::on_back_to_recepmenue_2_clicked()
{
    ui->esp_date->clear();
    ui->memID->clear();
    ui->dob->clear();
    ui->memName->clear();
    ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}


void MainWindow::on_back_to_recepmenu_2_clicked()
{
    if(Member::deleteMember(members, ui->memID_2->text().toInt())){
        QMessageBox::information(this,"Congratulations","This member has been deleted successfully");
        s.cancel(mapp, ui->memID_2->text().toInt());
        ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
    }
    else{
        QMessageBox::information(this,"Error","Member not found!!");
        return;
    }
}


void MainWindow::on_deletemember_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->deleteMem);
}


void MainWindow::on_back_to_modifyMem_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->modifyId);
}


void MainWindow::on_back_to_recepmenu_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}


void MainWindow::on_back_to_modifyMem_clicked()
{
     Member *mem= Member::findMember(members,ui->memID_3->text().toInt());
    if(ui->modifyname->isChecked()&&(!ui->newModifying->text().isEmpty())){

         mem->setName(ui->newModifying->text().toStdString());
        QMessageBox::warning(this,"Congratulations","Name updated");
        ui->memID_3->clear();
        ui->newModifying->clear();
        ui->modifying->clear();
        ui->modifyname->setAutoExclusive(false);
        ui->modifydob->setAutoExclusive(false);
        ui->modifyname->setChecked(false);
        ui->modifydob->setChecked(false);
        ui->modifyname->setAutoExclusive(true);
        ui->modifydob->setAutoExclusive(true);
         ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);

    }
    else if(ui->modifydob->isChecked()&&(!ui->newModifying->text().isEmpty())){
        mem->setDob(ui->newModifying->text().toStdString());
        QMessageBox::warning(this,"Congratulations","Date of birth updated");
        ui->memID_3->clear();
        ui->newModifying->clear();
        ui->modifying->clear();
        ui->modifyname->setAutoExclusive(false);
        ui->modifydob->setAutoExclusive(false);
        ui->modifyname->setChecked(false);
        ui->modifydob->setChecked(false);
        ui->modifyname->setAutoExclusive(true);
        ui->modifydob->setAutoExclusive(true);
         ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
    }
    else{
         QMessageBox::warning(this,"Error","Fill the field,please");
        return;

    }
}


void MainWindow::on_modiftmember_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->modifyId);
}


void MainWindow::on_back_to_recepmenue_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
    ui->memName_3->clear();
     ui->membersearch->clear();
}


void MainWindow::on_back_to_recepmenue_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
    ui->memID_4->clear();
    ui->current_exsp_date->clear();
    ui->current_subscription->clear();
    ui->new_exsp_date->clear();
    ui->onemonth_2->setAutoExclusive(false);
    ui->oneyear_2->setAutoExclusive(false);
    ui->six_2->setAutoExclusive(false);
    ui->three_2->setAutoExclusive(false);
    ui->onemonth_2->setChecked(false);
    ui->oneyear_2->setChecked(false);
    ui->six_2->setChecked(false);
    ui->three_2->setChecked(false);
    ui->onemonth_2->setAutoExclusive(true);
    ui->oneyear_2->setAutoExclusive(true);
    ui->six_2->setAutoExclusive(true);
    ui->three_2->setAutoExclusive(true);

}


void MainWindow::on_searchmembers_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->searchMem);
}


void MainWindow::on_Renew_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->renewreceptionist);
}


void MainWindow::on_back_to_padelsys_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gymsys);
}


void MainWindow::on_back_to_manager_menu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_memlistmanager_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->memberlistmanager);
    viewAllMembers(members);
}


void MainWindow::on_back_to_manager_menu_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_viewstaff_clicked()
{
    Staff::viewAllStaff(staffList, ui->StaffList);
    ui->stackedWidget->setCurrentWidget(ui->staffList);
}


void MainWindow::on_activemanager_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->managerActive);
}


void MainWindow::on_back_to_manager_menu_3_clicked()
{
    ui->mon_4->clear();
    ui->activemembermanager->clear();
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_submit_12_clicked()
{
    ui->textEdit_3->clear();
    QString message = Manager::addStaff(
        staffList,
        ui->staffId->text(),
        ui->staffName->text(),
        ui->StaffPass->text(),
        ui->isCoachSelected->isChecked(),
        ui->isReceptionistSelected->isChecked()
        );

    ui->textEdit_3->setText(message);

}


void MainWindow::on_addstaff_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addnewstaff);
}


void MainWindow::on_addclasses_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addgymclasses);
}


void MainWindow::on_back_to_manager_menu_4_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_showclasses_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->showgymclasses);
     ui->GymClasses->setText(QString::fromStdString(Manager::showGymClasses(GymClass::gymClasses)));

}


void MainWindow::on_back_to_manager_menu_5_clicked()
{

    ui->monthlyrevenue_2->clear();
    ui->monthlyrevenue_3->clear();
     ui->mon_5->clear();
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_deletebooking_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->monthluRevenue);
}


void MainWindow::on_back_to_manager_menu_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
    ui->ClassName->clear();
    ui->Day->clear();
    ui->Duration->clear();
    ui->Capacity->clear();
    ui->CoachChosen->clear();
    ui->availableCoaches->clear();
    ui->availableCoaches_2->clear();
}


void MainWindow::on_back_to_viewbookingbyday_clicked()
{

    if (ui->monday_7->isChecked()) day_to_view_by_day = "Monday";
    else if (ui->tuesday_7->isChecked()) day_to_view_by_day = "Tuesday";
    else if (ui->wednesday_7->isChecked()) day_to_view_by_day = "Wednesday";
    else if (ui->thursday_7->isChecked()) day_to_view_by_day = "Thursday";
    else if (ui->friday_7->isChecked()) day_to_view_by_day = "Friday";
    else if (ui->saturday_7->isChecked()) day_to_view_by_day = "Saturday";
    else if (ui->sunday_7->isChecked()) day_to_view_by_day = "Sunday";
    else {
        QMessageBox::warning(this, "Error", "Please select a day.");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->bookingsbyDay);
    displayBookingsByDay(QString::fromStdString(day_to_view_by_day));
    ui->monday_7->setAutoExclusive(false);
    ui->tuesday_7->setAutoExclusive(false);
    ui->wednesday_7->setAutoExclusive(false);
    ui->thursday_7->setAutoExclusive(false);
    ui->friday_7->setAutoExclusive(false);
    ui->saturday_7->setAutoExclusive(false);
    ui->sunday_7->setAutoExclusive(false);
    ui->monday_7->setChecked(false);
    ui->tuesday_7->setChecked(false);
    ui->wednesday_7->setChecked(false);
    ui->thursday_7->setChecked(false);
    ui->friday_7->setChecked(false);
    ui->saturday_7->setChecked(false);
    ui->sunday_7->setChecked(false);
    ui->monday_7->setAutoExclusive(true);
    ui->tuesday_7->setAutoExclusive(true);
    ui->wednesday_7->setAutoExclusive(true);
    ui->thursday_7->setAutoExclusive(true);
    ui->friday_7->setAutoExclusive(true);
    ui->saturday_7->setAutoExclusive(true);
    ui->sunday_7->setAutoExclusive(true);


}

void MainWindow::view_availability(string day, QString time) {
    QFile file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->Check_available_member->setPlainText("No bookings available.");
        return;
    }

    QTextStream in(&file);
    QSet<int> bookedCourts;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(",");
        if (parts.size() < 4) continue;

        QString fileDay = parts[1].trimmed();
        QString fileTime = parts[2].trimmed();
        int courtNum = parts[3].toInt();

        if (fileDay == day && fileTime == time) {
            bookedCourts.insert(courtNum);
        }
    }
    file.close();

    QString result;
    bool anyAvailable = false;
    for (int i = 1; i <= 3; ++i) { // Assuming 3 courts
        if (!bookedCourts.contains(i)) {
            result += "Court " + QString::number(i) + " is available.\n";
            anyAvailable = true;
        }
    }

    if (!anyAvailable) {
        result = "No courts available at this time!";
    }

    ui->Check_available_member->setPlainText(result);
}
void MainWindow::viewMyBookings(int memberid){
    QFile file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      ui->view_my_bookings->setPlainText("No bookings available.");
        return;
    }

    QTextStream in(&file);
    QString result;
    bool anyBookings = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(",");
        if (parts.size() < 4) continue;

        QString id = parts[0].trimmed();
        QString day = parts[1].trimmed();
        QString time = parts[2].trimmed();
        QString courtNum = parts[3].trimmed();

        QString memberId = QString::number(memberid);

        if (id == memberId) {
            result += "Court " + courtNum + ", Day: " + day + ", Time: " + time + "\n";
            anyBookings = true;
        }
    }

    file.close();

    if (!anyBookings) {
        result = "No bookings found for this member.";
    }

   ui->view_my_bookings->setPlainText(result);
}



void MainWindow::displayWaitlist(const QString& day)
{
    auto showWaitlist = [&](const QString& filename, const QString& type) -> QString {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return "Could not open " + filename + " file.\n";
        }

        QTextStream in(&file);
        QString result;
        bool found = false;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            QStringList parts = line.split(",");
            if (parts.size() < 4) continue;

            QString idStr = parts[0].trimmed();
            QString d = parts[1].trimmed();
            QString time = parts[2].trimmed();
            int court = parts[3].toInt();

            if (d == day) {
                result += "Member ID: " + idStr +
                          " | Time: " + time +
                          " | Court: " + QString::number(court) +
                          " | Type: " + type + "\n";
                found = true;
            }
        }

        if (!found) {
            result += "No " + type + " waitlist on " + day + ".\n";
        }

        file.close();
        return result;
    };

    QString result;
    result += "Waitlist for " + day + ":\n\n";
    result += showWaitlist("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\vip_waitlist.txt", "VIP");
    result += "\n";
    result += showWaitlist("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\regular_waitlist.txt", "Regular");

    ui->view_waitinglist->setPlainText(result);
}

void MainWindow::displayBookingsByDay(const QString& day)
{
    vector<Booking> bookings = Booking::loadFromFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");

    if (bookings.empty()) {
        ui->view_bookings_by_day->setPlainText("No bookings found.");
        return;
    }

    vector<Booking> filtered;
    for (const Booking& b : bookings) {
        if (QString::fromStdString(b.getDay()) == day) {
            filtered.push_back(b);
        }
    }

    if (filtered.empty()) {
        ui->view_bookings_by_day->setPlainText("No bookings found for " + day + ".");
        return;
    }

    // Sort by time, then court number
    sort(filtered.begin(), filtered.end(), [](const Booking& a, const Booking& b) {
        if (a.getTime() == b.getTime())
            return a.getCourtNumber() < b.getCourtNumber();
        return a.getTime() < b.getTime();
    });

    QString result = "📅 Bookings for " + day + ":\n\n";
    for (const Booking& b : filtered) {
        result += "At " + QString::fromStdString(b.getTime()) +
                  ", Court number " + QString::number(b.getCourtNumber()) +
                  ", booked for Member ID: " + QString::number(b.getUserid()) + "\n";
    }

    ui->view_bookings_by_day->setPlainText(result);
}
void MainWindow::view_availability_admin(string day, QString time) {
    QFile file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\bookings.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->Check_available_member_2->setPlainText("No bookings available.");
        return;
    }

    QTextStream in(&file);
    QSet<int> bookedCourts;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(",");
        if (parts.size() < 4) continue;

        QString fileDay = parts[1].trimmed();
        QString fileTime = parts[2].trimmed();
        int courtNum = parts[3].toInt();

        if (fileDay == day && fileTime == time) {
            bookedCourts.insert(courtNum);
        }
    }
    file.close();

    QString result;
    bool anyAvailable = false;
    for (int i = 1; i <= 3; ++i) { // Assuming 3 courts
        if (!bookedCourts.contains(i)) {
            result += "Court " + QString::number(i) + " is available.\n";
            anyAvailable = true;
        }
    }

    if (!anyAvailable) {
        result = "No courts available at this time!";
    }

    ui->Check_available_member_2->setPlainText(result);
}
void MainWindow::on_submit_4_clicked()
{
     ui->year->setFocus();
    Member *mem= Member::findMember(members,member_id);
     if(ui->year->text().isEmpty()){
         QMessageBox::warning(this,"Error","Fill the field ,please");
         return;
     }
     else{
    ui->yearlymins->setText(QString::number(mem->history.getYearlyWorkoutMinutes((ui->year)->text().toInt())));
    ui->year->clear();
     }
}


void MainWindow::on_submit_5_clicked()
{
     ui->mon->setFocus();
    Member *mem= Member::findMember(members,member_id);
     if(ui->mon->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
         return;
     }
     else{
     ui->monthlymins->setText(QString::number(mem->history.getMonthlyWorkoutMinutes((ui->mon)->text().toInt())));
     }
}


void MainWindow::on_view_clicked()
{
     ui->recent->setFocus();
    Member *mem= Member::findMember(members,member_id);
     if(ui->recent->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
         return;
     }
    else{int m=(ui->recent)->text().toInt() ;

    ui->viewing_recent->setText((QString::fromStdString(mem->history.recentWorkouts(m))));
     }
}

void MainWindow::on_back_to_memmenue_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
    ui->addMon->clear();
     ui->afterrenew->clear();
     ui->current_subscription_2->clear();
}


void MainWindow::on_back_to_memmenue_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::viewAllMembers(vector<Member>& members) {
    QString output;

    if (members.empty()) {
        output = "No members found.\n";
    } else {
        for ( auto member : members) {
            output += member.getInfo();
            output += "---------------------------------\n";
        }
    }

    ui->MemberListManager->setPlainText(output);
}
void MainWindow::viewAllMemberss(vector<Member>& members) {
    QString output;

    if (members.empty()) {
        output = "No members found.\n";
    } else {
        for ( auto member : members) {
            output += member.getInfo();
            output += "---------------------------------\n";
        }
    }

    ui->member_list->setPlainText(output);
}
void MainWindow::viewAllMembersss(vector<Member>& members) {
    QString output;

    if (members.empty()) {
        output = "No members found.\n";
    } else {
        for ( auto member : members) {
            output += member.getInfo();
            output += "---------------------------------\n";
        }
    }

    ui->MemberListReceptionist->setPlainText(output);
}


void MainWindow::on_submit_7_clicked()
{
    if(ui->mon_2->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
        return;
    }

    else{
        for (const auto& member : members) {
        memberMap.emplace(member.getId(), member);
    }
    ui->activememberforthecoach->setText(QString::fromStdString(monthlyActivityReport(memberMap,(ui->mon_2)->text().toInt())));
    ui->mon_2->clear();
    }
}
string MainWindow::monthlyActivityReport(map<const int, Member>& members, int month) {
    int max = 0;
    Member* winner = nullptr;
    for (auto& pair : members) {
        int totalMinutes = pair.second.history.getMonthlyWorkoutMinutes(month);
        if (totalMinutes > max) {
            max = totalMinutes;
            winner = &pair.second;
        }
    }

    ostringstream result;

    if (winner) {
        result << "The most active member is: " << winner->getName()
        << " with ID #" << winner->getId()
        << ", total: " << max << " minutes this month.\n";
    } else {
        result << "There are no active members or workouts in this month.\n";
    }

    return result.str();
}


void MainWindow::on_submit_8_clicked()
{
    if(ui->mon_3->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
        return;
    }
    else{
        for (const auto& member : members) {
        memberMap.emplace(member.getId(), member);
    }
    ui->activememberforthereceptionist->setText(QString::fromStdString(monthlyActivityReport(memberMap,(ui->mon_3)->text().toInt())));
    ui->mon_3->clear();
}
}


void MainWindow::on_submit_11_clicked()
{
    if(ui->mon_4->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
        return;
    }
    else{
        for (const auto& member : members) {
        memberMap.emplace(member.getId(), member);
    }
    ui->activemembermanager->setText(QString::fromStdString(monthlyActivityReport(memberMap,(ui->mon_4)->text().toInt())));
     ui->mon_4->clear();
    }
}


void MainWindow::on_startnewmonth_clicked()
{
    GymClass::gymClasses.clear();
    ofstream file("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\gymclasses.txt", ios::trunc);
    file.close();
    QMessageBox::information(this, "Done", "Your classes have been cleared.");
}


void MainWindow::on_submit_14_clicked()
{
    if(ui->mon_5->text().isEmpty()){
        QMessageBox::warning(this,"Error","Fill the field ,please");
        return;
    }
    else{
        const string revenue="C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\revenue";
    ui->monthlyrevenue_3->setText("Total Revenue = ");
    ui->monthlyrevenue_2->setText(QString::number(Manager::getMonthlyRevenue((ui->mon_5)->text().toInt(),revenue)));
    ui->mon_5->clear();
    }
}


void MainWindow::on_back_to_manager_menu_8_clicked()
{
    ui->StaffPass->clear();
    ui->staffId->clear();
    ui->staffName->clear();
    ui->isCoachSelected->setAutoExclusive(false);
    ui->isReceptionistSelected->setAutoExclusive(false);
    ui->isCoachSelected->setChecked(false);
    ui->isReceptionistSelected->setChecked(false);
    ui->isCoachSelected->setAutoExclusive(true);
    ui->isReceptionistSelected->setAutoExclusive(true);
    ui->stackedWidget->setCurrentWidget(ui->managerMenu);
}


void MainWindow::on_back_to_manager_menu_7_clicked()
{

    QString result = Manager::addGymClass2(
        staffList,
        GymClass::gymClasses,
        ui->ClassName->text(),
        ui->Day->text(),
        ui->Duration->text(),
        ui->Capacity->text(),
        ui->CoachChosen->text()
        );

    ui->availableCoaches_2->setPlainText(result);

}


void MainWindow::on_back_to_manager_menu_9_clicked()
{
    QString result = Manager::addGymClass(
        staffList,
        GymClass::gymClasses,
        ui->ClassName->text(),
        ui->Day->text(),
        ui->Duration->text(),
        ui->Capacity->text(),
        ui->CoachChosen->text()
        );

    ui->availableCoaches->setPlainText(result);
}


void MainWindow::on_submit_10_clicked()
{
    member_id=ui->memID_4->text().toInt();
    Member *mem= Member::findMember(members,member_id);
    if(!mem){
        QMessageBox::warning(this,"Error","Id not found!");
        ui->memID_4->clear();
        return;
    }
    else{
    ui->current_subscription->setText(QString::number(mem->getSubPeriod()));
    ui->current_exsp_date->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
    }
}

void MainWindow::on_submit_9_clicked()
{
    Member *mem= Member::findMember(members,member_id);
    if(ui->six_2->isChecked()){
        mem->renewSubscription(6);
    }
    else if(ui->three_2->isChecked()){
         mem->renewSubscription(3);
    }
    else if (ui->onemonth_2->isChecked()){
         mem->renewSubscription(1);
    }
    else if(ui->oneyear_2->isChecked()){
         mem->renewSubscription(12);
    }
    else{
        QMessageBox::warning(this,"Error","Please select a subscription period");
        return;
    }
    ui->new_exsp_date->setText(QString::fromStdString(mem->getSubscription_expiration_date()));
    ui->onemonth_2->setAutoExclusive(false);
    ui->oneyear_2->setAutoExclusive(false);
    ui->six_2->setAutoExclusive(false);
    ui->three_2->setAutoExclusive(false);
    ui->onemonth_2->setChecked(false);
    ui->oneyear_2->setChecked(false);
    ui->six_2->setChecked(false);
    ui->three_2->setChecked(false);
    ui->onemonth_2->setAutoExclusive(true);
    ui->oneyear_2->setAutoExclusive(true);
    ui->six_2->setAutoExclusive(true);
    ui->three_2->setAutoExclusive(true);
}


void MainWindow::on_back_to_recepmenue_5_clicked()
{
    ui->memID_2->clear();
    ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}

void MainWindow::addMember(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp) {
    if(!ui->memID ||!ui->memName||!ui->dob ||(!ui->six->isChecked()&&!ui->three->isChecked()&&!ui->onemonth->isChecked()&&!ui->oneyear->isChecked())){
        QMessageBox::warning(this,"Error","Fill all fields, please");
        return;

    }
    else{
        if(Member::findMember(members,ui->memID->text().toInt())){
            ui->onemonth->setAutoExclusive(false);
            ui->oneyear->setAutoExclusive(false);
            ui->six->setAutoExclusive(false);
            ui->three->setAutoExclusive(false);
            ui->onemonth->setChecked(false);
            ui->oneyear->setChecked(false);
            ui->six->setChecked(false);
            ui->three->setChecked(false);
            ui->onemonth->setAutoExclusive(true);
            ui->oneyear->setAutoExclusive(true);
            ui->six->setAutoExclusive(true);
            ui->three->setAutoExclusive(true);
            ui->memID->clear();
            ui->memName->clear();
            ui->dob->clear();
            QMessageBox::warning(this,"Error","this id already exists");
            return;
        }

        else{
            tm today = getCurrentUTCDate();
            string SD = formatDate(today);
            int day, m, year;
            sscanf_s(SD.c_str(), "%d/%d/%d", &day, &m, &year);
            int subPeriod;
            if(ui->six->isChecked()){
                subPeriod=6;
            }
            else if(ui->three->isChecked()){
                subPeriod=3;
            }
            else if (ui->onemonth->isChecked()){
               subPeriod=1;
            }
            else if(ui->oneyear->isChecked()){
               subPeriod=12;
            }
            tm expiration = addMonthsToDate(today, subPeriod);

            string subscriptionExpirationDate = formatDate(expiration);

            members.push_back(Member(ui->memID->text().toInt(), ui->memName->text().toStdString(), ui->dob->text().toStdString(), subPeriod, subscriptionExpirationDate,0));

            Member m1 = members.back();

            s.store_to_map(m1, mapp);
            m1.savePayment(m, m1.getSubscriptionRevenue(subPeriod), "C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\revenue");
            ui->esp_date->setText(QString::fromStdString(subscriptionExpirationDate)) ;
            ui->onemonth->setAutoExclusive(false);
            ui->oneyear->setAutoExclusive(false);
            ui->six->setAutoExclusive(false);
            ui->three->setAutoExclusive(false);
            ui->onemonth->setChecked(false);
            ui->oneyear->setChecked(false);
            ui->six->setChecked(false);
            ui->three->setChecked(false);
            ui->onemonth->setAutoExclusive(true);
            ui->oneyear->setAutoExclusive(true);
            ui->six->setAutoExclusive(true);
            ui->three->setAutoExclusive(true);
            ui->memID->clear();
            ui->memName->clear();
            ui->dob->clear();
            QMessageBox::warning(this,"Congratulations","Member added successfully");
            return;
        }
    }
    Member::saveToFile(members);
}


void MainWindow::on_submit_13_clicked()
{
    addMember(members,s,mapp);
}


void MainWindow::on_search_clicked()
{
    string name=ui->memName_3->text().toStdString();
    searchAndDisplayMemberByName(members, name, ui->membersearch);
}

void MainWindow::searchAndDisplayMemberByName(const std::vector<Member>& members, const std::string& EnteredName, QTextEdit* textEdit) {
    QString result;
    bool found = false;

    for (const auto& member : members) {
        if (member.getName() == EnteredName) {
            result += member.getDisplayText();
            result += "------------------------\n";
            found = true;
        }
    }

    if (!found) {
        result = "No member found with that name.";
    }

    textEdit->setPlainText(result);
}
void MainWindow::modifyMember(vector<Member>& members, int memberId) {
     Member *mem= Member::findMember(members,ui->memID_3->text().toInt());
    if(!ui->memID_3 ||(!ui->modifyname->isChecked()&&!ui->modifydob->isChecked())){
         QMessageBox::warning(this,"Error","Fill all fields, please");
         return;
    }
    else{
    if (!mem) {
        ui->memID_3->clear();
        ui->modifyname->setAutoExclusive(false);
        ui->modifydob->setAutoExclusive(false);
        ui->modifyname->setChecked(false);
        ui->modifydob->setChecked(false);
        ui->modifyname->setAutoExclusive(true);
        ui->modifydob->setAutoExclusive(true);
         QMessageBox::warning(this,"Error","Member not found");
         return;
    }
    else{
        if(ui->modifyname->isChecked()){
            ui->modifying->setText("Enter new name : ");
        }
        else if(ui->modifydob->isChecked()){

            ui->modifying->setText("Enter new DOB(00/00/0000): ");
        }

    }
    }
}

void MainWindow::on_submit_15_clicked()
{
    modifyMember(members,ui->memID_3->text().toInt());
}


void MainWindow::on_back_to_memmenue_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
}




void MainWindow::on_back_to_memmenue_11_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->member_menu);
}


void MainWindow::on_back_to_recepmenue_6_clicked()
{
    ui->memID_3->clear();
     ui->stackedWidget->setCurrentWidget(ui->receptionistMenu);
}

