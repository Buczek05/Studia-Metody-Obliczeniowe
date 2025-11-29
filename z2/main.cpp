#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

double f_naiwna(double x) {
    double d = std::sinh(x) - x;
    if (d == 0.0) return std::nan("");
    return (x * x * x) / (6.0 * d);
}

double f_taylor(double x) {
    if (std::fabs(x) > 1.0) return f_naiwna(x);

    double x2 = x * x;
    double x4 = x2 * x2;
    return 1.0 / (1.0 + x2/20.0 + x4/840.0 + x4*x2/60480.0 + x4*x4/6652800.0);
}

int main() {
    std::ifstream fin("values.txt");
    if (!fin) {
        std::cerr << "Blad: nie mozna otworzyc values.txt\n";
        return 1;
    }

    std::ofstream f1("bledy_basic.dat"), f2("bledy_improved.dat");
    f1 << std::scientific << std::setprecision(16);
    f2 << std::scientific << std::setprecision(16);

    std::string line;
    for (int i = 0; i < 3; i++) std::getline(fin, line);

    double log_x, x, f_exact;
    while (fin >> log_x >> x >> f_exact) {
        double v1 = f_naiwna(x);
        double v2 = f_taylor(x);

        double err1 = (std::isnan(v1) || std::isinf(v1)) ? 1.0 : std::fabs((v1 - f_exact) / f_exact);
        double err2 = (std::isnan(v2) || std::isinf(v2)) ? 1.0 : std::fabs((v2 - f_exact) / f_exact);

        if (err1 < 1e-17) err1 = 1e-16;
        if (err2 < 1e-17) err2 = 1e-16;

        f1 << log_x << " " << std::log10(err1) << "\n";
        f2 << log_x << " " << std::log10(err2) << "\n";
    }

    std::cout << "Gotowe\n";
    return 0;
}
