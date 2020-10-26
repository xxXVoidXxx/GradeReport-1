#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Student
{
private:
	string firstName = "no first name";
	string lastName = "no last name";
	vector<double> testGrades;
	double finalGrade = 0;
	double average = 0;
	string letterGrade = "X";

public:
	
	void SetFirstName(string first);
	string GetFirstName();
	void SetLastName(string last);
	string GetLastName();
	void AddTestGrade(double grade);
	double GetTestGrade(int index);
	void SetFinalGrade(double finalGrade);
	double GetFinalGrade();
	void SetAverage();
	double GetAverage();
	void SetLetterGrade();
	string GetLetterGrade();

};

#endif