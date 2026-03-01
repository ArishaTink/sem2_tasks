#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <cctype>  

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

const char MAGIC_SIGNATURE[4] = { 'G', 'R', 'D', 'S' };
const uint32_t FILE_VERSION = 1;

#pragma pack(push, 1)
struct FileHeader {
    char signature[4];
    uint32_t version;
    uint32_t numStudents;
};
#pragma pack(pop)

void saveToFile(const vector<vector<double>>& allStudentsGrades, int N, int M, const string& filename = "students.bin") {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Cannot open file for writing!\n";
        return;
    }

    FileHeader header;
    memcpy(header.signature, MAGIC_SIGNATURE, 4);
    header.version = FILE_VERSION;
    header.numStudents = static_cast<uint32_t>(N);

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));

    uint32_t numSubjects = static_cast<uint32_t>(M);
    file.write(reinterpret_cast<const char*>(&numSubjects), sizeof(numSubjects));

    for (const auto& student : allStudentsGrades) {
        for (double grade : student) {
            file.write(reinterpret_cast<const char*>(&grade), sizeof(double));
        }
    }

    file.close();
    cout << "Data successfully saved to " << filename << "\n";
}

bool loadFromFile(vector<vector<double>>& allStudentsGrades, int& N, int& M, const string& filename = "students.bin") {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "File not found.\n";
        return false;
    }

    FileHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (memcmp(header.signature, MAGIC_SIGNATURE, 4) != 0) {
        cout << "Invalid signature!\n";
        return false;
    }
    if (header.version != FILE_VERSION) {
        cout << "Unsupported version!\n";
        return false;
    }

    N = static_cast<int>(header.numStudents);

    uint32_t numSubjects;
    file.read(reinterpret_cast<char*>(&numSubjects), sizeof(numSubjects));
    M = static_cast<int>(numSubjects);

    allStudentsGrades.assign(N, vector<double>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            file.read(reinterpret_cast<char*>(&allStudentsGrades[i][j]), sizeof(double));
        }
    }

    file.close();
    cout << "Successfully loaded " << N << " students, " << M << " subjects.\n";
    return true;
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
    cout << "Size of FileHeader structure: " << sizeof(FileHeader) << " bytes\n\n";

    vector<vector<double>> allStudentsGrades;
    int N = 0, M = 0;
    string filename = "students.bin";

    cout << "1. Enter new data\n";
    cout << "2. Load from binary file (" << filename << ")\n";
    int mode = getValidNumber("Choose (1-2): ");

    bool loaded = false;
    if (mode == 2) {
        loaded = loadFromFile(allStudentsGrades, N, M, filename);
    }

    if (!loaded) {
        N = getValidNumber("Enter the number of students: ");
        M = getValidNumber("Enter the number of subjects: ");

        allStudentsGrades.clear(); 

        for (int i = 0; i < N; i++) {
            vector<double> studentGrades;
            cout << "Student #" << i + 1 << ":\n";
            for (int j = 0; j < M; j++) {
                string prompt = "Subject " + to_string(j + 1) + " grade: ";
                studentGrades.push_back(getValidGrade(prompt));
            }
            allStudentsGrades.push_back(studentGrades);
        }
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

    vector<double> best = bestStudent(average, N, M);
    cout << "Best average score - student #" << static_cast<int>(best[0]) + 1
        << ": " << best[1] << "\n";

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

    int excellent = 0, atRisk = 0;
    for (double avg : average) {
        if (avg >= 4.5) excellent++;
        if (avg < 3.0) atRisk++;
    }
    cout << "\nExcellent students (>= 4.5): " << excellent << "\n";
    cout << "Students at risk of expulsion (< 3.0): " << atRisk << "\n";

    auto new_end = std::remove_if(studentRanking.begin(), studentRanking.end(),
        [threshold](const pair<int, double>& student) {
            return student.second < threshold;
        });
    studentRanking.erase(new_end, studentRanking.end());

    cout << "\nStudents AFTER filtering (average >= " << threshold << ")\n";
    for (const auto& entry : studentRanking) {
        cout << "Student #" << entry.first + 1 << ": " << entry.second << "\n";
    }

    cout << "\nSave data to binary file? (y/n): ";
    char ch;
    cin >> ch;
    clearInput();
    if (tolower(ch) == 'y') {
        saveToFile(allStudentsGrades, N, M, filename);
    }

    return 0;
}