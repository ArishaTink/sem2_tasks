#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>   
#include <utility>   

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidNumber(const string& prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (cin.fail() || number <= 0) {
            cout << "Invalid input! Please enter a positive number.\n";
            clearInput();
        }
        else {
            clearInput();
            return number;
        }
    }
}

double getValidGrade(const string& prompt) {
    double grade;
    while (true) {
        cout << prompt;
        cin >> grade;
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number.\n";
            clearInput();
        }
        else if (grade < 0 || grade > 5) {   
            cout << "Invalid grade! Grade must be between 0 and 5.\n";
        }
        else {
            clearInput();
            return grade;
        }
    }
}

vector<double> averageScore(vector<vector<double>> allStudentsGrades, int N, int M) {
    vector<double> averageScore(N);
    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < M; j++) {
            sum += allStudentsGrades[i][j];
        }
        averageScore[i] = sum / M;
    }
    return averageScore;
}

void averageSubjectScore(const vector<vector<double>>& allStudentsGrades, const int N, const int M) {
    vector<double> subjectAverages(M, 0.0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            subjectAverages[j] += allStudentsGrades[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        cout << "Average score, subject #" << i + 1 << ": " << subjectAverages[i] / N << "\n";
    }
}

vector<double> bestStudent(const vector<double>& averageGrades, const int N, const int M) {
    int studentId = 0;
    double max = averageGrades[0];
    for (int i = 1; i < N; i++) {
        if (averageGrades[i] > max) {
            max = averageGrades[i];
            studentId = i;
        }
    }
    return { static_cast<double>(studentId), max };
}

int main() {
    vector<vector<double>> allStudentsGrades;
    int N = getValidNumber("Enter the number of students: ");
    int M = getValidNumber("Enter the number of subjects: ");

    for (int i = 0; i < N; i++) {
        vector<double> studentGrades;
        cout << "Student #" << i + 1 << ":\n";
        for (int j = 0; j < M; j++) {
            string prompt = "Subject " + to_string(j + 1) + " grade: ";
            double grade = getValidGrade(prompt);
            studentGrades.push_back(grade);
        }
        allStudentsGrades.push_back(studentGrades);
    }

    for (int i = 0; i < N; i++) {
        cout << "\nStudent #" << i + 1 << " grades:\n";
        for (int j = 0; j < M; j++) {
            cout << "Subject " << j + 1 << ": " << allStudentsGrades[i][j] << "\n";
        }
    }

    cout << "\n";
    vector<double> average = averageScore(allStudentsGrades, N, M);
    for (int i = 0; i < N; i++) {
        cout << "Average score, student #" << i + 1 << ": " << average[i] << "\n";
    }
    cout << "\n";
    averageSubjectScore(allStudentsGrades, N, M);
    cout << "\n";

    vector<double> best = bestStudent(averageScore(allStudentsGrades, N, M), N, M);
    cout << "Best average score - student #" << best[0] + 1 << ": " << best[1] << "\n";

    vector<pair<int, double>> studentRanking;
    for (int i = 0; i < N; i++) {
        studentRanking.emplace_back(i, average[i]);
    }

    sort(studentRanking.begin(), studentRanking.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    cout << "\nStudents sorted by average score (descending)\n";
    for (const auto& entry : studentRanking) {
        cout << "Student #" << entry.first + 1
            << ": " << entry.second << "\n";
    }

    double threshold = getValidGrade("\nEnter the threshold to remove students below: ");

    int excellent = 0;
    int atRisk = 0;
    for (double avg : average) {
        if (avg >= 4.5) excellent++;
        if (avg < 3.0) atRisk++;
    }

    cout << "\nExcellent students (>= 4.5): " << excellent << "\n";
    cout << "Students at risk of expulsion (< 3.0): " << atRisk << "\n";

    auto new_end = std::remove_if(studentRanking.begin(), studentRanking.end(),
        [threshold](const pair<int, double>& student) {
            return student.second < threshold;   // true = удалить этого студента
        });

    studentRanking.erase(new_end, studentRanking.end());

    cout << "\nStudents AFTER filtering (average >= " << threshold << ")\n";
    for (const auto& entry : studentRanking) {
        cout << "Student #" << entry.first + 1 << ": " << entry.second << "\n";
    }



    return 0;
}