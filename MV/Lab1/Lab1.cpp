#include <iostream>
#include <vector>

int main() {

	int n = 0;
	std::cout << "Print dimension: ";
	std::cin >> n;

	std::vector<std::vector<int>> matr(n, std::vector<int>(n));
	std::cout << "Print matrix:\n";
	for (size_t i = 0; i < n * n; ++i) {
		size_t row = i / n, column = i % n;
		std::cin >> matr[row][column];
	}

	std::vector<int> b(n);
	std::cout << "\nPrint vector b: ";
	for (size_t i = 0; i < n; ++i) {
		std::cin >> b[i];
	}

	std::vector<std::vector<double>> matrixL(n, std::vector<double>(n));
	
	for (int i = 0; i < n; ++i) {
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			if (i == j) {
				double sum = 0;
				for (int k = 0; k + 1 < i; ++k) {
					sum += (matrixL[i][k] * matrixL[i][k]);
				}
				matrixL[i][i] = sqrt(matr[i][i] - sum);
			}
			else {
				int sum = 0;
				for (int k = 0; k + 1 < i; ++k) {
					sum += (matrixL[j][k] * matrixL[i][k]);
				}
				matrixL[j][i] = (matr[j][i] - sum) / matrixL[i][i];
			}
		}
	}

	std::vector<double> x(n);
	std::vector<double> y(n);
	for (int i = 0; i < n; ++i) {
		double sum = 0;
		for (int k = 0; k + 1 < i; ++k) {
			sum += (matrixL[i][k] * y[k]);
		}
		y[i] = (b[i] - sum) / matrixL[i][i];
	}

	for (int i = n - 1; i + 1 > 0; --i) {
		double sum = 0;
		for (int k = i + 1; k < n; ++k) {
			sum += (matrixL[k][i] * x[k]);
		}
		x[i] = (y[i] - sum) / matrixL[i][i];
	}

	std::cout << "\nSolution of the system of equations:\n";
	for (size_t i = 0; i < n; ++i) {
		std::cout << x[i] << " ";
	}

	return 0;
}