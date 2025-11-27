#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * Dodatkowe ćwiczenie - analiza wpływu epsilon na stabilność numeryczną
 *
 * Macierz: A = (1+ε)I + (1-ε)J, gdzie I - macierz jednostkowa, J - macierz jedynek
 * Wektor: b = [6+ε, 6+2ε, 6+2ε, 6+ε]^T
 * Rozwiązanie analityczne: x = [1, 2, 2, 1]^T (niezależne od ε!)
 */

// Dekompozycja LU z częściowym wyborem elementu podstawowego
void luDecomposition(vector<vector<double>>& A, vector<int>& perm) {
    int n = A.size();
    perm.resize(n);

    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    for (int k = 0; k < n - 1; k++) {
        int maxRow = k;
        double maxVal = abs(A[k][k]);

        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                maxRow = i;
            }
        }

        if (maxRow != k) {
            swap(A[k], A[maxRow]);
            swap(perm[k], perm[maxRow]);
        }

        if (abs(A[k][k]) < 1e-20) {
            continue;
        }

        for (int i = k + 1; i < n; i++) {
            double multiplier = A[i][k] / A[k][k];
            A[i][k] = multiplier;

            for (int j = k + 1; j < n; j++) {
                A[i][j] -= multiplier * A[k][j];
            }
        }
    }
}

// Rozwiązywanie układu LU
vector<double> solveLU(const vector<vector<double>>& A, vector<double> b, const vector<int>& perm) {
    int n = A.size();
    vector<double> x(n);

    vector<double> pb(n);
    for (int i = 0; i < n; i++) {
        pb[i] = b[perm[i]];
    }

    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = pb[i];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// Obliczanie wskaźnika uwarunkowania (przybliżone, używając normy nieskończoności)
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

// Odwracanie macierzy przez rozwiązanie n układów równań
vector<vector<double>> invertMatrix(vector<vector<double>> A) {
    int n = A.size();
    vector<vector<double>> inv(n, vector<double>(n, 0.0));

    for (int col = 0; col < n; col++) {
        vector<double> e(n, 0.0);
        e[col] = 1.0;

        vector<vector<double>> A_copy = A;
        vector<int> perm;
        luDecomposition(A_copy, perm);
        vector<double> x = solveLU(A_copy, e, perm);

        for (int i = 0; i < n; i++) {
            inv[i][col] = x[i];
        }
    }

    return inv;
}

// Obliczanie warunkowania
double conditionNumber(const vector<vector<double>>& A) {
    double normA = matrixNormInf(A);
    vector<vector<double>> invA = invertMatrix(A);
    double normInvA = matrixNormInf(invA);
    return normA * normInvA;
}

// Obliczanie błędu względnego
double relativeError(const vector<double>& x_numerical, const vector<double>& x_exact) {
    int n = x_numerical.size();
    double errorNorm = 0.0;
    double exactNorm = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = x_numerical[i] - x_exact[i];
        errorNorm += diff * diff;
        exactNorm += x_exact[i] * x_exact[i];
    }

    return sqrt(errorNorm) / sqrt(exactNorm);
}

// Tworzenie macierzy A dla danego epsilon
vector<vector<double>> createMatrix(double epsilon) {
    int n = 4;
    vector<vector<double>> A(n, vector<double>(n, 1.0));

    for (int i = 0; i < n; i++) {
        A[i][i] = 1.0 + epsilon;
    }

    return A;
}

// Tworzenie wektora b dla danego epsilon
vector<double> createVector(double epsilon) {
    return {6.0 + epsilon, 6.0 + 2.0*epsilon, 6.0 + 2.0*epsilon, 6.0 + epsilon};
}

int main() {
    cout << "==========================================================\n";
    cout << "  DODATKOWE ĆWICZENIE - Analiza stabilności numerycznej\n";
    cout << "==========================================================\n";

    // Rozwiązanie analityczne (niezależne od epsilon!)
    vector<double> x_exact = {1.0, 2.0, 2.0, 1.0};

    cout << "\nRozwiązanie analityczne:\n";
    cout << "x = [1, 2, 2, 1]^T (niezależne od epsilon!)\n";

    cout << "\n" << string(80, '=') << "\n";
    cout << setw(15) << "Epsilon"
         << setw(20) << "Cond(A)"
         << setw(15) << "x[0]"
         << setw(15) << "x[1]"
         << setw(15) << "x[2]"
         << setw(15) << "x[3]"
         << setw(15) << "Błąd względny\n";
    cout << string(80, '=') << "\n";

    // Testowanie dla różnych wartości epsilon
    vector<double> epsilons = {1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10};

    for (double eps : epsilons) {
        // Tworzenie macierzy i wektora
        vector<vector<double>> A = createMatrix(eps);
        vector<double> b = createVector(eps);

        // Obliczanie wskaźnika uwarunkowania
        double cond = conditionNumber(A);

        // Rozwiązywanie numeryczne
        vector<vector<double>> A_copy = A;
        vector<int> perm;
        luDecomposition(A_copy, perm);
        vector<double> x_num = solveLU(A_copy, b, perm);

        // Obliczanie błędu względnego
        double error = relativeError(x_num, x_exact);

        // Wyświetlanie wyników
        cout << scientific << setprecision(2);
        cout << setw(15) << eps
             << setw(20) << cond;

        cout << fixed << setprecision(8);
        for (int i = 0; i < 4; i++) {
            cout << setw(15) << x_num[i];
        }

        cout << scientific << setprecision(2);
        cout << setw(15) << error << "\n";
    }

    cout << string(80, '=') << "\n";

    // Szczegółowa analiza dla wybranej wartości epsilon
    cout << "\n\nSZCZEGÓŁOWA ANALIZA dla epsilon = 1e-6:\n";
    cout << string(60, '-') << "\n";

    double eps_detail = 1e-6;
    vector<vector<double>> A_detail = createMatrix(eps_detail);
    vector<double> b_detail = createVector(eps_detail);

    cout << "\nMacierz A:\n";
    for (const auto& row : A_detail) {
        for (double val : row) {
            cout << setw(15) << setprecision(10) << fixed << val << " ";
        }
        cout << "\n";
    }

    cout << "\nWektor b:\n";
    for (double val : b_detail) {
        cout << setw(15) << setprecision(10) << fixed << val << "\n";
    }

    vector<vector<double>> A_copy = A_detail;
    vector<int> perm;
    luDecomposition(A_copy, perm);
    vector<double> x_num = solveLU(A_copy, b_detail, perm);

    cout << "\nRozwiązanie numeryczne:\n";
    for (int i = 0; i < 4; i++) {
        cout << "x[" << i << "] = " << setw(15) << setprecision(10) << x_num[i]
             << "  (dokładnie: " << x_exact[i] << ")\n";
    }

    double error_detail = relativeError(x_num, x_exact);
    double cond_detail = conditionNumber(A_detail);

    cout << "\nWskaźnik uwarunkowania: " << scientific << setprecision(4) << cond_detail << "\n";
    cout << "Błąd względny: " << error_detail << "\n";

    cout << "\n\nWNIOSKI:\n";
    cout << string(60, '-') << "\n";
    cout << "1. Dla większych wartości epsilon (1e-3, 1e-4) wskaźnik uwarunkowania\n";
    cout << "   jest mały, a rozwiązanie numeryczne jest bardzo dokładne.\n\n";
    cout << "2. Wraz ze zmniejszaniem się epsilon, wskaźnik uwarunkowania rośnie\n";
    cout << "   proporcjonalnie do 1/epsilon^2, co prowadzi do:\n";
    cout << "   - Macierz staje się coraz bardziej źle uwarunkowana\n";
    cout << "   - Elementy niemal równe prowadzą do utraty cyfr znaczących\n";
    cout << "   - Błęd względny rozwiązania rośnie\n\n";
    cout << "3. Dla bardzo małych epsilon (1e-9, 1e-10) błędy numeryczne mogą\n";
    cout << "   stać się znaczące, mimo że rozwiązanie analityczne jest proste!\n\n";
    cout << "4. Ten przykład ilustruje, dlaczego ważne jest monitorowanie wskaźnika\n";
    cout << "   uwarunkowania przed rozwiązywaniem układów równań.\n";

    cout << "\n==========================================================\n";

    return 0;
}
