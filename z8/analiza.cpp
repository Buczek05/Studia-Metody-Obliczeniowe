// Program pomocniczy do szczegółowej analizy pojedynczej metody
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

template <typename T>
void analyze_precision() {
    std::cout << "\n=== Analiza precyzji typu "
              << (sizeof(T) == sizeof(double) ? "double" : "long double")
              << " ===" << std::endl;
    std::cout << "Rozmiar: " << sizeof(T) << " bajtów" << std::endl;
    std::cout << "Cyfr znaczących: " << std::numeric_limits<T>::digits10 << std::endl;
    std::cout << "Epsilon maszynowy: " << std::scientific << std::setprecision(3)
              << std::numeric_limits<T>::epsilon() << std::endl;
    std::cout << "Min wartość: " << std::numeric_limits<T>::min() << std::endl;
    std::cout << "Max wartość: " << std::numeric_limits<T>::max() << std::endl;

    // Teoretyczne optymalne h dla różnych metod
    T eps = std::numeric_limits<T>::epsilon();
    std::cout << "\nTeoretyczne optymalne kroki h:" << std::endl;
    std::cout << "  O(h)  : h_opt ≈ " << std::sqrt(eps) << std::endl;
    std::cout << "  O(h²) : h_opt ≈ " << std::cbrt(eps) << std::endl;
    std::cout << "  O(h⁴) : h_opt ≈ " << std::pow(eps, 0.2) << std::endl;
}

template <typename T>
T test_cancellation(T h) {
    // Demonstracja catastrophic cancellation
    T x = 1.0;
    T f_plus = std::cos(x + h);
    T f_minus = std::cos(x);
    T diff = f_plus - f_minus;

    // Względny błąd zaokrąglenia
    T relative_error = std::numeric_limits<T>::epsilon() / diff;

    return relative_error;
}

template <typename T>
void analyze_cancellation() {
    std::cout << "\n=== Analiza catastrophic cancellation ===" << std::endl;
    std::cout << std::setw(12) << "h"
              << std::setw(15) << "f(x+h)-f(x)"
              << std::setw(15) << "Względny błąd" << std::endl;
    std::cout << std::string(42, '-') << std::endl;

    for (int exp = 0; exp >= -16; exp -= 2) {
        T h = std::pow(10.0, exp);
        T x = 1.0;
        T diff = std::cos(x + h) - std::cos(x);
        T rel_error = std::numeric_limits<T>::epsilon() / std::abs(diff);

        std::cout << std::scientific << std::setprecision(4)
                  << std::setw(12) << h
                  << std::setw(15) << diff
                  << std::setw(15) << rel_error << std::endl;

        if (rel_error > 1e-2) {
            std::cout << "  ^^^ Błędy zaokrągleń stają się znaczące!" << std::endl;
        }
    }
}

template <typename T>
void compare_methods_single_h(T h) {
    std::cout << "\n=== Porównanie metod dla h = " << h << " ===" << std::endl;

    T x = M_PI / 4;
    T exact = -std::sin(x);

    // Forward difference O(h)
    T forward = (std::cos(x + h) - std::cos(x)) / h;
    T error_forward = std::abs(forward - exact);

    // Central difference O(h²)
    T central3 = (std::cos(x + h) - std::cos(x - h)) / (2 * h);
    T error_central3 = std::abs(central3 - exact);

    // Central difference O(h⁴)
    T central5 = (std::cos(x - 2*h)/12 - 2*std::cos(x - h)/3
                  + 2*std::cos(x + h)/3 - std::cos(x + 2*h)/12) / h;
    T error_central5 = std::abs(central5 - exact);

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Wartość dokładna: " << exact << std::endl;
    std::cout << "\nMetoda               Wartość          Błąd bezwzględny" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Forward O(h)    " << std::setw(15) << forward
              << "  " << std::scientific << std::setw(12) << error_forward << std::endl;
    std::cout << "Central O(h²)   " << std::fixed << std::setw(15) << central3
              << "  " << std::scientific << std::setw(12) << error_central3 << std::endl;
    std::cout << "Central O(h⁴)   " << std::fixed << std::setw(15) << central5
              << "  " << std::scientific << std::setw(12) << error_central5 << std::endl;
}

template <typename T>
void find_optimal_h() {
    std::cout << "\n=== Szukanie optymalnego h (Central O(h²)) ===" << std::endl;

    T x = M_PI / 4;
    T exact = -std::sin(x);
    T min_error = std::numeric_limits<T>::max();
    T optimal_h = 0;

    std::cout << std::setw(12) << "h"
              << std::setw(15) << "Błąd" << std::endl;
    std::cout << std::string(27, '-') << std::endl;

    for (int exp = 0; exp >= -16; exp--) {
        T h = std::pow(10.0, exp);
        T approx = (std::cos(x + h) - std::cos(x - h)) / (2 * h);
        T error = std::abs(approx - exact);

        std::cout << std::scientific << std::setprecision(4)
                  << std::setw(12) << h
                  << std::setw(15) << error;

        if (error < min_error) {
            min_error = error;
            optimal_h = h;
            std::cout << " <- Najmniejszy błąd";
        }
        std::cout << std::endl;
    }

    std::cout << "\nOptymalny krok: h_opt = " << optimal_h << std::endl;
    std::cout << "Minimalny błąd: " << min_error << std::endl;

    T eps = std::numeric_limits<T>::epsilon();
    T theoretical_h = std::cbrt(eps);
    std::cout << "Teoretyczny h_opt (ε^(1/3)): " << theoretical_h << std::endl;
}

int main() {
    std::cout << "======================================================" << std::endl;
    std::cout << "  Szczegółowa analiza metod różnicowych" << std::endl;
    std::cout << "======================================================" << std::endl;

    // Analiza typu double
    analyze_precision<double>();
    analyze_cancellation<double>();
    compare_methods_single_h<double>(0.01);
    compare_methods_single_h<double>(0.001);
    compare_methods_single_h<double>(1e-8);
    find_optimal_h<double>();

    std::cout << "\n\n";

    // Analiza typu long double
    analyze_precision<long double>();
    analyze_cancellation<long double>();
    compare_methods_single_h<long double>(0.01L);
    compare_methods_single_h<long double>(0.001L);
    compare_methods_single_h<long double>(1e-10L);
    find_optimal_h<long double>();

    return 0;
}
