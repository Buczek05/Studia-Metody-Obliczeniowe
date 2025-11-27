#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// ========================================
// ALGORYTMY INTERPOLACJI - IMPLEMENTACJE
// ========================================

// -------------------- ZADANIE 1 --------------------
// Interpolacja Lagrange'a

// Funkcja pomocnicza: wielomian bazowy Lagrange'a L_i(x)
double lagrange_basis(double x, int i, const vector<double>& nodes) {
    double result = 1.0;
    int n = nodes.size();

    for (int j = 0; j < n; j++) {
        if (j != i) {
            result *= (x - nodes[j]) / (nodes[i] - nodes[j]);
        }
    }

    return result;
}

// Interpolacja Lagrange'a w bazie Lagrange'a
double lagrange_interpolation(double x, const vector<double>& nodes, const vector<double>& values) {
    double result = 0.0;
    int n = nodes.size();

    for (int i = 0; i < n; i++) {
        result += values[i] * lagrange_basis(x, i, nodes);
    }

    return result;
}

// Obliczenie ilorazów różnicowych (dla bazy Newtona)
vector<vector<double>> divided_differences(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> dd(n, vector<double>(n, 0.0));

    // Pierwsza kolumna to wartości funkcji
    for (int i = 0; i < n; i++) {
        dd[i][0] = y[i];
    }

    // Obliczanie kolejnych kolumn
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (x[i+j] - x[i]);
        }
    }

    return dd;
}

// Interpolacja w bazie Newtona
double newton_interpolation(double x, const vector<double>& nodes, const vector<vector<double>>& dd) {
    int n = nodes.size();
    double result = dd[0][0];
    double product = 1.0;

    for (int i = 1; i < n; i++) {
        product *= (x - nodes[i-1]);
        result += dd[0][i] * product;
    }

    return result;
}

// Schemat Hornera dla wielomianu Newtona
double newton_horner(double x, const vector<double>& nodes, const vector<vector<double>>& dd) {
    int n = nodes.size();
    double result = dd[0][n-1];

    for (int i = n - 2; i >= 0; i--) {
        result = result * (x - nodes[i]) + dd[0][i];
    }

    return result;
}

// Wyświetlenie tabeli ilorazów różnicowych
void print_divided_differences_table(const vector<double>& x, const vector<vector<double>>& dd) {
    int n = x.size();

    cout << "\nTabela ilorazów różnicowych:" << endl;
    cout << setw(10) << "x[i]" << " | ";

    for (int j = 0; j < n; j++) {
        cout << setw(15) << "f[...," << j << "]";
    }
    cout << endl;
    cout << string(10 + 3 + n * 20, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << fixed << setprecision(4) << x[i] << " | ";
        for (int j = 0; j <= i; j++) {
            cout << setw(15) << scientific << setprecision(6) << dd[i-j][j] << "     ";
        }
        cout << endl;
    }
}

// -------------------- ZADANIE 2 --------------------
// Algorytm Neville'a

double neville_algorithm(double x, const vector<double>& nodes, const vector<double>& values) {
    int n = nodes.size();
    vector<double> P = values; // Kopiujemy wartości

    // Schemat Neville'a
    for (int k = 1; k < n; k++) {
        for (int i = n - 1; i >= k; i--) {
            P[i] = ((x - nodes[i-k]) * P[i] - (x - nodes[i]) * P[i-1]) / (nodes[i] - nodes[i-k]);
        }
    }

    return P[n-1];
}

// Algorytm Neville'a z wyświetleniem tabeli
double neville_with_table(double x, const vector<double>& nodes, const vector<double>& values) {
    int n = nodes.size();
    vector<vector<double>> P(n, vector<double>(n, 0.0));

    // Pierwsza kolumna to wartości funkcji
    for (int i = 0; i < n; i++) {
        P[i][0] = values[i];
    }

    // Wypełnianie tabeli według schematu Neville'a
    for (int k = 1; k < n; k++) {
        for (int i = k; i < n; i++) {
            P[i][k] = ((x - nodes[i-k]) * P[i][k-1] - (x - nodes[i]) * P[i-1][k-1])
                      / (nodes[i] - nodes[i-k]);
        }
    }

    // Wyświetlenie tabeli
    cout << "\nTabela algorytmu Neville'a dla x = " << x << ":" << endl;
    cout << setw(8) << "i" << setw(12) << "x[i]" << setw(12) << "f[i]";
    for (int k = 1; k < n; k++) {
        cout << setw(15) << "P[i," << k << "]";
    }
    cout << endl;
    cout << string(8 + 12 + 12 + n * 15, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(8) << i
             << setw(12) << fixed << setprecision(4) << nodes[i]
             << setw(12) << values[i];
        for (int k = 1; k <= i; k++) {
            cout << setw(15) << setprecision(6) << P[i][k];
        }
        cout << endl;
    }

    return P[n-1][n-1];
}

// -------------------- ZADANIE 3 --------------------
// Interpolacja Hermite'a

// Interpolacja Hermite'a metodą ilorazów różnicowych
double hermite_interpolation(double x,
                             const vector<double>& nodes,
                             const vector<double>& values,
                             const vector<double>& derivatives) {
    int n = nodes.size();
    int m = 2 * n; // Podwojona liczba węzłów (wartości + pochodne)

    // Tworzymy rozszerzoną tablicę węzłów (każdy węzeł podwojony)
    vector<double> z(m);
    vector<double> Q(m);

    for (int i = 0; i < n; i++) {
        z[2*i] = nodes[i];
        z[2*i + 1] = nodes[i];
        Q[2*i] = values[i];
        Q[2*i + 1] = values[i];
    }

    // Obliczanie ilorazów różnicowych uogólnionych
    for (int i = 1; i < m; i++) {
        for (int j = m - 1; j >= i; j--) {
            if (z[j] == z[j-i]) {
                // Dla pokrywających się węzłów używamy pochodnej
                if (i == 1) {
                    Q[j] = derivatives[j/2];
                } else {
                    // Dla wyższych rzędów normalna formuła
                    Q[j] = (Q[j] - Q[j-1]) / (z[j] - z[j-i]);
                }
            } else {
                Q[j] = (Q[j] - Q[j-1]) / (z[j] - z[j-i]);
            }
        }
    }

    // Obliczanie wartości wielomianu
    double result = Q[m-1];
    for (int i = m - 2; i >= 0; i--) {
        result = result * (x - z[i]) + Q[i];
    }

    return result;
}

// ========================================
// PRZYKŁADY UŻYCIA
// ========================================

void example_zadanie_1() {
    cout << "\n========================================" << endl;
    cout << "ZADANIE 1: Interpolacja Lagrange'a" << endl;
    cout << "========================================\n" << endl;

    // Dane z zadania
    vector<double> nodes = {4.0, -6.0, -5.0, 1.0};
    vector<double> values = {2.0, -8.0, 4.0, 10.0};

    cout << "Punkty interpolacji:" << endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        cout << "  (" << nodes[i] << ", " << values[i] << ")" << endl;
    }

    // (a) Baza Lagrange'a
    cout << "\n(a) Interpolacja w bazie Lagrange'a:" << endl;
    double x_test = 0.0;
    double y_lagrange = lagrange_interpolation(x_test, nodes, values);
    cout << "  P(" << x_test << ") = " << y_lagrange << endl;

    // (b) Baza Newtona
    cout << "\n(b) Interpolacja w bazie Newtona:" << endl;
    vector<vector<double>> dd = divided_differences(nodes, values);
    print_divided_differences_table(nodes, dd);

    cout << "\nWspółczynniki wielomianu Newtona:" << endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        cout << "  c[" << i << "] = " << dd[0][i] << endl;
    }

    double y_newton = newton_interpolation(x_test, nodes, dd);
    cout << "\n  P(" << x_test << ") = " << y_newton << endl;

    cout << "\nWeryfikacja (Horner): P(" << x_test << ") = "
         << newton_horner(x_test, nodes, dd) << endl;
}

void example_zadanie_2() {
    cout << "\n========================================" << endl;
    cout << "ZADANIE 2: Algorytm Neville'a" << endl;
    cout << "========================================\n" << endl;

    vector<double> nodes = {-1.0, 2.0, -3.0};
    vector<double> values = {-1.0, 2.0, 3.0};
    double x = 1.0;

    cout << "Punkty interpolacji:" << endl;
    for (size_t i = 0; i < nodes.size(); i++) {
        cout << "  (" << nodes[i] << ", " << values[i] << ")" << endl;
    }
    cout << "\nObliczanie wartości w x = " << x << endl;

    double result = neville_with_table(x, nodes, values);

    cout << "\nWynik: P(" << x << ") = " << fixed << setprecision(6) << result << endl;
}

void example_zadanie_3() {
    cout << "\n========================================" << endl;
    cout << "ZADANIE 3: Interpolacja Hermite'a" << endl;
    cout << "========================================\n" << endl;

    // Warunki z zadania:
    // p(0) = 0, p'(0) = 1, p''(0) = 2
    // p(1) = 3, p'(1) = 4

    // Dla prostej implementacji: używamy tylko wartości i pierwszych pochodnych
    vector<double> nodes = {0.0, 1.0};
    vector<double> values = {0.0, 3.0};
    vector<double> derivatives = {1.0, 4.0};

    cout << "Warunki interpolacji Hermite'a:" << endl;
    cout << "  p(0) = 0, p'(0) = 1" << endl;
    cout << "  p(1) = 3, p'(1) = 4" << endl;
    cout << "\nUwaga: Ta implementacja nie uwzględnia p''(0) = 2" << endl;
    cout << "Pełna implementacja wymaga wielomianu stopnia 4.\n" << endl;

    // Test interpolacji
    double x_test = 0.5;
    double y_hermite = hermite_interpolation(x_test, nodes, values, derivatives);

    cout << "Wartość wielomianu Hermite'a:" << endl;
    cout << "  p(" << x_test << ") = " << y_hermite << endl;

    // Dla pełnego rozwiązania - wyświetlamy analityczną postać
    cout << "\nRozwiązanie analityczne (z p''(0) = 2):" << endl;
    cout << "  p(x) = x + x² + 3x³ - 2x⁴" << endl;

    // Obliczenie wartości z wzoru analitycznego
    double p_analytical = x_test + pow(x_test, 2) + 3*pow(x_test, 3) - 2*pow(x_test, 4);
    cout << "  p(" << x_test << ") = " << p_analytical << " (wzór analityczny)" << endl;
}

// ========================================
// FUNKCJA GŁÓWNA
// ========================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════╗\n";
    cout << "║   ALGORYTMY INTERPOLACJI WIELOMIANOWEJ - ZADANIA 1-3   ║\n";
    cout << "╚════════════════════════════════════════════════════════╝\n";

    example_zadanie_1();
    example_zadanie_2();
    example_zadanie_3();

    cout << "\n========================================" << endl;
    cout << "Koniec demonstracji" << endl;
    cout << "========================================\n" << endl;

    return 0;
}
