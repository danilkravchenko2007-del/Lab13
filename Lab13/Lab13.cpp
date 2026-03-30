#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


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

	for (int i = 0; i < M; i++) { // очистка памяти
		delete[] matrix[i];
	}
	delete[] matrix;

	file.close(); // закрытие файла

	return 0;

}