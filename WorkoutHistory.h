#ifndef WORKOUTHISTORY_H
#define WORKOUTHISTORY_H
#include "Workout.h"
#include <string>
#include <vector>
#include <iostream>


class Member;

class WorkoutHistory
{
private:
	vector<Workout> workouts;
    int memberID = 0;

public:
	void addWorkout(Workout& w);

    string recentWorkouts(int numberOfWorkouts=5);
	int getAllWorkoutMinutes();
	int getYearlyWorkoutMinutes(int year);
    int getMonthlyWorkoutMinutes(int month) ;
	int totalWorkouts();

	const vector<Workout>& getWorkouts() const;
	void setMemberID(int id);
	int getMemberID() const;
	void saveWorkoutToFile(int memberId, const Workout& workout);
	void loadWorkoutsFromFile(int memberId);


	static void saveAllWorkouts(const vector<Member>& members);
};
#endif
