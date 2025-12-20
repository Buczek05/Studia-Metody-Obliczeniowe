#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-10;
const double DELTA = 1e-10;
const int MAX_ITER = 50;

// Zadanie 1a: sinh(x) + x/4 - 1 = 0
double f1(double x) { return sinh(x) + x/4.0 - 1.0; }
double df1(double x) { return cosh(x) + 0.25; }
double g1(double x) { return asinh(1.0 - x/4.0); }

// Zadanie 1b: tanh(x) + 2(x-1) = 0
double f2(double x) { return tanh(x) + 2.0*(x - 1.0); }
double df2(double x) { return 1.0/(cosh(x)*cosh(x)) + 2.0; }
double g2(double x) { return 1.0 - tanh(x)/2.0; }

// Metoda Picarda
void picard(double (*g)(double), double (*f)(double), double x0) {
    cout << "\n--- PICARD ---\n";
    cout << setw(4) << "i" << setw(18) << "x" << setw(18) << "f(x)" << setw(18) << "blad\n";

    double x = x0;
    for(int i = 0; i < MAX_ITER; i++) {
        double x_new = g(x);
        double fx = f(x_new);
        double err = fabs(x_new - x);

        cout << setw(4) << i << setw(18) << x_new << setw(18) << fx << setw(18) << err << "\n";

        if(err < EPS && fabs(fx) < DELTA) {
            cout << "Wynik: " << x_new << " (iteracji: " << i+1 << ")\n";
            return;
        }
        x = x_new;
    }
    cout << "Brak zbieznosci\n";
}

// Metoda Bisekcji
void bisection(double (*f)(double), double a, double b) {
    cout << "\n--- BISEKCJA ---\n";

    if(f(a)*f(b) >= 0) {
        cout << "Zly przedzial!\n";
        return;
    }

    cout << setw(4) << "i" << setw(18) << "c" << setw(18) << "f(c)" << setw(18) << "blad\n";

    double c, prev = a;
    for(int i = 0; i < MAX_ITER; i++) {
        c = (a + b) / 2.0;
        double fc = f(c);

        cout << setw(4) << i << setw(18) << c << setw(18) << fc << setw(18) << fabs(c-prev) << "\n";

        if(fabs(fc) < DELTA && fabs(b-a)/2 < EPS) {
            cout << "Wynik: " << c << " (iteracji: " << i+1 << ")\n";
            return;
        }

        if(f(a)*fc < 0) b = c;
        else a = c;
        prev = c;
    }
    cout << "Wynik: " << c << "\n";
}

// Metoda Newtona
void newton(double (*f)(double), double (*df)(double), double x0) {
    cout << "\n--- NEWTON ---\n";
    cout << setw(4) << "i" << setw(18) << "x" << setw(18) << "f(x)" << setw(18) << "blad\n";

    double x = x0;
    for(int i = 0; i < MAX_ITER; i++) {
        double fx = f(x);
        double dfx = df(x);

        if(fabs(dfx) < 1e-15) {
            cout << "Pochodna = 0!\n";
            return;
        }

        double x_new = x - fx/dfx;
        double err = fabs(x_new - x);

        cout << setw(4) << i << setw(18) << x_new << setw(18) << f(x_new) << setw(18) << err << "\n";

        if(err < EPS || fabs(f(x_new)) < DELTA) {
            cout << "Wynik: " << x_new << " (iteracji: " << i+1 << ")\n";
            return;
        }
        x = x_new;
    }
    cout << "Brak zbieznosci\n";
}

// Metoda Siecznych
void secant(double (*f)(double), double x0, double x1) {
    cout << "\n--- SIECZNE ---\n";
    cout << setw(4) << "i" << setw(18) << "x" << setw(18) << "f(x)" << setw(18) << "blad\n";

    double xp = x0, xc = x1;
    for(int i = 0; i < MAX_ITER; i++) {
        double fp = f(xp), fc = f(xc);

        if(fabs(fc - fp) < 1e-15) {
            cout << "Dzielenie przez 0!\n";
            return;
        }

        double x_new = xc - fc*(xc - xp)/(fc - fp);
        double err = fabs(x_new - xc);

        cout << setw(4) << i << setw(18) << x_new << setw(18) << f(x_new) << setw(18) << err << "\n";

        if(err < EPS || fabs(f(x_new)) < DELTA) {
            cout << "Wynik: " << x_new << " (iteracji: " << i+1 << ")\n";
            return;
        }
        xp = xc;
        xc = x_new;
    }
    cout << "Brak zbieznosci\n";
}

// Algorytm Herona
void heron(double a, double x0) {
    cout << "\n--- HERON (sqrt(" << a << ")) ---\n";
    cout << setw(4) << "i" << setw(18) << "x" << setw(18) << "x^2-a" << setw(18) << "blad\n";

    double x = x0;
    for(int i = 0; i < MAX_ITER; i++) {
        double x_new = 0.5*(x + a/x);
        double err = fabs(x_new - x);

        cout << setw(4) << i << setw(18) << x_new << setw(18) << x_new*x_new - a << setw(18) << err << "\n";

        if(err < EPS) {
            cout << "Wynik: " << x_new << " (dokladny: " << sqrt(a) << ")\n";
            return;
        }
        x = x_new;
    }
}

int main() {
    cout << fixed << setprecision(10);

    // Zadanie 1a: sinh(x) + x/4 - 1 = 0
    cout << "\n========== ZADANIE 1a: sinh(x) + x/4 - 1 = 0 ==========\n";
    picard(g1, f1, 0.5);
    bisection(f1, 0.0, 2.0);
    newton(f1, df1, 0.5);
    secant(f1, 0.0, 1.0);

    // Zadanie 1b: tanh(x) + 2(x-1) = 0
    cout << "\n========== ZADANIE 1b: tanh(x) + 2(x-1) = 0 ==========\n";
    picard(g2, f2, 0.5);
    bisection(f2, 0.0, 1.0);
    newton(f2, df2, 0.5);
    secant(f2, 0.0, 1.0);

    // Zadanie 2: Algorytm Herona
    cout << "\n========== ZADANIE 2: Algorytm Herona ==========\n";
    heron(16.0, 1.0);
    heron(2.0, 1.0);

    return 0;
}
