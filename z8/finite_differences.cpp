#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

// Szablon funkcji - funkcja testowa
template <typename T>
T test_function(T x) {
    return std::cos(x);
}

// Dokładna pochodna funkcji testowej
template <typename T>
T exact_derivative(T x) {
    return -std::sin(x);
}

// Dwupunktowe przybliżenie do przodu (forward difference) - O(h)
template <typename T>
T forward_diff_2pt(T (*f)(T), T x, T h) {
    return (f(x + h) - f(x)) / h;
}

// Dwupunktowe przybliżenie do tyłu (backward difference) - O(h)
template <typename T>
T backward_diff_2pt(T (*f)(T), T x, T h) {
    return (f(x) - f(x - h)) / h;
}

// Trzypunktowe przybliżenie centralne - O(h^2)
template <typename T>
T central_diff_3pt(T (*f)(T), T x, T h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

// Trzypunktowe przybliżenie jednostronne na brzegu początkowym - O(h^2)
template <typename T>
T forward_diff_3pt(T (*f)(T), T x, T h) {
    return (-3 * f(x) / 2 + 2 * f(x + h) - f(x + 2*h) / 2) / h;
}

// Trzypunktowe przybliżenie jednostronne na brzegu końcowym - O(h^2)
template <typename T>
T backward_diff_3pt(T (*f)(T), T x, T h) {
    return (3 * f(x) / 2 - 2 * f(x - h) + f(x - 2*h) / 2) / h;
}

// Pięciopunktowe przybliżenie centralne - O(h^4)
template <typename T>
T central_diff_5pt(T (*f)(T), T x, T h) {
    return (f(x - 2*h) / 12 - 2 * f(x - h) / 3 + 2 * f(x + h) / 3 - f(x + 2*h) / 12) / h;
}

// Struktura przechowująca wyniki dla danego kroku h
template <typename T>
struct Results {
    T h;
    T x;
    T exact;
    T forward_2pt;
    T backward_2pt;
    T central_3pt;
    T forward_3pt;
    T backward_3pt;
    T central_5pt;
    T error_forward_2pt;
    T error_backward_2pt;
    T error_central_3pt;
    T error_forward_3pt;
    T error_backward_3pt;
    T error_central_5pt;
};

// Funkcja obliczająca wszystkie przybliżenia dla danego punktu
template <typename T>
Results<T> compute_derivatives(T (*f)(T), T x, T h, bool use_forward_3pt, bool use_backward_3pt, bool use_5pt) {
    Results<T> res;
    res.h = h;
    res.x = x;
    res.exact = exact_derivative(x);

    // Przybliżenia dwupunktowe
    res.forward_2pt = forward_diff_2pt(f, x, h);
    res.backward_2pt = backward_diff_2pt(f, x, h);
    res.central_3pt = central_diff_3pt(f, x, h);

    // Przybliżenia trzypunktowe jednostronne
    if (use_forward_3pt) {
        res.forward_3pt = forward_diff_3pt(f, x, h);
    } else {
        res.forward_3pt = 0;
    }

    if (use_backward_3pt) {
        res.backward_3pt = backward_diff_3pt(f, x, h);
    } else {
        res.backward_3pt = 0;
    }

    // Przybliżenie pięciopunktowe
    if (use_5pt) {
        res.central_5pt = central_diff_5pt(f, x, h);
    } else {
        res.central_5pt = 0;
    }

    // Błędy bezwzględne
    res.error_forward_2pt = std::abs(res.forward_2pt - res.exact);
    res.error_backward_2pt = std::abs(res.backward_2pt - res.exact);
    res.error_central_3pt = std::abs(res.central_3pt - res.exact);
    res.error_forward_3pt = use_forward_3pt ? std::abs(res.forward_3pt - res.exact) : 0;
    res.error_backward_3pt = use_backward_3pt ? std::abs(res.backward_3pt - res.exact) : 0;
    res.error_central_5pt = use_5pt ? std::abs(res.central_5pt - res.exact) : 0;

    return res;
}

// Funkcja generująca dane do wykresu
template <typename T>
void generate_convergence_data(const std::string& filename_prefix) {
    const T x_test = M_PI / 4; // Punkt testowy w środku przedziału
    const T x_start = 0.0;     // Brzeg początkowy
    const T x_end = M_PI / 2;  // Brzeg końcowy

    std::vector<T> h_values;

    // Generujemy wartości h od 1 do 10^-14
    for (int exp = 0; exp >= -14; exp--) {
        T h = std::pow(10.0, exp);
        h_values.push_back(h);
    }

    // Pliki wyjściowe
    std::ofstream file_middle(filename_prefix + "_middle.dat");
    std::ofstream file_start(filename_prefix + "_start.dat");
    std::ofstream file_end(filename_prefix + "_end.dat");

    file_middle << std::scientific << std::setprecision(16);
    file_start << std::scientific << std::setprecision(16);
    file_end << std::scientific << std::setprecision(16);

    // Nagłówki
    file_middle << "# log10(h) log10(error_forward_2pt) log10(error_backward_2pt) log10(error_central_3pt) log10(error_central_5pt)\n";
    file_start << "# log10(h) log10(error_forward_2pt) log10(error_central_3pt) log10(error_forward_3pt)\n";
    file_end << "# log10(h) log10(error_backward_2pt) log10(error_central_3pt) log10(error_backward_3pt)\n";

    std::cout << "\n=== Analiza dla typu: " << (sizeof(T) == sizeof(double) ? "double" : "long double") << " ===\n\n";

    // Punkt środkowy
    std::cout << "Punkt środkowy (x = π/4):\n";
    std::cout << std::setw(12) << "h"
              << std::setw(15) << "Forward 2pt"
              << std::setw(15) << "Backward 2pt"
              << std::setw(15) << "Central 3pt"
              << std::setw(15) << "Central 5pt" << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (T h : h_values) {
        Results<T> res = compute_derivatives(test_function<T>, x_test, h, false, false, h >= 2e-14);

        if (res.error_forward_2pt > 0 && res.error_backward_2pt > 0 && res.error_central_3pt > 0) {
            file_middle << std::log10(h) << " "
                       << std::log10(res.error_forward_2pt) << " "
                       << std::log10(res.error_backward_2pt) << " "
                       << std::log10(res.error_central_3pt);

            if (res.error_central_5pt > 0) {
                file_middle << " " << std::log10(res.error_central_5pt);
            }
            file_middle << "\n";

            std::cout << std::scientific << std::setprecision(4)
                     << std::setw(12) << h
                     << std::setw(15) << res.error_forward_2pt
                     << std::setw(15) << res.error_backward_2pt
                     << std::setw(15) << res.error_central_3pt
                     << std::setw(15) << res.error_central_5pt << "\n";
        }
    }

    // Brzeg początkowy
    std::cout << "\nBrzeg początkowy (x = 0):\n";
    std::cout << std::setw(12) << "h"
              << std::setw(15) << "Forward 2pt"
              << std::setw(15) << "Central 3pt"
              << std::setw(15) << "Forward 3pt" << "\n";
    std::cout << std::string(57, '-') << "\n";

    for (T h : h_values) {
        if (h < M_PI / 4) { // Upewniamy się, że mamy punkty w przedziale
            Results<T> res = compute_derivatives(test_function<T>, x_start, h, true, false, false);

            if (res.error_forward_2pt > 0 && res.error_central_3pt > 0 && res.error_forward_3pt > 0) {
                file_start << std::log10(h) << " "
                          << std::log10(res.error_forward_2pt) << " "
                          << std::log10(res.error_central_3pt) << " "
                          << std::log10(res.error_forward_3pt) << "\n";

                std::cout << std::scientific << std::setprecision(4)
                         << std::setw(12) << h
                         << std::setw(15) << res.error_forward_2pt
                         << std::setw(15) << res.error_central_3pt
                         << std::setw(15) << res.error_forward_3pt << "\n";
            }
        }
    }

    // Brzeg końcowy
    std::cout << "\nBrzeg końcowy (x = π/2):\n";
    std::cout << std::setw(12) << "h"
              << std::setw(15) << "Backward 2pt"
              << std::setw(15) << "Central 3pt"
              << std::setw(15) << "Backward 3pt" << "\n";
    std::cout << std::string(57, '-') << "\n";

    for (T h : h_values) {
        if (h < M_PI / 4) {
            Results<T> res = compute_derivatives(test_function<T>, x_end, h, false, true, false);

            if (res.error_backward_2pt > 0 && res.error_central_3pt > 0 && res.error_backward_3pt > 0) {
                file_end << std::log10(h) << " "
                        << std::log10(res.error_backward_2pt) << " "
                        << std::log10(res.error_central_3pt) << " "
                        << std::log10(res.error_backward_3pt) << "\n";

                std::cout << std::scientific << std::setprecision(4)
                         << std::setw(12) << h
                         << std::setw(15) << res.error_backward_2pt
                         << std::setw(15) << res.error_central_3pt
                         << std::setw(15) << res.error_backward_3pt << "\n";
            }
        }
    }

    file_middle.close();
    file_start.close();
    file_end.close();
}

// Funkcja wyznaczająca rząd dokładności
template <typename T>
void estimate_convergence_order() {
    const T x_test = M_PI / 4;

    std::cout << "\n=== Wyznaczanie doświadczalnego rzędu dokładności ===\n\n";

    T h1 = 0.1;
    T h2 = 0.01;

    Results<T> res1 = compute_derivatives(test_function<T>, x_test, h1, false, false, true);
    Results<T> res2 = compute_derivatives(test_function<T>, x_test, h2, false, false, true);

    auto calc_order = [](T e1, T e2, T h1, T h2) {
        return (std::log10(e2) - std::log10(e1)) / (std::log10(h2) - std::log10(h1));
    };

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Metoda                   Rząd teoretyczny    Rząd doświadczalny\n";
    std::cout << std::string(65, '-') << "\n";

    std::cout << "Forward 2pt              " << std::setw(8) << 1
              << std::setw(24) << calc_order(res1.error_forward_2pt, res2.error_forward_2pt, h1, h2) << "\n";

    std::cout << "Backward 2pt             " << std::setw(8) << 1
              << std::setw(24) << calc_order(res1.error_backward_2pt, res2.error_backward_2pt, h1, h2) << "\n";

    std::cout << "Central 3pt              " << std::setw(8) << 2
              << std::setw(24) << calc_order(res1.error_central_3pt, res2.error_central_3pt, h1, h2) << "\n";

    std::cout << "Central 5pt              " << std::setw(8) << 4
              << std::setw(24) << calc_order(res1.error_central_5pt, res2.error_central_5pt, h1, h2) << "\n";
}

int main() {
    std::cout << "=================================================================\n";
    std::cout << "  Analiza przybliżeń różnicowych pierwszej pochodnej\n";
    std::cout << "  Funkcja: f(x) = cos(x), f'(x) = -sin(x)\n";
    std::cout << "  Przedział: [0, π/2]\n";
    std::cout << "=================================================================\n";

    // Analiza dla typu double
    std::cout << "\n*** TYP: DOUBLE ***\n";
    generate_convergence_data<double>("convergence_double");
    estimate_convergence_order<double>();

    // Analiza dla typu long double
    std::cout << "\n\n*** TYP: LONG DOUBLE ***\n";
    generate_convergence_data<long double>("convergence_long_double");
    estimate_convergence_order<long double>();

    std::cout << "\n=================================================================\n";
    std::cout << "Dane zapisane do plików:\n";
    std::cout << "  - convergence_double_*.dat\n";
    std::cout << "  - convergence_long_double_*.dat\n";
    std::cout << "\nWygeneruj wykresy używając skryptu gnuplot: plot_convergence.gnu\n";
    std::cout << "=================================================================\n";

    return 0;
}
