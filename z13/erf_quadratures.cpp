#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

// Funkcja podcałkowa dla erf(x): exp(-y^2)
double integrand(double y) {
    return std::exp(-y * y);
}

// ============================================================================
// METODY KWADRATUR
// ============================================================================

// Metoda prostokątów z węzłem po lewej stronie
double rectangleLeft(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

// Metoda prostokątów z węzłem po prawej stronie
double rectangleRight(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

// Metoda prostokątów z węzłem w środku
double rectangleMid(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += f(x);
    }

    return h * sum;
}

// Metoda trapezów
double trapezoid(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

// Metoda Simpsona (parabol)
// Wymaga parzystej liczby przedziałów
double simpson(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++; // Zapewnij parzystą liczbę przedziałów
    }

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2.0 * f(x);
        } else {
            sum += 4.0 * f(x);
        }
    }

    return (h / 3.0) * sum;
}

// ============================================================================
// FUNKCJA ERF(X)
// ============================================================================

// Obliczanie erf(x) wybraną metodą
double erf_numerical(double x, double (*quadrature)(double (*)(double), double, double, int), int n) {
    double coeff = 2.0 / std::sqrt(M_PI);
    double integral = quadrature(integrand, 0.0, x, n);
    return coeff * integral;
}

// ============================================================================
// ANALIZA BŁĘDÓW I RZĘDÓW DOKŁADNOŚCI
// ============================================================================

void analyzeMethod(const std::string& methodName,
                   double (*quadrature)(double (*)(double), double, double, int),
                   double x,
                   const std::vector<int>& n_values,
                   std::ofstream& outputFile) {

    double exactValue = std::erf(x);

    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "Metoda: " << methodName << " dla x = " << x << "\n";
    std::cout << "Wartość dokładna: " << std::setprecision(15) << exactValue << "\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << std::setw(10) << "n"
              << std::setw(15) << "h"
              << std::setw(18) << "erf(x)"
              << std::setw(15) << "Błąd"
              << std::setw(15) << "Błąd wzgl. [%]\n";
    std::cout << std::string(70, '-') << "\n";

    for (int n : n_values) {
        double h = x / n;
        double approxValue = erf_numerical(x, quadrature, n);
        double error = std::abs(exactValue - approxValue);
        double relativeError = (error / std::abs(exactValue)) * 100.0;

        std::cout << std::setw(10) << n
                  << std::setw(15) << std::scientific << std::setprecision(4) << h
                  << std::setw(18) << std::fixed << std::setprecision(10) << approxValue
                  << std::setw(15) << std::scientific << std::setprecision(4) << error
                  << std::setw(15) << std::fixed << std::setprecision(6) << relativeError << "\n";

        // Zapisz do pliku: log10(h), log10(błąd)
        outputFile << std::log10(h) << " " << std::log10(error) << "\n";
    }
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << std::fixed << std::setprecision(10);

    // Wartości x do obliczenia
    std::vector<double> x_values = {1.0, 2.0, 3.0};

    // Różne wartości n (liczba przedziałów) dla analizy
    std::vector<int> n_values;
    for (int i = 1; i <= 10; i++) {
        n_values.push_back(10 * i);
    }
    for (int i = 2; i <= 10; i++) {
        n_values.push_back(100 * i);
    }
    for (int i = 2; i <= 10; i++) {
        n_values.push_back(1000 * i);
    }

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║        NUMERYCZNE OBLICZANIE FUNKCJI ERF(X)                        ║\n";
    std::cout << "║        Porównanie metod kwadratur numerycznych                     ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";

    // ========================================================================
    // CZĘŚĆ 1: Obliczenia dla x = 1.0, 2.0, 3.0 z różnymi metodami
    // ========================================================================

    std::vector<int> display_n = {10, 50, 100, 500, 1000};

    for (double x : x_values) {
        std::cout << "\n\n";
        std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
        std::cout << "║  x = " << std::setw(4) << x << "                                                      ║\n";
        std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";

        double exactValue = std::erf(x);
        std::cout << "\nWartość dokładna erf(" << x << ") = "
                  << std::setprecision(15) << exactValue << "\n";

        std::cout << "\n" << std::string(100, '-') << "\n";
        std::cout << std::setw(15) << "Metoda"
                  << std::setw(10) << "n";
        for (int n : display_n) {
            std::cout << std::setw(17) << "n=" + std::to_string(n);
        }
        std::cout << "\n" << std::string(100, '-') << "\n";

        // Prostokąty (lewe)
        std::cout << std::setw(15) << "Rect-Left" << std::setw(10) << "";
        for (int n : display_n) {
            double result = erf_numerical(x, rectangleLeft, n);
            std::cout << std::setw(17) << std::setprecision(10) << result;
        }
        std::cout << "\n";

        // Prostokąty (prawe)
        std::cout << std::setw(15) << "Rect-Right" << std::setw(10) << "";
        for (int n : display_n) {
            double result = erf_numerical(x, rectangleRight, n);
            std::cout << std::setw(17) << std::setprecision(10) << result;
        }
        std::cout << "\n";

        // Prostokąty (środek)
        std::cout << std::setw(15) << "Rect-Mid" << std::setw(10) << "";
        for (int n : display_n) {
            double result = erf_numerical(x, rectangleMid, n);
            std::cout << std::setw(17) << std::setprecision(10) << result;
        }
        std::cout << "\n";

        // Trapezy
        std::cout << std::setw(15) << "Trapezoid" << std::setw(10) << "";
        for (int n : display_n) {
            double result = erf_numerical(x, trapezoid, n);
            std::cout << std::setw(17) << std::setprecision(10) << result;
        }
        std::cout << "\n";

        // Simpson
        std::cout << std::setw(15) << "Simpson" << std::setw(10) << "";
        for (int n : display_n) {
            double result = erf_numerical(x, simpson, n);
            std::cout << std::setw(17) << std::setprecision(10) << result;
        }
        std::cout << "\n";

        std::cout << std::string(100, '-') << "\n";
        std::cout << std::setw(15) << "Exact" << std::setw(10) << "";
        std::cout << std::setw(17) << std::setprecision(15) << exactValue << "\n";
    }

    // ========================================================================
    // CZĘŚĆ 2: Analiza błędów dla x = 3.0
    // ========================================================================

    std::cout << "\n\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  ANALIZA BŁĘDÓW I RZĘDÓW DOKŁADNOŚCI DLA x = 3.0                   ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";

    double x_analysis = 3.0;

    // Generowanie danych dla wykresów
    std::ofstream file_left("data_rect_left.txt");
    analyzeMethod("Prostokąty (lewy węzeł)", rectangleLeft, x_analysis, n_values, file_left);
    file_left.close();

    std::ofstream file_right("data_rect_right.txt");
    analyzeMethod("Prostokąty (prawy węzeł)", rectangleRight, x_analysis, n_values, file_right);
    file_right.close();

    std::ofstream file_mid("data_rect_mid.txt");
    analyzeMethod("Prostokąty (środek)", rectangleMid, x_analysis, n_values, file_mid);
    file_mid.close();

    std::ofstream file_trap("data_trapezoid.txt");
    analyzeMethod("Trapezy", trapezoid, x_analysis, n_values, file_trap);
    file_trap.close();

    std::ofstream file_simp("data_simpson.txt");
    analyzeMethod("Simpson", simpson, x_analysis, n_values, file_simp);
    file_simp.close();

    // ========================================================================
    // CZĘŚĆ 3: Generowanie skryptu gnuplot
    // ========================================================================

    std::ofstream gnuplotScript("plot_errors.gp");
    gnuplotScript << "set terminal pngcairo size 1200,800 enhanced font 'Arial,12'\n";
    gnuplotScript << "set output 'error_analysis.png'\n";
    gnuplotScript << "set title 'Analiza błędów metod kwadratur dla erf(3.0)'\n";
    gnuplotScript << "set xlabel 'log_{10}(h)'\n";
    gnuplotScript << "set ylabel 'log_{10}(błąd)'\n";
    gnuplotScript << "set grid\n";
    gnuplotScript << "set key left top\n\n";

    gnuplotScript << "# Dopasowanie liniowe dla wyznaczenia rzędów\n";
    gnuplotScript << "f1(x) = a1*x + b1\n";
    gnuplotScript << "f2(x) = a2*x + b2\n";
    gnuplotScript << "f3(x) = a3*x + b3\n";
    gnuplotScript << "f4(x) = a4*x + b4\n";
    gnuplotScript << "f5(x) = a5*x + b5\n\n";

    gnuplotScript << "fit f1(x) 'data_rect_left.txt' using 1:2 via a1, b1\n";
    gnuplotScript << "fit f2(x) 'data_rect_right.txt' using 1:2 via a2, b2\n";
    gnuplotScript << "fit f3(x) 'data_rect_mid.txt' using 1:2 via a3, b3\n";
    gnuplotScript << "fit f4(x) 'data_trapezoid.txt' using 1:2 via a4, b4\n";
    gnuplotScript << "fit f5(x) 'data_simpson.txt' using 1:2 via a5, b5\n\n";

    gnuplotScript << "plot 'data_rect_left.txt' u 1:2 w p pt 7 ps 0.5 lc rgb 'red' title 'Prostokąty (lewe)', \\\n";
    gnuplotScript << "     f1(x) w l lc rgb 'red' dt 2 title sprintf('Rząd: %.2f', a1), \\\n";
    gnuplotScript << "     'data_rect_right.txt' u 1:2 w p pt 7 ps 0.5 lc rgb 'blue' title 'Prostokąty (prawe)', \\\n";
    gnuplotScript << "     f2(x) w l lc rgb 'blue' dt 2 title sprintf('Rząd: %.2f', a2), \\\n";
    gnuplotScript << "     'data_rect_mid.txt' u 1:2 w p pt 7 ps 0.5 lc rgb 'green' title 'Prostokąty (środek)', \\\n";
    gnuplotScript << "     f3(x) w l lc rgb 'green' dt 2 title sprintf('Rząd: %.2f', a3), \\\n";
    gnuplotScript << "     'data_trapezoid.txt' u 1:2 w p pt 7 ps 0.5 lc rgb 'orange' title 'Trapezy', \\\n";
    gnuplotScript << "     f4(x) w l lc rgb 'orange' dt 2 title sprintf('Rząd: %.2f', a4), \\\n";
    gnuplotScript << "     'data_simpson.txt' u 1:2 w p pt 7 ps 0.5 lc rgb 'purple' title 'Simpson', \\\n";
    gnuplotScript << "     f5(x) w l lc rgb 'purple' dt 2 title sprintf('Rząd: %.2f', a5)\n";
    gnuplotScript.close();

    std::cout << "\n\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  PLIKI WYGENEROWANE                                                ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    std::cout << "\nDane zapisane do plików:\n";
    std::cout << "  - data_rect_left.txt\n";
    std::cout << "  - data_rect_right.txt\n";
    std::cout << "  - data_rect_mid.txt\n";
    std::cout << "  - data_trapezoid.txt\n";
    std::cout << "  - data_simpson.txt\n";
    std::cout << "  - plot_errors.gp (skrypt gnuplot)\n\n";
    std::cout << "Aby wygenerować wykres, uruchom:\n";
    std::cout << "  gnuplot plot_errors.gp\n\n";

    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  OCZEKIWANE RZĘDY DOKŁADNOŚCI                                      ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    std::cout << "\nRzędy dokładności teoretyczne:\n";
    std::cout << "  - Prostokąty (lewe/prawe):  O(h²)  → nachylenie ≈ 2\n";
    std::cout << "  - Prostokąty (środek):      O(h³)  → nachylenie ≈ 3\n";
    std::cout << "  - Trapezy:                  O(h³)  → nachylenie ≈ 3\n";
    std::cout << "  - Simpson:                  O(h⁵)  → nachylenie ≈ 5\n\n";

    return 0;
}
