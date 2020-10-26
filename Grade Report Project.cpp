// Grade Report Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Student.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Grade Report Project.h"

using namespace std;

bool GetTextFile(vector<Student>& students, string userText) {
    Student studentObj;     //creates default student object for repeat pushing into vector later
    
    string firstName = "no first";  // the following vars are used to temporarily hold information to populate objects in the students vector
    string lastName = "no last";
    double gradeTemp = 0.0;
    double finalGrade = 0.0;

    ifstream inFS;            //create in file stream variable
    int counter = 0;

    inFS.open(userText); 
    cout << fixed << setprecision(2);

    if (!inFS.is_open()) {
        //if cannot open file return false to then close program
        return false;
    }

    while (!inFS.eof()) {
        students.push_back(studentObj); //Adds a new student object to the list for each iteration

        inFS >> firstName;
        students.at(counter).SetFirstName(firstName);   //sets first name for each student
        inFS >> lastName;
        students.at(counter).SetLastName(lastName);     //sets last name for each student
        for (int i = 0; i < 4; i++) {
            inFS >> gradeTemp;
            students.at(counter).AddTestGrade(gradeTemp);   //adds each grade to each students grade vector
        }
        inFS >> finalGrade;
        students.at(counter).SetFinalGrade(finalGrade); //sets each student's final grade

        students.at(counter).SetAverage();
        students.at(counter).SetLetterGrade();
        counter++;         //used to specify which student object is being manipulated

    }

    inFS.close();
    return true;
}

//FindHighestTestGrade finds both the highest test grade out of all tests
void FindHighestTestGrade(vector<Student>& students, double& HighestGrade) {
    double maxVal = students.at(0).GetTestGrade(0);

    for (int i = 0; i < students.size(); i++) {
        for (int j = 0; j < 4; j++) {
            if (students.at(i).GetTestGrade(j) > maxVal) {
                maxVal = students.at(i).GetTestGrade(j);
                
            }
        }
        if (students.at(i).GetFinalGrade() > maxVal) {
            maxVal = students.at(i).GetFinalGrade();
            
        }
        
    }
    HighestGrade = maxVal;
    
}
//Createreport function neatly draws all the calculated information into a newly created text and closes the file on completion
void CreateReport(vector<Student>& students, vector<double>& individualTestAverages, double finalTestAverage, double overallTestAverage, double highestGrade, string& highGradeStudent) {
   
    ofstream File;
    File.open("GradeReport.txt"); //creates new text file for the report
    File << fixed << setprecision(2); //show only 2 decimal values
    File << setw(15) << left << "Name" << setw(10) << "Test 1" << setw(10) << "Test2" << setw(10) << "Test3" << setw(10) << "Test4" << setw(15) << "Final Grade" << setw(10) << "Average" << setw(10) << "Letter Grade" << endl;
    File << setfill('*') << setw(92) << "*" << endl;
    for (int i = 0; i < students.size(); i++) {
        File << setfill(' ') << setw(15) << left << students.at(i).GetFirstName() + " " + students.at(i).GetLastName() << setw(10) << students.at(i).GetTestGrade(0) << setw(10) << students.at(i).GetTestGrade(1) << setw(10) << students.at(i).GetTestGrade(2) << setw(10) << students.at(i).GetTestGrade(3);
        File << setw(15) << students.at(i).GetFinalGrade() << setw(10) << students.at(i).GetAverage() << setw(10) << students.at(i).GetLetterGrade() << endl;
    }
    File << endl;
    
   
    File << setfill('*') << setw(92) << "*" <<  setfill(' ') << endl;
    File << setw(15) << left << "" << setw(10) << "Test 1" << setw(10) << "Test2" << setw(10) << "Test3" << setw(10) << "Test4" << setw(15) << "Final Grade" << setw(10) << "Overall" << endl;
    File << setw(15) << left << "" << setw(10) << "Average" << setw(10) << "Average" << setw(10) << "Average" << setw(10) << "Average" << setw(15) << "Average" << setw(10) << "Average" << endl;
    File << setw(15) << left << "" << setw(10) << individualTestAverages.at(0) << setw(10) << individualTestAverages.at(1) << setw(10) << individualTestAverages.at(2) << setw(10) << individualTestAverages.at(3) << setw(15) << finalTestAverage << setw(10) << overallTestAverage << endl << endl;
    File << setw(15) << left << "Highest Test Grade: " << highestGrade << endl;
    File << setw(15) << left << "Student with the highest class Grade: " << highGradeStudent;
    File.close();
}

void FindTestAverage(vector<Student>& students, vector<double>& individualTestAverages) {       //Function to find each test average and populate individualTestAverages vector
    double average = 0;
    double sum = 0;
    int numStudents = 0;
    

    for (int i = 0; i < 4; i++) {
        numStudents = 0;
        average = 0;
        sum = 0;
        for (int j = 0; j < students.size(); j++) {
            sum += students.at(j).GetTestGrade(i);
            numStudents += 1;
        }
        average = sum / numStudents;
        individualTestAverages.push_back(average);
    }
    
}
void FindFinalTestAverage(vector<Student>& students, double& finalTestAverage) {        //Function to find final test average and store in finalTestAverage
    double average = 0;
    double sum = 0;
    

    for (int i = 0; i < students.size(); i++) {
        sum += students.at(i).GetFinalGrade();
        
    }
    average = sum / students.size();
    finalTestAverage = average;
}

void FindOverallTestAverage(double& finalTestAverage, vector<double>& individualTestAverages, double& overallTestAverage) { //function that averages all collected test averages into var overallTestAverage
    double sum = 0;
    double average = 0;
    sum += finalTestAverage;
    for (int i = 0; i < individualTestAverages.size(); i++) {
        sum += individualTestAverages.at(i);
        
    }
    average = sum / 5;
    overallTestAverage = average;
}

void FindStudentWithHighestGrade(vector<Student>& students, string& highGradeStudent) {     //this function finds the student with the highest class grade/average
    highGradeStudent = students.at(0).GetFirstName();
    highGradeStudent += " ";
    highGradeStudent += students.at(0).GetLastName();
    double maxAverage = students.at(0).GetAverage();

    for (int i = 0; i < students.size(); i++) {
        if (students.at(i).GetAverage() > maxAverage) {
            maxAverage = students.at(i).GetAverage();

            highGradeStudent = students.at(i).GetFirstName();
            highGradeStudent += " ";
            highGradeStudent += students.at(i).GetLastName();
        }
    }


}
string  GetUserInput() {        //prompts user for the name of the text file to be opened
    string userText;

    cout << "Enter a file name to create a report on: example: userText.txt" << endl;
    getline(cin, userText);

    return userText;
}
int main()
{
    double highestGrade = 0;            //The following vars are used to store data relevant to the programs calculations on the data
    double overallTestAverage = 0;
    double finalTestAverage = 0;
    string highGradeStudent = "noName"; //holds students with highest class grade
    vector <double> individualTestAverages;
    vector<Student> students;       //vector of student class declaration
    string userText = "no text"; 
    cout << fixed << setprecision(2);

    userText = GetUserInput();  //prompts user for text file name to open 


    if (GetTextFile(students, userText) == false) {     //opens text file specified by the user stored in userText, then populates the students vector with information of the file
        cout << "Sorry, the specified file could not be open" << endl;
        cout << "Closing Program" << endl;
        return 1;                                      //if the function cannot properly open the file, print error message are return 1 to close program
    }
    else {
        cout << "Opening: " << userText << endl;
    }

    FindTestAverage(students, individualTestAverages);  //Function to find each test average and populate individualTestAverages vector
    FindFinalTestAverage(students, finalTestAverage);   //Function to find final test average and store in finalTestAverage
    FindOverallTestAverage(finalTestAverage, individualTestAverages, overallTestAverage);  //function that averages all collected test averages into var overallTestAverage
    FindHighestTestGrade(students, highestGrade); //FindHighestTestGrade finds both the highest test grade out of all tests, as well as, find the student who holds this highest grade
    FindStudentWithHighestGrade(students, highGradeStudent);    //this function finds the student with the highest class grade/average
    //Createreport function neatly draws all the calculated information into a newly created text and closes the file on completion
    CreateReport(students, individualTestAverages, finalTestAverage, overallTestAverage, highestGrade, highGradeStudent);

    cout << "Operations complete!" << endl;
    cout << "Text File: GradeRepoert.txt has been created" << endl;
    

    return 0;
}



