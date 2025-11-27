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
 * Oblicza macierz Jacobiego J(x, y, z)
 */
void computeJacobian(const Vec3& v, double J[3][3]) {
    double x = v.x, y = v.y, z = v.z;

    J[0][0] = 2.0 * x;
    J[0][1] = 2.0 * y;
    J[0][2] = 2.0 * z;

    J[1][0] = 2.0 * x;
    J[1][1] = y;
    J[1][2] = 0.0;

    J[2][0] = y;
    J[2][1] = x;
    J[2][2] = 0.0;
}

/**
 * Rozwiązuje układ równań liniowych Ax = b metodą eliminacji Gaussa
 */
bool solveLinearSystem(double A[3][3], double b[3], double x[3]) {
    const double EPSILON = 1e-14;
    double augmented[3][4];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            augmented[i][j] = A[i][j];
        }
        augmented[i][3] = b[i];
    }

    for (int k = 0; k < 3; k++) {
        int maxRow = k;
        double maxVal = abs(augmented[k][k]);
        for (int i = k + 1; i < 3; i++) {
            if (abs(augmented[i][k]) > maxVal) {
                maxVal = abs(augmented[i][k]);
                maxRow = i;
            }
        }

        if (abs(augmented[maxRow][k]) < EPSILON) {
            return false;
        }

        if (maxRow != k) {
            for (int j = 0; j < 4; j++) {
                swap(augmented[k][j], augmented[maxRow][j]);
            }
        }

        for (int i = k + 1; i < 3; i++) {
            double factor = augmented[i][k] / augmented[k][k];
            for (int j = k; j < 4; j++) {
                augmented[i][j] -= factor * augmented[k][j];
            }
        }
    }

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
 * Implementacja uogólnionej metody Newtona
 */
Vec3 newtonMethod(Vec3 x0, double tol_delta = 1e-10, double tol_residual = 1e-10,
                  int max_iter = 100, bool verbose = false) {

    Vec3 x = x0;
    bool converged = false;
    int final_iter = 0;

    for (int iter = 0; iter < max_iter; iter++) {
        Vec3 F = computeF(x);
        double normF = norm(F);

        double J[3][3];
        computeJacobian(x, J);

        double rhs[3] = {-F.x, -F.y, -F.z};
        double delta[3];

        if (!solveLinearSystem(J, rhs, delta)) {
            if (verbose) cout << "Błąd: Macierz osobliwa w iteracji " << iter << endl;
            return x;
        }

        Vec3 deltaVec(delta[0], delta[1], delta[2]);
        double normDelta = norm(deltaVec);

        if (verbose) {
            cout << "Iter " << setw(3) << iter
                 << ": ||F|| = " << scientific << setw(12) << normF
                 << ", ||Δx|| = " << setw(12) << normDelta << endl;
        }

        if (normF < tol_residual || normDelta < tol_delta) {
            converged = true;
            final_iter = iter + 1;
            if (verbose) {
                cout << "Zbieżność w iteracji " << final_iter << endl;
            }
            return x + deltaVec;
        }

        x = x + deltaVec;
    }

    if (verbose && !converged) {
        cout << "Brak zbieżności po " << max_iter << " iteracjach" << endl;
    }

    return x;
}

/**
 * Test wrażliwości na przybliżenie początkowe
 */
void testSensitivity() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  EKSPERYMENT 1: Wrażliwość na przybliżenie początkowe     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    vector<Vec3> initialGuesses = {
        Vec3(1.0, 0.5, 1.7),
        Vec3(1.5, 0.3, 1.8),
        Vec3(0.8, 0.7, 1.6),
        Vec3(0.5, 1.0, 1.5),
        Vec3(2.0, 0.25, 1.9),
        Vec3(-1.0, -0.5, 1.7),
        Vec3(-0.8, -0.7, 1.6),
        Vec3(0.9, 0.6, -1.5),  // ujemne z
    };

    cout << fixed << setprecision(6);
    cout << setw(30) << "Przybliżenie początkowe"
         << setw(35) << "Rozwiązanie"
         << setw(15) << "||F(x)||" << endl;
    cout << string(80, '-') << endl;

    for (const auto& x0 : initialGuesses) {
        Vec3 solution = newtonMethod(x0, 1e-10, 1e-10, 100, false);
        Vec3 F = computeF(solution);
        double normF = norm(F);

        cout << "[" << setw(6) << x0.x << ", " << setw(6) << x0.y << ", " << setw(6) << x0.z << "]";
        cout << " → ";
        cout << "[" << setw(8) << solution.x << ", " << setw(8) << solution.y << ", " << setw(8) << solution.z << "]";
        cout << scientific << setw(15) << normF << endl;
    }
}

/**
 * Test różnych tolerancji
 */
void testTolerances() {
    cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  EKSPERYMENT 2: Wpływ tolerancji na liczbę iteracji       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    Vec3 x0(1.0, 0.5, 1.7);
    vector<double> tolerances = {1e-3, 1e-5, 1e-7, 1e-9, 1e-11, 1e-13};

    cout << setw(20) << "Tolerancja"
         << setw(20) << "Rozwiązanie x"
         << setw(15) << "||F(x)||" << endl;
    cout << string(55, '-') << endl;

    for (double tol : tolerances) {
        cout << scientific << setw(20) << tol;
        Vec3 solution = newtonMethod(x0, tol, tol, 100, false);
        Vec3 F = computeF(solution);
        cout << fixed << setw(20) << setprecision(10) << solution.x;
        cout << scientific << setw(15) << norm(F) << endl;
    }
}

/**
 * Analiza zbieżności - jak zmienia się błąd w kolejnych iteracjach
 */
void analyzeConvergence() {
    cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  EKSPERYMENT 3: Analiza zbieżności (szczegółowa)          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    Vec3 x0(1.0, 0.5, 1.7);

    cout << "Przybliżenie początkowe: ";
    x0.print();
    cout << "\n" << endl;

    newtonMethod(x0, 1e-12, 1e-12, 10, true);
}

/**
 * Porównanie norm w kryteriach stopu
 */
void compareNorms() {
    cout << "\n\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  EKSPERYMENT 4: Porównanie różnych norm                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;

    Vec3 x0(1.0, 0.5, 1.7);
    Vec3 x = x0;

    cout << setw(8) << "Iteracja"
         << setw(18) << "||Δx||₂"
         << setw(18) << "||Δx||∞"
         << setw(18) << "||F||₂"
         << setw(18) << "||F||∞" << endl;
    cout << string(80, '-') << endl;

    for (int iter = 0; iter < 8; iter++) {
        Vec3 F = computeF(x);
        double J[3][3];
        computeJacobian(x, J);

        double rhs[3] = {-F.x, -F.y, -F.z};
        double delta[3];

        if (!solveLinearSystem(J, rhs, delta)) {
            break;
        }

        Vec3 deltaVec(delta[0], delta[1], delta[2]);

        cout << setw(8) << iter
             << scientific << setprecision(4)
             << setw(18) << norm(deltaVec)
             << setw(18) << normInf(deltaVec)
             << setw(18) << norm(F)
             << setw(18) << normInf(F) << endl;

        x = x + deltaVec;

        if (norm(deltaVec) < 1e-12) break;
    }
}

int main() {
    cout << fixed << setprecision(6);

    // Uruchom wszystkie eksperymenty
    testSensitivity();
    testTolerances();
    analyzeConvergence();
    compareNorms();

    cout << "\n\n════════════════════════════════════════════════════════════" << endl;
    cout << "Wszystkie eksperymenty zakończone!" << endl;
    cout << "════════════════════════════════════════════════════════════\n" << endl;

    return 0;
}
