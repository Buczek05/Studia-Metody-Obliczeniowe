#ifndef THOMAS_SOLVER_H
#define THOMAS_SOLVER_H

#include <vector>
#include <stdexcept>
#include <cmath>

/**
 * Klasa realizująca algorytm Thomasa dla rozwiązywania układów równań
 * z macierzą trójdiagonalną
 *
 * Użycie:
 *   ThomasSolver solver(n);
 *   solver.setMatrix(a, b, c);
 *   solver.setRHS(d);
 *   solver.solve();
 *   vector<double> solution = solver.getSolution();
 */
class ThomasSolver {
private:
    int n;                          // rozmiar układu równań
    std::vector<double> a;          // poddiagonala
    std::vector<double> b;          // diagonala główna
    std::vector<double> c;          // naddiagonala
    std::vector<double> d;          // wektor prawych stron
    std::vector<double> b_modified; // zmodyfikowana diagonala główna
    bool matrix_factorized;         // czy macierz została zfaktoryzowana

    /**
     * Faza 1: Forward elimination
     * Faktoryzacja macierzy - wykonywana raz dla danej macierzy A
     */
    void forwardElimination() {
        b_modified = b; // kopia oryginalnej diagonali

        for (int i = 1; i < n; i++) {
            if (std::abs(b_modified[i-1]) < 1e-15) {
                throw std::runtime_error("Dzielenie przez zero w algorytmie Thomasa");
            }
            double m = a[i] / b_modified[i-1];
            b_modified[i] = b_modified[i] - m * c[i-1];
        }

        // Sprawdzenie czy ostatni element diagonalny jest niezerowy
        if (std::abs(b_modified[n-1]) < 1e-15) {
            throw std::runtime_error("Macierz jest osobliwa");
        }

        matrix_factorized = true;
    }

public:
    /**
     * Konstruktor
     * @param size - rozmiar macierzy (liczba niewiadomych)
     */
    ThomasSolver(int size) : n(size), matrix_factorized(false) {
        if (n <= 0) {
            throw std::invalid_argument("Rozmiar macierzy musi być dodatni");
        }
        a.resize(n);
        b.resize(n);
        c.resize(n);
        d.resize(n);
        b_modified.resize(n);
    }

    /**
     * Ustawienie współczynników macierzy trójdiagonalnej
     * @param sub - poddiagonala (n elementów, sub[0] ignorowane)
     * @param diag - diagonala główna (n elementów)
     * @param super - naddiagonala (n elementów, super[n-1] ignorowane)
     */
    void setMatrix(const std::vector<double>& sub,
                   const std::vector<double>& diag,
                   const std::vector<double>& super) {
        if (sub.size() != n || diag.size() != n || super.size() != n) {
            throw std::invalid_argument("Nieprawidłowy rozmiar wektorów macierzy");
        }
        a = sub;
        b = diag;
        c = super;
        matrix_factorized = false;
    }

    /**
     * Ustawienie wektora prawych stron
     * @param rhs - wektor prawych stron (n elementów)
     */
    void setRHS(const std::vector<double>& rhs) {
        if (rhs.size() != n) {
            throw std::invalid_argument("Nieprawidłowy rozmiar wektora prawych stron");
        }
        d = rhs;
    }

    /**
     * Rozwiązanie układu równań
     * Wykonuje faktoryzację (jeśli jeszcze nie wykonana) oraz rozwiązanie
     */
    void solve() {
        // Faktoryzacja macierzy (jeśli nie została jeszcze wykonana)
        if (!matrix_factorized) {
            forwardElimination();
        }

        // Forward elimination dla wektora d
        for (int i = 1; i < n; i++) {
            double m = a[i] / b_modified[i-1];
            d[i] = d[i] - m * d[i-1];
        }

        // Back substitution
        d[n-1] = d[n-1] / b_modified[n-1];

        for (int i = n-2; i >= 0; i--) {
            d[i] = (d[i] - c[i] * d[i+1]) / b_modified[i];
        }
    }

    /**
     * Pobranie rozwiązania
     * @return wektor rozwiązań x
     */
    std::vector<double> getSolution() const {
        return d;
    }

    /**
     * Weryfikacja rozwiązania - oblicza normę residuum ||Ax - b||
     * @param original_rhs - oryginalny wektor prawych stron
     * @return norma residuum
     */
    double verifyResiduum(const std::vector<double>& original_rhs) const {
        if (original_rhs.size() != n) {
            throw std::invalid_argument("Nieprawidłowy rozmiar wektora");
        }

        std::vector<double> residuum(n);

        // Obliczenie A*x
        residuum[0] = b[0] * d[0] + c[0] * d[1] - original_rhs[0];
        for (int i = 1; i < n - 1; i++) {
            residuum[i] = a[i] * d[i-1] + b[i] * d[i] + c[i] * d[i+1] - original_rhs[i];
        }
        residuum[n-1] = a[n-1] * d[n-2] + b[n-1] * d[n-1] - original_rhs[n-1];

        // Obliczenie normy euklidesowej residuum
        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            norm += residuum[i] * residuum[i];
        }
        return std::sqrt(norm);
    }

    /**
     * Rozwiązanie wielu układów równań z tą samą macierzą
     * ale różnymi wektorami prawych stron
     * @param rhs_vectors - wektor zawierający różne wektory prawych stron
     * @return wektor zawierający rozwiązania dla każdego wektora prawych stron
     */
    std::vector<std::vector<double>> solveMultiple(
        const std::vector<std::vector<double>>& rhs_vectors) {

        // Faktoryzacja wykonywana tylko raz
        if (!matrix_factorized) {
            forwardElimination();
        }

        std::vector<std::vector<double>> solutions;

        for (const auto& rhs : rhs_vectors) {
            setRHS(rhs);
            solve();
            solutions.push_back(getSolution());
        }

        return solutions;
    }
};

#endif // THOMAS_SOLVER_H
