#include "Student.h"

using namespace std;

void Student::SetFirstName(string first) {
	firstName = first;
}
string Student::GetFirstName() {
	return firstName;
}
void Student::SetLastName(string last) {
	lastName = last;
}
string Student::GetLastName() {
	return lastName;
}
void Student::AddTestGrade(double grade) {
	testGrades.push_back(grade);
}
double Student::GetTestGrade(int index) {
	return testGrades.at(index);
}
void Student::SetFinalGrade(double fGrade) {
	finalGrade = fGrade;
}
double Student::GetFinalGrade() {
	return finalGrade;
}
void Student::SetAverage() {
	double sum = 0;
	for (int i = 0; i < testGrades.size(); i++) {
		sum += testGrades.at(i);
	}
	sum += finalGrade;
	average = sum / 5;
}

double Student::GetAverage() {
	return average;
}
void Student::SetLetterGrade() {
	if (average > 90) {
		letterGrade = "A";
	}
	else if (average > 80) {
		letterGrade = "B";
	}
	else if (average > 70) {
		letterGrade = "C";
	}
	else if (average > 60) {
		letterGrade = "D";
	}
	else {
		letterGrade = "F";
	}
}

string Student::GetLetterGrade() {
	return letterGrade;
}