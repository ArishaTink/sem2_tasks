#include <iostream>
#include <windows.h>

using namespace std;

double getValidGrade(int studentNumber) {
    double grade;
    bool correct = true;

    do {
        cout << "Student #" << studentNumber << ": ";

        if (cin >> grade) {
            // Удалось прочитать число
            if (grade >= 0 && grade <= 5) {
                correct = true;
            }
            else {
                cout << "Error: the value should be from 0 to 5!\n";
                correct = false;
            }
        }
        else {
            // Не число ввели
            cout << "Error: please enter a number!\n";
            cin.clear();                                // снимаем failbit
            cin.ignore(10000, '\n');                    // выбрасываем мусор из буфера
            correct = false;
        }
    } while (!correct);

    return grade;
}

void enterAverageScore(double* grades, int numberOfStudents) {
    cout << "Enter average grades: \n";
    for (int i = 0; i < numberOfStudents; i++) {
        grades[i] = getValidGrade(i + 1);
    }
    cout << "Completed \n";
}

double searchMax(double* grades, int numberOdStudents) {
    double maxValue = grades[0];
    for (int i = 1; i < numberOdStudents; i++) {
        if (maxValue < grades[i]) {
            maxValue = grades[i];
        }
    }
    return maxValue;
}

double searchMin(double* grades, int numberOdStudents) {
    double minValue = grades[0];
    for (int i = 1; i < numberOdStudents; i++) {
        if (minValue > grades[i]) {
            minValue = grades[i];
        }
    }
    return minValue;
}

int higherThan(double* grades, int numberOdStudents, double grade) {
    int counter = 0;
    for (int i = 0; i < numberOdStudents; i++) {
        if (grades[i] > grade) {
            counter++;
        }
    }
    return counter;
}

double countAverage(double* grades, int numberOdStudents) {
    int counter = 0;
    double sum = 0;
    for (int i = 0; i < numberOdStudents; i++) {
        sum += grades[i];
        counter++;
    }
    return sum / counter;
}

int main()
{
    int numberOfStudents;
    do{
        cout << "Enter number of students: ";
        cin >> numberOfStudents;
        if (numberOfStudents <= 0) {
            cout << "The number of students should be > 0!\n";
        }
    } while (numberOfStudents<=0);
    

    double* grades = new double[numberOfStudents];

    enterAverageScore(grades, numberOfStudents);

    for (int i = 0; i < numberOfStudents; i++) {
        cout << grades[i] << " ";
    }

    
    delete[] grades;
    return 0;
}