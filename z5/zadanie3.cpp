#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * Program dla Zadania 3 - szczegółowa demonstracja dekompozycji LU
 * krok po kroku z częściowym wyborem elementu podstawowego
 */

void printMatrix(const vector<vector<double>>& matrix, const string& name) {
    cout << name << ":\n";
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < m; j++) {
            cout << setw(10) << setprecision(4) << fixed << matrix[i][j];
        }
        cout << "\n";
    }
}

void printVector(const vector<double>& vec, const string& name) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << setprecision(4) << fixed << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

void luDecompositionVerbose(vector<vector<double>>& A, vector<int>& perm) {
    int n = A.size();
    perm.resize(n);

    for (int i = 0; i < n; i++) {
        perm[i] = i;
    }

    cout << "\n" << string(70, '=') << "\n";
    cout << "DEKOMPOZYCJA LU Z CZĘŚCIOWYM WYBOREM ELEMENTU PODSTAWOWEGO\n";
    cout << string(70, '=') << "\n";

    printMatrix(A, "\nMacierz początkowa A");

    for (int k = 0; k < n - 1; k++) {
        cout << "\n" << string(70, '-') << "\n";
        cout << "KROK " << (k + 1) << ": Eliminacja w kolumnie " << (k + 1) << "\n";
        cout << string(70, '-') << "\n";

        // Częściowy wybór elementu podstawowego
        int maxRow = k;
        double maxVal = abs(A[k][k]);

        cout << "\nSzukanie maksymalnego elementu w kolumnie " << (k + 1)
             << " (wiersze " << (k + 1) << "-" << n << "):\n";

        for (int i = k; i < n; i++) {
            cout << "  Wiersz " << (i + 1) << ": |" << A[i][k] << "| = "
                 << abs(A[i][k]) << "\n";
            if (abs(A[i][k]) > maxVal) {
                maxVal = abs(A[i][k]);
                maxRow = i;
            }
        }

        cout << "\nMaksymalny element: |" << A[maxRow][k] << "| = " << maxVal
             << " w wierszu " << (maxRow + 1) << "\n";

        // Zamiana wierszy
        if (maxRow != k) {
            cout << "Zamiana wierszy: " << (k + 1) << " ↔ " << (maxRow + 1) << "\n";
            swap(A[k], A[maxRow]);
            swap(perm[k], perm[maxRow]);

            printMatrix(A, "\nMacierz po zamianie");
        } else {
            cout << "Brak konieczności zamiany wierszy.\n";
        }

        if (abs(A[k][k]) < 1e-15) {
            cout << "\nOSTRZEŻENIE: Element główny bliski zeru!\n";
            continue;
        }

        // Eliminacja
        cout << "\nEliminacja pod pozycją (" << (k + 1) << "," << (k + 1) << "):\n";

        for (int i = k + 1; i < n; i++) {
            double multiplier = A[i][k] / A[k][k];
            cout << "  m[" << (i + 1) << "," << (k + 1) << "] = "
                 << A[i][k] << " / " << A[k][k] << " = " << multiplier << "\n";

            A[i][k] = multiplier;  // Zachowujemy mnożnik w L

            for (int j = k + 1; j < n; j++) {
                A[i][j] -= multiplier * A[k][j];
            }
        }

        printMatrix(A, "\nMacierz po eliminacji");
    }

    cout << "\n" << string(70, '=') << "\n";
    cout << "DEKOMPOZYCJA ZAKOŃCZONA\n";
    cout << string(70, '=') << "\n";
}

vector<vector<double>> extractL(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
        for (int j = 0; j < i; j++) {
            L[i][j] = A[i][j];
        }
    }
    return L;
}

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

vector<double> solveLUVerbose(const vector<vector<double>>& A, const vector<double>& b_orig,
                               const vector<int>& perm) {
    int n = A.size();
    vector<double> x(n);

    cout << "\n" << string(70, '=') << "\n";
    cout << "ROZWIĄZYWANIE UKŁADU RÓWNAŃ\n";
    cout << string(70, '=') << "\n";

    // Permutacja wektora b
    vector<double> b(n);
    cout << "\nStosowanie permutacji do wektora b:\n";
    for (int i = 0; i < n; i++) {
        b[i] = b_orig[perm[i]];
        cout << "b_perm[" << (i + 1) << "] = b_orig[" << (perm[i] + 1) << "] = "
             << b[i] << "\n";
    }
    printVector(b, "\nWektor b po permutacji (Pb)");

    // Krok 1: Ly = Pb
    cout << "\nKrok 1: Rozwiązanie Ly = Pb (podstawienie w przód)\n";
    cout << "gdzie L ma jedynki na diagonali\n\n";

    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        cout << "y[" << (i + 1) << "] = " << b[i];

        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
            cout << " - (" << A[i][j] << ") * (" << y[j] << ")";
        }

        cout << " = " << y[i] << "\n";
    }

    printVector(y, "\nWektor y");

    // Krok 2: Ux = y
    cout << "\nKrok 2: Rozwiązanie Ux = y (podstawienie wstecz)\n\n";

    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        cout << "x[" << (i + 1) << "] = (" << y[i];

        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
            cout << " - " << A[i][j] << " * " << x[j];
        }

        cout << ") / " << A[i][i] << " = " << (x[i] / A[i][i]) << "\n";
        x[i] /= A[i][i];
    }

    cout << "\n" << string(70, '=') << "\n";

    return x;
}

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
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                         ZADANIE 3                                  ║\n";
    cout << "║  Dekompozycja LU z częściowym wyborem elementu podstawowego        ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════╝\n";

    // Dane z zadania 3
    vector<vector<double>> A_original = {
        {1, 2, 2, 1},
        {2, 4, 4, 1},
        {2, 2, 2, 1},
        {1, 1, 2, 1}
    };

    vector<double> b_original = {1, 2, 3, 4};

    // Kopie do obliczeń
    vector<vector<double>> A = A_original;
    vector<int> perm;

    // Wykonanie dekompozycji
    luDecompositionVerbose(A, perm);

    // Wyodrębnienie L i U
    vector<vector<double>> L = extractL(A);
    vector<vector<double>> U = extractU(A);

    cout << "\nWektor permutacji: [";
    for (size_t i = 0; i < perm.size(); i++) {
        cout << perm[i];
        if (i < perm.size() - 1) cout << ", ";
    }
    cout << "]\n";

    printMatrix(L, "\nMacierz L (dolna trójkątna z jedynkami na diagonali)");
    printMatrix(U, "\nMacierz U (górna trójkątna)");

    // Rozwiązanie układu
    vector<double> x = solveLUVerbose(A, b_original, perm);

    printVector(x, "\n\nROZWIĄZANIE x");

    // Weryfikacja
    cout << "\n" << string(70, '=') << "\n";
    cout << "WERYFIKACJA ROZWIĄZANIA\n";
    cout << string(70, '=') << "\n";

    vector<double> b_check = multiplyMatrixVector(A_original, x);

    printVector(b_original, "\nWektor b (oczekiwany)");
    printVector(b_check, "Wektor A*x (obliczony)");

    double error = 0.0;
    for (size_t i = 0; i < b_original.size(); i++) {
        error += (b_original[i] - b_check[i]) * (b_original[i] - b_check[i]);
    }
    error = sqrt(error);

    cout << "\nBłąd ||b - A*x||_2 = " << scientific << setprecision(6) << error << "\n";

    if (error < 1e-10) {
        cout << "\n✓ Rozwiązanie jest POPRAWNE!\n";
    } else {
        cout << "\n⚠ UWAGA: Wykryto błąd numeryczny!\n";
    }

    cout << "\n" << string(70, '=') << "\n\n";

    return 0;
}
