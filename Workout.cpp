#include "Workout.h"
Workout::Workout() {}
Workout::Workout(string date, string type, int duration) {
	dateOfTheDay = date;
	typeOfWorkout = type;
	durationInMinutes = duration;
}
