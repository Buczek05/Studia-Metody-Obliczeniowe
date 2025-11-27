#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// Funkcja rozwiązująca układ trójdiagonalny (algorytm Thomasa)
vector<double> solveTridiagonal(vector<double> a, vector<double> b,
                                vector<double> c, vector<double> d) {
    int n = d.size();
    vector<double> c_star(n, 0.0);
    vector<double> d_star(n, 0.0);
    vector<double> x(n, 0.0);

    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double m = 1.0 / (b[i] - a[i] * c_star[i-1]);
        c_star[i] = c[i] * m;
        d_star[i] = (d[i] - a[i] * d_star[i-1]) * m;
    }

    x[n-1] = d_star[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i+1];
    }

    return x;
}

// Wyświetlenie macierzy trójdiagonalnej
void displayTridiagonalSystem(const vector<double>& a, const vector<double>& b,
                              const vector<double>& c, const vector<double>& d,
                              const string& title) {
    cout << "\n" << title << "\n";
    cout << string(60, '-') << "\n";

    int n = d.size();
    cout << "\nMacierz współczynników (trójdiagonalna):\n";

    for (int i = 0; i < n; i++) {
        cout << "  [";
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << setw(10) << b[i];
            } else if (j == i - 1 && i > 0) {
                cout << setw(10) << a[i];
            } else if (j == i + 1 && i < n - 1) {
                cout << setw(10) << c[i];
            } else {
                cout << setw(10) << 0.0;
            }
        }
        cout << " ] [ U" << i+1 << " ] = [ " << setw(10) << d[i] << " ]\n";
    }

    cout << "\nElementy macierzy:\n";
    cout << "  Diagonala główna b[i] = " << b[0] << "\n";
    if (n > 1) {
        cout << "  Diagonala dolna  a[i] = " << a[1] << "\n";
        cout << "  Diagonala górna  c[i] = " << c[0] << "\n";
    }
}

// Metoda Laasonen dla równania reakcji-dyfuzji
void laasonenReactionDiffusion(double D, double r, double L, int N,
                               double dt, double t_final,
                               function<double(double)> alpha,
                               function<double(double)> beta,
                               function<double(double)> u0) {
    cout << "\n╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "║  METODA LAASONEN DLA RÓWNANIA REAKCJI-DYFUZJI                ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════╝\n";

    double dx = L / N;
    int n_interior = N - 1; // liczba węzłów wewnętrznych
    double lambda = D * dt / (dx * dx);
    double mu = r * dt;

    cout << "\nParametry:\n";
    cout << "  D (dyfuzja) = " << D << "\n";
    cout << "  r (reakcja) = " << r << "\n";
    cout << "  L (długość) = " << L << "\n";
    cout << "  N (liczba przedziałów) = " << N << "\n";
    cout << "  Δx = " << dx << "\n";
    cout << "  δt = " << dt << "\n";
    cout << "  λ = D·δt/(Δx)² = " << lambda << "\n";
    cout << "  μ = r·δt = " << mu << "\n";

    cout << "\nRównanie: ∂U/∂t = D·∂²U/∂x² - r·U\n";

    cout << "\nSchemat Laasonen:\n";
    cout << "  (U[i]^(n+1) - U[i]^n)/δt = D·(U[i+1]^(n+1) - 2U[i]^(n+1) + U[i-1]^(n+1))/(Δx)² - r·U[i]^(n+1)\n";
    cout << "\nPo przekształceniu:\n";
    cout << "  -λ·U[i-1]^(n+1) + (1 + 2λ + μ)·U[i]^(n+1) - λ·U[i+1]^(n+1) = U[i]^n\n";

    // Inicjalizacja siatki
    vector<double> x(N+1);
    vector<double> U(N+1);

    for (int i = 0; i <= N; i++) {
        x[i] = i * dx;
        U[i] = u0(x[i]);
    }

    cout << "\nWarunek początkowy:\n";
    for (int i = 0; i <= N; i++) {
        cout << "  U(" << x[i] << ", 0) = " << U[i] << "\n";
    }

    // Budowa macierzy dla węzłów wewnętrznych
    vector<double> a(n_interior, -lambda);           // diagonala dolna
    vector<double> b(n_interior, 1 + 2*lambda + mu); // diagonala główna
    vector<double> c(n_interior, -lambda);           // diagonala górna

    cout << "\n┌─────────────────────────────────────────────────────────┐\n";
    cout << "│ STRUKTURA UKŁADU RÓWNAŃ                                 │\n";
    cout << "└─────────────────────────────────────────────────────────┘\n";

    cout << "\nPostać macierzowa: A·U^(n+1) = b^n\n";
    cout << "\nMacierz A (trójdiagonalna " << n_interior << "×" << n_interior << "):\n";
    cout << "  Diagonala główna:  b[i] = 1 + 2λ + μ = " << b[0] << "\n";
    cout << "  Diagonala dolna:   a[i] = -λ = " << a[0] << "\n";
    cout << "  Diagonala górna:   c[i] = -λ = " << c[0] << "\n";

    cout << "\nWektor prawej strony b^n:\n";
    cout << "  b[0] = U[1]^n + λ·α(t^(n+1))\n";
    cout << "  b[i] = U[i+1]^n, dla i = 1, ..., " << n_interior-2 << "\n";
    cout << "  b[" << n_interior-1 << "] = U[" << N-1 << "]^n + λ·β(t^(n+1))\n";

    // Przykładowy układ dla pierwszego kroku czasowego
    vector<double> d_example(n_interior);
    double t_next = dt;
    for (int i = 0; i < n_interior; i++) {
        d_example[i] = U[i+1];
    }
    d_example[0] += lambda * alpha(t_next);
    d_example[n_interior-1] += lambda * beta(t_next);

    displayTridiagonalSystem(a, b, c, d_example,
                            "Przykład: Układ równań dla pierwszego kroku czasowego (t = 0 → t = " +
                            to_string(dt) + ")");

    // Iteracja w czasie
    cout << "\n\n┌─────────────────────────────────────────────────────────┐\n";
    cout << "│ ITERACJA W CZASIE                                       │\n";
    cout << "└─────────────────────────────────────────────────────────┘\n";

    double t = 0.0;
    int step = 0;

    while (t < t_final - 1e-10) {
        vector<double> d(n_interior);
        double t_next = t + dt;

        // Warunki brzegowe
        double U_left = alpha(t_next);
        double U_right = beta(t_next);

        // Prawa strona
        for (int i = 0; i < n_interior; i++) {
            d[i] = U[i+1];
        }

        // Uwzględnienie warunków brzegowych
        d[0] += lambda * U_left;
        d[n_interior-1] += lambda * U_right;

        // Rozwiązanie układu
        vector<double> U_interior = solveTridiagonal(a, b, c, d);

        // Aktualizacja
        U[0] = U_left;
        for (int i = 0; i < n_interior; i++) {
            U[i+1] = U_interior[i];
        }
        U[N] = U_right;

        t = t_next;
        step++;

        cout << "\nKrok " << step << " (t = " << t << "):\n";
        for (int i = 0; i <= N; i++) {
            cout << "  U(" << x[i] << ") = " << U[i] << "\n";
        }
    }

    cout << "\n✓ Metoda Laasonen jest BEZWARUNKOWO STABILNA\n";
}

// Metoda Cranka-Nicolson dla równania reakcji-dyfuzji
void crankNicolsonReactionDiffusion(double D, double r, double L, int N,
                                   double dt, double t_final,
                                   function<double(double)> alpha,
                                   function<double(double)> beta,
                                   function<double(double)> u0) {
    cout << "\n\n╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "║  METODA CRANKA-NICOLSON DLA RÓWNANIA REAKCJI-DYFUZJI         ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════╝\n";

    double dx = L / N;
    int n_interior = N - 1;
    double lambda = D * dt / (dx * dx);
    double mu = r * dt;

    cout << "\nParametry:\n";
    cout << "  D (dyfuzja) = " << D << "\n";
    cout << "  r (reakcja) = " << r << "\n";
    cout << "  λ = D·δt/(Δx)² = " << lambda << "\n";
    cout << "  μ = r·δt = " << mu << "\n";

    cout << "\nSchemat Cranka-Nicolson:\n";
    cout << "  (U[i]^(n+1) - U[i]^n)/δt = D/2·[(∂²U/∂x²)^(n+1) + (∂²U/∂x²)^n] - r/2·(U[i]^(n+1) + U[i]^n)\n";

    cout << "\nPo przekształceniu:\n";
    cout << "  -λ/2·U[i-1]^(n+1) + (1 + λ + μ/2)·U[i]^(n+1) - λ/2·U[i+1]^(n+1) =\n";
    cout << "  = λ/2·U[i-1]^n + (1 - λ - μ/2)·U[i]^n + λ/2·U[i+1]^n\n";

    // Inicjalizacja
    vector<double> x(N+1);
    vector<double> U(N+1);

    for (int i = 0; i <= N; i++) {
        x[i] = i * dx;
        U[i] = u0(x[i]);
    }

    cout << "\nWarunek początkowy:\n";
    for (int i = 0; i <= N; i++) {
        cout << "  U(" << x[i] << ", 0) = " << U[i] << "\n";
    }

    // Macierze
    double alpha_coef = lambda / 2.0;
    double beta_coef = mu / 2.0;

    vector<double> a_left(n_interior, -alpha_coef);           // macierz A, dolna
    vector<double> b_left(n_interior, 1 + 2*alpha_coef + beta_coef); // macierz A, główna
    vector<double> c_left(n_interior, -alpha_coef);           // macierz A, górna

    cout << "\n┌─────────────────────────────────────────────────────────┐\n";
    cout << "│ STRUKTURA UKŁADU RÓWNAŃ                                 │\n";
    cout << "└─────────────────────────────────────────────────────────┘\n";

    cout << "\nPostać macierzowa: A·U^(n+1) = B·U^n + b\n";

    cout << "\nMacierz A (lewa strona, " << n_interior << "×" << n_interior << "):\n";
    cout << "  Diagonala główna:  1 + λ + μ/2 = " << b_left[0] << "\n";
    cout << "  Diagonala boczna:  -λ/2 = " << a_left[0] << "\n";

    cout << "\nMacierz B (prawa strona, " << n_interior << "×" << n_interior << "):\n";
    cout << "  Diagonala główna:  1 - λ - μ/2 = " << (1 - lambda - beta_coef) << "\n";
    cout << "  Diagonala boczna:  λ/2 = " << alpha_coef << "\n";

    cout << "\nWektor b (warunki brzegowe):\n";
    cout << "  b[0] = (λ/2)·[α(t^(n+1)) + α(t^n)]\n";
    cout << "  b[i] = 0, dla i = 1, ..., " << n_interior-2 << "\n";
    cout << "  b[" << n_interior-1 << "] = (λ/2)·[β(t^(n+1)) + β(t^n)]\n";

    // Iteracja w czasie
    cout << "\n\n┌─────────────────────────────────────────────────────────┐\n";
    cout << "│ ITERACJA W CZASIE                                       │\n";
    cout << "└─────────────────────────────────────────────────────────┘\n";

    double t = 0.0;
    int step = 0;

    while (t < t_final - 1e-10) {
        vector<double> d(n_interior);
        double t_next = t + dt;

        // Warunki brzegowe
        double U_left_old = alpha(t);
        double U_right_old = beta(t);
        double U_left_new = alpha(t_next);
        double U_right_new = beta(t_next);

        // Prawa strona: B·U^n
        for (int i = 0; i < n_interior; i++) {
            int idx = i + 1;
            d[i] = alpha_coef * U[idx-1] + (1 - 2*alpha_coef - beta_coef) * U[idx] + alpha_coef * U[idx+1];
        }

        // Dodanie warunków brzegowych
        d[0] += alpha_coef * (U_left_new + U_left_old);
        d[n_interior-1] += alpha_coef * (U_right_new + U_right_old);

        // Rozwiązanie układu
        vector<double> U_interior = solveTridiagonal(a_left, b_left, c_left, d);

        // Aktualizacja
        U[0] = U_left_new;
        for (int i = 0; i < n_interior; i++) {
            U[i+1] = U_interior[i];
        }
        U[N] = U_right_new;

        t = t_next;
        step++;

        cout << "\nKrok " << step << " (t = " << t << "):\n";
        for (int i = 0; i <= N; i++) {
            cout << "  U(" << x[i] << ") = " << U[i] << "\n";
        }
    }

    cout << "\n✓ Metoda Cranka-Nicolson jest BEZWARUNKOWO STABILNA\n";
    cout << "✓ Dokładność: O(δt², Δx²)\n";
}

int main() {
    cout << fixed << setprecision(6);

    cout << "╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║  RÓWNANIE REAKCJI-DYFUZJI: METODY LAASONEN I CRANK-NICOLSON   ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";

    // Parametry przykładowego problemu
    double D = 0.1;        // współczynnik dyfuzji
    double r = 0.5;        // stała reakcji
    double L = 1.0;        // długość dziedziny
    int N = 4;             // liczba przedziałów (5 węzłów)
    double dt = 0.1;       // krok czasowy
    double t_final = 0.2;  // czas końcowy

    // Warunki brzegowe
    auto alpha = [](double) { return 0.0; };          // U(0,t) = 0
    auto beta = [](double) { return 0.0; };           // U(L,t) = 0

    // Warunek początkowy (przykład: funkcja sin)
    auto u0 = [L](double x) { return sin(M_PI * x / L); };

    cout << "\nPrzykładowy problem:\n";
    cout << "  ∂U/∂t = " << D << "·∂²U/∂x² - " << r << "·U\n";
    cout << "  x ∈ [0, " << L << "]\n";
    cout << "  U(0,t) = 0, U(" << L << ",t) = 0\n";
    cout << "  U(x,0) = sin(πx/" << L << ")\n";

    // Metoda Laasonen
    laasonenReactionDiffusion(D, r, L, N, dt, t_final, alpha, beta, u0);

    // Metoda Cranka-Nicolson
    crankNicolsonReactionDiffusion(D, r, L, N, dt, t_final, alpha, beta, u0);

    // Podsumowanie
    cout << "\n\n╔════════════════════════════════════════════════════════════════╗\n";
    cout << "║  PODSUMOWANIE                                                  ║\n";
    cout << "╚════════════════════════════════════════════════════════════════╝\n";

    cout << "\nUOGÓLNIENIE DLA RÓWNANIA REAKCJI-DYFUZJI:\n";
    cout << "\n1. Metoda Laasonen:\n";
    cout << "   • Schemat fully implicit\n";
    cout << "   • Bezwarunkowo stabilna\n";
    cout << "   • Macierz: A = tridiag(-λ, 1+2λ+μ, -λ)\n";
    cout << "   • Wymaga rozwiązania układu w każdym kroku\n";
    cout << "   • Dokładność: O(δt, Δx²)\n";

    cout << "\n2. Metoda Cranka-Nicolson:\n";
    cout << "   • Schemat semi-implicit (średnia)\n";
    cout << "   • Bezwarunkowo stabilna\n";
    cout << "   • Wyższa dokładność: O(δt², Δx²)\n";
    cout << "   • Macierz A: tridiag(-λ/2, 1+λ+μ/2, -λ/2)\n";
    cout << "   • Macierz B: tridiag(λ/2, 1-λ-μ/2, λ/2)\n";
    cout << "   • Zalecana dla problemów wymagających wysokiej dokładności\n";

    cout << "\nWPŁYW CZŁONU REAKCYJNEGO (-r·U):\n";
    cout << "   • Dla r > 0: rozpad/zanik (decay)\n";
    cout << "   • Zwiększa stabilność numeryczną\n";
    cout << "   • Modyfikuje elementy diagonalne macierzy\n";
    cout << "   • Parametr μ = r·δt wpływa na układ równań\n";

    cout << "\nZALECANIA:\n";
    cout << "   • Dla problemów z dominacją dyfuzji (r mało): Crank-Nicolson\n";
    cout << "   • Dla problemów sztywnych (r duże): Laasonen lub implicit\n";
    cout << "   • Zawsze sprawdzaj warunek CFL dla explicit methods\n";
    cout << "   • Używaj metod implicit dla dużych kroków czasowych\n";

    return 0;
}
