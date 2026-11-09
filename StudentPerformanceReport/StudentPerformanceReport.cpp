
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Structure to store student information
struct Student {
    string name;
    double scores[3];
    double average;
    char grade;
};

// Function to calculate a student's average
double calculateAverage(double scores[], int size) {
    double total = 0;

    for (int i = 0; i < size; i++) {
        total += scores[i];
    }

    return total / size;
}

// Function to determine the letter grade
char calculateGrade(double average) {
    if (average >= 90)
        return 'A';
    else if (average >= 80)
        return 'B';
    else if (average >= 70)
        return 'C';
    else if (average >= 60)
        return 'D';
    else
        return 'F';
}

int main() {

    // Open the input file
    ifstream inputFile("students.txt");

    if (!inputFile) {
        cout << "Error: Could not open students.txt" << endl;
        return 1;
    }

    vector<Student> students;
    Student currentStudent;

    // Read student information from the file
    while (inputFile >> currentStudent.name
        >> currentStudent.scores[0]
        >> currentStudent.scores[1]
        >> currentStudent.scores[2]) {

        currentStudent.average =
            calculateAverage(currentStudent.scores, 3);

        currentStudent.grade =
            calculateGrade(currentStudent.average);

        students.push_back(currentStudent);
    }

    inputFile.close();

    if (students.empty()) {
        cout << "No student data found." << endl;
        return 1;
    }

    // Pointer to access student information
    Student* ptr = students.data();

    double classTotal = 0;
    int highestIndex = 0;
    int lowestIndex = 0;

    // Calculate class statistics
    for (int i = 0; i < students.size(); i++) {

        classTotal += (ptr + i)->average;

        if ((ptr + i)->average >
            (ptr + highestIndex)->average) {
            highestIndex = i;
        }

        if ((ptr + i)->average <
            (ptr + lowestIndex)->average) {
            lowestIndex = i;
        }
    }

    double classAverage = classTotal / students.size();

    // Open output file
    ofstream outputFile("performance_report.txt");

    if (!outputFile) {
        cout << "Error: Could not create output file." << endl;
        return 1;
    }

    // Functionality to display report on screen and file
    auto printReport = [&](ostream& output) {

        output << fixed << setprecision(2);

        output << "STUDENT PERFORMANCE REPORT" << endl;
        output << "==========================" << endl;

        for (int i = 0; i < students.size(); i++) {

            output << "Name: " << (ptr + i)->name << endl;

            output << "Scores: ";

            for (int j = 0; j < 3; j++) {
                output << (ptr + i)->scores[j] << " ";
            }

            output << endl;

            output << "Average: "
                << (ptr + i)->average << endl;

            output << "Grade: "
                << (ptr + i)->grade << endl;

            output << "--------------------------" << endl;
        }

        output << endl;
        output << "CLASS SUMMARY" << endl;
        output << "==========================" << endl;

        output << "Class Average: "
            << classAverage << endl;

        output << "Highest Average: "
            << (ptr + highestIndex)->name
            << " - "
            << (ptr + highestIndex)->average
            << endl;

        output << "Lowest Average: "
            << (ptr + lowestIndex)->name
            << " - "
            << (ptr + lowestIndex)->average
            << endl;
        };

    // Display report on screen
    printReport(cout);

    // Save report to output file
    printReport(outputFile);

    outputFile.close();

    cout << endl;
    cout << "Report successfully saved to "
        << "performance_report.txt" << endl;

    return 0;
}
