#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Typ dla wektora i macierzy
typedef vector<double> Vector;
typedef vector<Vector> Matrix;

// Funkcje pomocnicze
void printVector(const Vector& v, const string& name = "") {
    if (!name.empty()) cout << name << " = ";
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << setw(12) << setprecision(6) << fixed << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void printMatrix(const Matrix& A, const string& name = "") {
    if (!name.empty()) cout << name << ":" << endl;
    for (const auto& row : A) {
        for (double val : row) {
            cout << setw(10) << setprecision(4) << fixed << val << " ";
        }
        cout << endl;
    }
}

// Mnożenie macierzy przez wektor: result = A * x
Vector matrixVectorMultiply(const Matrix& A, const Vector& x) {
    int n = A.size();
    Vector result(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Odejmowanie wektorów: result = a - b
Vector vectorSubtract(const Vector& a, const Vector& b) {
    Vector result(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        result[i] = a[i] - b[i];
    }
    return result;
}

// Norma maksimum (nieskończoność) wektora
double normInfinity(const Vector& v) {
    double maxVal = 0.0;
    for (double val : v) {
        maxVal = max(maxVal, fabs(val));
    }
    return maxVal;
}

// Norma euklidesowa wektora
double normEuclidean(const Vector& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Obliczanie residuum: ||b - Ax||
double calculateResiduum(const Matrix& A, const Vector& x, const Vector& b) {
    Vector Ax = matrixVectorMultiply(A, x);
    Vector residuum = vectorSubtract(b, Ax);
    return normEuclidean(residuum);
}

// Metoda Jacobiego
Vector jacobiIteration(const Matrix& A, const Vector& b, const Vector& x_old) {
    int n = A.size();
    Vector x_new(n, 0.0);

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                sum += A[i][j] * x_old[j];
            }
        }
        x_new[i] = (b[i] - sum) / A[i][i];
    }

    return x_new;
}

// Metoda Gaussa-Seidela
Vector gaussSeidelIteration(const Matrix& A, const Vector& b, const Vector& x_old) {
    int n = A.size();
    Vector x_new = x_old;  // Kopiujemy, bo będziemy nadpisywać

    for (int i = 0; i < n; i++) {
        double sum = 0.0;

        // Suma dla j < i (używamy już zaktualizowanych wartości)
        for (int j = 0; j < i; j++) {
            sum += A[i][j] * x_new[j];
        }

        // Suma dla j > i (używamy starych wartości)
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x_new[j];
        }

        x_new[i] = (b[i] - sum) / A[i][i];
    }

    return x_new;
}

// Metoda SOR (Successive Over-Relaxation)
Vector sorIteration(const Matrix& A, const Vector& b, const Vector& x_old, double omega) {
    int n = A.size();
    Vector x_new = x_old;

    for (int i = 0; i < n; i++) {
        double sum = 0.0;

        // Suma dla j < i (używamy już zaktualizowanych wartości)
        for (int j = 0; j < i; j++) {
            sum += A[i][j] * x_new[j];
        }

        // Suma dla j > i (używamy starych wartości)
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x_new[j];
        }

        // Wzór SOR
        double x_gs = (b[i] - sum) / A[i][i];
        x_new[i] = (1.0 - omega) * x_old[i] + omega * x_gs;
    }

    return x_new;
}

// Ogólna funkcja rozwiązująca układ metodą iteracyjną
void solveIterative(const Matrix& A, const Vector& b, Vector x0,
                   const string& methodName,
                   Vector (*iterationFunc)(const Matrix&, const Vector&, const Vector&),
                   double omega = 1.0,
                   double tolerance = 1e-6,
                   int maxIterations = 1000,
                   bool verbose = true) {

    int n = A.size();
    Vector x_old = x0;
    Vector x_new(n);

    cout << "\n" << string(80, '=') << endl;
    cout << "Metoda: " << methodName << endl;
    cout << string(80, '=') << endl;

    if (verbose) {
        cout << "\nPrzybliżenie początkowe:" << endl;
        printVector(x0, "x0");
        cout << "\nIteracja    ||x^(k+1) - x^(k)||    ||b - Ax^(k)||" << endl;
        cout << string(60, '-') << endl;
    }

    int iteration = 0;
    double error = tolerance + 1;
    double residuum = calculateResiduum(A, x_old, b);

    while (iteration < maxIterations && (error > tolerance || residuum > tolerance)) {
        if (methodName.find("SOR") != string::npos) {
            x_new = sorIteration(A, b, x_old, omega);
        } else {
            x_new = iterationFunc(A, b, x_old);
        }

        Vector diff = vectorSubtract(x_new, x_old);
        error = normEuclidean(diff);
        residuum = calculateResiduum(A, x_new, b);

        iteration++;

        // Wyświetl wyniki pośrednie
        if (verbose && (iteration <= 10 || iteration % 10 == 0 ||
            error <= tolerance || residuum <= tolerance)) {
            cout << setw(5) << iteration
                 << setw(25) << scientific << setprecision(6) << error
                 << setw(25) << residuum << endl;
        }

        x_old = x_new;
    }

    cout << "\nWyniki końcowe:" << endl;
    cout << "Liczba iteracji: " << iteration << endl;
    cout << "Estymator błędu: " << scientific << setprecision(10) << error << endl;
    cout << "Residuum: " << scientific << setprecision(10) << residuum << endl;
    cout << "\nRozwiązanie:" << endl;
    printVector(x_new, "x");

    // Weryfikacja: Ax = b
    Vector Ax = matrixVectorMultiply(A, x_new);
    cout << "\nWeryfikacja (Ax):" << endl;
    printVector(Ax, "Ax");
    printVector(b, "b ");

    // Kryterium zbieżności
    if (iteration >= maxIterations) {
        cout << "\nOSTRZEŻENIE: Osiągnięto maksymalną liczbę iteracji!" << endl;
    } else if (error <= tolerance && residuum <= tolerance) {
        cout << "\nMetoda zbieżna - osiągnięto zadaną dokładność." << endl;
    }
}

// Funkcja do sprawdzania dominacji diagonalnej
bool checkDiagonalDominance(const Matrix& A) {
    int n = A.size();
    bool strictlyDominant = true;
    bool weaklyDominant = true;

    cout << "\nSprawdzanie dominacji diagonalnej:" << endl;
    cout << "Wiersz    |a_ii|    Suma |a_ij| (j!=i)    Warunek" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < n; i++) {
        double diag = fabs(A[i][i]);
        double sum = 0.0;

        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += fabs(A[i][j]);
            }
        }

        cout << setw(3) << i+1
             << setw(12) << fixed << setprecision(4) << diag
             << setw(20) << sum;

        if (diag > sum) {
            cout << "    SPEŁNIONY (>)" << endl;
        } else if (diag == sum) {
            cout << "    RÓWNOŚĆ (=)" << endl;
            strictlyDominant = false;
        } else {
            cout << "    NIESPEŁNIONY (<)" << endl;
            strictlyDominant = false;
            weaklyDominant = false;
        }
    }

    cout << "\nWniosek: ";
    if (strictlyDominant) {
        cout << "Macierz ma SILNĄ dominację diagonalną - metody iteracyjne są zbieżne." << endl;
        return true;
    } else if (weaklyDominant) {
        cout << "Macierz ma słabą dominację diagonalną - zbieżność wymaga dodatkowej analizy." << endl;
        return false;
    } else {
        cout << "Macierz NIE ma dominacji diagonalnej - zbieżność NIE jest zagwarantowana." << endl;
        return false;
    }
}

int main() {
    cout << fixed << setprecision(6);

    // Dane z zadania - układ 5x5
    Matrix A = {
        {50,  5,  4,  3,  2},
        { 1, 40,  1,  2,  3},
        { 4,  5, 30, -5, -4},
        {-3, -2, -1, 20,  0},
        { 1,  2,  3,  4, 30}
    };

    Vector b = {140, 67, 62, 89, 153};
    Vector x0 = {6, 6, 6, 6, 6};

    cout << "\n" << string(80, '#') << endl;
    cout << "ROZWIĄZYWANIE UKŁADU RÓWNAŃ LINIOWYCH METODAMI ITERACYJNYMI" << endl;
    cout << string(80, '#') << endl;

    cout << "\nDane wejściowe:" << endl;
    printMatrix(A, "Macierz A");
    printVector(b, "Wektor b");
    printVector(x0, "Przybliżenie początkowe x0");

    // Sprawdzenie dominacji diagonalnej
    checkDiagonalDominance(A);

    // Parametry
    double tolerance = 1e-6;
    int maxIterations = 1000;
    double omega = 0.5;  // Parametr dla SOR

    cout << "\nParametry obliczeń:" << endl;
    cout << "Tolerancja (epsilon): " << scientific << tolerance << endl;
    cout << "Maksymalna liczba iteracji: " << maxIterations << endl;
    cout << "Parametr omega dla SOR: " << fixed << omega << endl;

    // Rozwiązanie metodą Jacobiego
    solveIterative(A, b, x0, "Jacobiego", jacobiIteration, 1.0, tolerance, maxIterations, true);

    // Rozwiązanie metodą Gaussa-Seidela
    solveIterative(A, b, x0, "Gaussa-Seidela", gaussSeidelIteration, 1.0, tolerance, maxIterations, true);

    // Rozwiązanie metodą SOR
    solveIterative(A, b, x0, "SOR (omega = 0.5)", nullptr, omega, tolerance, maxIterations, true);

    cout << "\n" << string(80, '#') << endl;
    cout << "KONIEC OBLICZEŃ" << endl;
    cout << string(80, '#') << endl;

    return 0;
}
