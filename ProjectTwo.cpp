#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// structure for course
struct Course {
	string number;
	string title;
	vector<string> prereqs;
};


unordered_map<string, Course> courses;

// load file
void loadFile() {
	string fileName;
	ifstream file;
	int attempts = 0;
	bool loaded = false;

	while (attempts < 3 && !loaded) {
		cout << "Enter file name: ";
		cin >> fileName;

		file.clear();
		file.open(fileName);

		if (!file) {
			cout << "Error: Could not open file." << endl;
			attempts++;

			if (attempts < 3) {
				cout << "Try again (" << 3 - attempts << " attempts left)." << endl;
			}
		}
		else {
			loaded = true;
		}
	}

	
	if (!loaded) {
		cout << "Failed to load file after 3 attempts." << endl;
		return;
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		string temp;

		Course c;

		// course number
		getline(ss, temp, ',');
		c.number = temp;

		// title
		getline(ss, temp, ',');
		c.title = temp;

		// prerequisites
		while (getline(ss, temp, ',')) {
			if (temp != "") {
				c.prereqs.push_back(temp);
			}
		}

		courses[c.number] = c;
	}

	file.close();
	cout << "File loaded successfully." << endl;
}

// print all courses
void printAllCourses() {
	vector<string> keys;

	for (auto it = courses.begin(); it != courses.end(); ++it) {
		keys.push_back(it->first);
	}

	sort(keys.begin(), keys.end());

	for (int i = 0; i < keys.size(); i++) {
		Course c = courses[keys[i]];
		cout << c.number << ", " << c.title << endl;
	}
}

// print course
void printOneCourse(string courseNum) {
	transform(courseNum.begin(), courseNum.end(), courseNum.begin(), ::toupper);

	cout << "Looking for: " << courseNum << endl;

	if (courses.find(courseNum) == courses.end()) {
		cout << "Course not found." << endl;
		return;
	}

	Course c = courses[courseNum];

	cout << c.number << ", " << c.title << endl;

	if (c.prereqs.size() > 0) {
		cout << "Prerequisites: ";

		for (int i = 0; i < c.prereqs.size(); i++) {
			string prereq = c.prereqs[i];

			if (courses.find(prereq) != courses.end()) {
				cout << prereq << ", " << courses[prereq].title;
			}
			else {
				cout << prereq;
			}

			if (i < c.prereqs.size() - 1) {
				cout << "; ";
			}
		}
		cout << endl;
	}
	else {
		cout << "Prerequisites: None" << endl;
	}
}

int main() {
	int choice = 0;

	while (true) {
		cout << endl;
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "What would you like to do? ";

		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid input. Enter a number." << endl;
			continue;
		}

		if (choice == 1) {
			loadFile();
		}
		else if (choice == 2) {
			if (courses.empty()) {
				cout << "Load data first." << endl;
			}
			else {
				cout << "Here is a sample schedule:" << endl;
				printAllCourses();
			}
		}
		else if (choice == 3) {
			if (courses.empty()) {
				cout << "Load data first." << endl;
			}
			else {
				string courseNum;
				cout << "What course do you want to know about? ";
				cin >> courseNum;

				printOneCourse(courseNum);
			}
		}
		else if (choice == 9) {
			cout << "Thank you for using the course planner!" << endl;
			break;
		}
		else {
			cout << choice << " is not a valid option." << endl;
		}
	}
}