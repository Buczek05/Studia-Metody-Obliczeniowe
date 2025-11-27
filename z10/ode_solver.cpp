#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Funkcja p(t) = (100*t + 10)/(t + 1)
double p_function(double t) {
    return (100.0 * t + 10.0) / (t + 1.0);
}

// Prawa strona równania: y' = -p(t) * (y - 1)
double f(double t, double y) {
    return -p_function(t) * (y - 1.0);
}

// Rozwiązanie analityczne: y(t) = 1 + (1 + t)^90 * exp(-100*t)
double analytical_solution(double t) {
    return 1.0 + pow(1.0 + t, 90.0) * exp(-100.0 * t);
}

// Metoda Eulera bezpośrednia (explicit Euler)
double euler_explicit_step(double t, double y, double dt) {
    return y + dt * f(t, y);
}

// Metoda Eulera pośrednia (implicit Euler)
// y_{n+1} = y_n - dt * p(t_{n+1}) * (y_{n+1} - 1)
// y_{n+1} * (1 + dt * p(t_{n+1})) = y_n + dt * p(t_{n+1})
double euler_implicit_step(double t, double y, double dt) {
    double t_next = t + dt;
    double p_next = p_function(t_next);
    return (y + dt * p_next) / (1.0 + dt * p_next);
}

// Metoda trapezów
// y_{n+1} = y_n + (dt/2) * [f(t_n, y_n) + f(t_{n+1}, y_{n+1})]
// Rozwiązujemy równanie nieliniowe iteracyjnie (metoda punktu stałego)
double trapezoidal_step(double t, double y, double dt) {
    double t_next = t + dt;
    double f_n = f(t, y);

    // Iteracja punktu stałego
    double y_next = y; // Początkowe przybliżenie
    for (int iter = 0; iter < 10; iter++) {
        double f_next = f(t_next, y_next);
        y_next = y + 0.5 * dt * (f_n + f_next);
    }

    return y_next;
}

// Struktura do przechowywania wyników
struct Solution {
    vector<double> t;
    vector<double> y;
};

// Rozwiązywanie ODE daną metodą
Solution solve_ode(double t0, double y0, double t_end, double dt,
                    double (*step_method)(double, double, double)) {
    Solution sol;
    double t = t0;
    double y = y0;

    sol.t.push_back(t);
    sol.y.push_back(y);

    while (t < t_end) {
        if (t + dt > t_end) {
            dt = t_end - t;
        }

        y = step_method(t, y, dt);
        t += dt;

        sol.t.push_back(t);
        sol.y.push_back(y);
    }

    return sol;
}

// Zapisywanie wyników do pliku CSV
void save_to_csv(const string& filename, const Solution& sol, bool include_analytical = true) {
    ofstream file(filename);
    file << fixed << setprecision(10);

    if (include_analytical) {
        file << "t,y_numerical,y_analytical,error\n";
        for (size_t i = 0; i < sol.t.size(); i++) {
            double y_anal = analytical_solution(sol.t[i]);
            double error = abs(sol.y[i] - y_anal);
            file << sol.t[i] << "," << sol.y[i] << "," << y_anal << "," << error << "\n";
        }
    } else {
        file << "t,y\n";
        for (size_t i = 0; i < sol.t.size(); i++) {
            file << sol.t[i] << "," << sol.y[i] << "\n";
        }
    }

    file.close();
    cout << "Zapisano: " << filename << endl;
}

// Zapisywanie tylko rozwiązania analitycznego
void save_analytical_to_csv(const string& filename, double t0, double t_end, int n_points) {
    ofstream file(filename);
    file << fixed << setprecision(10);
    file << "t,y_analytical\n";

    double dt = (t_end - t0) / (n_points - 1);
    for (int i = 0; i < n_points; i++) {
        double t = t0 + i * dt;
        file << t << "," << analytical_solution(t) << "\n";
    }

    file.close();
    cout << "Zapisano: " << filename << endl;
}

// Obliczanie maksymalnego błędu
double compute_max_error(const Solution& sol) {
    double max_error = 0.0;
    for (size_t i = 0; i < sol.t.size(); i++) {
        double error = abs(sol.y[i] - analytical_solution(sol.t[i]));
        if (error > max_error) {
            max_error = error;
        }
    }
    return max_error;
}

// Analiza zbieżności - badanie zależności błędu od kroku
void convergence_analysis(double t0, double y0, double t_end) {
    ofstream file("convergence_analysis.csv");
    file << fixed << setprecision(15);
    file << "dt,error_euler_explicit,error_euler_implicit,error_trapezoidal\n";

    cout << "\n=== Analiza zbieżności ===" << endl;
    cout << setw(15) << "dt"
         << setw(20) << "Błąd Euler exp"
         << setw(20) << "Błąd Euler imp"
         << setw(20) << "Błąd trapez" << endl;
    cout << string(75, '-') << endl;

    // Testujemy różne kroki czasowe
    vector<double> dt_values;
    for (double dt = 0.1; dt >= 1e-6; dt /= 1.5) {
        dt_values.push_back(dt);
    }

    for (double dt : dt_values) {
        // Tylko dla metod stabilnych przy danym kroku
        double error_explicit = 0.0;
        double error_implicit = 0.0;
        double error_trapezoidal = 0.0;

        // Euler explicit - może być niestabilny dla dużych dt
        if (dt <= 0.025) { // Tylko dla stabilnych kroków
            Solution sol_explicit = solve_ode(t0, y0, t_end, dt, euler_explicit_step);
            error_explicit = compute_max_error(sol_explicit);
        }

        // Euler implicit - zawsze stabilny
        Solution sol_implicit = solve_ode(t0, y0, t_end, dt, euler_implicit_step);
        error_implicit = compute_max_error(sol_implicit);

        // Trapezoidal - zawsze stabilny
        Solution sol_trapezoidal = solve_ode(t0, y0, t_end, dt, trapezoidal_step);
        error_trapezoidal = compute_max_error(sol_trapezoidal);

        cout << setw(15) << scientific << dt
             << setw(20) << (error_explicit > 0 ? error_explicit : 0.0)
             << setw(20) << error_implicit
             << setw(20) << error_trapezoidal << endl;

        file << dt << ","
             << (error_explicit > 0 ? error_explicit : 0.0) << ","
             << error_implicit << ","
             << error_trapezoidal << "\n";
    }

    file.close();
    cout << "\nZapisano: convergence_analysis.csv" << endl;
}

int main() {
    // Parametry problemu
    double t0 = 0.0;
    double y0 = 2.0;
    double t_end = 0.5;

    cout << "=== Rozwiązywanie równania różniczkowego ===" << endl;
    cout << "y'(t) + p(t)*(y(t) - 1) = 0" << endl;
    cout << "p(t) = (100*t + 10)/(t + 1)" << endl;
    cout << "Warunek początkowy: y(0) = " << y0 << endl;
    cout << "Przedział: t ∈ [" << t0 << ", " << t_end << "]" << endl;
    cout << string(60, '=') << endl;

    // ========================================================================
    // CZĘŚĆ 1: Metoda Eulera bezpośrednia - 3 przypadki
    // ========================================================================

    cout << "\n1. Metoda Eulera bezpośrednia:" << endl;

    // Przypadek 1a: Stabilny (mały krok)
    double dt_stable = 0.005;
    cout << "   a) Stabilny (dt = " << dt_stable << ")" << endl;
    Solution sol_euler_stable = solve_ode(t0, y0, t_end, dt_stable, euler_explicit_step);
    save_to_csv("euler_explicit_stable.csv", sol_euler_stable);

    // Przypadek 1b: Niestabilny (duży krok)
    double dt_unstable = 0.05;
    cout << "   b) Niestabilny (dt = " << dt_unstable << ")" << endl;
    Solution sol_euler_unstable = solve_ode(t0, y0, t_end, dt_unstable, euler_explicit_step);
    save_to_csv("euler_explicit_unstable.csv", sol_euler_unstable, false);

    // Przypadek 1c: Graniczny (krok na granicy stabilności)
    double dt_marginal = 0.02;
    cout << "   c) Graniczny (dt = " << dt_marginal << ")" << endl;
    Solution sol_euler_marginal = solve_ode(t0, y0, t_end, dt_marginal, euler_explicit_step);
    save_to_csv("euler_explicit_marginal.csv", sol_euler_marginal);

    // ========================================================================
    // CZĘŚĆ 2: Metoda Eulera pośrednia
    // ========================================================================

    cout << "\n2. Metoda Eulera pośrednia:" << endl;
    double dt_implicit = 0.01;
    cout << "   dt = " << dt_implicit << endl;
    Solution sol_euler_implicit = solve_ode(t0, y0, t_end, dt_implicit, euler_implicit_step);
    save_to_csv("euler_implicit.csv", sol_euler_implicit);

    // ========================================================================
    // CZĘŚĆ 3: Metoda trapezów
    // ========================================================================

    cout << "\n3. Metoda trapezów:" << endl;
    double dt_trap = 0.01;
    cout << "   dt = " << dt_trap << endl;
    Solution sol_trapezoidal = solve_ode(t0, y0, t_end, dt_trap, trapezoidal_step);
    save_to_csv("trapezoidal.csv", sol_trapezoidal);

    // ========================================================================
    // CZĘŚĆ 4: Rozwiązanie analityczne (dla porównania)
    // ========================================================================

    cout << "\n4. Rozwiązanie analityczne (linia ciągła):" << endl;
    save_analytical_to_csv("analytical.csv", t0, t_end, 1000);

    // ========================================================================
    // CZĘŚĆ 5: Analiza zbieżności
    // ========================================================================

    convergence_analysis(t0, y0, t_end);

    // ========================================================================
    // CZĘŚĆ 6: Weryfikacja warunków stabilności
    // ========================================================================

    cout << "\n=== Warunki stabilności ===" << endl;
    cout << "\nMetoda Eulera bezpośrednia:" << endl;
    cout << "Warunek: dt <= 2/p(t)" << endl;
    cout << "Dla t=0: p(0) = " << p_function(0.0)
         << " => dt_max = " << 2.0/p_function(0.0) << endl;
    cout << "Dla t→∞: p(∞) ≈ 100 => dt_max ≈ " << 2.0/100.0 << endl;
    cout << "\nMetoda Eulera pośrednia: bezwarunkowo stabilna" << endl;
    cout << "Metoda trapezów: bezwarunkowo stabilna" << endl;

    // ========================================================================
    // CZĘŚĆ 7: Statystyki błędów
    // ========================================================================

    cout << "\n=== Błędy maksymalne ===" << endl;
    cout << fixed << setprecision(10);
    cout << "Euler bezpośrednia (stabilna): " << compute_max_error(sol_euler_stable) << endl;
    cout << "Euler bezpośrednia (graniczna): " << compute_max_error(sol_euler_marginal) << endl;
    cout << "Euler pośrednia: " << compute_max_error(sol_euler_implicit) << endl;
    cout << "Trapezów: " << compute_max_error(sol_trapezoidal) << endl;

    cout << "\n=== Program zakończony pomyślnie ===" << endl;
    cout << "Wygenerowano pliki CSV gotowe do wizualizacji w Python/gnuplot" << endl;

    return 0;
}
