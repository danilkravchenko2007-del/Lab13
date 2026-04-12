#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib> 

using namespace std;

extern void gaussMethod(double** matrix, int M, int N);
extern void analyzeResult(double** matrix, int M, int N, ostream& out);

void parseEquation(string eq, double& A, double& B, double& C) {
    string s = "";
    for (char ch : eq) {
        if (ch != ' ') s += ch;
    }

    int xPos = s.find('x');
    int yPos = s.find('y');
    int eqPos = s.find('=');

    string aStr = s.substr(0, xPos);
    if (aStr == "" || aStr == "+") A = 1.0;
    else if (aStr == "-") A = -1.0;
    else A = stod(aStr);

    string bStr = s.substr(xPos + 1, yPos - xPos - 1);
    if (bStr == "" || bStr == "+") B = 1.0;
    else if (bStr == "-") B = -1.0;
    else B = stod(bStr);

    string cStr = s.substr(eqPos + 1);
    C = stod(cStr);
}

void solveTask3_1() {
    ifstream file("C:\\Users\\danilka\\Downloads\\tests.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла tests.txt" << endl;
        return;
    }

    int M = 2, N = 2;

    double** matrix = new double* [M];
    for (int i = 0; i < M; i++) {
        matrix[i] = new double[N + 1];
    }

    string eq1, eq2;
    getline(file, eq1, ',');
    getline(file, eq2);

    parseEquation(eq1, matrix[0][0], matrix[0][1], matrix[0][2]);
    parseEquation(eq2, matrix[1][0], matrix[1][1], matrix[1][2]);

    double A1 = matrix[0][0], B1 = matrix[0][1], C1 = matrix[0][2];
    double A2 = matrix[1][0], B2 = matrix[1][1], C2 = matrix[1][2];

    cout << "--- Задание: Пересечение прямых ---" << endl;
    cout << "Прямая 1: " << eq1 << endl;
    cout << "Прямая 2: " << eq2 << endl;
    cout << "-----------------------------------" << endl;

    gaussMethod(matrix, M, N);

    cout << "Координаты точки пересечения:" << endl;
    analyzeResult(matrix, M, N, cout);

    ofstream transfer("C:\\Users\\danilka\\Downloads\\transfer.txt");
    if (transfer.is_open()) {
        transfer << A1 << " " << B1 << " " << C1 << endl;
        transfer << A2 << " " << B2 << " " << C2 << endl;
        transfer << matrix[0][2] << " " << matrix[1][2] << endl;
        transfer.close();
    }

    system("start \"\" \"C:\\Users\\danilka\\OneDrive\\Документы\\basicsofprogramming1\\pascal\\labs\\lab4\\lab42\\project1.exe\"");
 

    for (int i = 0; i < M; i++) delete[] matrix[i];
    delete[] matrix;

    file.close();
}