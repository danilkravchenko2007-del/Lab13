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

int main() {
	setlocale(LC_ALL, "Russian");

	ifstream file("C:\\Users\\danilka\\Downloads\\tests.txt");
	if (!file.is_open()) {
		cout << "Ошибка открытия файла." << endl;
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

	for (int i = 0; i < M; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(8) << matrix[i][j] << " ";
		}
		cout << endl;
	}

    gaussMethod(matrix, M, N);

    cout << "\nМатрица после Гаусса-Жордана:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= N; j++) {
            if (abs(matrix[i][j]) < 1e-9) matrix[i][j] = 0;
            cout << setw(8) << fixed << setprecision(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }

	for (int i = 0; i < M; i++) { // очистка памяти
		delete[] matrix[i];
	}
	delete[] matrix;

	file.close(); // закрытие файла

	return 0;

}