# Studentas v1.5

## Reikalavimai

| Reikalavimas | Versija |
|---|---|
| C++ standartas | C++14 |
| Kompiliatorius | g++ arba MSVC |
| CMake | 3.14+ |

---

## Įdiegimas ir paleidimas

### 1. Klonuok repoziciją
```bash
git clone https://github.com/zukasdovis/objektinis_1.git
cd objektinis/v1_0Vector
```

### 2. Kompiliavimas su g++
```bash
g++ failai.cpp generatorius.cpp ivedimas.cpp mediana.cpp output.cpp rusiavimas.cpp studentai.cpp tyrimai.cpp v1_0.cpp -o programa
```

### 3. Paleidimas
```bash
# Linux / Mac
./programa

# Windows
programa.exe
```

---

## Kompiliavimas su CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .

# Paleidimas
.\Debug\programa.exe   # Windows
./programa             # Linux
```

---

## Testų paleidimas

```bash
cd build
cmake ..
cmake --build .

.\Debug\testai.exe   # Windows
./testai             # Linux
```

---

## Naudojimas

Paleidus programą pasirodo meniu:


# Studentas v2.0

Šioje versijoje projektas papildytas automatizuotais unit testais ir Doxygen dokumentacija. Unit testai realizuoti naudojant GoogleTest karkasą, o testų tikslas - patikrinti svarbiausią Studentas klasės elgseną: konstruktorių, kopijavimą, perkėlimą, priskyrimo operatorių, įvesties/išvesties operatorių ir galutinio balo skaičiavimą.

# v1.5 rezultatai

Šioje versijoje išlaikyta ta pati v1.2 versijos logika, tačiau pridėta abstrakti bazinė klasė `Zmogus` ir iš jos išvesta `Studentas` klasė.

| Klasė       | Tipas    | Ką saugo                                        |
| ----------- | -------- | ----------------------------------------------- |
| `Zmogus`    | Abstract | vardą ir pavardę                                |
| `Studentas` | Derived  | pažymius, egzamino balą, galutinius įvertinimus |

---

## Bandymas sukurti abstrakčios "Zmogus" klasės objektą

## ![alt text](image.png)

## Rule of Five metodai

| Metodas                     | Sintaksė                                   | Paskirtis                                        |
| --------------------------- | ------------------------------------------ | ------------------------------------------------ |
| Default konstruktorius      | `Studentas()`                              | Sukuria tuščią objektą                           |
| Copy konstruktorius         | `Studentas(const Studentas& a)`            | Kuriama objekto kopija                           |
| Copy priskyrimo operatorius | `Studentas& operator=(const Studentas& a)` | Objekto kopijos priskyrimas — `b = a`            |
| Move konstruktorius         | `Studentas(Studentas&& a)`                 | Objekto perėmimas — `Studentas b = std::move(a)` |
| Move priskyrimo operatorius | `Studentas& operator=(Studentas&& a)`      | Objekto perėmimas — `b = std::move(a)`           |
| Destruktorius               | `~Studentas()`                             | Objekto sunaikinimas (veikia automatiškai)       |

---

## Įvesties/Išvesties operatoriai

| Operatorius  | Sintaksė                                                         | Paskirtis                             |
| ------------ | ---------------------------------------------------------------- | ------------------------------------- |
| `operator>>` | `std::istream& operator>>(std::istream& is, Studentas& s)`       | Nuskaito duomenis iš srauto į objektą |
| `operator<<` | `std::ostream& operator<<(std::ostream& os, const Studentas& s)` | Išveda objekto duomenis į srautą      |
