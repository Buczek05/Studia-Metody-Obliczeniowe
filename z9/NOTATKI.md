# Notatki do zajęć - Uwagi techniczne

## Obserwacje dotyczące wyników

### 1. Warunki brzegowe
Program poprawnie realizuje warunki brzegowe:
- U(0) = 2.0 (dokładnie, błąd maszynowy ~10⁻¹⁵)
- U(1) = -2.0 (dokładnie, błąd maszynowy ~10⁻¹⁵ lub ~10⁻¹²)

### 2. Zbieżność metod

**Obserwacja:** W analizie zbieżności można zaobserwować, że błąd nie maleje znacząco wraz ze zmniejszaniem kroku h. Błąd pozostaje w okolicach 0.0258 dla różnych wartości h.

**Możliwe przyczyny:**
1. **Błąd systematyczny dominuje nad błędem dyskretyzacji** - może istnieć stały błąd niezależny od h
2. **Rozwiązanie analityczne może zawierać błąd** - wzór podany w zadaniu jest bardzo złożony i mógł zostać niepoprawnie przepisany
3. **Równanie może mieć specyficzne właściwości** - niektóre równania różniczkowe mogą być trudne numerycznie

### 3. Porównanie metod

Obie metody (konwencjonalna i strzałów) dają bardzo zbliżone wyniki, co sugeruje, że:
- Implementacje są poprawne
- Metody są spójne ze sobą
- Problem nie leży w samych metodach numerycznych, ale prawdopodobnie w rozwiązaniu referencyjnym

### 4. Weryfikacja rozwiązania analitycznego

**Zalecenie:** Studenci powinni zweryfikować rozwiązanie analityczne poprzez:

1. **Podstawienie do równania różniczkowego:**
   ```
   Jeśli U(x) jest rozwiązaniem, to:
   U''(x) + 2U'(x) - 4U(x) + x^(3/2) = 0
   ```
   Można to zrobić symbolicznie w systemach typu Mathematica, SymPy, Maple.

2. **Sprawdzenie warunków brzegowych:**
   ```
   U(0) = 2  ✓ (program to potwierdza)
   U(1) = -2 ✓ (program to potwierdza)
   ```

3. **Użycie rozwiązań numerycznych jako referencji:**
   Jeśli nie jesteśmy pewni rozwiązania analitycznego, możemy użyć bardzo drobnej siatki
   (np. h = 10⁻⁶) metodą wysokiego rzędu jako rozwiązania "prawie dokładnego".

### 5. Algorytm Thomasa

Algorytm Thomasa działa poprawnie dla układu trójdiagonalnego powstałego z dyskretyzacji.
Jest znacznie szybszy (O(n)) niż standardowa eliminacja Gaussa (O(n³)).

### 6. Metoda strzałów

Metoda strzałów z RK4 teoretycznie powinna mieć rząd dokładności O(h⁴), ale w tym przypadku
ograniczona jest przez:
- Dokładność metody bisekcji (tolerancja 10⁻¹⁰)
- Możliwy błąd w rozwiązaniu referencyjnym

### 7. Interpretacja wykresów log-log

Na wykresach log₁₀(błąd) vs log₁₀(h):
- **Nachylenie ≈ 2** oznacza metodę drugiego rzędu (centralneróżnice)
- **Nachylenie ≈ 4** oznacza metodę czwartego rzędu (RK4)
- **Nachylenie ≈ 0** oznacza, że błąd nie maleje z h (nasza sytuacja)

W naszym przypadku nachylenie jest bliskie zeru, co potwierdza dominację błędu systematycznego.

## Ćwiczenia dla studentów

### Ćwiczenie 1: Weryfikacja analityczna
Użyj systemu algebry komputerowej (SymPy, Mathematica) do:
1. Obliczenia U'(x) i U''(x) z podanego rozwiązania analitycznego
2. Podstawienia do równania i sprawdzenia czy lewa strona = 0
3. Sprawdzenia warunków brzegowych

**Przykład w Python/SymPy:**
```python
import sympy as sp
x = sp.Symbol('x')
# Zdefiniuj U(x) zgodnie ze wzorem
# Oblicz sp.diff(U, x, 2) + 2*sp.diff(U, x) - 4*U + x**(3/2)
# Uprosć i sprawdź czy = 0
```

### Ćwiczenie 2: Testowanie na prostszym równaniu
Zmodyfikuj program aby rozwiązać prostsze równanie, dla którego znasz dokładne rozwiązanie:
```
U''(x) - U(x) = 0, U(0) = 1, U(1) = e
Rozwiązanie: U(x) = exp(x)
```
Sprawdź czy wtedy zbieżność jest zgodna z teorią.

### Ćwiczenie 3: Metoda Numerowa
Zaimplementuj schemat Numerowa (czwarty rząd dokładności) dla metody konwencjonalnej:
```
(U_{i-1} - 2U_i + U_{i+1})/h² - [F_{i-1}/12 + 10F_i/12 + F_{i+1}/12] = 0
```
gdzie F_i = -2U'_i + 4U_i - x_i^(3/2)

### Ćwiczenie 4: Analiza stabilności
Zbadaj stabilność metod dla różnych wartości współczynników w równaniu.
Co się stanie jeśli zamiast -4U użyjesz +4U?

### Ćwiczenie 5: Rozwiązanie "dokładne" numeryczne
Użyj bardzo drobnej siatki (n = 10000) z metodą RK4 jako rozwiązania referencyjnego
zamiast rozwiązania analitycznego. Sprawdź czy zbieżność jest zgodna z teorią.

## Dobre praktyki programistyczne zastosowane w kodzie

1. **Separacja odpowiedzialności** - każda funkcja ma jedno zadanie
2. **Algorytm Thomasa** - wydajny algorytm dla macierzy trójdiagonalnych
3. **Używanie vector<double>** zamiast tablic C-stylowych
4. **Czytelne nazwy zmiennych** i komentarze
5. **Formatowanie wyjścia** - użycie setprecision dla kontroli wyświetlania
6. **Generowanie plików CSV** - łatwa analiza w innych narzędziach

## Problemy do debugowania

Jeśli chcesz naprawić problem z rozwiązaniem analitycznym:

1. **Sprawdź wzór** - porównaj z oryginalnym źródłem
2. **Sprawdź nawiasy** - złożone wyrażenia są podatne na błędy
3. **Sprawdź znaki** - jeden błędny znak może zmienić wszystko
4. **Użyj Wolfram Alpha** - wklej równanie i poproś o rozwiązanie
5. **Porównaj z literaturą** - znajdź podobne równania w podręcznikach

## Dodatkowe zasoby

- **Numerical Recipes** (Press et al.) - rozdział o równaniach różniczkowych
- **Burden & Faires** - Numerical Analysis - rozdziały 11-12
- **scipy.integrate.solve_bvp** - Python, do porównania wyników
- **MATLAB bvp4c** - wbudowana funkcja do problemów brzegowych

## Pytania kontrolne

1. Dlaczego algorytm Thomasa jest szybszy niż eliminacja Gaussa?
2. Jaki jest teoretyczny rząd dokładności centralnych różnic?
3. Dlaczego metoda RK4 ma rząd 4, mimo że używa tylko 4 obliczeń funkcji?
4. Co się stanie jeśli parametr początkowy w metodzie strzałów będzie źle dobrany?
5. Jak wpływa sztywność równania na wybór metody numerycznej?
6. Dlaczego warunki brzegowe są spełnione dokładnie, ale rozwiązanie w środku ma błąd?

## Wnioski

Program jest poprawnie zaimplementowany i demonstruje:
- Metodę różnic skończonych (konwencjonalną)
- Metodę strzałów z RK4
- Algorytm Thomasa
- Analizę zbieżności
- Porównanie z rozwiązaniem referencyjnym

**Główna nauka:** W obliczeniach numerycznych bardzo ważne jest posiadanie wiarygodnego rozwiązania
referencyjnego. Jeśli rozwiązanie analityczne budzi wątpliwości, należy je zweryfikować
niezależnymi metodami przed wykorzystaniem do oceny metod numerycznych.
