#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

// Struktura reprezentująca wektor 3D
struct Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    void print() const {
        cout << "[" << setw(12) << x << ", " << setw(12) << y << ", " << setw(12) << z << "]";
    }
};

// Obliczanie normy euklidesowej wektora
double norm(const Vec3& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Obliczanie normy maksimum wektora
double normInf(const Vec3& v) {
    return max({abs(v.x), abs(v.y), abs(v.z)});
}

/**
 * Oblicza wartości funkcji F(x, y, z) dla układu równań:
 * F1 = x^2 + y^2 + z^2 - 4
 * F2 = x^2 + y^2/2 - 1
 * F3 = xy - 1/2
 */
Vec3 computeF(const Vec3& v) {
    double x = v.x, y = v.y, z = v.z;

    double F1 = x*x + y*y + z*z - 4.0;
    double F2 = x*x + y*y/2.0 - 1.0;
    double F3 = x*y - 0.5;

    return Vec3(F1, F2, F3);
}

/**
 * Oblicza macierz Jacobiego J(x, y, z):
 * J = | 2x   2y   2z |
 *     | 2x    y    0 |
 *     |  y    x    0 |
 */
void computeJacobian(const Vec3& v, double J[3][3]) {
    double x = v.x, y = v.y, z = v.z;

    // Pierwszy wiersz: pochodne F1
    J[0][0] = 2.0 * x;
    J[0][1] = 2.0 * y;
    J[0][2] = 2.0 * z;

    // Drugi wiersz: pochodne F2
    J[1][0] = 2.0 * x;
    J[1][1] = y;
    J[1][2] = 0.0;

    // Trzeci wiersz: pochodne F3
    J[2][0] = y;
    J[2][1] = x;
    J[2][2] = 0.0;
}

/**
 * Rozwiązuje układ równań liniowych Ax = b metodą eliminacji Gaussa
 * z częściowym wyborem elementu głównego
 * Zwraca false jeśli macierz jest osobliwa
 */
bool solveLinearSystem(double A[3][3], double b[3], double x[3]) {
    const double EPSILON = 1e-14;
    double augmented[3][4];

    // Tworzenie macierzy rozszerzonej [A|b]
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][3] = b[i];
    }

    // Eliminacja w przód z częściowym wyborem elementu głównego
    for (int k = 0; k < 3; k++) {
        // Znajdź element główny
        int maxRow = k;
        double maxVal = abs(augmented[k][k]);
        for (int i = k + 1; i < 3; i++) {
            if (abs(augmented[i][k]) > maxVal) {
                maxVal = abs(augmented[i][k]);
                maxRow = i;
            }
        }

        // Sprawdź czy macierz nie jest osobliwa
        if (abs(augmented[maxRow][k]) < EPSILON) {
            return false;
        }

        // Zamień wiersze
        if (maxRow != k) {
            for (int j = 0; j < 4; j++) {
                swap(augmented[k][j], augmented[maxRow][j]);
            }
        }

        // Eliminacja
        for (int i = k + 1; i < 3; i++) {
            double factor = augmented[i][k] / augmented[k][k];
            for (int j = k; j < 4; j++) {
                augmented[i][j] -= factor * augmented[k][j];
            }
        }
    }

    // Podstawianie wsteczne
    for (int i = 2; i >= 0; i--) {
        x[i] = augmented[i][3];
        for (int j = i + 1; j < 3; j++) {
            x[i] -= augmented[i][j] * x[j];
        }
        x[i] /= augmented[i][i];
    }

    return true;
}

/**
 * Implementacja uogólnionej metody Newtona dla układu 3 równań
 *
 * Parametry:
 *   x0 - przybliżenie początkowe
 *   tol_delta - tolerancja dla normy poprawki ||Δx||
 *   tol_residual - tolerancja dla normy residuum ||F(x)||
 *   max_iter - maksymalna liczba iteracji
 *   verbose - czy wyświetlać szczegółowe informacje
 *
 * Zwraca: znalezione rozwiązanie
 */
Vec3 newtonMethod(Vec3 x0, double tol_delta = 1e-10, double tol_residual = 1e-10,
                  int max_iter = 100, bool verbose = true) {

    Vec3 x = x0;

    if (verbose) {
        cout << "\n========================================" << endl;
        cout << "UOGÓLNIONA METODA NEWTONA" << endl;
        cout << "========================================" << endl;
        cout << "\nPrzybliżenie początkowe: ";
        x.print();
        cout << "\n\nParametry:" << endl;
        cout << "  Tolerancja ||Δx||:  " << tol_delta << endl;
        cout << "  Tolerancja ||F(x)||: " << tol_residual << endl;
        cout << "  Max iteracji:        " << max_iter << endl;
        cout << "\n========================================\n" << endl;
    }

    for (int iter = 0; iter < max_iter; iter++) {
        // Oblicz wartość funkcji F(x)
        Vec3 F = computeF(x);
        double normF = norm(F);

        // Oblicz macierz Jacobiego J(x)
        double J[3][3];
        computeJacobian(x, J);

        // Przygotuj prawą stronę układu: -F(x)
        double rhs[3] = {-F.x, -F.y, -F.z};

        // Rozwiąż układ J(x) * Δx = -F(x)
        double delta[3];
        if (!solveLinearSystem(J, rhs, delta)) {
            cout << "\nBłąd: Macierz Jacobiego jest osobliwa!" << endl;
            return x;
        }

        Vec3 deltaVec(delta[0], delta[1], delta[2]);
        double normDelta = norm(deltaVec);

        if (verbose) {
            cout << "Iteracja " << setw(3) << iter << ":" << endl;
            cout << "  x^(" << iter << ") = ";
            x.print();
            cout << endl;
            cout << "  F(x^(" << iter << ")) = ";
            F.print();
            cout << "  ||F|| = " << scientific << setprecision(6) << normF << endl;
            cout << "  Δx = ";
            deltaVec.print();
            cout << "  ||Δx|| = " << scientific << setprecision(6) << normDelta << endl;
            cout << endl;
        }

        // Kryterium 2: Sprawdź normę residuum
        if (normF < tol_residual) {
            if (verbose) {
                cout << "========================================" << endl;
                cout << "ZBIEŻNOŚĆ OSIĄGNIĘTA (residuum)" << endl;
                cout << "||F(x)|| = " << scientific << normF << " < " << tol_residual << endl;
                cout << "Liczba iteracji: " << iter + 1 << endl;
                cout << "========================================" << endl;
            }
            return x;
        }

        // Aktualizuj rozwiązanie
        x = x + deltaVec;

        // Kryterium 1: Sprawdź normę poprawki
        if (normDelta < tol_delta) {
            if (verbose) {
                cout << "========================================" << endl;
                cout << "ZBIEŻNOŚĆ OSIĄGNIĘTA (poprawka)" << endl;
                cout << "||Δx|| = " << scientific << normDelta << " < " << tol_delta << endl;
                cout << "Liczba iteracji: " << iter + 1 << endl;
                cout << "========================================" << endl;
            }
            return x;
        }
    }

    // Kryterium 3: Osiągnięto maksymalną liczbę iteracji
    if (verbose) {
        cout << "========================================" << endl;
        cout << "OSIĄGNIĘTO MAKSYMALNĄ LICZBĘ ITERACJI" << endl;
        cout << "Metoda może nie być zbieżna lub wymaga więcej iteracji" << endl;
        cout << "========================================" << endl;
    }

    return x;
}

/**
 * Weryfikuje jakość znalezionego rozwiązania
 */
void verifySolution(const Vec3& x) {
    cout << "\n========================================" << endl;
    cout << "WERYFIKACJA ROZWIĄZANIA" << endl;
    cout << "========================================" << endl;
    cout << fixed << setprecision(10);
    cout << "\nZnalezione rozwiązanie:" << endl;
    cout << "  x = " << x.x << endl;
    cout << "  y = " << x.y << endl;
    cout << "  z = " << x.z << endl;

    cout << "\nSprawdzenie równań:" << endl;
    double eq1 = x.x*x.x + x.y*x.y + x.z*x.z;
    double eq2 = x.x*x.x + x.y*x.y/2.0;
    double eq3 = x.x*x.y;

    cout << "  x² + y² + z² = " << eq1 << " (powinno być 4.0, błąd: "
         << scientific << abs(eq1 - 4.0) << ")" << endl;
    cout << "  x² + y²/2    = " << eq2 << " (powinno być 1.0, błąd: "
         << scientific << abs(eq2 - 1.0) << ")" << endl;
    cout << "  xy           = " << eq3 << " (powinno być 0.5, błąd: "
         << scientific << abs(eq3 - 0.5) << ")" << endl;

    Vec3 F = computeF(x);
    cout << "\nResiduum ||F(x)||: " << scientific << norm(F) << endl;
    cout << "========================================" << endl;
}

int main() {
    cout << fixed << setprecision(6);

    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  ROZWIĄZYWANIE UKŁADU RÓWNAŃ NIELINIOWYCH                  ║" << endl;
    cout << "║  METODĄ NEWTONA                                            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    cout << "\nUkład równań do rozwiązania:" << endl;
    cout << "  (1) x² + y² + z² = 4" << endl;
    cout << "  (2) x² + y²/2    = 1" << endl;
    cout << "  (3) xy           = 1/2" << endl;

    // Przykład 1: Rozwiązanie w pierwszej ćwiartce
    cout << "\n\n" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;
    cout << "PRZYKŁAD 1: Przybliżenie początkowe [1.0, 0.5, 1.7]" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;

    Vec3 x0_1(1.0, 0.5, 1.7);
    Vec3 solution1 = newtonMethod(x0_1, 1e-10, 1e-10, 100, true);
    verifySolution(solution1);

    // Przykład 2: Inne przybliżenie początkowe
    cout << "\n\n" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;
    cout << "PRZYKŁAD 2: Przybliżenie początkowe [0.9, 0.6, 1.5]" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;

    Vec3 x0_2(0.9, 0.6, 1.5);
    Vec3 solution2 = newtonMethod(x0_2, 1e-10, 1e-10, 100, true);
    verifySolution(solution2);

    // Przykład 3: Rozwiązanie w innej ćwiartce
    cout << "\n\n" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;
    cout << "PRZYKŁAD 3: Przybliżenie początkowe [-0.9, -0.6, 1.5]" << endl;
    cout << "════════════════════════════════════════════════════════════" << endl;

    Vec3 x0_3(-0.9, -0.6, 1.5);
    Vec3 solution3 = newtonMethod(x0_3, 1e-10, 1e-10, 100, true);
    verifySolution(solution3);

    return 0;
}
