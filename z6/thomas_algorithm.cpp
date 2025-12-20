#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


void thomas_forward_elimination(vector<double>& a, vector<double>& b, vector<double>& c, int n) {
    // Modyfikacja współczynników c i b
    for (int i = 1; i < n; i++) {
        double m = a[i] / b[i-1];  // mnożnik eliminacji
        b[i] = b[i] - m * c[i-1];   // modyfikacja elementu diagonalnego
        // c[i] pozostaje bez zmian (w uproszczonej wersji)
    }
}

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

void print_vector(const string& name, const vector<double>& vec) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << setw(10) << setprecision(4) << fixed << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

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

    return 0;
}
