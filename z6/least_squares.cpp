#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Program rozwiązujący nad-określone układy równań
 * metodą najmniejszych kwadratów
 */

/**
 * Wyświetlanie macierzy
 */
void print_matrix(const string& name, const vector<vector<double>>& mat) {
    cout << name << ":" << endl;
    for (const auto& row : mat) {
        for (double val : row) {
            cout << setw(12) << setprecision(4) << fixed << val;
        }
        cout << endl;
    }
}

/**
 * Wyświetlanie wektora
 */
void print_vector(const string& name, const vector<double>& vec) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << setw(10) << setprecision(6) << fixed << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * Transpozycja macierzy
 */
vector<vector<double>> transpose(const vector<vector<double>>& A) {
    int m = A.size();
    int n = A[0].size();
    vector<vector<double>> AT(n, vector<double>(m));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            AT[j][i] = A[i][j];
        }
    }
    return AT;
}

/**
 * Mnożenie macierzy: C = A * B
 */
vector<vector<double>> matrix_multiply(const vector<vector<double>>& A,
                                       const vector<vector<double>>& B) {
    int m = A.size();
    int n = B[0].size();
    int k = B.size();

    vector<vector<double>> C(m, vector<double>(n, 0.0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int p = 0; p < k; p++) {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }
    return C;
}

/**
 * Mnożenie macierzy przez wektor: result = A * v
 */
vector<double> matrix_vector_multiply(const vector<vector<double>>& A,
                                      const vector<double>& v) {
    int m = A.size();
    int n = v.size();
    vector<double> result(m, 0.0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * v[j];
        }
    }
    return result;
}

/**
 * Rozwiązanie układu równań metodą eliminacji Gaussa
 * dla macierzy kwadratowej n×n
 */
vector<double> gauss_elimination(vector<vector<double>> A, vector<double> b) {
    int n = A.size();

    // Forward elimination
    for (int k = 0; k < n - 1; k++) {
        // Częściowe pivotowanie
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > abs(A[max_row][k])) {
                max_row = i;
            }
        }
        swap(A[k], A[max_row]);
        swap(b[k], b[max_row]);

        // Eliminacja
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // Back substitution
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

/**
 * Rozwiązanie nad-określonego układu równań metodą najmniejszych kwadratów
 * Minimalizuje ||Ax - b||^2
 */
vector<double> least_squares_solve(const vector<vector<double>>& A,
                                   const vector<double>& b) {
    cout << "\n=== Metoda najmniejszych kwadratów ===" << endl;

    // Krok 1: Obliczenie A^T
    cout << "\nKrok 1: Transpozycja macierzy A" << endl;
    vector<vector<double>> AT = transpose(A);
    print_matrix("A^T", AT);

    // Krok 2: Obliczenie A^T * A
    cout << "\nKrok 2: Obliczenie A^T * A" << endl;
    vector<vector<double>> ATA = matrix_multiply(AT, A);
    print_matrix("A^T * A", ATA);

    // Krok 3: Obliczenie A^T * b
    cout << "\nKrok 3: Obliczenie A^T * b" << endl;
    vector<double> ATb = matrix_vector_multiply(AT, b);
    print_vector("A^T * b", ATb);

    // Krok 4: Rozwiązanie układu równań normalnych: (A^T * A) * x = A^T * b
    cout << "\nKrok 4: Rozwiązanie układu równań normalnych" << endl;
    cout << "Układ: (A^T * A) * x = A^T * b" << endl;
    vector<double> x = gauss_elimination(ATA, ATb);

    return x;
}

/**
 * Obliczenie normy residuum ||Ax - b||
 */
double compute_residuum(const vector<vector<double>>& A,
                       const vector<double>& x,
                       const vector<double>& b) {
    vector<double> Ax = matrix_vector_multiply(A, x);
    double norm = 0.0;

    for (size_t i = 0; i < b.size(); i++) {
        double diff = Ax[i] - b[i];
        norm += diff * diff;
    }

    return sqrt(norm);
}

int main() {
    cout << "=== Rozwiązywanie nad-określonych układów równań ===" << endl;
    cout << "=== Metoda najmniejszych kwadratów ===" << endl;

    // Zadanie z zajęć:
    // x + 2y = 1
    // 3x + 4y = 2
    // 5x + 6y = 3

    cout << "\n--- Zadanie 1 ---" << endl;
    cout << "Układ równań:" << endl;
    cout << "x + 2y = 1" << endl;
    cout << "3x + 4y = 2" << endl;
    cout << "5x + 6y = 3" << endl;

    vector<vector<double>> A = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    vector<double> b = {1, 2, 3};

    cout << "\nMacierz A (3×2):" << endl;
    print_matrix("A", A);

    cout << "\nWektor b:" << endl;
    print_vector("b", b);

    // Rozwiązanie metodą najmniejszych kwadratów
    vector<double> x = least_squares_solve(A, b);

    cout << "\n=== ROZWIĄZANIE ===" << endl;
    print_vector("x", x);
    cout << "\nInterpretacja: x = " << x[0] << ", y = " << x[1] << endl;

    // Weryfikacja
    cout << "\n=== Weryfikacja ===" << endl;
    cout << "Podstawienie rozwiązania do oryginalnych równań:" << endl;
    vector<double> Ax = matrix_vector_multiply(A, x);

    for (size_t i = 0; i < Ax.size(); i++) {
        cout << "Równanie " << i + 1 << ": ";
        if (i == 0) cout << x[0] << " + 2*" << x[1];
        else if (i == 1) cout << "3*" << x[0] << " + 4*" << x[1];
        else cout << "5*" << x[0] << " + 6*" << x[1];
        cout << " = " << Ax[i];
        cout << " (oczekiwane: " << b[i] << ")";
        if (abs(Ax[i] - b[i]) < 1e-10) {
            cout << " ✓";
        }
        cout << endl;
    }

    double residuum = compute_residuum(A, x, b);
    cout << "\nNorma residuum ||Ax - b||: " << scientific << residuum << endl;

    // Dodatkowy przykład - rzeczywiście nad-określony układ
    cout << "\n\n--- Przykład 2: Aproksymacja liniowa ---" << endl;
    cout << "Dopasowanie linii y = ax + b do punktów:" << endl;
    cout << "(0, 1), (1, 2), (2, 4), (3, 4), (4, 6)" << endl;

    // Macierz A: każdy wiersz to [x_i, 1]
    vector<vector<double>> A2 = {
        {0, 1},
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 1}
    };

    vector<double> b2 = {1, 2, 4, 4, 6};

    print_matrix("\nMacierz A", A2);
    print_vector("Wektor b (wartości y)", b2);

    vector<double> x2 = least_squares_solve(A2, b2);

    cout << "\n=== ROZWIĄZANIE ===" << endl;
    cout << "Najlepsza linia w sensie najmniejszych kwadratów:" << endl;
    cout << "y = " << x2[0] << "*x + " << x2[1] << endl;

    cout << "\nPorównanie wartości:" << endl;
    cout << "x\ty_rzeczywiste\ty_aproksymowane\tBłąd" << endl;
    cout << "---------------------------------------------------" << endl;

    vector<double> y_approx = matrix_vector_multiply(A2, x2);
    for (size_t i = 0; i < b2.size(); i++) {
        cout << fixed << setprecision(1) << i << "\t"
             << setprecision(4) << b2[i] << "\t\t"
             << y_approx[i] << "\t\t"
             << abs(y_approx[i] - b2[i]) << endl;
    }

    residuum = compute_residuum(A2, x2, b2);
    cout << "\nNorma residuum: " << scientific << residuum << endl;

    return 0;
}
