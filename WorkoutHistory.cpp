#include "WorkoutHistory.h"
#include"Member.h"
#include <fstream>
#include <sstream>
void WorkoutHistory::addWorkout(Workout& w) {
	workouts.push_back(w);
	saveWorkoutToFile(memberID, w);
}
string WorkoutHistory::recentWorkouts(int numberOfWorkouts) {
    ostringstream result;

    if (workouts.empty()) {
        result << "Empty record of workouts.\n";
    } else {
        int total = workouts.size();
        int count = std::min(numberOfWorkouts, total);

        if (numberOfWorkouts >= total) {
            result << "We only have a record of " << total << " workouts.\n";
        }

        result << "Here are this member's last " << count << " workouts:\n";

        int day = 1;
        for (int i = total - 1; i >= total - count; --i) {
            result << "Date of day #" << day
                   << " : " << workouts[i].dateOfTheDay
                   << " | Type of workout: " << workouts[i].typeOfWorkout
                   << " | Duration: " << workouts[i].durationInMinutes << " minutes\n";
            day++;
        }
    }

    return result.str();
}

int WorkoutHistory::getAllWorkoutMinutes() {
	int total = 0;
	for (const auto& workout : workouts) {
		total += workout.durationInMinutes; 
	}
	return total;
}
int WorkoutHistory::getYearlyWorkoutMinutes(int year) {
	int total = 0;
	for (const auto& workout : workouts) {
		int day, month, y;
		sscanf_s(workout.dateOfTheDay.c_str(), "%d/%d/%d", &day, &month, &y);
		if (y == year) {
			total += workout.durationInMinutes;
		}
	}
	return total;
}
int WorkoutHistory::getMonthlyWorkoutMinutes(int month)  {
	int total = 0;
	for (const auto& workout : workouts) {
		int day, m, year;
		sscanf_s(workout.dateOfTheDay.c_str(), "%d/%d/%d", &day, &m, &year);
		if (m == month) {
			total += workout.durationInMinutes;
            cout<<total;
		}
	}
	return total;
}
int WorkoutHistory::totalWorkouts() {
	return workouts.size();
}

// ali
const vector<Workout>& WorkoutHistory::getWorkouts() const {
	return workouts;
}


void WorkoutHistory::setMemberID(int id) {
	memberID = id;
}

int WorkoutHistory::getMemberID() const {
	return memberID;
}


void WorkoutHistory::saveWorkoutToFile(int memberId, const Workout& workout) {
    ofstream outFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\workouts.txt", ios::app);
	if (!outFile) {
		cout << "Error opening workouts file for writing!" << endl;
		return;
	}

	outFile << memberId << ","
		<< workout.dateOfTheDay << ","
		<< workout.typeOfWorkout << ","
		<< workout.durationInMinutes << endl;

	outFile.close();
}

// Load workouts for a specific member from file
void WorkoutHistory::loadWorkoutsFromFile(int memberId) {
    ifstream inFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\workouts.txt");
	if (!inFile) {
		cout << "Workouts file not found. No workout history loaded." << endl;
		return;
	}

    workouts.clear();
	memberID = memberId;

	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string token;
		vector<string> tokens;

		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		if (tokens.size() == 4) {
			int id = stoi(tokens[0]);


			if (id == memberId) {
				string date = tokens[1];
				string type = tokens[2];
				int duration = stoi(tokens[3]);

				workouts.emplace_back(date, type, duration);
			}
		}
	}

	inFile.close();

}


void WorkoutHistory::saveAllWorkouts(const vector<Member>& members) {
    ofstream outFile("C:\\Users\\Calipso0\\Documents\\GYM test\\test4\\test4\\workouts.txt");
	if (!outFile) {
		cout << "Error opening workouts file for writing!" << endl;
		return;
	}

	for (const auto& member : members) {
		int memberId = member.getId();
		const vector<Workout>& memberWorkouts = member.history.getWorkouts();

		for (const auto& workout : memberWorkouts) {
			outFile << memberId << ","
				<< workout.dateOfTheDay << ","
				<< workout.typeOfWorkout << ","
				<< workout.durationInMinutes << endl;
		}
	}

	outFile.close();
	cout << "All workout data saved successfully!" << endl;
}
