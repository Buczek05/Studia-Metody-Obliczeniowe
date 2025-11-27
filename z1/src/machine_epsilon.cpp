#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <string>

/**
 * Program do eksperymentalnego wyznaczania epsylona maszynowego
 * i liczby bitów mantysy dla różnych typów zmiennoprzecinkowych.
 *
 * Zajęcia nr 1 - Metody Obliczeniowe
 */

// Deklaracje funkcji
template<typename T>
T oblicz_epsilon_maszynowy();

template<typename T>
int oblicz_bity_mantysy(T epsilon);

template<typename T>
int oblicz_cyfry_znaczace(T epsilon);

template<typename T>
void analizuj_typ(const std::string& nazwa_typu);

void wyjasnij_zwiazek_epsilon_precyzja();

/**
 * Eksperymentalne wyznaczenie epsylona maszynowego.
 *
 * Epsylon maszynowy to najmniejsza liczba ε taka, że fl(1 + ε) > 1,
 * gdzie fl() oznacza reprezentację zmiennoprzecinkową.
 *
 * Algorytm:
 * 1. Zaczynamy od epsilon = 1.0
 * 2. W pętli dzielimy epsilon przez 2
 * 3. Sprawdzamy czy (1.0 + epsilon/2) > 1.0
 * 4. Jeśli tak, kontynuujemy dzielenie
 * 5. Jeśli nie, to obecna wartość epsilon jest epsylonem maszynowym
 */
template<typename T>
T oblicz_epsilon_maszynowy() {
    T epsilon = static_cast<T>(1.0);
    T jeden = static_cast<T>(1.0);

    // Dzielimy epsilon przez 2 dopóki 1 + epsilon/2 > 1
    while (jeden + epsilon / static_cast<T>(2.0) > jeden) {
        epsilon /= static_cast<T>(2.0);
    }

    return epsilon;
}

/**
 * Oblicza liczbę bitów mantysy na podstawie epsylona maszynowego.
 *
 * Związek: epsilon = 2^(-liczba_bitów_mantysy)
 * Zatem: liczba_bitów = -log2(epsilon)
 *
 * W praktyce: liczba_bitów ≈ log2(1/epsilon)
 */
template<typename T>
int oblicz_bity_mantysy(T epsilon) {
    // Obliczamy log2(1/epsilon) = -log2(epsilon)
    // Używamy log2(x) = log(x) / log(2)
    return static_cast<int>(std::round(-std::log2(static_cast<double>(epsilon))));
}

/**
 * Oblicza liczbę cyfr znaczących w reprezentacji dziesiętnej.
 *
 * Liczba cyfr znaczących w systemie dziesiętnym:
 * cyfry = floor(log10(1/epsilon))
 */
template<typename T>
int oblicz_cyfry_znaczace(T epsilon) {
    return static_cast<int>(std::floor(-std::log10(static_cast<double>(epsilon))));
}

/**
 * Przeprowadza pełną analizę dla danego typu zmiennoprzecinkowego.
 */
template<typename T>
void analizuj_typ(const std::string& nazwa_typu) {
    std::cout << "═══════════════════════════════════════════════════════\n";
    std::cout << "  Analiza dla typu: " << nazwa_typu << "\n";
    std::cout << "═══════════════════════════════════════════════════════\n\n";

    // Obliczenia eksperymentalne
    T epsilon_eksp = oblicz_epsilon_maszynowy<T>();
    int bity_mantysy = oblicz_bity_mantysy(epsilon_eksp);
    int cyfry_znaczace = oblicz_cyfry_znaczace(epsilon_eksp);

    // Wartości teoretyczne z biblioteki standardowej
    T epsilon_std = std::numeric_limits<T>::epsilon();
    int bity_mantysy_std = std::numeric_limits<T>::digits;

    // Wyświetlanie wyników
    std::cout << std::scientific << std::setprecision(15);

    std::cout << "Wyniki eksperymentalne:\n";
    std::cout << "  Epsylon maszynowy:       " << epsilon_eksp << "\n";
    std::cout << "  Liczba bitów mantysy:    " << bity_mantysy << " bitów\n";
    std::cout << "  Liczba cyfr znaczących:  " << cyfry_znaczace << " cyfr dziesiętnych\n\n";

    std::cout << "Wartości ze standardowej biblioteki C++ (<limits>):\n";
    std::cout << "  std::numeric_limits::epsilon(): " << epsilon_std << "\n";
    std::cout << "  std::numeric_limits::digits:    " << bity_mantysy_std << " bitów\n\n";

    // Weryfikacja
    std::cout << "Weryfikacja:\n";
    bool epsilon_zgodny = (std::abs(epsilon_eksp - epsilon_std) < epsilon_std * 0.01);
    bool bity_zgodne = (bity_mantysy == bity_mantysy_std);

    std::cout << "  Zgodność epsylona:  " << (epsilon_zgodny ? "✓ TAK" : "✗ NIE") << "\n";
    std::cout << "  Zgodność bitów:     " << (bity_zgodne ? "✓ TAK" : "✗ NIE") << "\n\n";

    // Demonstracja znaczenia epsylona
    std::cout << "Demonstracja znaczenia epsylona maszynowego:\n";
    T jeden = static_cast<T>(1.0);
    bool test1 = (jeden + epsilon_eksp / static_cast<T>(2.0)) == jeden;
    bool test2 = (jeden + epsilon_eksp) > jeden;

    std::cout << "  1 + epsilon/2 == 1?     " << (test1 ? "TAK" : "NIE")
              << " (oczekiwane: TAK)\n";
    std::cout << "  1 + epsilon > 1?        " << (test2 ? "TAK" : "NIE")
              << " (oczekiwane: TAK)\n\n";
}

/**
 * Wyjaśnia związek między epsylonem maszynowym a precyzją arytmetyki.
 */
void wyjasnij_zwiazek_epsilon_precyzja() {
    std::cout << "╔═══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  ZWIĄZEK MIĘDZY EPSYLONEM MASZYNOWYM A PRECYZJĄ ARYTMETYKI   ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════╝\n\n";

    std::cout << "1. DEFINICJA EPSYLONA MASZYNOWEGO:\n";
    std::cout << "   Epsylon maszynowy (ε) to najmniejsza liczba, dla której\n";
    std::cout << "   fl(1 + ε) > 1, gdzie fl() oznacza reprezentację zmiennoprzecinkową.\n\n";

    std::cout << "2. REPREZENTACJA ZMIENNOPRZECINKOWA (IEEE 754):\n";
    std::cout << "   Liczba zmiennoprzecinkowa: x = (-1)^s × m × 2^e\n";
    std::cout << "   gdzie:\n";
    std::cout << "   - s: bit znaku\n";
    std::cout << "   - m: mantysa (1 ≤ m < 2 dla liczb znormalizowanych)\n";
    std::cout << "   - e: cecha (wykładnik)\n\n";

    std::cout << "3. ZWIĄZEK Z MANTYSĄ:\n";
    std::cout << "   Jeśli mantysa ma p bitów, to:\n";
    std::cout << "   ε = 2^(-p) lub ε = 2^(-(p-1)) (zależnie od definicji)\n\n";
    std::cout << "   Oznacza to, że epsylon maszynowy bezpośrednio określa\n";
    std::cout << "   precyzję z jaką możemy reprezentować liczby.\n\n";

    std::cout << "4. PRECYZJA WZGLĘDNA:\n";
    std::cout << "   Dla dowolnej liczby x reprezentowanej w systemie zmiennoprzecinkowym:\n";
    std::cout << "   |x - fl(x)| / |x| ≤ ε/2\n\n";
    std::cout << "   Oznacza to, że względny błąd reprezentacji jest ograniczony\n";
    std::cout << "   przez połowę epsylona maszynowego.\n\n";

    std::cout << "5. PRAKTYCZNE ZNACZENIE:\n";
    std::cout << "   - Im mniejszy epsylon, tym większa precyzja\n";
    std::cout << "   - Epsylon wyznacza \"rozdzielczość\" systemu liczbowego\n";
    std::cout << "   - Dwie liczby różniące się o mniej niż ε mogą być\n";
    std::cout << "     nierozróżnialne w arytmetyce zmiennoprzecinkowej\n\n";

    std::cout << "6. PRZYKŁAD:\n";
    std::cout << "   Dla float (IEEE 754 single precision):\n";
    std::cout << "   - Mantysa: 23 bity (+ 1 bit niejawny = 24 bity efektywnie)\n";
    std::cout << "   - Epsylon: 2^(-23) ≈ 1.19 × 10^(-7)\n";
    std::cout << "   - Precyzja: ~7 cyfr dziesiętnych\n\n";

    std::cout << "   Dla double (IEEE 754 double precision):\n";
    std::cout << "   - Mantysa: 52 bity (+ 1 bit niejawny = 53 bity efektywnie)\n";
    std::cout << "   - Epsylon: 2^(-52) ≈ 2.22 × 10^(-16)\n";
    std::cout << "   - Precyzja: ~16 cyfr dziesiętnych\n\n";

    std::cout << "7. KONSEKWENCJE DLA OBLICZEŃ NUMERYCZNYCH:\n";
    std::cout << "   - Błędy zaokrągleń akumulują się w obliczeniach\n";
    std::cout << "   - Odejmowanie bliskich liczb prowadzi do utraty cyfr znaczących\n";
    std::cout << "   - Należy unikać porównywania liczb zmiennoprzecinkowych\n";
    std::cout << "     na równość (a == b), lepiej sprawdzać |a - b| < ε\n\n";
}

/**
 * Funkcja główna programu.
 */
int main() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║     EKSPERYMENTALNE WYZNACZANIE EPSYLONA MASZYNOWEGO         ║\n";
    std::cout << "║              Metody Obliczeniowe - Zajęcia nr 1               ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════╝\n\n";

    // Analiza dla różnych typów
    analizuj_typ<float>("float");
    analizuj_typ<double>("double");
    analizuj_typ<long double>("long double");

    // Wyjaśnienie teoretyczne
    wyjasnij_zwiazek_epsilon_precyzja();

    std::cout << "╔═══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    KONIEC ANALIZY                             ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════╝\n\n";

    return 0;
}
