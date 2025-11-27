#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

// Program do analizy statystycznej błędów

struct ErrorStats {
    double min_error;
    double max_error;
    double mean_error;
    int count;
    std::string method_name;
};

ErrorStats analyze_file(const std::string& filename, const std::string& method_name) {
    ErrorStats stats;
    stats.method_name = method_name;
    stats.min_error = 1e100;
    stats.max_error = 0.0;
    stats.mean_error = 0.0;
    stats.count = 0;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return stats;
    }

    std::string line;
    // Pomijamy nagłówek
    std::getline(file, line);

    double x, log_x, computed, exact, rel_error, log_rel_error;
    while (file >> x >> log_x >> computed >> exact >> rel_error >> log_rel_error) {
        // Pomijamy NaN i wartości zerowe
        if (std::isnan(rel_error) || std::isinf(rel_error) || rel_error == 0.0) {
            continue;
        }

        stats.min_error = std::min(stats.min_error, rel_error);
        stats.max_error = std::max(stats.max_error, rel_error);
        stats.mean_error += rel_error;
        stats.count++;
    }

    if (stats.count > 0) {
        stats.mean_error /= stats.count;
    }

    file.close();
    return stats;
}

int main() {
    std::cout << "=== Analiza statystyczna błędów ===" << std::endl;
    std::cout << std::endl;

    std::vector<std::string> files = {
        "results_naive.txt",
        "results_taylor.txt",
        "results_hybrid.txt"
    };

    std::vector<std::string> names = {
        "Metoda naiwna",
        "Szereg Taylora",
        "Metoda hybrydowa"
    };

    std::cout << std::setw(20) << "Metoda"
              << std::setw(20) << "Min błąd"
              << std::setw(20) << "Max błąd"
              << std::setw(20) << "Średni błąd"
              << std::setw(15) << "Liczba próbek" << std::endl;
    std::cout << std::string(95, '-') << std::endl;

    for (size_t i = 0; i < files.size(); i++) {
        ErrorStats stats = analyze_file(files[i], names[i]);

        std::cout << std::setw(20) << stats.method_name
                  << std::scientific << std::setprecision(3)
                  << std::setw(20) << stats.min_error
                  << std::setw(20) << stats.max_error
                  << std::setw(20) << stats.mean_error
                  << std::setw(15) << stats.count << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== Wnioski ===" << std::endl;
    std::cout << "1. Metoda naiwna ma największe błędy dla małych x (utrata cyfr znaczących)" << std::endl;
    std::cout << "2. Szereg Taylora działa doskonale dla małych x" << std::endl;
    std::cout << "3. Metoda hybrydowa łączy zalety obu podejść" << std::endl;
    std::cout << std::endl;

    // Szczegółowa analiza dla małych x
    std::cout << "=== Analiza dla małych x (log10(x) < -2) ===" << std::endl;

    std::ifstream naive("results_naive.txt");
    std::ifstream taylor("results_taylor.txt");

    std::string line;
    std::getline(naive, line);  // Skip header
    std::getline(taylor, line); // Skip header

    int small_x_count = 0;
    int naive_better = 0;
    int taylor_better = 0;

    double x, log_x, comp_n, comp_t, exact_n, exact_t, err_n, err_t, log_err_n, log_err_t;

    while (naive >> x >> log_x >> comp_n >> exact_n >> err_n >> log_err_n &&
           taylor >> x >> log_x >> comp_t >> exact_t >> err_t >> log_err_t) {

        if (log_x < -2.0) {
            small_x_count++;

            if (!std::isnan(err_n) && !std::isnan(err_t)) {
                if (err_n < err_t) {
                    naive_better++;
                } else {
                    taylor_better++;
                }
            } else if (!std::isnan(err_t)) {
                taylor_better++;
            } else if (!std::isnan(err_n)) {
                naive_better++;
            }
        }
    }

    naive.close();
    taylor.close();

    std::cout << "Liczba punktów z małym x: " << small_x_count << std::endl;
    std::cout << "Metoda naiwna lepsza: " << naive_better << " razy" << std::endl;
    std::cout << "Szereg Taylora lepszy: " << taylor_better << " razy" << std::endl;
    std::cout << std::endl;

    if (taylor_better > naive_better) {
        std::cout << "✓ Szereg Taylora jest zdecydowanie lepszy dla małych x!" << std::endl;
    }

    return 0;
}
