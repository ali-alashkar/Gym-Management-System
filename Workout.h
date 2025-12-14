#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>
using namespace std;
class Workout
{
public:
	string dateOfTheDay;
	string typeOfWorkout;
	int durationInMinutes;
	Workout();
	Workout(string date, string type, int duration);
};
#endif
