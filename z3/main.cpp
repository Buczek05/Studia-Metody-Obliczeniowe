#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <string>

using namespace std;

// Struktura przechowująca parametry obliczeń
struct Parameters {
    double epsilon;      // Tolerancja dla estymatora błędu
    double delta;        // Tolerancja dla residuum
    int max_iterations;  // Maksymalna liczba iteracji

    Parameters(double eps = 1e-10, double del = 1e-10, int max_iter = 100)
        : epsilon(eps), delta(del), max_iterations(max_iter) {}
};

// Struktura przechowująca wyniki obliczeń
struct Result {
    double root;
    int iterations;
    double final_error;
    double final_residuum;
    bool converged;
    string stop_criterion;
};

// Wypisywanie nagłówka tabeli wyników
void printHeader() {
    cout << setw(6) << "Iter"
         << setw(20) << "x_n"
         << setw(20) << "f(x_n)"
         << setw(20) << "|x_n - x_{n-1}|"
         << endl;
    cout << string(66, '-') << endl;
}

// Wypisywanie wiersza wyników
void printIteration(int iter, double x, double fx, double error) {
    cout << setw(6) << iter
         << setw(20) << scientific << setprecision(10) << x
         << setw(20) << scientific << setprecision(10) << fx
         << setw(20) << scientific << setprecision(10) << error
         << endl;
}

// Wypisywanie podsumowania
void printSummary(const Result& res) {
    cout << "\n=== PODSUMOWANIE ===" << endl;
    cout << "Zbieżność: " << (res.converged ? "TAK" : "NIE") << endl;
    if (res.converged) {
        cout << "Kryterium stopu: " << res.stop_criterion << endl;
    }
    cout << "Liczba iteracji: " << res.iterations << endl;
    cout << "Rozwiązanie: " << scientific << setprecision(15) << res.root << endl;
    cout << "Końcowe residuum: " << scientific << setprecision(10) << res.final_residuum << endl;
    cout << "Końcowy błąd: " << scientific << setprecision(10) << res.final_error << endl;
    cout << string(66, '=') << endl << endl;
}

// ============================================
// METODA PICARDA
// ============================================
Result picard(function<double(double)> g, function<double(double)> f,
              double x0, const Parameters& params) {
    Result res;
    res.converged = false;

    cout << "\n=== METODA PICARDA ===" << endl;
    printHeader();

    double x_old = x0;
    double x_new;

    for (int i = 0; i < params.max_iterations; i++) {
        x_new = g(x_old);
        double fx = f(x_new);
        double error = fabs(x_new - x_old);

        printIteration(i, x_new, fx, error);

        // Sprawdzanie kryteriów stopu
        if (error < params.epsilon) {
            res.converged = true;
            res.stop_criterion = "|x_n - x_{n-1}| < epsilon";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx);
            break;
        }

        if (fabs(fx) < params.delta) {
            res.converged = true;
            res.stop_criterion = "|f(x_n)| < delta";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx);
            break;
        }

        x_old = x_new;
    }

    if (!res.converged) {
        res.iterations = params.max_iterations;
        res.root = x_new;
        res.final_error = fabs(x_new - x_old);
        res.final_residuum = fabs(f(x_new));
    }

    return res;
}

// ============================================
// METODA BISEKCJI
// ============================================
Result bisection(function<double(double)> f, double a, double b,
                 const Parameters& params) {
    Result res;
    res.converged = false;

    cout << "\n=== METODA BISEKCJI ===" << endl;

    // Sprawdzenie warunku początkowego
    if (f(a) * f(b) >= 0) {
        cout << "BŁĄD: f(a) * f(b) >= 0. Metoda nie może być zastosowana!" << endl;
        res.iterations = 0;
        res.root = 0;
        return res;
    }

    printHeader();

    double c, fc;
    double prev_c = a;

    for (int i = 0; i < params.max_iterations; i++) {
        c = (a + b) / 2.0;
        fc = f(c);
        double error = fabs(c - prev_c);

        printIteration(i, c, fc, error);

        // Sprawdzanie kryteriów stopu
        if (fabs(fc) < params.delta) {
            res.converged = true;
            res.stop_criterion = "|f(x_n)| < delta";
            res.iterations = i + 1;
            res.root = c;
            res.final_error = error;
            res.final_residuum = fabs(fc);
            break;
        }

        if (fabs(b - a) < params.epsilon) {
            res.converged = true;
            res.stop_criterion = "|b - a| < epsilon";
            res.iterations = i + 1;
            res.root = c;
            res.final_error = fabs(b - a);
            res.final_residuum = fabs(fc);
            break;
        }

        // Aktualizacja przedziału
        if (f(a) * fc < 0) {
            b = c;
        } else {
            a = c;
        }

        prev_c = c;
    }

    if (!res.converged) {
        res.iterations = params.max_iterations;
        res.root = c;
        res.final_error = fabs(b - a);
        res.final_residuum = fabs(fc);
    }

    return res;
}

// ============================================
// METODA NEWTONA
// ============================================
Result newton(function<double(double)> f, function<double(double)> df,
              double x0, const Parameters& params) {
    Result res;
    res.converged = false;

    cout << "\n=== METODA NEWTONA ===" << endl;
    printHeader();

    double x_old = x0;
    double x_new;

    for (int i = 0; i < params.max_iterations; i++) {
        double fx = f(x_old);
        double dfx = df(x_old);

        if (fabs(dfx) < 1e-15) {
            cout << "BŁĄD: Pochodna bliska zeru!" << endl;
            break;
        }

        x_new = x_old - fx / dfx;
        double fx_new = f(x_new);
        double error = fabs(x_new - x_old);

        printIteration(i, x_new, fx_new, error);

        // Sprawdzanie kryteriów stopu
        if (error < params.epsilon) {
            res.converged = true;
            res.stop_criterion = "|x_n - x_{n-1}| < epsilon";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx_new);
            break;
        }

        if (fabs(fx_new) < params.delta) {
            res.converged = true;
            res.stop_criterion = "|f(x_n)| < delta";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx_new);
            break;
        }

        x_old = x_new;
    }

    if (!res.converged) {
        res.iterations = params.max_iterations;
        res.root = x_new;
        res.final_error = fabs(x_new - x_old);
        res.final_residuum = fabs(f(x_new));
    }

    return res;
}

// ============================================
// METODA SIECZNYCH
// ============================================
Result secant(function<double(double)> f, double x0, double x1,
              const Parameters& params) {
    Result res;
    res.converged = false;

    cout << "\n=== METODA SIECZNYCH ===" << endl;
    printHeader();

    double x_old = x0;
    double x_curr = x1;
    double x_new;

    for (int i = 0; i < params.max_iterations; i++) {
        double f_old = f(x_old);
        double f_curr = f(x_curr);

        if (fabs(f_curr - f_old) < 1e-15) {
            cout << "BŁĄD: Różnica wartości funkcji bliska zeru!" << endl;
            break;
        }

        x_new = x_curr - f_curr * (x_curr - x_old) / (f_curr - f_old);
        double fx_new = f(x_new);
        double error = fabs(x_new - x_curr);

        printIteration(i, x_new, fx_new, error);

        // Sprawdzanie kryteriów stopu
        if (error < params.epsilon) {
            res.converged = true;
            res.stop_criterion = "|x_n - x_{n-1}| < epsilon";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx_new);
            break;
        }

        if (fabs(fx_new) < params.delta) {
            res.converged = true;
            res.stop_criterion = "|f(x_n)| < delta";
            res.iterations = i + 1;
            res.root = x_new;
            res.final_error = error;
            res.final_residuum = fabs(fx_new);
            break;
        }

        x_old = x_curr;
        x_curr = x_new;
    }

    if (!res.converged) {
        res.iterations = params.max_iterations;
        res.root = x_new;
        res.final_error = fabs(x_new - x_curr);
        res.final_residuum = fabs(f(x_new));
    }

    return res;
}

// ============================================
// DEFINICJE FUNKCJI DLA ZADAŃ
// ============================================

// Zadanie 1a: sinh(x) + x/4 - 1 = 0
double f1(double x) {
    return sinh(x) + x / 4.0 - 1.0;
}

double df1(double x) {
    return cosh(x) + 0.25;
}

// Przekształcenie dla metody Picarda: x = asinh(1 - x/4)
double g1(double x) {
    return asinh(1.0 - x / 4.0);
}

// Zadanie 1b: tanh(x) + 2(x - 1) = 0
double f2(double x) {
    return tanh(x) + 2.0 * (x - 1.0);
}

double df2(double x) {
    return 1.0 / (cosh(x) * cosh(x)) + 2.0;
}

// Przekształcenie dla metody Picarda: x = 1 - tanh(x)/2
double g2(double x) {
    return 1.0 - tanh(x) / 2.0;
}

// ============================================
// ALGORYTM HERONA (Bonus)
// ============================================
void heronAlgorithm(double a, double x0, const Parameters& params) {
    cout << "\n\n";
    cout << string(66, '=') << endl;
    cout << "=== ALGORYTM HERONA (obliczanie sqrt(" << a << ")) ===" << endl;
    cout << string(66, '=') << endl;

    printHeader();

    double x_old = x0;
    double x_new;

    for (int i = 0; i < params.max_iterations; i++) {
        x_new = 0.5 * (x_old + a / x_old);
        double error = fabs(x_new - x_old);
        double fx = x_new * x_new - a; // f(x) = x^2 - a

        printIteration(i, x_new, fx, error);

        if (error < params.epsilon) {
            cout << "\nZbieżność osiągnięta!" << endl;
            cout << "sqrt(" << a << ") = " << setprecision(15) << x_new << endl;
            cout << "Rzeczywista wartość: " << sqrt(a) << endl;
            cout << "Różnica: " << fabs(x_new - sqrt(a)) << endl;
            break;
        }

        x_old = x_new;
    }
}

// ============================================
// FUNKCJA GŁÓWNA
// ============================================
int main() {
    cout << fixed << setprecision(10);

    Parameters params(1e-10, 1e-10, 50);

    cout << "\n";
    cout << "################################################################" << endl;
    cout << "#                                                              #" << endl;
    cout << "#  METODY ROZWIĄZYWANIA NIELINIOWYCH RÓWNAŃ ALGEBRAICZNYCH    #" << endl;
    cout << "#                                                              #" << endl;
    cout << "################################################################" << endl;

    // ============================================
    // ZADANIE 1a: sinh(x) + x/4 - 1 = 0
    // ============================================
    cout << "\n\n";
    cout << string(66, '=') << endl;
    cout << "ZADANIE 1a: sinh(x) + x/4 - 1 = 0" << endl;
    cout << string(66, '=') << endl;

    double x0_1a = 0.5;

    Result res_picard_1a = picard(g1, f1, x0_1a, params);
    printSummary(res_picard_1a);

    Result res_bisection_1a = bisection(f1, 0.0, 2.0, params);
    printSummary(res_bisection_1a);

    Result res_newton_1a = newton(f1, df1, x0_1a, params);
    printSummary(res_newton_1a);

    Result res_secant_1a = secant(f1, 0.0, 1.0, params);
    printSummary(res_secant_1a);

    // ============================================
    // ZADANIE 1b: tanh(x) + 2(x - 1) = 0
    // ============================================
    cout << "\n\n";
    cout << string(66, '=') << endl;
    cout << "ZADANIE 1b: tanh(x) + 2(x - 1) = 0" << endl;
    cout << string(66, '=') << endl;

    double x0_1b = 0.5;

    Result res_picard_1b = picard(g2, f2, x0_1b, params);
    printSummary(res_picard_1b);

    Result res_bisection_1b = bisection(f2, 0.0, 1.0, params);
    printSummary(res_bisection_1b);

    Result res_newton_1b = newton(f2, df2, x0_1b, params);
    printSummary(res_newton_1b);

    Result res_secant_1b = secant(f2, 0.0, 1.0, params);
    printSummary(res_secant_1b);

    // ============================================
    // ZADANIE 2: Algorytm Herona
    // ============================================
    heronAlgorithm(16.0, 1.0, params);
    heronAlgorithm(2.0, 1.0, params);

    // ============================================
    // PORÓWNANIE METOD
    // ============================================
    cout << "\n\n";
    cout << string(66, '=') << endl;
    cout << "PORÓWNANIE METOD" << endl;
    cout << string(66, '=') << endl;

    cout << "\nZadanie 1a: sinh(x) + x/4 - 1 = 0" << endl;
    cout << "Metoda Picarda:   " << res_picard_1a.iterations << " iteracji" << endl;
    cout << "Metoda Bisekcji:  " << res_bisection_1a.iterations << " iteracji" << endl;
    cout << "Metoda Newtona:   " << res_newton_1a.iterations << " iteracji" << endl;
    cout << "Metoda Siecznych: " << res_secant_1a.iterations << " iteracji" << endl;

    cout << "\nZadanie 1b: tanh(x) + 2(x - 1) = 0" << endl;
    cout << "Metoda Picarda:   " << res_picard_1b.iterations << " iteracji" << endl;
    cout << "Metoda Bisekcji:  " << res_bisection_1b.iterations << " iteracji" << endl;
    cout << "Metoda Newtona:   " << res_newton_1b.iterations << " iteracji" << endl;
    cout << "Metoda Siecznych: " << res_secant_1b.iterations << " iteracji" << endl;

    return 0;
}
