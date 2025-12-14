QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Booking.cpp \
    Coach.cpp \
    GymClass.cpp \
    Manager.cpp \
    Member.cpp \
    PadelCourt.cpp \
    PadelSystem.cpp \
    Receptionist.cpp \
    Staff.cpp \
    SubscribtionManagment.cpp \
    Workout.cpp \
    WorkoutHistory.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Booking.h \
    Coach.h \
    GymClass.h \
    Manager.h \
    Member.h \
    PadelCourt.h \
    PadelSystem.h \
    Receptionist.h \
    Staff.h \
    SubscribtionManagment.h \
    Workout.h \
    WorkoutHistory.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bgi.qrc

DISTFILES += \
    bookings.txt \
    gymClasses.txt \
    gym_classes.txt \
    members.txt \
    regular_waitlist.txt \
    revenue \
    staff.txt \
    subs.txt \
    vip_waitlist.txt \
    workouts.txt
