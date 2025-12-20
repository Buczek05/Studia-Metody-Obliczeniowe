/*
TEORIA MATEMATYCZNA:

1. IDEA PRZYBLIZEN ROZNICOWYCH
   Pochodna jest zdefiniowana jako granica:
   f'(x) = lim[h→0] (f(x+h) - f(x)) / h

   W obliczeniach numerycznych nie mozemy wziac h=0, wiec uzywamy
   malego, ale skonczonego h. Roznica miedzy wartoscia dokladna
   a przyblizona to BLAD OBCIECIA (truncation error).

2. WYPROWADZENIE WZOROW - SZEREG TAYLORA
   Rozwijamy f(x+h) i f(x-h) w szereg Taylora wokol x:

   f(x+h) = f(x) + h*f'(x) + (h²/2!)*f''(x) + (h³/3!)*f'''(x) + O(h⁴)
   f(x-h) = f(x) - h*f'(x) + (h²/2!)*f''(x) - (h³/3!)*f'''(x) + O(h⁴)

3. PRZYBLIZENIA DWUPUNKTOWE (dla pierwszej pochodnej)

   a) Roznica progresywna (forward difference):
      f'(x) ≈ (f(x+h) - f(x)) / h
      Blad obciecia: O(h) - rzad PIERWSZY
      Stosujemy na POCZATKU przedzialu (nie wymaga f(x-h))

   b) Roznica wsteczna (backward difference):
      f'(x) ≈ (f(x) - f(x-h)) / h
      Blad obciecia: O(h) - rzad PIERWSZY
      Stosujemy na KONCU przedzialu (nie wymaga f(x+h))

4. PRZYBLIZENIA TRZYPUNKTOWE

   a) Roznica centralna (dla pierwszej pochodnej):
      f'(x) ≈ (f(x+h) - f(x-h)) / (2h)
      Blad obciecia: O(h²) - rzad DRUGI
      Stosujemy w SRODKU przedzialu (wymaga f(x-h) i f(x+h))

   b) Roznica centralna drugiego rzedu (dla drugiej pochodnej):
      f''(x) ≈ (f(x+h) - 2*f(x) + f(x-h)) / h²
      Blad obciecia: O(h²) - rzad DRUGI

5. WPLYW BLEDOW MASZYNOWYCH
   - Dla DUZYCH h: dominuje blad obciecia (O(hⁿ))
   - Dla MALYCH h: dominuje blad maszynowy (≈ ε_mach / h)

   Istnieje optymalne h_opt, dla ktorego suma bledow jest minimalna.

6. WERYFIKACJA RZEDU DOKLADNOSCI
   Jesli blad = C * h^p, to:
   log|blad| = log(C) + p * log(h)

   Na wykresie log-log nachylenie prostej = rzad dokladnosci p

*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Badana funkcja: f(x) = cos(x)
template <typename T>
T funkcja(T x) {
    return cos(x);
}

// Dokladna pierwsza pochodna: f'(x) = -sin(x)
template <typename T>
T pochodna1Dokladna(T x) {
    return -sin(x);
}

// Dokladna druga pochodna: f''(x) = -cos(x)
template <typename T>
T pochodna2Dokladna(T x) {
    return -cos(x);
}

// Roznica progresywna: f'(x) ≈ (f(x+h) - f(x)) / h
template <typename T>
T roznicaProgresywna(T x, T h) {
    return (funkcja(x + h) - funkcja(x)) / h;
}

// Roznica wsteczna: f'(x) ≈ (f(x) - f(x-h)) / h
template <typename T>
T roznicaWsteczna(T x, T h) {
    return (funkcja(x) - funkcja(x - h)) / h;
}

// Roznica centralna (pierwsza pochodna): f'(x) ≈ (f(x+h) - f(x-h)) / (2h)
template <typename T>
T roznicaCentralna(T x, T h) {
    return (funkcja(x + h) - funkcja(x - h)) / (2 * h);
}

// Roznica centralna drugiego rzedu (druga pochodna): f''(x) ≈ (f(x+h) - 2*f(x) + f(x-h)) / h²
template <typename T>
T roznicaCentralna2Pochodna(T x, T h) {
    return (funkcja(x + h) - 2 * funkcja(x) + funkcja(x - h)) / (h * h);
}

/*
FUNKCJE OBLICZAJACE BLEDY DLA ROZNYCH PUNKTOW
*/

// POCZATEK PRZEDZIALU (x = 0) - tylko progresywna
template <typename T>
void obliczBledyPoczatek(T x, const string& nazwaTypu, ofstream& plik) {
    cout << "\n========================================" << endl;
    cout << "Punkt: x = 0 (POCZATEK przedzialu)" << endl;
    cout << "Typ zmiennej: " << nazwaTypu << endl;
    cout << "Metody: PROGRESYWNA" << endl;
    cout << "========================================" << endl;

    T dokladna1 = pochodna1Dokladna(x);
    cout << "Wartosc dokladna f'(0) = " << scientific << setprecision(10) << (double)dokladna1 << endl;

    cout << "\n" << setw(10) << "log10(h)"
         << setw(18) << "progresywna" << endl;
    cout << string(28, '-') << endl;

    for (int exp = -1; exp >= -15; exp--) {
        T h = pow((T)10, exp);

        T blad_prog = fabs(roznicaProgresywna(x, h) - dokladna1);

        double log_blad_prog = (blad_prog > 0) ? log10((double)blad_prog) : -20;

        cout << setw(10) << fixed << setprecision(0) << exp
             << setw(18) << fixed << setprecision(6) << log_blad_prog << endl;

        plik << log10((double)h) << " "
             << log_blad_prog << endl;
    }
    plik << "\n\n";
}

// SRODEK PRZEDZIALU (x = pi/4) - wszystkie metody
template <typename T>
void obliczBledySrodek(T x, const string& nazwaTypu, ofstream& plik) {
    cout << "\n========================================" << endl;
    cout << "Punkt: x = pi/4 (SRODEK przedzialu)" << endl;
    cout << "Typ zmiennej: " << nazwaTypu << endl;
    cout << "Metody: WSZYSTKIE" << endl;
    cout << "========================================" << endl;

    T dokladna1 = pochodna1Dokladna(x);
    T dokladna2 = pochodna2Dokladna(x);
    cout << "Wartosc dokladna f'(pi/4) = " << scientific << setprecision(10) << (double)dokladna1 << endl;
    cout << "Wartosc dokladna f''(pi/4) = " << scientific << setprecision(10) << (double)dokladna2 << endl;

    cout << "\n" << setw(10) << "log10(h)"
         << setw(18) << "progresywna"
         << setw(18) << "wsteczna"
         << setw(18) << "centralna"
         << setw(18) << "centr.II rzad" << endl;
    cout << string(82, '-') << endl;

    for (int exp = -1; exp >= -15; exp--) {
        T h = pow((T)10, exp);

        T blad_prog = fabs(roznicaProgresywna(x, h) - dokladna1);
        T blad_wst = fabs(roznicaWsteczna(x, h) - dokladna1);
        T blad_centr = fabs(roznicaCentralna(x, h) - dokladna1);
        T blad_centr2 = fabs(roznicaCentralna2Pochodna(x, h) - dokladna2);

        double log_blad_prog = (blad_prog > 0) ? log10((double)blad_prog) : -20;
        double log_blad_wst = (blad_wst > 0) ? log10((double)blad_wst) : -20;
        double log_blad_centr = (blad_centr > 0) ? log10((double)blad_centr) : -20;
        double log_blad_centr2 = (blad_centr2 > 0) ? log10((double)blad_centr2) : -20;

        cout << setw(10) << fixed << setprecision(0) << exp
             << setw(18) << fixed << setprecision(6) << log_blad_prog
             << setw(18) << fixed << setprecision(6) << log_blad_wst
             << setw(18) << fixed << setprecision(6) << log_blad_centr
             << setw(18) << fixed << setprecision(6) << log_blad_centr2 << endl;

        plik << log10((double)h) << " "
             << log_blad_prog << " "
             << log_blad_wst << " "
             << log_blad_centr << " "
             << log_blad_centr2 << endl;
    }
    plik << "\n\n";
}

// KONIEC PRZEDZIALU (x = pi/2) - tylko wsteczna
template <typename T>
void obliczBledyKoniec(T x, const string& nazwaTypu, ofstream& plik) {
    cout << "\n========================================" << endl;
    cout << "Punkt: x = pi/2 (KONIEC przedzialu)" << endl;
    cout << "Typ zmiennej: " << nazwaTypu << endl;
    cout << "Metody: WSTECZNA" << endl;
    cout << "========================================" << endl;

    T dokladna1 = pochodna1Dokladna(x);
    cout << "Wartosc dokladna f'(pi/2) = " << scientific << setprecision(10) << (double)dokladna1 << endl;

    cout << "\n" << setw(10) << "log10(h)"
         << setw(18) << "wsteczna" << endl;
    cout << string(28, '-') << endl;

    for (int exp = -1; exp >= -15; exp--) {
        T h = pow((T)10, exp);

        T blad_wst = fabs(roznicaWsteczna(x, h) - dokladna1);

        double log_blad_wst = (blad_wst > 0) ? log10((double)blad_wst) : -20;

        cout << setw(10) << fixed << setprecision(0) << exp
             << setw(18) << fixed << setprecision(6) << log_blad_wst << endl;

        plik << log10((double)h) << " "
             << log_blad_wst << endl;
    }
    plik << "\n\n";
}


int main() {
    cout << "   PRZYBLIZENIA ROZNICOWE DLA POCHODNYCH" << endl;
    cout << "   Funkcja: f(x) = cos(x), przedzial [0, pi/2]" << endl;

    double x_start = 0.0;
    double x_middle = M_PI / 4.0;
    double x_end = M_PI / 2.0;

    long double x_start_ld = 0.0L;
    long double x_middle_ld = M_PI / 4.0L;
    long double x_end_ld = M_PI / 2.0L;

    cout << "\nPunkty badania:" << endl;
    cout << "  x = 0 (poczatek) -> progresywna" << endl;
    cout << "  x = pi/4 (srodek) -> wszystkie metody" << endl;
    cout << "  x = pi/2 (koniec) -> wsteczna" << endl;

    // OBLICZENIA DLA TYPU DOUBLE
    cout << "\n============== TYP: DOUBLE ==============" << endl;

    ofstream plik_double_start("bledy_double_start.dat");
    ofstream plik_double_middle("bledy_double_middle.dat");
    ofstream plik_double_end("bledy_double_end.dat");

    plik_double_start << "# log10(h)  log10(blad_prog)" << endl;
    plik_double_middle << "# log10(h)  log10(blad_prog)  log10(blad_wst)  log10(blad_centr)  log10(blad_centr2)" << endl;
    plik_double_end << "# log10(h)  log10(blad_wst)" << endl;

    obliczBledyPoczatek<double>(x_start, "double", plik_double_start);
    obliczBledySrodek<double>(x_middle, "double", plik_double_middle);
    obliczBledyKoniec<double>(x_end, "double", plik_double_end);

    plik_double_start.close();
    plik_double_middle.close();
    plik_double_end.close();

    // OBLICZENIA DLA TYPU LONG DOUBLE
    cout << "\n============ TYP: LONG DOUBLE ============" << endl;

    ofstream plik_ld_start("bledy_long_double_start.dat");
    ofstream plik_ld_middle("bledy_long_double_middle.dat");
    ofstream plik_ld_end("bledy_long_double_end.dat");

    plik_ld_start << "# log10(h)  log10(blad_prog)" << endl;
    plik_ld_middle << "# log10(h)  log10(blad_prog)  log10(blad_wst)  log10(blad_centr)  log10(blad_centr2)" << endl;
    plik_ld_end << "# log10(h)  log10(blad_wst)" << endl;

    obliczBledyPoczatek<long double>(x_start_ld, "long double", plik_ld_start);
    obliczBledySrodek<long double>(x_middle_ld, "long double", plik_ld_middle);
    obliczBledyKoniec<long double>(x_end_ld, "long double", plik_ld_end);

    plik_ld_start.close();
    plik_ld_middle.close();
    plik_ld_end.close();

    // PODSUMOWANIE
    cout << "\n========================================" << endl;
    cout << "PODSUMOWANIE" << endl;
    cout << "========================================" << endl;

    cout << "\n1. TEORETYCZNE RZEDY DOKLADNOSCI:" << endl;
    cout << "   - Progresywna (2-pkt):        O(h)  - rzad 1" << endl;
    cout << "   - Wsteczna (2-pkt):           O(h)  - rzad 1" << endl;
    cout << "   - Centralna (3-pkt):          O(h^2) - rzad 2" << endl;
    cout << "   - Centralna II rzad (3-pkt):  O(h^2) - rzad 2" << endl;

    cout << "\n2. ZASTOSOWANIE METOD:" << endl;
    cout << "   - Poczatek (x=0):   progresywna" << endl;
    cout << "   - Srodek (x=pi/4):  wszystkie metody" << endl;
    cout << "   - Koniec (x=pi/2):  wsteczna" << endl;

    cout << "\nDane zapisane do plikow:" << endl;
    cout << "  bledy_double_start.dat, bledy_double_middle.dat, bledy_double_end.dat" << endl;
    cout << "  bledy_long_double_start.dat, bledy_long_double_middle.dat, bledy_long_double_end.dat" << endl;

    return 0;
}
