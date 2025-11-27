#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * Program pomocniczy do weryfikacji rozwiązań zadań 1 i 2
 */

// Obliczanie norm wektora
double vectorNorm1(const vector<double>& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += abs(val);
    }
    return sum;
}

double vectorNorm2(const vector<double>& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

double vectorNormInf(const vector<double>& v) {
    double maxVal = 0.0;
    for (double val : v) {
        maxVal = max(maxVal, abs(val));
    }
    return maxVal;
}

// Obliczanie norm macierzy
double matrixNorm1(const vector<vector<double>>& A) {
    int n = A.size();
    int m = A[0].size();
    double maxSum = 0.0;

    for (int j = 0; j < m; j++) {
        double colSum = 0.0;
        for (int i = 0; i < n; i++) {
            colSum += abs(A[i][j]);
        }
        maxSum = max(maxSum, colSum);
    }
    return maxSum;
}

double matrixNormInf(const vector<vector<double>>& A) {
    double maxSum = 0.0;

    for (const auto& row : A) {
        double rowSum = 0.0;
        for (double val : row) {
            rowSum += abs(val);
        }
        maxSum = max(maxSum, rowSum);
    }
    return maxSum;
}

double matrixNormFrobenius(const vector<vector<double>>& A) {
    double sum = 0.0;

    for (const auto& row : A) {
        for (double val : row) {
            sum += val * val;
        }
    }
    return sqrt(sum);
}

// Odwracanie macierzy 2x2
vector<vector<double>> invert2x2(const vector<vector<double>>& A) {
    double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];

    if (abs(det) < 1e-15) {
        cerr << "Macierz osobliwa!\n";
        return {{0, 0}, {0, 0}};
    }

    return {
        {A[1][1]/det, -A[0][1]/det},
        {-A[1][0]/det, A[0][0]/det}
    };
}

void printMatrix(const vector<vector<double>>& matrix, const string& name) {
    cout << "\n" << name << ":\n";
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << setw(12) << setprecision(6) << fixed << val << " ";
        }
        cout << "\n";
    }
}

void printVector(const vector<double>& vec, const string& name) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    cout << "=======================================================\n";
    cout << "  Weryfikacja rozwiązań zadań teoretycznych\n";
    cout << "=======================================================\n";

    // ========== ZADANIE 1 ==========
    cout << "\n\n*** ZADANIE 1: Obliczanie norm ***\n";
    cout << string(60, '-') << "\n";

    // Wektor x z zadania 1
    vector<double> x = {-1, 2, -3, 4, -5};

    cout << "\nWektor x:\n";
    printVector(x, "x");

    cout << "\nNormy wektora x:\n";
    cout << "||x||_1 (Manhattan):     " << setw(12) << setprecision(6) << fixed
         << vectorNorm1(x) << "\n";
    cout << "||x||_2 (Euklidesowa):   " << setw(12) << setprecision(6) << fixed
         << vectorNorm2(x) << "\n";
    cout << "||x||_∞ (Maksimum):      " << setw(12) << setprecision(6) << fixed
         << vectorNormInf(x) << "\n";

    // Macierz A z zadania 1
    vector<vector<double>> A1 = {
        {1, -2},
        {-3, 4}
    };

    printMatrix(A1, "\nMacierz A");

    cout << "\nNormy macierzy A:\n";
    cout << "||A||_1 (Kolumnowa):     " << setw(12) << setprecision(6) << fixed
         << matrixNorm1(A1) << "\n";
    cout << "||A||_∞ (Wierszowa):     " << setw(12) << setprecision(6) << fixed
         << matrixNormInf(A1) << "\n";
    cout << "||A||_F (Frobenius):     " << setw(12) << setprecision(6) << fixed
         << matrixNormFrobenius(A1) << "\n";

    // ========== ZADANIE 2 ==========
    cout << "\n\n*** ZADANIE 2: Wskaźnik uwarunkowania ***\n";
    cout << string(60, '-') << "\n";

    // Macierz A
    vector<vector<double>> A2 = {
        {10, 1},
        {1, 20}
    };

    printMatrix(A2, "\nMacierz A");

    double normA = matrixNormInf(A2);
    vector<vector<double>> invA = invert2x2(A2);
    double normInvA = matrixNormInf(invA);
    double condA = normA * normInvA;

    printMatrix(invA, "\nMacierz A^(-1)");

    cout << "\n||A||_∞ = " << normA << "\n";
    cout << "||A^(-1)||_∞ = " << normInvA << "\n";
    cout << "cond_∞(A) = " << condA << "\n";

    // Macierz B z różnymi wartościami epsilon
    cout << "\n\nMacierz B dla różnych wartości epsilon:\n";
    cout << string(60, '=') << "\n";
    cout << setw(15) << "Epsilon"
         << setw(15) << "||B||_∞"
         << setw(15) << "||B^(-1)||_∞"
         << setw(15) << "cond_∞(B)\n";
    cout << string(60, '=') << "\n";

    vector<double> epsilons = {0.1, 0.01, 0.001, 0.0001};

    for (double eps : epsilons) {
        vector<vector<double>> B = {
            {1, 1 + eps},
            {1 - eps, 1}
        };

        double normB = matrixNormInf(B);
        vector<vector<double>> invB = invert2x2(B);
        double normInvB = matrixNormInf(invB);
        double condB = normB * normInvB;

        cout << setw(15) << setprecision(4) << scientific << eps
             << setw(15) << fixed << normB
             << setw(15) << normInvB
             << setw(15) << condB << "\n";
    }

    cout << string(60, '=') << "\n";

    cout << "\nWniosek:\n";
    cout << "Macierz A ma wskaźnik uwarunkowania cond(A) ≈ " << condA << "\n";
    cout << "Macierz B ma wskaźnik uwarunkowania cond(B) ≈ 4/ε² dla małych ε\n";
    cout << "\nMacierz A jest LEPIEJ uwarunkowana i zapewnia stabilniejsze\n";
    cout << "rozwiązania numeryczne układów równań!\n";

    // ========== ZADANIE 3 - podpowiedź ==========
    cout << "\n\n*** ZADANIE 3: Dekompozycja LU ***\n";
    cout << string(60, '-') << "\n";
    cout << "Dekompozycja LU dla zadania 3 została zaimplementowana\n";
    cout << "w programie głównym lu_decomposition.cpp\n\n";
    cout << "Możesz zmodyfikować dane wejściowe w lu_decomposition.cpp\n";
    cout << "aby przetestować macierz z zadania 3:\n\n";
    cout << "A = [ 1  2  2  1 ]\n";
    cout << "    [ 2  4  4  1 ]\n";
    cout << "    [ 2  2  2  1 ]\n";
    cout << "    [ 1  1  2  1 ]\n\n";
    cout << "b = [1, 2, 3, 4]^T\n";

    cout << "\n=======================================================\n";

    return 0;
}
