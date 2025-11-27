#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// Funkcja rozwiązująca układ trójdiagonalny (algorytm Thomasa)
// a - diagonala dolna, b - diagonala główna, c - diagonala górna, d - prawa strona
vector<double> solveTridiagonal(vector<double> a, vector<double> b,
                                vector<double> c, vector<double> d) {
    int n = d.size();
    vector<double> c_star(n, 0.0);
    vector<double> d_star(n, 0.0);
    vector<double> x(n, 0.0);

    // Forward sweep
    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double m = 1.0 / (b[i] - a[i] * c_star[i-1]);
        c_star[i] = c[i] * m;
        d_star[i] = (d[i] - a[i] * d_star[i-1]) * m;
    }

    // Back substitution
    x[n-1] = d_star[n-1];
    for (int i = n-2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i+1];
    }

    return x;
}

// Metoda klasyczna bezpośrednia (explicit)
void explicitMethod(double D, double dx, double dt, double t_final,
                   vector<double>& x, vector<double>& u) {
    cout << "\n========================================\n";
    cout << "METODA KLASYCZNA BEZPOŚREDNIA (EXPLICIT)\n";
    cout << "========================================\n\n";

    int n = x.size();
    double lambda = D * dt / (dx * dx);

    cout << "Parametr stabilności: λ = D·δt/(Δx)² = " << lambda << "\n";
    cout << "Warunek stabilności: λ ≤ 0.5\n";

    if (lambda <= 0.5) {
        cout << "✓ Metoda jest STABILNA dla podanych parametrów\n\n";
    } else {
        cout << "✗ UWAGA: Metoda jest NIESTABILNA dla podanych parametrów!\n\n";
    }

    // Warunek początkowy
    cout << "Warunek początkowy u(x,0) = x³:\n";
    for (int i = 0; i < n; i++) {
        u[i] = x[i] * x[i] * x[i];
        cout << "  u(" << x[i] << ", 0) = " << u[i] << "\n";
    }
    cout << "\n";

    // Iteracja w czasie
    double t = 0.0;
    int step = 0;

    while (t < t_final - 1e-10) {
        vector<double> u_new(n);

        // Warunki brzegowe
        u_new[0] = -1.0 - (t + dt);  // u(-1, t+dt)
        u_new[n-1] = 1.0 + (t + dt); // u(1, t+dt)

        // Węzły wewnętrzne
        for (int i = 1; i < n-1; i++) {
            u_new[i] = u[i] + lambda * (u[i+1] - 2*u[i] + u[i-1]);
        }

        u = u_new;
        t += dt;
        step++;

        cout << "Krok czasowy " << step << " (t = " << t << "):\n";
        for (int i = 0; i < n; i++) {
            cout << "  u(" << x[i] << ", " << t << ") = " << u[i] << "\n";
        }
        cout << "\n";
    }

    cout << "Rozwiązanie końcowe w t = " << t_final << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "  u(" << x[i] << ", " << t_final << ") = " << u[i] << "\n";
    }
    cout << "\n";
}

// Metoda Laasonen (fully implicit)
void laasonenMethod(double D, double dx, double dt, double t_final,
                   vector<double>& x, vector<double>& u) {
    cout << "\n========================================\n";
    cout << "METODA LAASONEN (FULLY IMPLICIT)\n";
    cout << "========================================\n\n";

    int n = x.size();
    double lambda = D * dt / (dx * dx);

    cout << "Parametr: λ = D·δt/(Δx)² = " << lambda << "\n";
    cout << "Metoda Laasonen jest BEZWARUNKOWO STABILNA\n";
    cout << "✓ Stabilna dla dowolnych wartości λ > 0\n\n";

    // Warunek początkowy
    cout << "Warunek początkowy u(x,0) = x³:\n";
    for (int i = 0; i < n; i++) {
        u[i] = x[i] * x[i] * x[i];
        cout << "  u(" << x[i] << ", 0) = " << u[i] << "\n";
    }
    cout << "\n";

    // Iteracja w czasie
    double t = 0.0;
    int step = 0;

    while (t < t_final - 1e-10) {
        int interior = n - 2; // liczba węzłów wewnętrznych

        if (interior > 0) {
            // Macierz trójdiagonalna dla węzłów wewnętrznych
            vector<double> a(interior, -lambda);      // dolna diagonala
            vector<double> b(interior, 1 + 2*lambda); // główna diagonala
            vector<double> c(interior, -lambda);      // górna diagonala
            vector<double> d(interior);               // prawa strona

            // Warunki brzegowe dla następnego kroku czasowego
            double u_left = -1.0 - (t + dt);   // u(-1, t+dt)
            double u_right = 1.0 + (t + dt);   // u(1, t+dt)

            // Prawa strona równania
            for (int i = 0; i < interior; i++) {
                d[i] = u[i+1]; // wartość w poprzedniej chwili czasu
            }

            // Uwzględnienie warunków brzegowych
            d[0] += lambda * u_left;
            d[interior-1] += lambda * u_right;

            // Rozwiązanie układu
            vector<double> u_interior = solveTridiagonal(a, b, c, d);

            // Aktualizacja rozwiązania
            u[0] = u_left;
            for (int i = 0; i < interior; i++) {
                u[i+1] = u_interior[i];
            }
            u[n-1] = u_right;
        } else {
            // Tylko warunki brzegowe
            u[0] = -1.0 - (t + dt);
            u[n-1] = 1.0 + (t + dt);
        }

        t += dt;
        step++;

        cout << "Krok czasowy " << step << " (t = " << t << "):\n";
        for (int i = 0; i < n; i++) {
            cout << "  u(" << x[i] << ", " << t << ") = " << u[i] << "\n";
        }
        cout << "\n";
    }

    cout << "Rozwiązanie końcowe w t = " << t_final << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "  u(" << x[i] << ", " << t_final << ") = " << u[i] << "\n";
    }
    cout << "\n";
}

// Metoda Cranka-Nicolson
void crankNicolsonMethod(double D, double dx, double dt, double t_final,
                        vector<double>& x, vector<double>& u) {
    cout << "\n========================================\n";
    cout << "METODA CRANKA-NICOLSON\n";
    cout << "========================================\n\n";

    int n = x.size();
    double lambda = D * dt / (dx * dx);

    cout << "Parametr: λ = D·δt/(Δx)² = " << lambda << "\n";
    cout << "Metoda Cranka-Nicolson jest BEZWARUNKOWO STABILNA\n";
    cout << "✓ Stabilna dla dowolnych wartości λ > 0\n";
    cout << "✓ Dokładność: O(δt², Δx²)\n\n";

    // Warunek początkowy
    cout << "Warunek początkowy u(x,0) = x³:\n";
    for (int i = 0; i < n; i++) {
        u[i] = x[i] * x[i] * x[i];
        cout << "  u(" << x[i] << ", 0) = " << u[i] << "\n";
    }
    cout << "\n";

    // Iteracja w czasie
    double t = 0.0;
    int step = 0;

    while (t < t_final - 1e-10) {
        int interior = n - 2;

        if (interior > 0) {
            // Współczynniki dla Cranka-Nicolson
            double alpha = lambda / 2.0;

            // Macierz po lewej stronie (dla u^{n+1})
            vector<double> a(interior, -alpha);          // dolna diagonala
            vector<double> b(interior, 1 + 2*alpha);     // główna diagonala
            vector<double> c(interior, -alpha);          // górna diagonala
            vector<double> d(interior);                  // prawa strona

            // Warunki brzegowe
            double u_left_new = -1.0 - (t + dt);
            double u_right_new = 1.0 + (t + dt);
            double u_left_old = u[0];
            double u_right_old = u[n-1];

            // Prawa strona: zawiera u^n i warunki brzegowe
            for (int i = 0; i < interior; i++) {
                int idx = i + 1;
                double rhs = alpha * u[idx-1] + (1 - 2*alpha) * u[idx] + alpha * u[idx+1];
                d[i] = rhs;
            }

            // Uwzględnienie warunków brzegowych
            d[0] += alpha * (u_left_new + u_left_old);
            d[interior-1] += alpha * (u_right_new + u_right_old);

            // Rozwiązanie układu
            vector<double> u_interior = solveTridiagonal(a, b, c, d);

            // Aktualizacja rozwiązania
            u[0] = u_left_new;
            for (int i = 0; i < interior; i++) {
                u[i+1] = u_interior[i];
            }
            u[n-1] = u_right_new;
        } else {
            u[0] = -1.0 - (t + dt);
            u[n-1] = 1.0 + (t + dt);
        }

        t += dt;
        step++;

        cout << "Krok czasowy " << step << " (t = " << t << "):\n";
        for (int i = 0; i < n; i++) {
            cout << "  u(" << x[i] << ", " << t << ") = " << u[i] << "\n";
        }
        cout << "\n";
    }

    cout << "Rozwiązanie końcowe w t = " << t_final << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "  u(" << x[i] << ", " << t_final << ") = " << u[i] << "\n";
    }
    cout << "\n";
}

int main() {
    cout << fixed << setprecision(6);

    cout << "╔════════════════════════════════════════════════════════════╗\n";
    cout << "║  ROZWIĄZYWANIE RÓWNANIA DYFUZJI METODAMI RÓŻNICOWYMI      ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    // Parametry problemu
    double D = 1.0;           // współczynnik dyfuzji
    double dx = 1.0;          // krok przestrzenny
    double dt = 1.0;          // krok czasowy
    double t_final = 1.0;     // czas końcowy

    // Siatka przestrzenna: x0 = -1, x1 = 0, x2 = 1
    vector<double> x = {-1.0, 0.0, 1.0};
    int n = x.size();

    cout << "\nParametry problemu:\n";
    cout << "  Współczynnik dyfuzji D = " << D << "\n";
    cout << "  Dziedzina przestrzenna: x ∈ [-1, 1]\n";
    cout << "  Węzły przestrzenne: x₀ = " << x[0] << ", x₁ = " << x[1]
         << ", x₂ = " << x[2] << "\n";
    cout << "  Krok przestrzenny: Δx = " << dx << "\n";
    cout << "  Krok czasowy: δt = " << dt << "\n";
    cout << "  Czas końcowy: t = " << t_final << "\n";
    cout << "\nWarunki:\n";
    cout << "  Początkowy: u(x,0) = x³\n";
    cout << "  Brzegowy lewy: u(-1,t) = -1 - t\n";
    cout << "  Brzegowy prawy: u(1,t) = 1 + t\n";

    // Metoda 1: Explicit
    vector<double> u1(n);
    explicitMethod(D, dx, dt, t_final, x, u1);

    // Metoda 2: Laasonen
    vector<double> u2(n);
    laasonenMethod(D, dx, dt, t_final, x, u2);

    // Metoda 3: Crank-Nicolson
    vector<double> u3(n);
    crankNicolsonMethod(D, dx, dt, t_final, x, u3);

    // Porównanie wyników
    cout << "\n========================================\n";
    cout << "PORÓWNANIE WYNIKÓW\n";
    cout << "========================================\n\n";
    cout << "Wartości w t = " << t_final << ":\n\n";
    cout << "  x      | Explicit  | Laasonen  | Crank-Nicolson\n";
    cout << "---------|-----------|-----------|---------------\n";
    for (int i = 0; i < n; i++) {
        cout << setw(7) << x[i] << "  |";
        cout << setw(10) << u1[i] << " |";
        cout << setw(10) << u2[i] << " |";
        cout << setw(10) << u3[i] << "\n";
    }

    cout << "\n========================================\n";
    cout << "PODSUMOWANIE STABILNOŚCI\n";
    cout << "========================================\n\n";

    double lambda = D * dt / (dx * dx);
    cout << "Parametr λ = D·δt/(Δx)² = " << lambda << "\n\n";

    cout << "1. Metoda Explicit:\n";
    if (lambda <= 0.5) {
        cout << "   ✓ STABILNA (λ = " << lambda << " ≤ 0.5)\n";
    } else {
        cout << "   ✗ NIESTABILNA (λ = " << lambda << " > 0.5)\n";
        cout << "   Metoda może dawać oscylujące lub rozbieżne wyniki!\n";
    }

    cout << "\n2. Metoda Laasonen:\n";
    cout << "   ✓ BEZWARUNKOWO STABILNA\n";
    cout << "   Stabilna dla dowolnych λ > 0\n";
    cout << "   Dokładność: O(δt, Δx²)\n";

    cout << "\n3. Metoda Cranka-Nicolson:\n";
    cout << "   ✓ BEZWARUNKOWO STABILNA\n";
    cout << "   Stabilna dla dowolnych λ > 0\n";
    cout << "   Dokładność: O(δt², Δx²) - najlepsza!\n";

    cout << "\n========================================\n";
    cout << "WNIOSKI\n";
    cout << "========================================\n\n";

    if (lambda > 0.5) {
        cout << "⚠ Dla λ = " << lambda << " > 0.5:\n";
        cout << "  - Metoda explicit jest NIESTABILNA\n";
        cout << "  - Należy użyć metod implicit (Laasonen lub Crank-Nicolson)\n";
        cout << "  - Lub zmniejszyć δt lub zwiększyć Δx\n\n";
    } else {
        cout << "✓ Dla λ = " << lambda << " ≤ 0.5:\n";
        cout << "  - Wszystkie metody są stabilne\n";
        cout << "  - Metoda Crank-Nicolson daje najdokładniejsze wyniki\n";
        cout << "  - Metoda explicit jest najprostsza obliczeniowo\n\n";
    }

    cout << "Zalecenia:\n";
    cout << "  1. Dla małych kroków czasowych: metoda explicit (szybka)\n";
    cout << "  2. Dla dużych kroków czasowych: Crank-Nicolson (stabilna i dokładna)\n";
    cout << "  3. Dla problemów sztywnych: metody implicit\n";

    return 0;
}
