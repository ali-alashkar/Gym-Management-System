#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include <vector>
#include <string>
#include "Member.h"
#include "Booking.h"
#include "Staff.h"
#include "SubscribtionManagment.h"
#include "GymClass.h"
using namespace std;
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    vector<Member> members;
    vector<Staff*> staffList;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gymbtn_clicked();

    void on_padelbt_clicked();

    void on_exit1_clicked();

    void on_loginmembt_clicked();

    void on_back_to_startbtn_clicked();

    void on_back_to_startbtn_2_clicked();

    void on_loginstaffbtn_clicked();

    void on_loginmembt_2_clicked();

    void on_loginstaffbtn_2_clicked();

    void on_back_to_gymsys_clicked();

    void on_back_to_gymsys_2_clicked();

    void on_back_to_padelsys_clicked();

    void on_backtopadelsys_clicked();

    void on_back_to_gymsys_3_clicked();

    void on_logmembtn_clicked();

    void on_view_info_btn_clicked();


    void on_back_to_memmenue_clicked();

    void on_back_to_memmenue_2_clicked();

    void on_submit_2_clicked();

    void on_back_to_memmenue_3_clicked();

    void on_back_to_memmenue_4_clicked();

    void on_submit_3_clicked();

    void on_back_to_memmenue_5_clicked();

    void on_back_to_memmenue_6_clicked();

    void on_back_to_memmenue_7_clicked();

    void on_submit_6_clicked();

    void on_renew_sub_clicked();

    void on_add_workout_clicked();

    void on_view_recent_clicked();

    void on_all_mins_clicked();

    void on_yearly_mins_clicked();

    void on_monthly_mins_clicked();

    void on_total_workouts_clicked();

    void on_cancelBooking_clicked();

    void on_bookClass_clicked();

    void on_submit_clicked();

    void on_back_to_check_clicked();

    void on_checkAvailability_clicked();

    void on_back_to_padelsys_2_clicked();

    void on_back_to_membermenu_padel_clicked();

    void on_back_to_member_menu_padel_clicked();

    void on_back_to_bookingCourt_clicked();

    void on_bookCourt_clicked();

    void on_back_to_membermenu_padel_2_clicked();

    void on_viewmybookings_clicked();

    void on_cancelbooking_clicked();

    void on_back_to_member_menu_padel_2_clicked();

    void on_back_to_cancelCourt_clicked();

    void on_logmembtn_2_clicked();

    void on_viewthemostactive_clicked();

    void on_back_to_gymsys_4_clicked();

    void on_back_to_coachmenu_clicked();

    void on_back_to_coachmenu_2_clicked();

    void on_viewmyclasses_clicked();

    void on_viewallmembers_clicked();

    void on_logstaffbtn_clicked();

    void on_cheackavailabilityadmin_clicked();

    void on_back_to_padelsys_3_clicked();

    void on_back_to_adminmenu_clicked();

    void on_viewallbookings_clicked();

    void on_logstaffbtn_2_clicked();

    void on_back_to_adminmenu_2_clicked();

    void on_viewbookingsbyday_clicked();

    void on_back_to_adminmenu_3_clicked();

    void on_back_to_view_waitinglist_clicked();

    void on_viewwaitinglist_clicked();

    void on_deletebooking_clicked();

    void on_back_to_adminmenu_padel_clicked();

    void on_back_to_chechavailadmin_clicked();

    void on_back_to_admin_menu_padel_clicked();

    void on_back_to_deleteCourt_clicked();

    void on_back_to_coachmenue_8_clicked();

    void on_back_to_gymsys_5_clicked();

    void on_back_to_recepmenue_clicked();

    void on_activereceptionist_clicked();

    void on_back_to_recepmenu_clicked();

    void on_viewALLmembers_clicked();

    void on_addmember_clicked();

    void on_back_to_recepmenue_2_clicked();

    void on_back_to_recepmenu_2_clicked();

    void on_deletemember_clicked();

    void on_back_to_modifyMem_3_clicked();

    void on_back_to_recepmenu_3_clicked();

    void on_back_to_modifyMem_clicked();

    void on_modiftmember_clicked();

    void on_back_to_recepmenue_3_clicked();

    void on_back_to_recepmenue_4_clicked();

    void on_searchmembers_clicked();

    void on_Renew_clicked();

    void on_back_to_padelsys_4_clicked();

    void on_back_to_manager_menu_clicked();

    void on_memlistmanager_clicked();

    void on_back_to_manager_menu_2_clicked();

    void on_viewstaff_clicked();

    void on_activemanager_clicked();
    void on_back_to_manager_menu_3_clicked();
    void on_submit_12_clicked();

    void on_addstaff_clicked();

    void on_addclasses_clicked();

    void on_back_to_manager_menu_4_clicked();

    void on_showclasses_clicked();


    void on_back_to_manager_menu_5_clicked();

    void on_deletebooking_6_clicked();

    void on_back_to_manager_menu_6_clicked();

    void on_back_to_viewbookingbyday_clicked();

    void viewMyBookings(int memberid) ;
    void view_availability(string day, QString time);
    void view_availability_admin(string day, QString time);
    void displayWaitlist(const QString& day);
    void displayBookingsByDay(const QString& day);

    void on_submit_4_clicked();

    void on_submit_5_clicked();

    void on_view_clicked();

    void on_back_to_memmenue_8_clicked();

    void on_back_to_memmenue_9_clicked();
    void viewAllMembers( vector<Member>& members);
    void viewAllMemberss( vector<Member>& members);
    void viewAllMembersss(vector<Member>& members);
    string monthlyActivityReport(map<const int, Member>& members, int month);


    void on_submit_7_clicked();

    void on_submit_8_clicked();

    void on_submit_11_clicked();

    void on_startnewmonth_clicked();

    void on_submit_14_clicked();

    void on_back_to_manager_menu_8_clicked();

    void on_back_to_manager_menu_7_clicked();

    void on_back_to_manager_menu_9_clicked();

    void on_submit_10_clicked();

    void on_submit_9_clicked();

    void on_back_to_recepmenue_5_clicked();

    void on_label_35_linkActivated(const QString &link);
    void addMember(vector<Member>& members, SubscribtionManagment s, map<int, int>& mapp);

    void searchAndDisplayMemberByName(const vector<Member>& members, const string& EnteredName, QTextEdit* lineEdit);
    void modifyMember(vector<Member>& members, int memberId);
    void on_submit_13_clicked();

    void on_search_clicked();

    void on_submit_15_clicked();
    QString checkAvailableCourtsFromVector(const string& day, const string& time, const vector<Booking>& loadedBookings);



    void on_back_to_memmenue_10_clicked();

    void on_book_class_cursorPositionChanged(int arg1, int arg2);

    void on_back_to_memmenue_11_clicked();

    void on_back_to_recepmenue_6_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
