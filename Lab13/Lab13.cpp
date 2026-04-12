#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void gaussMethod(double** matrix, int M, int N) {
    for (int k = 0; k < min(M, N); k++) { // проходимся по столбцам
        // находим максимальный элемент в столбце
        int maxRow = k;
        for (int i = k + 1; i < M; i++) {
            if (abs(matrix[i][k]) > abs(matrix[maxRow][k])) {
                maxRow = i;
            }
        }

        // меняем местами текущую строку и строку с максимальным элементом в столбце
        if (maxRow != k) {
            swap(matrix[k], matrix[maxRow]);
        }

        // если ведущий элемент равен нулю, значит, в этом столбце нет решений
        if (abs(matrix[k][k]) < 1e-9) continue;

        // запоминаем ведущий элемент
        double pivot = matrix[k][k];

        // делим строку на ведущий элемент, чтоб на диагонали получить 1
        for (int j = k; j <= N; j++) {
            matrix[k][j] /= pivot;
        }

        // обнуляем все элементы в столбце k выше и ниже главной диагонали
        for (int i = 0; i < M; i++) {
            if (i != k) { // пропускаем текущую строку
                double factor = matrix[i][k]; // множитель
                for (int j = k; j <= N; j++) {
                    matrix[i][j] -= factor * matrix[k][j];
                }
            }
        }
    }
}

void analyzeResult(double** matrix, int M, int N, ostream& out) {
    int nonZeroRows = 0;

    for (int i = 0; i < M; i++) {
        bool allZeros = true;
        for (int j = 0; j < N; j++) {
            if (abs(matrix[i][j]) > 1e-9) {
                allZeros = false;
                break;
            }
        }
        if (allZeros) {
            if (abs(matrix[i][N]) > 1e-9) {
                out << "Inconsistent system" << endl;
                return;
            }
        }
        else {
            nonZeroRows++;
        }
    }

    if (nonZeroRows < N) {

        bool* isFree = new bool[N]; // массив для свободных переменных
        for (int j = 0; j < N; j++) isFree[j] = true; // изначально все свободные

        int* pivotCol = new int[M]; // массив для базисных переменныз
        for (int i = 0; i < M; i++) pivotCol[i] = -1;

        // ищем базисные переменные (первая ненулевая в каждой строке)
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (abs(matrix[i][j]) > 1e-9) {
                    pivotCol[i] = j;
                    isFree[j] = false;
                    break;
                }
            }
        }

        double* ans = new double[N];

        bool firstFree = true;
        for (int j = 0; j < N; j++) {
            if (isFree[j]) {
                if (!firstFree) out << ", ";
                out << "x" << j + 1;
                firstFree = false;
                ans[j] = 1.0; // присваиваем 1 свободным переменным
            }
            else {
                ans[j] = 0.0;
            }
        }
        if (!firstFree) out << " are free\n";

        // считаем базисные переменные
        for (int i = 0; i < M; i++) {
            int p = pivotCol[i];
            if (p != -1) {
                double sum = 0;
                for (int j = 0; j < N; j++) {
                    if (j != p) {
                        sum += matrix[i][j] * ans[j];
                    }
                }
                ans[p] = matrix[i][N] - sum;
            }
        }

        for (int j = 0; j < N; j++) {
            if (abs(ans[j]) < 1e-9) ans[j] = 0.0;
            out << "x" << j + 1 << "=" << fixed << setprecision(3) << ans[j];
            if (j < N - 1) out << "; ";
        }
        out << endl;

        // Очищаем память
        delete[] isFree;
        delete[] pivotCol;
        delete[] ans;

        return;
    }

    for (int i = 0; i < N; i++) {
        double answer = matrix[i][N];
        if (abs(answer) < 1e-9) answer = 0.0;

        out << "x" << i + 1 << "=" << fixed << setprecision(3) << answer;
        if (i < N - 1) out << "; ";
    }
    out << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("C:\\Users\\danilka\\Downloads\\tests.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        return 1;
    }

    // создаем файл для записи
    ofstream fout("C:\\Users\\danilka\\source\\repos\\Lab13\\Lab13\\output.txt");
    if (!fout.is_open()) {
        cout << "Ошибка создания файла для записи." << endl;
        return 1;
    }

    int M, N; // кол-во уравнений (M) и кол-во неизвестных (N)
    file >> M >> N;

    double** matrix = new double* [M]; // выделяем память под матрицу
    for (int i = 0; i < M; i++) {
        matrix[i] = new double[N + 1];
    }

    for (int i = 0; i < M; i++) { // записываем данные из файла в наш двумерный массив
        for (int j = 0; j <= N; j++) {
            file >> matrix[i][j];
        }
    }

    cout << "Исходная матрица:" << endl;
    fout << "Исходная матрица:" << endl;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= N; j++) {
            cout << setw(8) << matrix[i][j] << " ";
            fout << setw(8) << matrix[i][j] << " ";
        }
        cout << endl;
        fout << endl;
    }

    gaussMethod(matrix, M, N);

    cout << "\nМатрица после Гаусса-Жордана:" << endl;
    fout << "\nМатрица после Гаусса-Жордана:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= N; j++) {
            if (abs(matrix[i][j]) < 1e-9) matrix[i][j] = 0;
            cout << setw(8) << fixed << setprecision(3) << matrix[i][j] << " ";
            fout << setw(8) << fixed << setprecision(3) << matrix[i][j] << " ";
        }
        cout << endl;
        fout << endl;
    }

    cout << "\nРезультат:" << endl;
    fout << "\nРезультат:" << endl;
    analyzeResult(matrix, M, N, cout);
    analyzeResult(matrix, M, N, fout);

    for (int i = 0; i < M; i++) { // очистка памяти
        delete[] matrix[i];
    }
    delete[] matrix;

    file.close(); // закрытие файлов
    fout.close();

    return 0;
}