#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Rozwiązanie analityczne
double analyticalSolution(double x) {
    double sqrt5 = sqrt(5.0);
    double term1 = 9.0 - 95.0 * exp((-1.0 - sqrt5) * (-1.0 + x));
    double term2 = 55.0 * exp((-1.0 + sqrt5) * x);
    double term3 = 95.0 * exp(1.0 + sqrt5 + (-1.0 + sqrt5) * x);
    double term4 = -55.0 * exp(2.0 * sqrt5 - (1.0 + sqrt5) * x);
    double term5 = 2.0 * x * (6.0 + x * (3.0 + 2.0 * x));
    double term6 = -exp(2.0 * sqrt5) * (9.0 + 2.0 * x * (6.0 + x * (3.0 + 2.0 * x)));
    double coth_sqrt5 = cosh(sqrt5) / sinh(sqrt5);

    return -((term1 + term2 + term3 + term4 + term5 + term6) * (-1.0 + coth_sqrt5)) / 64.0;
}

// Algorytm Thomasa dla układu trójdiagonalnego
// a - diagonala dolna, b - diagonala główna, c - diagonala górna, d - prawa strona
vector<double> thomasAlgorithm(vector<double> a, vector<double> b, vector<double> c, vector<double> d) {
    int n = d.size();
    vector<double> c_star(n, 0.0);
    vector<double> d_star(n, 0.0);
    vector<double> x(n, 0.0);

    // Forward elimination
    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double denom = b[i] - a[i] * c_star[i-1];
        if (i < n - 1) {
            c_star[i] = c[i] / denom;
        }
        d_star[i] = (d[i] - a[i] * d_star[i-1]) / denom;
    }

    // Back substitution
    x[n-1] = d_star[n-1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i+1];
    }

    return x;
}

// Funkcje równania: U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0
double f(double x) {
    return pow(x, 1.5);
}

// Metoda konwencjonalna - rozwiązanie równania różnicowego
vector<double> conventionalMethod(int n, double U0, double U1) {
    double h = 1.0 / n;
    vector<double> x(n+1);

    // Generowanie siatki
    for (int i = 0; i <= n; i++) {
        x[i] = i * h;
    }

    // Układ równań: A*u = d (trójdiagonalny)
    // U_{i-1} - 2U_i + U_{i+1}   +   2h(U_{i+1} - U_{i-1})/2   -   4h^2 U_i   =   -h^2 * x_i^(3/2)
    // => (1 - h)U_{i-1} + (-2 - 4h^2)U_i + (1 + h)U_{i+1} = -h^2 * x_i^(3/2)

    vector<double> a(n-1), b(n-1), c(n-1), d(n-1);

    for (int i = 0; i < n-1; i++) {
        double xi = x[i+1];

        // Współczynniki
        a[i] = 1.0 - h;  // współczynnik przy U_{i-1}
        b[i] = -2.0 - 4.0 * h * h;  // współczynnik przy U_i
        c[i] = 1.0 + h;  // współczynnik przy U_{i+1}
        d[i] = -h * h * f(xi);
    }

    // Warunki brzegowe
    d[0] -= a[0] * U0;
    d[n-2] -= c[n-2] * U1;

    // Rozwiązanie układu
    vector<double> u_inner = thomasAlgorithm(a, b, c, d);

    // Składanie pełnego rozwiązania
    vector<double> u(n+1);
    u[0] = U0;
    for (int i = 0; i < n-1; i++) {
        u[i+1] = u_inner[i];
    }
    u[n] = U1;

    return u;
}

// Funkcja prawej strony dla metody strzałów: U'' = F(x, U, U')
// U'' + 2U' - 4U + x^(3/2) = 0  =>  U'' = -2U' + 4U - x^(3/2)
double F_shooting(double x, double U, double Uprime) {
    return -2.0 * Uprime + 4.0 * U - f(x);
}

// Rozwiązanie problemu początkowego metodą Runge-Kutta 4. rzędu
vector<double> rk4_shooting(double s, int n, double U0) {
    double h = 1.0 / n;
    vector<double> u(n+1);
    vector<double> v(n+1);  // v = U'

    u[0] = U0;
    v[0] = s;  // parametr strzału

    for (int i = 0; i < n; i++) {
        double xi = i * h;
        double ui = u[i];
        double vi = v[i];

        // RK4 dla układu:
        // U' = V
        // V' = F(x, U, V)

        double k1_u = vi;
        double k1_v = F_shooting(xi, ui, vi);

        double k2_u = vi + h * k1_v / 2.0;
        double k2_v = F_shooting(xi + h/2.0, ui + h * k1_u / 2.0, vi + h * k1_v / 2.0);

        double k3_u = vi + h * k2_v / 2.0;
        double k3_v = F_shooting(xi + h/2.0, ui + h * k2_u / 2.0, vi + h * k2_v / 2.0);

        double k4_u = vi + h * k3_v;
        double k4_v = F_shooting(xi + h, ui + h * k3_u, vi + h * k3_v);

        u[i+1] = ui + h * (k1_u + 2.0 * k2_u + 2.0 * k3_u + k4_u) / 6.0;
        v[i+1] = vi + h * (k1_v + 2.0 * k2_v + 2.0 * k3_v + k4_v) / 6.0;
    }

    return u;
}

// Metoda strzałów z bisekcją
vector<double> shootingMethod(int n, double U0, double U1) {
    // Szukamy parametru s takiego, że u(1) = U1
    double s_low = -20.0;
    double s_high = 20.0;
    double tolerance = 1e-10;
    int max_iterations = 100;

    for (int iter = 0; iter < max_iterations; iter++) {
        double s_mid = (s_low + s_high) / 2.0;

        vector<double> u_low = rk4_shooting(s_low, n, U0);
        vector<double> u_mid = rk4_shooting(s_mid, n, U0);

        double error_low = u_low[n] - U1;
        double error_mid = u_mid[n] - U1;

        if (abs(error_mid) < tolerance) {
            return u_mid;
        }

        if (error_low * error_mid < 0) {
            s_high = s_mid;
        } else {
            s_low = s_mid;
        }
    }

    // Zwróć ostatnie przybliżenie
    return rk4_shooting((s_low + s_high) / 2.0, n, U0);
}

// Obliczenie maksymalnego błędu
double maxError(const vector<double>& u_numerical, int n) {
    double h = 1.0 / n;
    double max_err = 0.0;

    for (int i = 0; i <= n; i++) {
        double x = i * h;
        double u_exact = analyticalSolution(x);
        double err = abs(u_numerical[i] - u_exact);
        max_err = max(max_err, err);
    }

    return max_err;
}

// Zapisanie wyników do pliku
void saveResults(const string& filename, const vector<double>& u_conv, const vector<double>& u_shoot, int n) {
    ofstream file(filename);
    double h = 1.0 / n;

    file << "x,U_conventional,U_shooting,U_analytical,Error_conv,Error_shoot\n";
    file << setprecision(10) << scientific;

    for (int i = 0; i <= n; i++) {
        double x = i * h;
        double u_exact = analyticalSolution(x);
        file << x << ","
             << u_conv[i] << ","
             << u_shoot[i] << ","
             << u_exact << ","
             << abs(u_conv[i] - u_exact) << ","
             << abs(u_shoot[i] - u_exact) << "\n";
    }

    file.close();
}

// Analiza rzędu dokładności
void convergenceAnalysis() {
    vector<int> n_values = {10, 20, 40, 80, 160, 320, 640, 1280, 2560};
    double U0 = 2.0;
    double U1 = -2.0;

    ofstream file("convergence.csv");
    file << "n,h,log10_h,Error_conv,log10_Error_conv,Error_shoot,log10_Error_shoot\n";
    file << setprecision(12) << scientific;

    for (int n : n_values) {
        cout << "Analyzing n = " << n << "..." << endl;

        double h = 1.0 / n;

        vector<double> u_conv = conventionalMethod(n, U0, U1);
        vector<double> u_shoot = shootingMethod(n, U0, U1);

        double err_conv = maxError(u_conv, n);
        double err_shoot = maxError(u_shoot, n);

        file << n << ","
             << h << ","
             << log10(h) << ","
             << err_conv << ","
             << log10(err_conv) << ","
             << err_shoot << ","
             << log10(err_shoot) << "\n";

        cout << "  h = " << h << ", Error_conv = " << err_conv << ", Error_shoot = " << err_shoot << endl;
    }

    file.close();
    cout << "\nAnaliza zbieżności zapisana do pliku convergence.csv" << endl;
}

// Obliczenie rzędu zbieżności empirycznie
void computeConvergenceOrder() {
    vector<int> n_values = {10, 20, 40, 80, 160, 320, 640};
    double U0 = 2.0;
    double U1 = -2.0;

    vector<double> errors_conv, errors_shoot;
    vector<double> h_values;

    for (int n : n_values) {
        double h = 1.0 / n;
        h_values.push_back(h);

        vector<double> u_conv = conventionalMethod(n, U0, U1);
        vector<double> u_shoot = shootingMethod(n, U0, U1);

        errors_conv.push_back(maxError(u_conv, n));
        errors_shoot.push_back(maxError(u_shoot, n));
    }

    cout << "\n=== Empiryczny rząd zbieżności ===" << endl;
    cout << "Metoda konwencjonalna:" << endl;
    for (size_t i = 1; i < errors_conv.size(); i++) {
        double order = log2(errors_conv[i-1] / errors_conv[i]);
        cout << "  n: " << n_values[i-1] << " -> " << n_values[i]
             << ", rząd: " << order << endl;
    }

    cout << "\nMetoda strzałów:" << endl;
    for (size_t i = 1; i < errors_shoot.size(); i++) {
        double order = log2(errors_shoot[i-1] / errors_shoot[i]);
        cout << "  n: " << n_values[i-1] << " -> " << n_values[i]
             << ", rząd: " << order << endl;
    }
}

int main() {
    cout << "=== Metody różnicowe dla równań różniczkowych drugiego rzędu ===" << endl;
    cout << "Równanie: U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0" << endl;
    cout << "Warunki brzegowe: U(0) = 2, U(1) = -2" << endl;
    cout << "Przedział: [0, 1]" << endl << endl;

    double U0 = 2.0;
    double U1 = -2.0;
    int n = 100;  // liczba podprzedziałów

    cout << "1. Rozwiązanie dla n = " << n << " podprzedziałów" << endl;

    // Metoda konwencjonalna
    cout << "\nRozwiązywanie metodą konwencjonalną..." << endl;
    vector<double> u_conv = conventionalMethod(n, U0, U1);
    double err_conv = maxError(u_conv, n);
    cout << "Maksymalny błąd bezwzględny (metoda konwencjonalna): " << err_conv << endl;

    // Metoda strzałów
    cout << "\nRozwiązywanie metodą strzałów..." << endl;
    vector<double> u_shoot = shootingMethod(n, U0, U1);
    double err_shoot = maxError(u_shoot, n);
    cout << "Maksymalny błąd bezwzględny (metoda strzałów): " << err_shoot << endl;

    // Zapisanie wyników
    saveResults("results.csv", u_conv, u_shoot, n);
    cout << "\nWyniki zapisane do pliku results.csv" << endl;

    // Porównanie w kilku punktach
    cout << "\n=== Porównanie rozwiązań w wybranych punktach ===" << endl;
    cout << setw(8) << "x" << setw(18) << "U_conv" << setw(18) << "U_shoot"
         << setw(18) << "U_analytical" << setw(15) << "Err_conv" << setw(15) << "Err_shoot" << endl;
    cout << string(94, '-') << endl;

    double h = 1.0 / n;
    for (int i = 0; i <= n; i += n/10) {
        double x = i * h;
        double u_exact = analyticalSolution(x);
        cout << fixed << setprecision(4) << setw(8) << x
             << scientific << setprecision(8)
             << setw(18) << u_conv[i]
             << setw(18) << u_shoot[i]
             << setw(18) << u_exact
             << setw(15) << abs(u_conv[i] - u_exact)
             << setw(15) << abs(u_shoot[i] - u_exact) << endl;
    }

    // Analiza zbieżności
    cout << "\n2. Analiza zbieżności dla różnych wartości h..." << endl;
    convergenceAnalysis();

    // Obliczenie empirycznego rzędu zbieżności
    cout << "\n3. Obliczenie empirycznego rzędu zbieżności..." << endl;
    computeConvergenceOrder();

    cout << "\n=== Program zakończony ===" << endl;
    cout << "\nPłiki wyjściowe:" << endl;
    cout << "  - results.csv: szczegółowe wyniki dla n=100" << endl;
    cout << "  - convergence.csv: analiza zbieżności dla różnych wartości h" << endl;
    cout << "\nAby zwizualizować wyniki, użyj dołączonego skryptu Python." << endl;

    return 0;
}
