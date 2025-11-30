#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

template<typename T>
T dodaj_epsylon(T liczba, T epsilon) {
    return liczba + epsilon / T(2.0);
}

// Wyznaczanie epsylona maszynowego
template<typename T>
T oblicz_epsilon() {
    T epsilon = T(1.0);
    T jeden = T(1.0);
    while (dodaj_epsylon(jeden, epsilon) > jeden) {
        std::cout << std::fixed << std::setprecision(130) << "Epsilon: " << epsilon << "\n";
        epsilon /= T(2.0);
    }
    return epsilon;
}

// Liczba bitow mantysy
template<typename T>
int oblicz_bity_mantysy(T epsilon) {
    return static_cast<int>(std::round(-std::log2(static_cast<double>(epsilon))));
}

// Liczba cyfr znaczacych
template<typename T>
int oblicz_cyfry_znaczace(T epsilon) {
    return static_cast<int>(std::floor(-std::log10(static_cast<double>(epsilon))));
}

template<typename T>
void analizuj_typ(const std::string& nazwa) {
    T eps = oblicz_epsilon<T>();
    int bity = oblicz_bity_mantysy(eps);
    int cyfry = oblicz_cyfry_znaczace(eps);

    std::cout << std::scientific << std::setprecision(10);
    std::cout << "\n=== " << nazwa << " ===\n";
    std::cout << "Epsilon (eksperymentalny): " << eps << "\n";
    std::cout << "Epsilon (biblioteka):      " << std::numeric_limits<T>::epsilon() << "\n";
    std::cout << "Bity mantysy: " << bity << " (biblioteka: " << std::numeric_limits<T>::digits << ")\n";
    std::cout << "Cyfry znaczace: " << cyfry << "\n";
}

int main() {
    std::cout << "Epsilon maszynowy - Metody Obliczeniowe\n";

    analizuj_typ<float>("float");
    analizuj_typ<double>("double");
    analizuj_typ<long double>("long double");

    std::cout << "\n";
    return 0;
}
// FLOAT 2384185791015625 - 17
// DOUBLE 444089209850062616169452667236328125 - 37
// LONG DOUBLE 385185988877447170611195588516985463707620329643077639047987759113311767578125 - 79