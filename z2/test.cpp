#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

// Testy jednostkowe dla funkcji obliczającej f(x) = x^3 / (6 * (sinh(x) - x))

// Funkcje z main.cpp (skopiowane do testów)
double compute_naive(double x) {
    double sinh_x = std::sinh(x);
    double denominator = 6.0 * (sinh_x - x);
    if (std::abs(denominator) < 1e-300) {
        return NAN;
    }
    return (x * x * x) / denominator;
}

double compute_taylor(double x) {
    double x2 = x * x;
    double x4 = x2 * x2;
    double x6 = x4 * x2;
    double x8 = x4 * x4;

    double series = 1.0
                  + x2 / 20.0
                  + x4 / 840.0
                  + x6 / 37800.0
                  + x8 / 1995840.0;

    return 1.0 / series;
}

double compute_hybrid(double x) {
    const double threshold = 0.1;

    if (std::abs(x) < threshold) {
        return compute_taylor(x);
    } else {
        return compute_naive(x);
    }
}

// Funkcja pomocnicza do porównywania liczb zmiennoprzecinkowych
bool approx_equal(double a, double b, double tolerance = 1e-10) {
    if (std::isnan(a) || std::isnan(b)) {
        return std::isnan(a) && std::isnan(b);
    }
    return std::abs(a - b) / std::max(std::abs(a), std::abs(b)) < tolerance;
}

// Testy
void test_limit_at_zero() {
    std::cout << "Test 1: Wartość graniczna lim(x->0) f(x) = 1" << std::endl;

    double x = 1e-10;
    double result_taylor = compute_taylor(x);

    std::cout << "  f(" << x << ") [Taylor] = " << std::setprecision(15) << result_taylor << std::endl;

    // Wartość powinna być bliska 1.0
    assert(approx_equal(result_taylor, 1.0, 1e-6));

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_taylor_for_small_x() {
    std::cout << "Test 2: Szereg Taylora dla małych x" << std::endl;

    double x_values[] = {1e-10, 1e-8, 1e-6, 1e-4, 1e-2};

    for (double x : x_values) {
        double result = compute_taylor(x);
        std::cout << "  f(" << x << ") = " << std::setprecision(10) << result << std::endl;

        // Dla małych x, wynik powinien być bliski 1.0
        assert(result <= 1.0 && result > 0.95);
    }

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_naive_for_large_x() {
    std::cout << "Test 3: Metoda naiwna dla dużych x" << std::endl;

    double x_values[] = {1.0, 2.0, 5.0, 10.0};

    for (double x : x_values) {
        double result = compute_naive(x);
        std::cout << "  f(" << x << ") = " << std::setprecision(10) << result << std::endl;

        // Dla dużych x, funkcja maleje do 0
        assert(result > 0.0 && result < 1.0);
    }

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_hybrid_consistency() {
    std::cout << "Test 4: Spójność metody hybrydowej" << std::endl;

    // Testuj w okolicach progu przełączenia (threshold = 0.1)
    double x_below = 0.09;
    double x_above = 0.11;

    double result_below = compute_hybrid(x_below);
    double result_above = compute_hybrid(x_above);

    std::cout << "  f(" << x_below << ") = " << std::setprecision(10) << result_below << std::endl;
    std::cout << "  f(" << x_above << ") = " << std::setprecision(10) << result_above << std::endl;

    // Wartości powinny być zbliżone (funkcja jest ciągła)
    double diff = std::abs(result_below - result_above);
    std::cout << "  Różnica: " << diff << std::endl;

    assert(diff < 0.01);  // Mniej niż 1% różnicy

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_symmetry() {
    std::cout << "Test 5: Symetria f(-x) ≈ f(x)" << std::endl;

    // Funkcja f(x) powinna być parzysta (symmetric)
    // Sprawdzmy to dla kilku wartości

    double x_values[] = {0.01, 0.1, 0.5, 1.0};

    for (double x : x_values) {
        double f_pos = compute_hybrid(x);
        double f_neg = compute_hybrid(-x);

        std::cout << "  f(" << x << ") = " << std::setprecision(10) << f_pos << std::endl;
        std::cout << "  f(" << -x << ") = " << std::setprecision(10) << f_neg << std::endl;

        // Funkcja jest parzysta
        assert(approx_equal(f_pos, f_neg, 1e-10));
    }

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_known_values() {
    std::cout << "Test 6: Znane wartości funkcji" << std::endl;

    // Dla x = 1.0, wartość teoretyczna (obliczona np. w Wolfram Alpha):
    // f(1.0) ≈ 0.9512872780590717

    double x = 1.0;
    double expected = 0.9512872780590717;
    double result_naive = compute_naive(x);
    double result_hybrid = compute_hybrid(x);

    std::cout << "  f(1.0) [oczekiwane] = " << std::setprecision(15) << expected << std::endl;
    std::cout << "  f(1.0) [naivne]     = " << std::setprecision(15) << result_naive << std::endl;
    std::cout << "  f(1.0) [hybryd]     = " << std::setprecision(15) << result_hybrid << std::endl;

    assert(approx_equal(result_naive, expected, 1e-8));
    assert(approx_equal(result_hybrid, expected, 1e-8));

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_monotonicity() {
    std::cout << "Test 7: Monotoniczność (funkcja maleje)" << std::endl;

    // Funkcja f(x) maleje dla x > 0
    double prev = compute_hybrid(0.01);

    for (double x = 0.1; x <= 10.0; x += 0.5) {
        double current = compute_hybrid(x);
        std::cout << "  f(" << x << ") = " << std::setprecision(10) << current << std::endl;

        // Każda następna wartość powinna być mniejsza
        assert(current < prev);
        prev = current;
    }

    std::cout << "  ✓ Test przeszedł!" << std::endl << std::endl;
}

void test_accuracy_comparison() {
    std::cout << "Test 8: Porównanie dokładności metod dla małych x" << std::endl;

    double x = 1e-5;
    double result_naive = compute_naive(x);
    double result_taylor = compute_taylor(x);
    double exact = 1.0;  // Wartość graniczna

    double error_naive = std::abs(result_naive - exact);
    double error_taylor = std::abs(result_taylor - exact);

    std::cout << "  x = " << x << std::endl;
    std::cout << "  Metoda naiwna:  f(x) = " << std::setprecision(10) << result_naive
              << ", błąd = " << error_naive << std::endl;
    std::cout << "  Szereg Taylora: f(x) = " << std::setprecision(10) << result_taylor
              << ", błąd = " << error_taylor << std::endl;

    if (!std::isnan(result_naive)) {
        // Taylor powinien być dokładniejszy (jeśli naive nie zwrócił NaN)
        std::cout << "  Szereg Taylora jest dokładniejszy: " << (error_taylor < error_naive ? "TAK" : "NIE") << std::endl;
    } else {
        std::cout << "  Metoda naiwna zwróciła NaN (oczekiwane dla bardzo małych x)" << std::endl;
    }

    std::cout << "  ✓ Test zakończony" << std::endl << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  TESTY JEDNOSTKOWE" << std::endl;
    std::cout << "  f(x) = x^3 / (6 * (sinh(x) - x))" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    try {
        test_limit_at_zero();
        test_taylor_for_small_x();
        test_naive_for_large_x();
        test_hybrid_consistency();
        test_symmetry();
        test_known_values();
        test_monotonicity();
        test_accuracy_comparison();

        std::cout << "========================================" << std::endl;
        std::cout << "  ✓ WSZYSTKIE TESTY PRZESZŁY POMYŚLNIE!" << std::endl;
        std::cout << "========================================" << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "✗ TEST NIEUDANY: " << e.what() << std::endl;
        return 1;
    }
}
