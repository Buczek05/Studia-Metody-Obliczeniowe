#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

// ============================================================================
// ZADANIE 5: KWADRATURA GAUSSA
// ============================================================================

// Kwadratura Gaussa z 2 punktami dla przedziału [-1, 1]
double gaussQuadrature2Points(double (*f)(double), double a, double b) {
    // Węzły i wagi dla kwadratury Gaussa z 2 punktami
    const double x1 = -1.0 / std::sqrt(3.0);  // -√3/3 ≈ -0.5773502692
    const double x2 = 1.0 / std::sqrt(3.0);   //  √3/3 ≈  0.5773502692
    const double w1 = 1.0;
    const double w2 = 1.0;

    // Transformacja do przedziału [a, b]
    // x = ((b-a)/2) * t + (b+a)/2, gdzie t ∈ [-1, 1]
    double scale = (b - a) / 2.0;
    double shift = (b + a) / 2.0;

    double t1 = scale * x1 + shift;
    double t2 = scale * x2 + shift;

    return scale * (w1 * f(t1) + w2 * f(t2));
}

// Kwadratura Gaussa z n punktami (ogólna)
double gaussQuadrature(double (*f)(double), double a, double b, int n) {
    // Węzły i wagi dla różnych n
    std::vector<double> nodes, weights;

    if (n == 2) {
        nodes = {-1.0/std::sqrt(3.0), 1.0/std::sqrt(3.0)};
        weights = {1.0, 1.0};
    } else if (n == 3) {
        nodes = {-std::sqrt(3.0/5.0), 0.0, std::sqrt(3.0/5.0)};
        weights = {5.0/9.0, 8.0/9.0, 5.0/9.0};
    } else if (n == 4) {
        double sqrt_val = std::sqrt(3.0/7.0 - 2.0/7.0 * std::sqrt(6.0/5.0));
        double sqrt_val2 = std::sqrt(3.0/7.0 + 2.0/7.0 * std::sqrt(6.0/5.0));
        nodes = {-sqrt_val2, -sqrt_val, sqrt_val, sqrt_val2};
        double w1 = (18.0 + std::sqrt(30.0)) / 36.0;
        double w2 = (18.0 - std::sqrt(30.0)) / 36.0;
        weights = {w2, w1, w1, w2};
    } else {
        std::cerr << "Nieobsługiwana liczba punktów Gaussa: " << n << std::endl;
        return 0.0;
    }

    // Transformacja do przedziału [a, b]
    double scale = (b - a) / 2.0;
    double shift = (b + a) / 2.0;

    double sum = 0.0;
    for (size_t i = 0; i < nodes.size(); i++) {
        double t = scale * nodes[i] + shift;
        sum += weights[i] * f(t);
    }

    return scale * sum;
}

// Funkcja do zadania 5: f(x) = x^4 + 1
double func_x4_plus_1(double x) {
    return x * x * x * x + 1.0;
}

void zadanie5_kwadratura_gaussa() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  ZADANIE 5: KWADRATURA GAUSSA                                      ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n\n";

    std::cout << "Obliczanie całki: ∫₋₁¹ (x⁴ + 1) dx\n\n";

    // Obliczenie wartości dokładnej
    // ∫(x^4 + 1)dx = x^5/5 + x + C
    // [x^5/5 + x]₋₁¹ = (1/5 + 1) - (-1/5 - 1) = 2/5 + 2 = 12/5
    double exact = 12.0 / 5.0;

    std::cout << "Wartość dokładna: " << std::setprecision(15) << exact << "\n\n";

    // Kwadratura Gaussa z różną liczbą punktów
    std::cout << std::string(70, '-') << "\n";
    std::cout << std::setw(25) << "Metoda"
              << std::setw(20) << "Wynik"
              << std::setw(15) << "Błąd"
              << std::setw(15) << "Błąd wzgl. [%]\n";
    std::cout << std::string(70, '-') << "\n";

    for (int n = 2; n <= 4; n++) {
        double result = gaussQuadrature(func_x4_plus_1, -1.0, 1.0, n);
        double error = std::abs(exact - result);
        double rel_error = (error / std::abs(exact)) * 100.0;

        std::cout << std::setw(25) << ("Gauss " + std::to_string(n) + " punkty")
                  << std::setw(20) << std::fixed << std::setprecision(15) << result
                  << std::setw(15) << std::scientific << std::setprecision(4) << error
                  << std::setw(15) << std::fixed << std::setprecision(6) << rel_error << "\n";
    }

    std::cout << std::string(70, '-') << "\n\n";

    std::cout << "Wyjaśnienie:\n";
    std::cout << "• Kwadratura Gaussa z n punktami jest dokładna dla wielomianów\n";
    std::cout << "  stopnia ≤ 2n - 1.\n";
    std::cout << "• Dla n=2: dokładna dla wielomianów stopnia ≤ 3\n";
    std::cout << "• Dla n=3: dokładna dla wielomianów stopnia ≤ 5\n";
    std::cout << "• Nasza funkcja f(x) = x⁴ + 1 ma stopień 4\n";
    std::cout << "• Dlatego n=3 daje już wynik dokładny (w granicach błędu maszynowego)\n\n";
}

// ============================================================================
// ZADANIE 4: METODA ROMBERGA
// ============================================================================

// Metoda trapezów podstawowa
double trapezoidBasic(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }

    return h * sum;
}

// Metoda Romberga
double rombergIntegration(double (*f)(double), double a, double b, int max_level = 5) {
    std::vector<std::vector<double>> R(max_level + 1, std::vector<double>(max_level + 1, 0.0));

    std::cout << "\nTablica Romberga:\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << std::setw(5) << "k" << " | ";
    for (int m = 0; m <= max_level; m++) {
        std::cout << std::setw(15) << ("m=" + std::to_string(m));
    }
    std::cout << "\n" << std::string(80, '-') << "\n";

    // Kolumna 0: obliczenia metodą trapezów z różnymi h
    for (int k = 0; k <= max_level; k++) {
        int n = std::pow(2, k);  // Liczba przedziałów: 1, 2, 4, 8, 16, ...
        R[k][0] = trapezoidBasic(f, a, b, n);
    }

    // Ekstrapolacja Richardsona
    for (int m = 1; m <= max_level; m++) {
        for (int k = m; k <= max_level; k++) {
            R[k][m] = R[k][m-1] + (R[k][m-1] - R[k-1][m-1]) / (std::pow(4, m) - 1);
        }
    }

    // Wyświetlenie tablicy
    for (int k = 0; k <= max_level; k++) {
        std::cout << std::setw(5) << k << " | ";
        for (int m = 0; m <= k; m++) {
            std::cout << std::setw(15) << std::fixed << std::setprecision(8) << R[k][m];
        }
        std::cout << "\n";
    }
    std::cout << std::string(80, '-') << "\n";

    return R[max_level][max_level];
}

// Funkcja dla zadania 4 (interpolacja wartości z zadania)
// Używamy interpolacji liniowej między punktami
class PiecewiseLinearFunction {
private:
    std::vector<double> x_points;
    std::vector<double> y_points;

public:
    PiecewiseLinearFunction(const std::vector<double>& x, const std::vector<double>& y)
        : x_points(x), y_points(y) {}

    double operator()(double x) const {
        // Znajdź przedział
        for (size_t i = 0; i < x_points.size() - 1; i++) {
            if (x >= x_points[i] && x <= x_points[i+1]) {
                // Interpolacja liniowa
                double t = (x - x_points[i]) / (x_points[i+1] - x_points[i]);
                return y_points[i] + t * (y_points[i+1] - y_points[i]);
            }
        }
        return y_points.back();
    }
};

// Wrapper dla funkcji wskaźnikowej
PiecewiseLinearFunction* global_func_ptr = nullptr;
double wrapper_function(double x) {
    return (*global_func_ptr)(x);
}

void zadanie4_romberg() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  ZADANIE 4: METODA ROMBERGA                                        ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n\n";

    std::cout << "Dane z zadania:\n";
    std::cout << "x = [0, 1, 2, 3, 4, 5, 6, 7, 8]\n";
    std::cout << "f(x) = [-5, -3, 1, 2, 1, -1, 2, 5, 4]\n\n";

    // Dane z zadania
    std::vector<double> x = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> y = {-5, -3, 1, 2, 1, -1, 2, 5, 4};

    PiecewiseLinearFunction func(x, y);
    global_func_ptr = &func;

    std::cout << "Obliczanie całki metodą Romberga...\n";
    double result = rombergIntegration(wrapper_function, 0.0, 8.0, 3);

    std::cout << "\nWynik końcowy: ∫₀⁸ f(x) dx ≈ " << std::setprecision(10) << result << "\n\n";
}

// ============================================================================
// PRZYKŁAD: PORÓWNANIE METOD DLA PROSTEJ FUNKCJI
// ============================================================================

double simple_function(double x) {
    return std::sin(x);
}

void comparison_example() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  PRZYKŁAD: PORÓWNANIE METOD DLA ∫₀^π sin(x) dx                     ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n\n";

    double a = 0.0;
    double b = M_PI;
    double exact = 2.0;  // ∫₀^π sin(x) dx = [-cos(x)]₀^π = 2

    std::cout << "Wartość dokładna: " << exact << "\n\n";

    std::vector<int> n_values = {10, 50, 100};

    std::cout << std::string(90, '-') << "\n";
    std::cout << std::setw(20) << "Metoda";
    for (int n : n_values) {
        std::cout << std::setw(20) << ("n=" + std::to_string(n));
    }
    std::cout << "\n" << std::string(90, '-') << "\n";

    // Trapezy
    std::cout << std::setw(20) << "Trapezy";
    for (int n : n_values) {
        double result = trapezoidBasic(simple_function, a, b, n);
        std::cout << std::setw(20) << std::fixed << std::setprecision(10) << result;
    }
    std::cout << "\n";

    // Gauss 2 punkty
    std::cout << std::setw(20) << "Gauss-2 (złożona)";
    for (int n : n_values) {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            double a_i = a + i * h;
            double b_i = a + (i + 1) * h;
            sum += gaussQuadrature2Points(simple_function, a_i, b_i);
        }
        std::cout << std::setw(20) << std::fixed << std::setprecision(10) << sum;
    }
    std::cout << "\n";

    std::cout << std::string(90, '-') << "\n";
    std::cout << std::setw(20) << "Wartość dokładna" << std::setw(20) << exact << "\n";
    std::cout << std::string(90, '-') << "\n\n";
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << std::fixed << std::setprecision(10);

    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║        PRZYKŁADY ROZWIĄZAŃ ZADAŃ                                   ║\n";
    std::cout << "║        Zajęcia 13 - Kwadratury numeryczne                          ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";

    // Zadanie 5
    zadanie5_kwadratura_gaussa();

    // Zadanie 4
    zadanie4_romberg();

    // Przykład porównawczy
    comparison_example();

    return 0;
}
