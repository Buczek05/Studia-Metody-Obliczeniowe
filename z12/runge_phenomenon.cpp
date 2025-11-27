#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Funkcja testowa demonstrująca zjawisko Rungego
double runge_function(double x, double a) {
    return x / (1.0 + a * pow(x, 4));
}

// Węzły równoodległe na przedziale [a, b]
vector<double> equidistant_nodes(int n, double a, double b) {
    vector<double> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = a + i * (b - a) / (n - 1);
    }
    return nodes;
}

// Węzły Czebyszewa na przedziale [a, b]
vector<double> chebyshev_nodes(int n, double a, double b) {
    vector<double> nodes(n);
    for (int i = 0; i < n; i++) {
        double t = cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
        nodes[i] = 0.5 * (a + b) + 0.5 * (b - a) * t;
    }
    return nodes;
}

// Obliczenie wartości funkcji w węzłach
vector<double> compute_values(const vector<double>& nodes, double a) {
    vector<double> values(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
        values[i] = runge_function(nodes[i], a);
    }
    return values;
}

// Obliczenie ilorazów różnicowych (tablica trójkątna)
vector<vector<double>> divided_differences(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    vector<vector<double>> dd(n, vector<double>(n, 0.0));

    // Pierwsza kolumna to wartości funkcji
    for (int i = 0; i < n; i++) {
        dd[i][0] = y[i];
    }

    // Obliczanie kolejnych kolumn ilorazów różnicowych
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            dd[i][j] = (dd[i+1][j-1] - dd[i][j-1]) / (x[i+j] - x[i]);
        }
    }

    return dd;
}

// Obliczenie wartości wielomianu w bazie Newtona przy użyciu schematu Hornera
double newton_polynomial(double x, const vector<double>& nodes, const vector<vector<double>>& dd) {
    int n = nodes.size();
    double result = dd[0][n-1];

    // Schemat Hornera dla wielomianu Newtona
    for (int i = n - 2; i >= 0; i--) {
        result = result * (x - nodes[i]) + dd[0][i];
    }

    return result;
}

// Alternatywna implementacja bez Hornera (dla porównania)
double newton_polynomial_direct(double x, const vector<double>& nodes, const vector<vector<double>>& dd) {
    int n = nodes.size();
    double result = dd[0][0];
    double product = 1.0;

    for (int i = 1; i < n; i++) {
        product *= (x - nodes[i-1]);
        result += dd[0][i] * product;
    }

    return result;
}

// Zapis danych do pliku CSV
void save_to_csv(const string& filename,
                 const vector<double>& x_vals,
                 const vector<double>& f_vals,
                 const vector<double>& p_equi,
                 const vector<double>& p_cheb) {
    ofstream file(filename);
    file << fixed << setprecision(10);

    // Nagłówek
    file << "x,f(x),P_equidistant(x),P_chebyshev(x),error_equi,error_cheb\n";

    // Dane
    for (size_t i = 0; i < x_vals.size(); i++) {
        file << x_vals[i] << ","
             << f_vals[i] << ","
             << p_equi[i] << ","
             << p_cheb[i] << ","
             << abs(f_vals[i] - p_equi[i]) << ","
             << abs(f_vals[i] - p_cheb[i]) << "\n";
    }

    file.close();
    cout << "Dane zapisane do pliku: " << filename << endl;
}

// Zapis węzłów do pliku
void save_nodes_to_csv(const string& filename,
                       const vector<double>& nodes_equi,
                       const vector<double>& values_equi,
                       const vector<double>& nodes_cheb,
                       const vector<double>& values_cheb) {
    ofstream file(filename);
    file << fixed << setprecision(10);

    file << "x_equi,y_equi,x_cheb,y_cheb\n";

    size_t max_size = max(nodes_equi.size(), nodes_cheb.size());
    for (size_t i = 0; i < max_size; i++) {
        if (i < nodes_equi.size()) {
            file << nodes_equi[i] << "," << values_equi[i];
        } else {
            file << ",";
        }
        file << ",";
        if (i < nodes_cheb.size()) {
            file << nodes_cheb[i] << "," << values_cheb[i];
        }
        file << "\n";
    }

    file.close();
    cout << "Węzły zapisane do pliku: " << filename << endl;
}

// Funkcja wyświetlająca błędy interpolacji
void display_errors(const vector<double>& x_vals,
                    const vector<double>& f_vals,
                    const vector<double>& p_vals,
                    const string& method_name) {
    double max_error = 0.0;
    double sum_error = 0.0;

    for (size_t i = 0; i < x_vals.size(); i++) {
        double error = abs(f_vals[i] - p_vals[i]);
        sum_error += error;
        if (error > max_error) {
            max_error = error;
        }
    }

    cout << "\n" << method_name << ":" << endl;
    cout << "  Maksymalny błąd: " << scientific << max_error << endl;
    cout << "  Średni błąd: " << sum_error / x_vals.size() << endl;
}

int main() {
    cout << "=== Demonstracja zjawiska Rungego ===" << endl;
    cout << "Funkcja: f(x) = x / (1 + a*x^4)" << endl;
    cout << "Przedział: [-1, 1]" << endl << endl;

    // Parametry
    double a;
    cout << "Podaj wartość parametru 'a' (np. 25 dla wyraźnego efektu Rungego): ";
    cin >> a;

    int n;
    cout << "Podaj liczbę węzłów interpolacji (np. 11): ";
    cin >> n;

    cout << "\n--- Rozpoczęcie obliczeń ---\n" << endl;

    // Zakres i liczba punktów do wykresu
    double x_min = -1.0;
    double x_max = 1.0;
    int num_plot_points = 1000;

    // Generowanie węzłów interpolacji
    cout << "Generowanie węzłów interpolacji..." << endl;
    vector<double> nodes_equi = equidistant_nodes(n, x_min, x_max);
    vector<double> nodes_cheb = chebyshev_nodes(n, x_min, x_max);

    // Obliczanie wartości funkcji w węzłach
    cout << "Obliczanie wartości funkcji w węzłach..." << endl;
    vector<double> values_equi = compute_values(nodes_equi, a);
    vector<double> values_cheb = compute_values(nodes_cheb, a);

    // Wyświetlenie węzłów
    cout << "\nWęzły równoodległe:" << endl;
    for (size_t i = 0; i < nodes_equi.size(); i++) {
        cout << "  x[" << i << "] = " << setw(10) << fixed << setprecision(6)
             << nodes_equi[i] << ", f(x) = " << values_equi[i] << endl;
    }

    cout << "\nWęzły Czebyszewa:" << endl;
    for (size_t i = 0; i < nodes_cheb.size(); i++) {
        cout << "  x[" << i << "] = " << setw(10) << fixed << setprecision(6)
             << nodes_cheb[i] << ", f(x) = " << values_cheb[i] << endl;
    }

    // Obliczanie ilorazów różnicowych
    cout << "\nObliczanie ilorazów różnicowych..." << endl;
    vector<vector<double>> dd_equi = divided_differences(nodes_equi, values_equi);
    vector<vector<double>> dd_cheb = divided_differences(nodes_cheb, values_cheb);

    // Wyświetlanie współczynników wielomianu (ilorazy różnicowe)
    cout << "\nWspółczynniki wielomianu Newtona (węzły równoodległe):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  c[" << i << "] = " << scientific << setprecision(6) << dd_equi[0][i] << endl;
    }

    cout << "\nWspółczynniki wielomianu Newtona (węzły Czebyszewa):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  c[" << i << "] = " << scientific << setprecision(6) << dd_cheb[0][i] << endl;
    }

    // Obliczanie wartości dla wykresu
    cout << "\nObliczanie wartości interpolacji dla " << num_plot_points << " punktów..." << endl;
    vector<double> x_vals(num_plot_points);
    vector<double> f_vals(num_plot_points);
    vector<double> p_equi(num_plot_points);
    vector<double> p_cheb(num_plot_points);

    double dx = (x_max - x_min) / (num_plot_points - 1);

    for (int i = 0; i < num_plot_points; i++) {
        x_vals[i] = x_min + i * dx;
        f_vals[i] = runge_function(x_vals[i], a);
        p_equi[i] = newton_polynomial(x_vals[i], nodes_equi, dd_equi);
        p_cheb[i] = newton_polynomial(x_vals[i], nodes_cheb, dd_cheb);
    }

    // Analiza błędów
    display_errors(x_vals, f_vals, p_equi, "Węzły równoodległe");
    display_errors(x_vals, f_vals, p_cheb, "Węzły Czebyszewa");

    // Zapis do pliku CSV
    cout << "\n--- Zapis wyników do plików ---" << endl;
    save_to_csv("runge_results.csv", x_vals, f_vals, p_equi, p_cheb);
    save_nodes_to_csv("runge_nodes.csv", nodes_equi, values_equi, nodes_cheb, values_cheb);

    // Podsumowanie
    cout << "\n=== Podsumowanie ===" << endl;
    cout << "Parametry:" << endl;
    cout << "  a = " << a << endl;
    cout << "  Liczba węzłów: " << n << endl;
    cout << "  Stopień wielomianu: " << n - 1 << endl;

    cout << "\nZjawisko Rungego:" << endl;
    cout << "  Dla węzłów równoodległych obserwujemy zjawisko Rungego -" << endl;
    cout << "  wielomian interpolacyjny oscyluje silnie na krańcach przedziału." << endl;
    cout << "  Węzły Czebyszewa znacząco redukują ten efekt, dając lepszą aproksymację." << endl;

    cout << "\nPliki wyjściowe:" << endl;
    cout << "  - runge_results.csv: wartości funkcji i interpolacji" << endl;
    cout << "  - runge_nodes.csv: współrzędne węzłów interpolacji" << endl;
    cout << "\nMożesz użyć tych plików do wizualizacji w Python, MATLAB, Excel itp." << endl;

    return 0;
}
