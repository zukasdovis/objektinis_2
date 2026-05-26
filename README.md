# Studentas v3.0

C++ programa skirta studentų duomenų valdymui su nuosavu Vector konteineriu.

## Reikalavimai

| Reikalavimas | Versija |
|---|---|
| C++ standartas | C++14 |
| Kompiliatorius | g++ arba MSVC |
| CMake | 3.14+ |
| NSIS | 3.0+ |

---

## Diegimas

### Su Setup.exe
1. Parsisiųsk `Studentas_Setup.exe`
2. Paleisk ir sekk instrukcijas
3. Programa įdiegiama į `C:\Program Files\VU\Vardenis-Pavardenis`
4. Darbalaukyje ir Start meniu atsiranda nuorodos
5. Programa paleidžiama su administratoriaus teisėmis

### Rankinis
```bash
git clone https://github.com/zukasdovis/objektinis2.git
cd objektinis2/v1_0Vector
```

---

## Kompiliavimas

```bash
# Su g++
g++ failai.cpp generatorius.cpp ivedimas.cpp mediana.cpp output.cpp rusiavimas.cpp studentai.cpp tyrimai.cpp v1_0.cpp -o programa

# Su CMake
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Naudojimas
1-ranka 2-generuoti pazymius 3-viska generuoti 4-skaityti faila
6-rusiuoti varda 7-pavarde 8-galutinis
9-i faila 10-i ekrana 11-atlikti tyrimus 5-baigti

| Pasirinkimas | Veiksmas |
|---|---|
| 1 | Įvesti studentą rankiniu būdu |
| 2 | Generuoti pažymius automatiškai |
| 3 | Generuoti viską automatiškai |
| 4 | Skaityti duomenis iš failo |
| 6 | Rūšiuoti pagal vardą |
| 7 | Rūšiuoti pagal pavardę |
| 8 | Rūšiuoti pagal galutinį balą |
| 9 | Išsaugoti į failą |
| 10 | Išvesti į ekraną |
| 11 | Greičio tyrimai |
| 5 | Baigti |

### Failo formatas
Vardas Pavarde ND1 ND2 ND3 ND4 ND5 ND6 ND7 ND8 ND9 ND10 Egz
Jonas  Jonaitis 8   7   9   6   5   8   7   9   6   8    10
---

## Vector konteineris

Nuosavas `Vector<T>` konteineris, analogiškas `std::vector`.

### Realizuoti metodai

| Kategorija | Metodai |
|---|---|
| Konstruktoriai | `Vector()`, `Vector(n, val)`, `Vector(copy)`, `Vector(move)`, `Vector({...})` |
| Rule of Five | `~Vector()`, `operator=(copy)`, `operator=(move)`, `operator=({...})` |
| Elementų prieiga | `at()`, `operator[]`, `front()`, `back()`, `data()` |
| Iteratoriai | `begin()`, `end()`, `cbegin()`, `cend()` |
| Talpa | `size()`, `capacity()`, `empty()`, `reserve()`, `shrink_to_fit()`, `max_size()` |
| Modifikatoriai | `push_back()`, `pop_back()`, `emplace_back()`, `insert()`, `erase()`, `clear()`, `resize()`, `swap()`, `assign()` |
| Lyginimo operatoriai | `==`, `!=`, `<`, `>`, `<=`, `>=` |

### Naudojimo pavyzdžiai

**push_back:**
```cpp
Vector<int> v;
v.push_back(1);
v.push_back(2);
// v = [1, 2]
```

**insert:**
```cpp
Vector<int> v = {1, 2, 3};
v.insert(v.begin() + 1, 99);
// v = [1, 99, 2, 3]
```

**erase:**
```cpp
Vector<int> v = {1, 2, 3, 4};
v.erase(v.begin() + 1);
// v = [1, 3, 4]
```

**reserve:**
```cpp
Vector<int> v;
v.reserve(100); // capacity=100, size=0
```

**sort su Vector:**
```cpp
Vector<int> v = {3, 1, 2};
std::sort(v.begin(), v.end());
// v = [1, 2, 3]
```

---

## Spartos analizė

### push_back() greitis

| Elementų sk. | std::vector | Vector |
|---|---|---|
| 10,000 | ~0.001s | ~0.001s |
| 100,000 | ~0.003s | ~0.003s |
| 1,000,000 | ~0.02s | ~0.02s |
| 10,000,000 | ~0.2s | ~0.2s |
| 100,000,000 | ~2.0s | ~2.1s |

### Atminties perskirstymai (100,000,000 elementų)

| Konteineris | Perskirstymų sk. |
|---|---|
| std::vector | 27 |
| Vector | 27 |

Abu naudoja x2 strategiją → log2(100,000,000) ≈ 27

### Programos greitis

| Studentų sk. | Operacija | std::vector | Vector |
|---|---|---|---|
| 100,000 | Nuskaitymas | ~0.05s | ~0.06s |
| 100,000 | Rūšiavimas | ~0.06s | ~0.06s |
| 100,000 | Skirstymas | ~0.05s | ~0.05s |
| 1,000,000 | Nuskaitymas | ~0.5s | ~0.6s |
| 1,000,000 | Rūšiavimas | ~0.6s | ~0.6s |
| 1,000,000 | Skirstymas | ~0.5s | ~0.5s |
| 10,000,000 | Nuskaitymas | ~5s | ~6s |
| 10,000,000 | Rūšiavimas | ~6s | ~6s |
| 10,000,000 | Skirstymas | ~5s | ~5s |

---

## Testai

```bash
# Kompiliavimas
cd build
cmake ..
cmake --build .

# Studentas testai
.\Debug\testai.exe

# Vector testai
.\Debug\testai_vector.exe
```

### Studentas testai

| Testas | Tikrina |
|---|---|
| `DefaultKonstruktorius` | Tuščio objekto sukūrimą |
| `StreamKonstruktorius` | Nuskaitymą iš srauto |
| `CopyKonstruktorius` | Rule of Five - kopijavimą |
| `MoveKonstruktorius` | Rule of Five - perkėlimą |
| `CopyAssignment` | Rule of Five - copy priskyrimą |
| `MoveAssignment` | Rule of Five - move priskyrimą |
| `Destruktorius` | Destruktoriaus iškvietimą |
| `IvestiesOperatorius` | `>>` operatorių |
| `IsvestiesOperatorius` | `<<` operatorių |
| `Polimorfizmas` | Zmogus abstrakčią klasę |

### Vector testai

| Testas | Tikrina |
|---|---|
| `DefaultKonstruktorius` | Tuščio vektoriaus sukūrimą |
| `CopyKonstruktorius` | Kopijavimą |
| `MoveKonstruktorius` | Perkėlimą |
| `CopyAssignment` | Copy priskyrimą |
| `MoveAssignment` | Move priskyrimą |
| `At_IsRibu` | Exception ribų tikrinimą |
| `PushBack` | Elementų pridėjimą |
| `InsertInterval` | Intervalo įterpimą |
| `Erase` | Elementų trinimą |
| `Swap` | Vektorių sukeitimą |

---

## Versijų istorija

| Versija | Pakeitimai |
|---|---|
| v1.0 | Pradinė versija su struct |
| v1.1 | Struct pakeistas į klasę |
| v1.2 | Rule of Five, I/O operatoriai, testai |
| v1.5 | Abstrakti klasė Zmogus, išvestinė klasė Studentas |
| v2.0 | Doxygen dokumentacija, Google Test |
| v3.0 | Nuosavas Vector konteineris, spartos analizė, Setup.exe |
