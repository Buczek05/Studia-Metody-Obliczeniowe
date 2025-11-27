#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>

// Struktura do przechowywania danych
struct DataPoint {
    double x;
    double exact_value;
};

// Funkcja obliczająca f(x) metodą prostą (naiwną)
// f(x) = x^3 / (6 * (sinh(x) - x))
double compute_naive(double x) {
    double sinh_x = std::sinh(x);
    double denominator = 6.0 * (sinh_x - x);

    // Zabezpieczenie przed dzieleniem przez zero
    if (std::abs(denominator) < 1e-300) {
        return NAN;
    }

    return (x * x * x) / denominator;
}

// Funkcja obliczająca f(x) metodą szeregu Taylora dla małych x
// sinh(x) - x = x^3/6 + x^5/120 + x^7/5040 + ...
// f(x) = x^3 / (6 * (x^3/6 + x^5/120 + x^7/5040 + ...))
//      = x^3 / (x^3 + x^5/20 + x^7/840 + ...)
//      = 1 / (1 + x^2/20 + x^4/840 + x^6/37800 + ...)
double compute_taylor(double x) {
    double x2 = x * x;
    double x4 = x2 * x2;
    double x6 = x4 * x2;
    double x8 = x4 * x4;

    // Rozwinięcie Taylora funkcji f(x) wokół x=0
    // f(x) = 1/(1 + x^2/20 + x^4/840 + x^6/37800 + x^8/1995840 + ...)
    double series = 1.0
                  + x2 / 20.0
                  + x4 / 840.0
                  + x6 / 37800.0
                  + x8 / 1995840.0;

    return 1.0 / series;
}

// Funkcja obliczająca f(x) metodą hybrydową
// Dla małych x używa szeregu Taylora, dla dużych - standardowej funkcji sinh
double compute_hybrid(double x) {
    // Próg przełączenia między metodami
    // Dla |x| < 0.1 używamy szeregu Taylora
    const double threshold = 0.1;

    if (std::abs(x) < threshold) {
        return compute_taylor(x);
    } else {
        return compute_naive(x);
    }
}

// Funkcja wczytująca dokładne wartości z pliku
std::vector<DataPoint> load_exact_values(const std::string& filename) {
    std::vector<DataPoint> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << filename << std::endl;
        return data;
    }

    std::string line;
    // Pomijamy nagłówek jeśli istnieje
    if (std::getline(file, line) && line.find('#') == 0) {
        // Linijka zaczyna się od '#' - to komentarz/nagłówek
    } else {
        // Jeśli pierwsza linijka nie jest komentarzem, cofamy się
        file.clear();
        file.seekg(0);
    }

    double x, exact;
    while (file >> x >> exact) {
        data.push_back({x, exact});
    }

    file.close();
    return data;
}

// Funkcja obliczająca błąd względny
double relative_error(double computed, double exact) {
    if (std::abs(exact) < 1e-300) {
        return NAN;
    }
    return std::abs((computed - exact) / exact);
}

int main() {
    std::cout << "=== Program do analizy błędów obliczeniowych ===" << std::endl;
    std::cout << "f(x) = x^3 / (6 * (sinh(x) - x))" << std::endl;
    std::cout << std::endl;

    // Wczytaj dokładne wartości
    std::string exact_file = "exact_values.txt";
    std::vector<DataPoint> exact_data = load_exact_values(exact_file);

    if (exact_data.empty()) {
        std::cerr << "Błąd: Nie udało się wczytać dokładnych wartości." << std::endl;
        std::cerr << "Generuję wartości testowe..." << std::endl;

        // Generuj wartości testowe (dla demonstracji)
        // W praktyce powinny być to wartości obliczone z wysoką precyzją
        for (double log_x = -10.0; log_x <= 3.0; log_x += 0.1) {
            double x = std::pow(10.0, log_x);
            // Dla wartości "dokładnych" użyjemy metody hybrydowej
            // (w prawdziwym scenariuszu byłyby to wartości obliczone np. w Mathematica)
            double exact = compute_hybrid(x);
            exact_data.push_back({x, exact});
        }
    }

    std::cout << "Wczytano " << exact_data.size() << " punktów danych." << std::endl;

    // Otwórz pliki wyjściowe
    std::ofstream out_naive("results_naive.txt");
    std::ofstream out_taylor("results_taylor.txt");
    std::ofstream out_hybrid("results_hybrid.txt");

    // Nagłówki
    out_naive << "# x  log10(x)  computed  exact  rel_error  log10(rel_error)" << std::endl;
    out_taylor << "# x  log10(x)  computed  exact  rel_error  log10(rel_error)" << std::endl;
    out_hybrid << "# x  log10(x)  computed  exact  rel_error  log10(rel_error)" << std::endl;

    // Oblicz i zapisz wyniki
    std::cout << "\nObliczam błędy dla różnych metod..." << std::endl;

    for (const auto& point : exact_data) {
        double x = point.x;
        double exact = point.exact_value;
        double log_x = std::log10(x);

        // Metoda naiwna
        double naive = compute_naive(x);
        double err_naive = relative_error(naive, exact);
        double log_err_naive = (err_naive > 0) ? std::log10(err_naive) : -20.0;

        // Metoda Taylora
        double taylor = compute_taylor(x);
        double err_taylor = relative_error(taylor, exact);
        double log_err_taylor = (err_taylor > 0) ? std::log10(err_taylor) : -20.0;

        // Metoda hybrydowa
        double hybrid = compute_hybrid(x);
        double err_hybrid = relative_error(hybrid, exact);
        double log_err_hybrid = (err_hybrid > 0) ? std::log10(err_hybrid) : -20.0;

        // Zapisz do plików
        out_naive << std::scientific << std::setprecision(15)
                  << x << " " << log_x << " " << naive << " " << exact << " "
                  << err_naive << " " << log_err_naive << std::endl;

        out_taylor << std::scientific << std::setprecision(15)
                   << x << " " << log_x << " " << taylor << " " << exact << " "
                   << err_taylor << " " << log_err_taylor << std::endl;

        out_hybrid << std::scientific << std::setprecision(15)
                   << x << " " << log_x << " " << hybrid << " " << exact << " "
                   << err_hybrid << " " << log_err_hybrid << std::endl;
    }

    out_naive.close();
    out_taylor.close();
    out_hybrid.close();

    std::cout << "Wyniki zapisane do plików:" << std::endl;
    std::cout << "  - results_naive.txt (metoda naiwna)" << std::endl;
    std::cout << "  - results_taylor.txt (szereg Taylora)" << std::endl;
    std::cout << "  - results_hybrid.txt (metoda hybrydowa)" << std::endl;
    std::cout << "\nUżyj skryptu plot.gnu aby wygenerować wykresy." << std::endl;
    std::cout << "Komenda: gnuplot plot.gnu" << std::endl;

    // Analiza kilku przykładowych punktów
    std::cout << "\n=== Przykładowe wartości ===" << std::endl;
    std::cout << std::setw(15) << "x"
              << std::setw(20) << "Metoda naiwna"
              << std::setw(20) << "Metoda Taylora"
              << std::setw(20) << "Metoda hybrydowa" << std::endl;

    std::vector<double> test_x = {1e-10, 1e-5, 1e-2, 0.1, 1.0, 10.0, 100.0};
    for (double x : test_x) {
        double naive = compute_naive(x);
        double taylor = compute_taylor(x);
        double hybrid = compute_hybrid(x);

        std::cout << std::scientific << std::setprecision(6)
                  << std::setw(15) << x
                  << std::setw(20) << naive
                  << std::setw(20) << taylor
                  << std::setw(20) << hybrid << std::endl;
    }

    return 0;
}
