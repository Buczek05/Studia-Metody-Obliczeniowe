/**
 * Demonstracja algorytmu Thomasa (TDMA)
 *
 * Ten program pokazuje działanie algorytmu Thomasa na prostym przykładzie
 * układu równań z macierzą trójdiagonalną.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * Algorytm Thomasa dla układu trójdiagonalnego
 *
 * Rozwiązuje układ: A*x = d, gdzie A jest macierzą trójdiagonalną:
 *
 *   [b₀ c₀  0  ...  0 ]   [x₀]   [d₀]
 *   [a₁ b₁ c₁  ...  0 ]   [x₁]   [d₁]
 *   [0  a₂ b₂  ...  0 ] * [x₂] = [d₂]
 *   [... ... ... ... cₙ]   [...] [...]
 *   [0  ...  0  aₙ bₙ]   [xₙ]   [dₙ]
 *
 * @param a - diagonala dolna (a₁, a₂, ..., aₙ)
 * @param b - diagonala główna (b₀, b₁, ..., bₙ)
 * @param c - diagonala górna (c₀, c₁, ..., cₙ₋₁)
 * @param d - prawa strona (d₀, d₁, ..., dₙ)
 * @return wektor rozwiązań x
 */
vector<double> thomasAlgorithm(vector<double> a, vector<double> b,
                               vector<double> c, vector<double> d) {
    int n = d.size();
    vector<double> c_star(n, 0.0);
    vector<double> d_star(n, 0.0);
    vector<double> x(n, 0.0);

    cout << "\n=== Forward Elimination ===\n";

    // Krok 1: Forward elimination
    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    cout << "i=0: c'[0] = " << c_star[0] << ", d'[0] = " << d_star[0] << "\n";

    for (int i = 1; i < n; i++) {
        double denom = b[i] - a[i] * c_star[i-1];

        if (i < n - 1) {
            c_star[i] = c[i] / denom;
        }
        d_star[i] = (d[i] - a[i] * d_star[i-1]) / denom;

        cout << "i=" << i << ": denom = " << denom
             << ", d'[" << i << "] = " << d_star[i];
        if (i < n - 1) {
            cout << ", c'[" << i << "] = " << c_star[i];
        }
        cout << "\n";
    }

    cout << "\n=== Back Substitution ===\n";

    // Krok 2: Back substitution
    x[n-1] = d_star[n-1];
    cout << "x[" << (n-1) << "] = " << x[n-1] << "\n";

    for (int i = n - 2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i+1];
        cout << "x[" << i << "] = " << x[i] << "\n";
    }

    return x;
}

/**
 * Wyświetla macierz trójdiagonalną
 */
void printTridiagonalMatrix(const vector<double>& a, const vector<double>& b,
                           const vector<double>& c) {
    int n = b.size();
    cout << "\nMacierz trójdiagonalna A:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << setw(10) << fixed << setprecision(4) << b[i];
            } else if (i == j - 1 && j < n) {
                cout << setw(10) << fixed << setprecision(4) << c[i];
            } else if (i == j + 1) {
                cout << setw(10) << fixed << setprecision(4) << a[i];
            } else {
                cout << setw(10) << "0.0000";
            }
        }
        cout << "\n";
    }
}

/**
 * Weryfikuje rozwiązanie: A*x = d
 */
void verifySolution(const vector<double>& a, const vector<double>& b,
                    const vector<double>& c, const vector<double>& d,
                    const vector<double>& x) {
    int n = x.size();
    cout << "\n=== Weryfikacja: A*x = d ===\n";
    cout << setw(5) << "i" << setw(15) << "A*x" << setw(15) << "d"
         << setw(15) << "błąd\n";
    cout << string(50, '-') << "\n";

    double max_error = 0.0;

    for (int i = 0; i < n; i++) {
        double result = b[i] * x[i];

        if (i > 0) {
            result += a[i] * x[i-1];
        }
        if (i < n - 1) {
            result += c[i] * x[i+1];
        }

        double error = abs(result - d[i]);
        max_error = max(max_error, error);

        cout << setw(5) << i
             << setw(15) << scientific << setprecision(6) << result
             << setw(15) << d[i]
             << setw(15) << error << "\n";
    }

    cout << "\nMaksymalny błąd: " << scientific << max_error << "\n";
}

int main() {
    cout << "=== Demonstracja algorytmu Thomasa (TDMA) ===\n";
    cout << "Rozwiązywanie układu równań z macierzą trójdiagonalną\n";

    // Przykład 1: Prosty układ 4x4
    cout << "\n\n>>> PRZYKŁAD 1: Prosty układ 4x4 <<<\n";

    // Układ:
    // 2x₀ + 1x₁           = 5
    // 1x₀ + 2x₁ + 1x₂     = 6
    //       1x₁ + 2x₂ + 1x₃ = 7
    //             1x₂ + 2x₃ = 8

    vector<double> a1 = {0, 1, 1, 1};  // diagonala dolna
    vector<double> b1 = {2, 2, 2, 2};  // diagonala główna
    vector<double> c1 = {1, 1, 1, 0};  // diagonala górna
    vector<double> d1 = {5, 6, 7, 8};  // prawa strona

    printTridiagonalMatrix(a1, b1, c1);

    cout << "\nWektor prawej strony d:\n";
    for (size_t i = 0; i < d1.size(); i++) {
        cout << "d[" << i << "] = " << d1[i] << "\n";
    }

    vector<double> x1 = thomasAlgorithm(a1, b1, c1, d1);

    cout << "\n=== Rozwiązanie ===\n";
    for (size_t i = 0; i < x1.size(); i++) {
        cout << "x[" << i << "] = " << fixed << setprecision(8) << x1[i] << "\n";
    }

    verifySolution(a1, b1, c1, d1, x1);

    // Przykład 2: Układ z równania różniczkowego
    cout << "\n\n>>> PRZYKŁAD 2: Układ z dyskretyzacji równania różniczkowego <<<\n";
    cout << "Rozwiązujemy: u''(x) = -π²sin(πx), u(0) = 0, u(1) = 0\n";
    cout << "Rozwiązanie analityczne: u(x) = sin(πx)\n";

    int n = 9;  // liczba punktów wewnętrznych
    double h = 1.0 / (n + 1);

    cout << "Krok siatki h = " << h << "\n";
    cout << "Liczba punktów wewnętrznych: " << n << "\n";

    // Dyskretyzacja: (u_{i-1} - 2u_i + u_{i+1})/h² = -π²sin(πx_i)
    // => u_{i-1} - 2u_i + u_{i+1} = -h²π²sin(πx_i)

    vector<double> a2(n), b2(n), c2(n), d2(n);

    for (int i = 0; i < n; i++) {
        a2[i] = 1.0;
        b2[i] = -2.0;
        c2[i] = 1.0;

        double x_i = (i + 1) * h;
        d2[i] = -h * h * M_PI * M_PI * sin(M_PI * x_i);
    }

    vector<double> x2 = thomasAlgorithm(a2, b2, c2, d2);

    cout << "\n=== Porównanie z rozwiązaniem analitycznym ===\n";
    cout << setw(5) << "i" << setw(10) << "x"
         << setw(15) << "u_num" << setw(15) << "u_exact"
         << setw(15) << "błąd\n";
    cout << string(60, '-') << "\n";

    double max_error = 0.0;

    cout << setw(5) << "0" << setw(10) << fixed << setprecision(6) << 0.0
         << setw(15) << 0.0 << setw(15) << 0.0
         << setw(15) << scientific << 0.0 << " (warunek brzegowy)\n";

    for (int i = 0; i < n; i++) {
        double x_i = (i + 1) * h;
        double u_exact = sin(M_PI * x_i);
        double error = abs(x2[i] - u_exact);
        max_error = max(max_error, error);

        cout << setw(5) << (i+1) << setw(10) << fixed << setprecision(6) << x_i
             << setw(15) << x2[i] << setw(15) << u_exact
             << setw(15) << scientific << error << "\n";
    }

    cout << setw(5) << (n+1) << setw(10) << fixed << setprecision(6) << 1.0
         << setw(15) << 0.0 << setw(15) << 0.0
         << setw(15) << scientific << 0.0 << " (warunek brzegowy)\n";

    cout << "\nMaksymalny błąd: " << scientific << max_error << "\n";
    cout << "Teoretyczny rząd błędu: O(h²) = O(" << h*h << ")\n";

    // Przykład 3: Porównanie złożoności czasowej
    cout << "\n\n>>> PRZYKŁAD 3: Złożoność obliczeniowa <<<\n";
    cout << "\nAlgorytm Thomasa:\n";
    cout << "  - Forward elimination: " << n << " iteracji\n";
    cout << "  - Back substitution: " << n << " iteracji\n";
    cout << "  - Złożoność: O(n) = O(" << n << ")\n";
    cout << "  - Liczba operacji: ~" << (5*n) << "\n";

    cout << "\nEliminacja Gaussa (dla porównania):\n";
    cout << "  - Złożoność: O(n³) = O(" << (n*n*n) << ")\n";
    cout << "  - Liczba operacji: ~" << (n*n*n) << "\n";

    cout << "\nPrzyspieszenie: ~" << fixed << setprecision(1)
         << (double)(n*n*n)/(5.0*n) << "x szybciej!\n";

    cout << "\n=== Demonstracja zakończona ===\n";

    return 0;
}
