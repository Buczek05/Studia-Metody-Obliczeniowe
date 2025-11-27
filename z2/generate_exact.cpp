#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

// Program generujący "dokładne" wartości referencyjne funkcji
// f(x) = x^3 / (6 * (sinh(x) - x))
//
// Dla małych x używa rozwinięcia w szereg Taylora z wieloma wyrazami
// Dla dużych x używa standardowej funkcji sinh (która tam jest dokładna)

// Funkcja obliczająca f(x) z wysoką dokładnością dla małych x
// Używa rozwinięcia Taylora z wieloma wyrazami
double compute_high_precision_small_x(double x) {
    double x2 = x * x;

    // Rozwinięcie: f(x) = 1 / (1 + c2*x^2 + c4*x^4 + c6*x^6 + ...)
    // gdzie współczynniki pochodzą z szeregu sinh(x) - x

    double result = 1.0;
    double term = 1.0;
    double x_power = x2;

    // Współczynniki z rozwinięcia
    // f(x) = 1 / (1 + x^2/20 + x^4/840 + x^6/37800 + ...)
    const double coeffs[] = {
        1.0,                    // x^0
        1.0/20.0,               // x^2
        1.0/840.0,              // x^4
        1.0/37800.0,            // x^6
        1.0/1995840.0,          // x^8
        1.0/118195200.0,        // x^10
        1.0/7558272000.0,       // x^12
        1.0/518666188800.0,     // x^14
        1.0/37497714585600.0    // x^16
    };

    double sum = coeffs[0];
    x_power = 1.0;

    for (int i = 1; i < 9; i++) {
        x_power *= x2;
        sum += coeffs[i] * x_power;
    }

    return 1.0 / sum;
}

// Funkcja obliczająca f(x) dla dużych x
double compute_high_precision_large_x(double x) {
    // Dla dużych x funkcja sinh działa dobrze
    double sinh_x = std::sinh(x);
    double diff = sinh_x - x;

    // Dla bardzo dużych x, sinh(x) ≈ exp(x)/2
    // więc f(x) ≈ x^3 / (6 * exp(x)/2) = x^3 / (3 * exp(x))
    if (x > 100.0) {
        // Obliczamy w postaci: x^3 * exp(-x) / 3
        // aby uniknąć overflow
        return (x * x * x) / (3.0 * std::exp(x));
    }

    return (x * x * x) / (6.0 * diff);
}

// Główna funkcja obliczająca z wysoką precyzją
double compute_exact(double x) {
    if (std::abs(x) < 1.0) {
        return compute_high_precision_small_x(x);
    } else {
        return compute_high_precision_large_x(x);
    }
}

int main() {
    std::ofstream outfile("exact_values.txt");

    outfile << "# x  f(x)" << std::endl;
    outfile << "# gdzie f(x) = x^3 / (6 * (sinh(x) - x))" << std::endl;
    outfile << "# Wartości obliczone z wysoką precyzją (szereg Taylora dla małych x)" << std::endl;

    // Generuj wartości dla x z zakresu [10^-10, 10^3]
    // Używamy skali logarytmicznej aby równomiernie pokryć zakres

    std::cout << "Generowanie dokładnych wartości..." << std::endl;

    int num_points = 0;

    // Gęsta siatka dla małych x (gdzie są problemy numeryczne)
    for (double log_x = -10.0; log_x <= -1.0; log_x += 0.05) {
        double x = std::pow(10.0, log_x);
        double f = compute_exact(x);
        outfile << std::scientific << std::setprecision(17)
                << x << " " << f << std::endl;
        num_points++;
    }

    // Rzadsza siatka dla średnich x
    for (double log_x = -1.0; log_x <= 2.0; log_x += 0.1) {
        double x = std::pow(10.0, log_x);
        double f = compute_exact(x);
        outfile << std::scientific << std::setprecision(17)
                << x << " " << f << std::endl;
        num_points++;
    }

    // Jeszcze rzadsza dla dużych x
    for (double log_x = 2.0; log_x <= 3.0; log_x += 0.2) {
        double x = std::pow(10.0, log_x);
        double f = compute_exact(x);
        outfile << std::scientific << std::setprecision(17)
                << x << " " << f << std::endl;
        num_points++;
    }

    outfile.close();

    std::cout << "Wygenerowano " << num_points << " punktów." << std::endl;
    std::cout << "Zapisano do pliku: exact_values.txt" << std::endl;

    // Wyświetl kilka przykładowych wartości
    std::cout << "\nPrzykładowe wartości:" << std::endl;
    std::cout << std::setw(15) << "x" << std::setw(25) << "f(x)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::vector<double> test_x = {1e-10, 1e-8, 1e-6, 1e-4, 1e-2, 1e-1, 1.0, 10.0, 100.0, 1000.0};
    for (double x : test_x) {
        double f = compute_exact(x);
        std::cout << std::scientific << std::setprecision(8)
                  << std::setw(15) << x
                  << std::setw(25) << f << std::endl;
    }

    // Wartość graniczna
    std::cout << "\nWartość graniczna lim(x->0) f(x) = " << compute_exact(1e-15) << std::endl;
    std::cout << "Wartość teoretyczna: 1.0" << std::endl;

    return 0;
}
