#include <iostream>
#include <iomanip>
#include "thomas_solver.h"

using namespace std;

void print_vector(const string& name, const vector<double>& vec) {
    cout << name << " = [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << setw(10) << setprecision(4) << fixed << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== Przykład użycia klasy ThomasSolver ===" << endl;

    try {
        // Przykład 1: Układ z zadania
        cout << "\n--- Przykład 1: Układ z zadania ---" << endl;
        int n = 5;

        vector<double> a = {0, 2, 4, -6, -8};
        vector<double> b = {100, 200, 300, 200, 100};
        vector<double> c = {-1, -3, 5, -7, 0};
        vector<double> d = {199, 195, 929, 954, 360};

        vector<double> d_original = d; // kopia do weryfikacji

        ThomasSolver solver(n);
        solver.setMatrix(a, b, c);
        solver.setRHS(d);
        solver.solve();

        vector<double> solution = solver.getSolution();
        print_vector("Rozwiązanie", solution);

        double residuum = solver.verifyResiduum(d_original);
        cout << "Norma residuum: " << scientific << residuum << endl;

        // Przykład 2: Prosty układ testowy
        cout << "\n--- Przykład 2: Prosty układ testowy ---" << endl;
        n = 3;

        vector<double> a2 = {0, -1, -1};
        vector<double> b2 = {2, 2, 2};
        vector<double> c2 = {-1, -1, 0};
        vector<double> d2 = {1, 0, 1};

        vector<double> d2_original = d2;

        ThomasSolver solver2(n);
        solver2.setMatrix(a2, b2, c2);
        solver2.setRHS(d2);
        solver2.solve();

        solution = solver2.getSolution();
        print_vector("Rozwiązanie", solution);

        residuum = solver2.verifyResiduum(d2_original);
        cout << "Norma residuum: " << scientific << residuum << endl;

        // Przykład 3: Rozwiązanie wielu układów z tą samą macierzą
        cout << "\n--- Przykład 3: Wiele wektorów prawych stron ---" << endl;

        vector<vector<double>> multiple_rhs = {
            {1, 0, 1},
            {0, 1, 0},
            {1, 1, 1}
        };

        vector<vector<double>> solutions = solver2.solveMultiple(multiple_rhs);

        for (size_t i = 0; i < solutions.size(); i++) {
            cout << "Rozwiązanie " << i + 1 << ": ";
            print_vector("", solutions[i]);
        }

        // Przykład 4: Macierz z równania ciepła (dyskretyzacja)
        cout << "\n--- Przykład 4: Równanie ciepła (1D) ---" << endl;
        cout << "Równanie: -u''(x) = f(x), u(0) = 0, u(1) = 0" << endl;
        cout << "Dyskretyzacja metodą różnic skończonych" << endl;

        n = 4; // 4 punkty wewnętrzne
        double h = 0.2; // krok siatki (5 przedziałów, 6 punktów, 4 wewnętrzne)
        double h2 = h * h;

        // Macierz z dyskretyzacji -u''(x) = f(x)
        // [-u_{i-1} + 2u_i - u_{i+1}] / h^2 = f_i
        vector<double> a4(n, -1.0);
        vector<double> b4(n, 2.0);
        vector<double> c4(n, -1.0);
        a4[0] = 0; // nie używane
        c4[n-1] = 0; // nie używane

        // f(x) = 1 (przykładowa funkcja)
        vector<double> d4(n, h2);

        ThomasSolver solver4(n);
        solver4.setMatrix(a4, b4, c4);
        solver4.setRHS(d4);
        solver4.solve();

        solution = solver4.getSolution();
        cout << "\nRozwiązanie w punktach wewnętrznych:" << endl;
        cout << "x\t\tu(x)" << endl;
        cout << "0.0\t\t0.0000 (warunek brzegowy)" << endl;
        for (int i = 0; i < n; i++) {
            double x = (i + 1) * h;
            cout << fixed << setprecision(1) << x << "\t\t"
                 << setprecision(4) << solution[i] << endl;
        }
        cout << "1.0\t\t0.0000 (warunek brzegowy)" << endl;

    } catch (const exception& e) {
        cerr << "Błąd: " << e.what() << endl;
        return 1;
    }

    return 0;
}
