#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Algorytm Thomasa dla rozwiązywania układów równań z macierzą trójdiagonalną
 *
 * Macierz trójdiagonalna jest reprezentowana przez trzy wektory:
 * - a[i] - poddiagonala (elementy poniżej głównej diagonali)
 * - b[i] - diagonala główna
 * - c[i] - naddiagonala (elementy powyżej głównej diagonali)
 *
 * Układ równań: Ax = d
 *
 * gdzie A jest macierzą trójdiagonalną n×n:
 * | b[0]  c[0]   0     0    ...   0   |   | x[0] |   | d[0] |
 * | a[1]  b[1]  c[1]   0    ...   0   |   | x[1] |   | d[1] |
 * |  0    a[2]  b[2]  c[2]  ...   0   | × | x[2] | = | d[2] |
 * | ...   ...   ...   ...   ...  ...  |   | ...  |   | ...  |
 * |  0     0     0    ... a[n-1] b[n-1]|   |x[n-1]|   |d[n-1]|
 */

/**
 * Faza 1: Forward elimination (eliminacja w przód)
 * Modyfikuje współczynniki macierzy A
 *
 * Parametry:
 * - a: poddiagonala (indeksy od 1 do n-1)
 * - b: diagonala główna (indeksy od 0 do n-1) - będzie zmodyfikowana
 * - c: naddiagonala (indeksy od 0 do n-2) - będzie zmodyfikowana
 * - n: rozmiar macierzy
 */
void thomas_forward_elimination(vector<double>& a, vector<double>& b, vector<double>& c, int n) {
    // Modyfikacja współczynników c i b
    for (int i = 1; i < n; i++) {
        double m = a[i] / b[i-1];  // mnożnik eliminacji
        b[i] = b[i] - m * c[i-1];   // modyfikacja elementu diagonalnego
        // c[i] pozostaje bez zmian (w uproszczonej wersji)
    }
}

/**
 * Faza 2: Forward elimination dla wektora prawych stron i back substitution
 * Operuje na wektorze d wykorzystując zmodyfikowaną macierz A
 *
 * Parametry:
 * - a: poddiagonala (oryginalna)
 * - b: diagonala główna (zmodyfikowana przez forward_elimination)
 * - c: naddiagonala (oryginalna)
 * - d: wektor prawych stron (będzie zmodyfikowany, a następnie zawierać będzie rozwiązanie)
 * - n: rozmiar wektora
 */
void thomas_solve(const vector<double>& a, const vector<double>& b,
                  const vector<double>& c, vector<double>& d, int n) {
    // Forward elimination dla wektora d
    for (int i = 1; i < n; i++) {
        double m = a[i] / b[i-1];
        d[i] = d[i] - m * d[i-1];
    }

    // Back substitution (podstawianie wstecz)
    d[n-1] = d[n-1] / b[n-1];  // ostatni element

    for (int i = n-2; i >= 0; i--) {
        d[i] = (d[i] - c[i] * d[i+1]) / b[i];
    }
    // Wynik jest teraz w wektorze d
}

/**
 * Funkcja pomocnicza do wyświetlania wektora
 */
void print_vector(const string& name, const vector<double>& vec) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << setw(10) << setprecision(4) << fixed << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

/**
 * Funkcja pomocnicza do wyświetlania macierzy trójdiagonalnej w pełnej formie
 */
void print_tridiagonal_matrix(const vector<double>& a, const vector<double>& b,
                               const vector<double>& c, int n) {
    cout << "Macierz A (pełna reprezentacja):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << setw(10) << setprecision(4) << fixed << b[i];
            } else if (j == i + 1 && i < n - 1) {
                cout << setw(10) << setprecision(4) << fixed << c[i];
            } else if (j == i - 1 && i > 0) {
                cout << setw(10) << setprecision(4) << fixed << a[i];
            } else {
                cout << setw(10) << setprecision(4) << fixed << 0.0;
            }
        }
        cout << endl;
    }
}

/**
 * Funkcja weryfikująca rozwiązanie
 */
void verify_solution(const vector<double>& a, const vector<double>& b,
                     const vector<double>& c, const vector<double>& x,
                     const vector<double>& d_original, int n) {
    cout << "\n=== Weryfikacja rozwiązania ===" << endl;
    vector<double> d_calculated(n);

    // Obliczenie A*x
    d_calculated[0] = b[0] * x[0] + c[0] * x[1];
    for (int i = 1; i < n - 1; i++) {
        d_calculated[i] = a[i] * x[i-1] + b[i] * x[i] + c[i] * x[i+1];
    }
    d_calculated[n-1] = a[n-1] * x[n-2] + b[n-1] * x[n-1];

    // Porównanie z oryginalnym wektorem d
    double max_error = 0.0;
    cout << "i\td_oryginalne\tA*x\t\tBłąd" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        double error = abs(d_calculated[i] - d_original[i]);
        max_error = max(max_error, error);
        cout << i << "\t" << setprecision(6) << fixed
             << d_original[i] << "\t\t"
             << d_calculated[i] << "\t"
             << scientific << error << endl;
    }
    cout << "\nMaksymalny błąd: " << scientific << max_error << endl;
}

int main() {
    cout << "=== Algorytm Thomasa dla macierzy trójdiagonalnej ===" << endl;
    cout << "\nPrzykład z zadania:" << endl;

    // Dane z zadania
    // Macierz A (5×5):
    // | 100   -1    0    0    0  |
    // |   2  200   -3    0    0  |
    // |   0    4  300    5    0  |
    // |   0    0   -6  200   -7  |
    // |   0    0    0   -8  100  |

    int n = 5;

    // Poddiagonala (a[i] dla i = 1..n-1)
    vector<double> a = {0, 2, 4, -6, -8};  // a[0] nie jest używane

    // Diagonala główna (b[i] dla i = 0..n-1)
    vector<double> b = {100, 200, 300, 200, 100};

    // Naddiagonala (c[i] dla i = 0..n-2)
    vector<double> c = {-1, -3, 5, -7, 0};  // c[n-1] nie jest używane

    // Wektor prawych stron
    vector<double> d = {199, 195, 929, 954, 360};

    // Kopia oryginalnych wartości do weryfikacji
    vector<double> a_orig = a;
    vector<double> b_orig = b;
    vector<double> c_orig = c;
    vector<double> d_orig = d;

    // Wyświetlenie danych wejściowych
    cout << "\n--- Dane wejściowe ---" << endl;
    print_tridiagonal_matrix(a, b, c, n);
    cout << endl;
    print_vector("Wektor b (prawe strony)", d);

    // FAZA 1: Forward elimination dla macierzy A
    cout << "\n--- FAZA 1: Forward elimination ---" << endl;
    thomas_forward_elimination(a, b, c, n);

    cout << "\nZmodyfikowane współczynniki:" << endl;
    print_vector("b' (diagonala główna)", b);

    // FAZA 2: Rozwiązanie układu (operacje na wektorze d)
    cout << "\n--- FAZA 2: Rozwiązanie układu ---" << endl;
    thomas_solve(a_orig, b, c, d, n);

    // Wyświetlenie rozwiązania
    cout << "\n=== ROZWIĄZANIE ===" << endl;
    print_vector("x", d);

    // Weryfikacja rozwiązania
    verify_solution(a_orig, b_orig, c_orig, d, d_orig, n);

    // Dodatkowy prosty przykład
    cout << "\n\n=== Prosty przykład testowy ===" << endl;
    cout << "\nUkład równań:" << endl;
    cout << "2x1 - x2 = 1" << endl;
    cout << "-x1 + 2x2 - x3 = 0" << endl;
    cout << "-x2 + 2x3 = 1" << endl;

    n = 3;
    vector<double> a2 = {0, -1, -1};
    vector<double> b2 = {2, 2, 2};
    vector<double> c2 = {-1, -1, 0};
    vector<double> d2 = {1, 0, 1};

    vector<double> a2_orig = a2;
    vector<double> b2_orig = b2;
    vector<double> c2_orig = c2;
    vector<double> d2_orig = d2;

    cout << "\n--- Dane wejściowe ---" << endl;
    print_tridiagonal_matrix(a2, b2, c2, n);
    cout << endl;
    print_vector("Wektor b (prawe strony)", d2);

    thomas_forward_elimination(a2, b2, c2, n);
    thomas_solve(a2_orig, b2, c2, d2, n);

    cout << "\n=== ROZWIĄZANIE ===" << endl;
    print_vector("x", d2);

    verify_solution(a2_orig, b2_orig, c2_orig, d2, d2_orig, n);

    return 0;
}
