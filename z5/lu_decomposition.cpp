#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Funkcje pomocnicze do wyświetlania
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
    cout << "\n" << name << ":\n";
    for (double val : vec) {
        cout << setw(12) << setprecision(6) << fixed << val << "\n";
    }
}

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

/**
 * Dekompozycja LU z częściowym wyborem elementu podstawowego
 *
 * Procedura 1: Operuje wyłącznie na macierzy A
 * Zwraca: macierz A zmodyfikowaną (zawiera L i U), oraz wektor permutacji
 *
 * Na wejściu: A - macierz n x n
 * Na wyjściu: A - macierz zawierająca L (poniżej diagonali) i U (na i powyżej diagonali)
 *             perm - wektor permutacji wierszy
 */
void luDecomposition(vector<vector<double>>& A, vector<int>& perm) {
    int n = A.size();
    perm.resize(n);

    // Inicjalizacja wektora permutacji
    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    // Główna pętla eliminacji Gaussa
    for (int k = 0; k < n - 1; k++) {
        // Częściowy wybór elementu podstawowego
        int maxRow = k;
        double maxVal = abs(A[k][k]);

        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                maxRow = i;
            }
        }

        // Zamiana wierszy, jeśli potrzebna
        if (maxRow != k) {
            swap(A[k], A[maxRow]);
            swap(perm[k], perm[maxRow]);
        }

        // Sprawdzenie czy element główny nie jest zerem
        if (abs(A[k][k]) < 1e-15) {
            cerr << "Ostrzeżenie: Element główny bliski zeru w kolumnie " << k << endl;
            continue;
        }

        // Eliminacja
        for (int i = k + 1; i < n; i++) {
            double multiplier = A[i][k] / A[k][k];
            A[i][k] = multiplier;  // Zachowujemy mnożnik w L

            for (int j = k + 1; j < n; j++) {
                A[i][j] -= multiplier * A[k][j];
            }
        }
    }
}

/**
 * Procedura 2: Rozwiązywanie układu równań Ax = b
 *
 * Wykorzystuje wynik dekompozycji LU z procedury 1
 * Operuje wyłącznie na wektorze b
 *
 * Na wejściu: A - macierz po dekompozycji LU
 *             b - wektor prawej strony
 *             perm - wektor permutacji z procedury 1
 * Na wyjściu: x - rozwiązanie układu
 */
vector<double> solveLU(const vector<vector<double>>& A, vector<double> b, const vector<int>& perm) {
    int n = A.size();
    vector<double> x(n);

    // Permutacja wektora b zgodnie z permutacją wierszy
    vector<double> pb(n);
    for (int i = 0; i < n; i++) {
        pb[i] = b[perm[i]];
    }

    // Krok 1: Rozwiązanie Ly = Pb (podstawienie w przód)
    // L ma jedynki na diagonali
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = pb[i];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    // Krok 2: Rozwiązanie Ux = y (podstawienie wstecz)
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// Funkcja do wyodrębnienia macierzy L
vector<vector<double>> extractL(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;  // Diagonala L to jedynki
        for (int j = 0; j < i; j++) {
            L[i][j] = A[i][j];
        }
    }

    return L;
}

// Funkcja do wyodrębnienia macierzy U
vector<vector<double>> extractU(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            U[i][j] = A[i][j];
        }
    }

    return U;
}

// Funkcja weryfikująca rozwiązanie
vector<double> multiplyMatrixVector(const vector<vector<double>>& A, const vector<double>& x) {
    int n = A.size();
    vector<double> result(n, 0.0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }

    return result;
}

int main() {
    cout << "=================================================\n";
    cout << "   Zajęcia nr 5: Dekompozycja LU z wyborem\n";
    cout << "   elementu podstawowego\n";
    cout << "=================================================\n";

    // Dane z zadania programowego
    vector<vector<double>> A = {
        {5,  4,  3,  2,  1},
        {10, 8,  7,  6,  5},
        {-1, 2, -3,  4, -5},
        {6,  5, -4,  3, -2},
        {1,  2,  3,  4,  5}
    };

    vector<double> b = {37, 99, -9, 12, 53};

    int n = A.size();

    cout << "\n--- DANE WEJŚCIOWE ---\n";
    printMatrix(A, "Macierz A");
    printVector(b, "Wektor b");

    // Obliczanie norm macierzy A
    cout << "\n--- NORMY MACIERZY A ---\n";
    cout << "||A||_1 (norma kolumnowa):      " << matrixNorm1(A) << "\n";
    cout << "||A||_inf (norma wierszowa):    " << matrixNormInf(A) << "\n";
    cout << "||A||_F (norma Frobeniusa):     " << matrixNormFrobenius(A) << "\n";

    // Obliczanie norm wektora b
    cout << "\n--- NORMY WEKTORA b ---\n";
    cout << "||b||_1 (norma Manhattan):      " << vectorNorm1(b) << "\n";
    cout << "||b||_2 (norma euklidesowa):    " << vectorNorm2(b) << "\n";
    cout << "||b||_inf (norma maksimum):     " << vectorNormInf(b) << "\n";

    // Kopia macierzy A do dekompozycji
    vector<vector<double>> A_copy = A;
    vector<int> perm;

    cout << "\n--- DEKOMPOZYCJA LU ---\n";
    cout << "Przeprowadzam dekompozycję LU z częściowym wyborem elementu podstawowego...\n";

    // PROCEDURA 1: Dekompozycja LU (operuje tylko na macierzy)
    luDecomposition(A_copy, perm);

    cout << "\nWektor permutacji: ";
    for (int i = 0; i < n; i++) {
        cout << perm[i] << " ";
    }
    cout << "\n";

    // Wyodrębnienie macierzy L i U
    vector<vector<double>> L = extractL(A_copy);
    vector<vector<double>> U = extractU(A_copy);

    printMatrix(L, "Macierz L");
    printMatrix(U, "Macierz U");

    cout << "\n--- ROZWIĄZYWANIE UKŁADU RÓWNAŃ ---\n";

    // PROCEDURA 2: Rozwiązywanie układu (operuje tylko na wektorze b)
    vector<double> x = solveLU(A_copy, b, perm);

    printVector(x, "Rozwiązanie x");

    // Weryfikacja rozwiązania
    cout << "\n--- WERYFIKACJA ROZWIĄZANIA ---\n";
    vector<double> b_check = multiplyMatrixVector(A, x);
    printVector(b_check, "A * x (powinno być równe b)");

    // Obliczanie błędu
    double error = 0.0;
    for (int i = 0; i < n; i++) {
        error += (b[i] - b_check[i]) * (b[i] - b_check[i]);
    }
    error = sqrt(error);

    cout << "\nBłąd ||b - Ax||_2 = " << scientific << error << "\n";

    if (error < 1e-10) {
        cout << "✓ Rozwiązanie jest poprawne!\n";
    } else {
        cout << "⚠ Uwaga: Wykryto błąd numeryczny!\n";
    }

    cout << "\n=================================================\n";

    return 0;
}
