# Cardiorama

Inżynieria Biomedyczna - Dedykowane Algorytmy Diagnostyki Medycznej - Analiza EKG

## Na początek

Dzięki poniższym instrukcjom pobierzesz i uruchomisz projekt na swoim komputerze.

### Wymagania

Wszystko co znajdziesz poniżej zostało przetestowane na systemach Ubuntu 16.04 i Linux Mint 18 z CMake w wersji 3.5.1. i GCC w wersji 5.4.0

### Sklonuj repozytorium
```
$ git clone https://github.com/zamkot/cardiorama.git
```

### Utwórz katalog do kompilacji
```
$ cd cardiorama
$ mkdir build
```

### Skonfiguruj i skompiluj
```
$ cd build
$ cmake ..
$ make
```

Program gotowy do uruchomiania znajdziesz w ```${PROJECT_DIR}/build/cardiorama```

### Bonus
Wklej to do swojego ```.bashrc``` i zapomnij co tu widziałeś.
```
alias cardio="your/path/to/repo/cardio.sh"
```

## Jak zrobić moduł?

### 1. ```include/TwójModułuBase```

```c++
class TwójModułModuleBase : public ModuleBase {
public:
    virtual TwójModułData getResults() = 0; // Oblicza i zwraca wynik.
    virtual void configure(TwójModułConfig) = 0; // Opcjonalne.*
};
```

Wszystkie klasy bazowe modułów dziedziczą po ```ModuleBase```, która obsługuje przepływ informacji o zmianie stanu modułów od których twój moduł zależy.
Klasa bazowa zawiera deklaracje metod publicznych.  

*Jeżeli potrzebujesz parametrów wejściowych od użytkownika (np. wybór implementacji z kilku oferowanych przez moduł, progi), zadeklaruj kontener na te parametry i obsłuż go w metodzie ```configure()```.
```c++
enum class TwójModułParametr1 {
    wariant1,
    wariant2
};


struct TwójModułConfig {
    TwójModułParametr1 parametr1;
    int parametr2;
};

```

### 2. ```include/TwójModułModule.hpp```
Właściwy plik nagłówkowy twojego modułu.

```c++
class TwójModułModule : public TwójModułModuleBase {
    
    // chcemy dziedziczyć konstruktor po ModuleBase
    using ModuleBase::ModuleBase;

    // deklarujemy referencje do obiektów, które dostarczają twoje dane wejściowe
    PotrzebnyMiTenModuł1ModuleBase& potrzebnyMiTenModuł1Module;
    PotrzebnyMiTenModuł2ModuleBase& potrzebnyMiTenModuł2Module;

    TwójModułData results; // Tu przechowujemy wyniki obliczeń
    TwójModułConfig config; // Opcjonalne.

    // Serce modułu. Tutaj robisz swoje obliczenia.
    void runTwójModuł(); 

    // Prawdopodobnie nie chcesz robić wszystkich obliczeń w jednej metodzie. Dodaj tyle prywatnych metod ile ci się podoba.
    void /*albo inny typ*/ jakiśKrokObliczeń( /* parametry */);

public:

    // Konstruktor przyjmuje referencje do modułów które dostarczają nasze dane wejściowe
    TwójModułModule(PotrzebnyMiTenModuł1ModuleBase&, PotrzebnyMiTenModuł2ModuleBase&);

    // Będziemy implementować wirtualne metody zadeklarowane w klasie bazowej
    TwójModułData getResults() override;
    void configure(TwójModułConfig) override; // Mówiłem że to opcjonalne?
    
    // Opcjonalne. Możesz powrzucać do tych metod jakieś printy do debugowania.
    void notify() override;
    void invalidateResults() override;
};
```

### 3. src/TwójModuł/TwójModułModule.cpp
Implementacja twojego modułu

#### Konstruktor
```c++
TwójModułModule::TwójModułModule(PotrzebnyMiTenModuł1ModuleBase& potrzebnyMiTenModuł1Module, PotrzebnyMiTenModuł2ModuleBase& potrzebnyMiTenModuł2Module) :
    
    // Inicjujemy referencje do modułów które dostarczają nasze dane
    potrzebnyMiTenModuł1Module{ potrzebnyMiTenModuł1Module }, potrzebnyMiTenModuł2Module{ potrzebnyMiTenModuł2Module } {
        
        // Zgłaszamy modułom że chcemy być informowani kiedy zmieni się ich stan. 
        potrzebnyMiTenModuł1Module.attach(this);
        potrzebnyMiTenModuł2Module.attach(this);

        // Chcemy mieć jakąś domyślną konfigurację
        config.parametr1 = TwójModułParametr1::wariant1;
        config.parametr2 = 120;
    }
```

#### Zmiany stanu
W razie zmiany konfiguracji (i w kilku innych przypadkach) wyniki obliczeń przestaną być aktualne. Zmianie stanu zawsze musi towarzyszyć wywołanie ```invalidateResults()```. Dzięki temu  przy najbliższym wywołaniu ```getResults()``` będziemy wiedzieć że należy wykonać obliczenia od nowa. ```invalidateResults()``` automatycznie propaguje się na wszystkie moduły zależne od naszego.

```c++
void TwójModułModule::configure(TwójModułConfig config) {
    invalidateResults();
    this->config = config;
}
```

#### Implementacja algorytmu

```c++
void TwójModułModule::runTwójModuł() {

    // Tak pobieramy nasze dane wejściowe
    auto wejscie1 = potrzebnyMiTenModuł1Module.getResults();
    auto wejscie2 = potrzebnyMiTenModuł2Module.getResults();

    /*jakis kod*/

    if (config.parametr1 == TwójModułParametr1::wariant2) {
        /*jakiś kod*/
    } 
    else {
        /*inny kod*/
    }

    /*KOD*/

    results = {};

    // Nie zapomnij zaznaczyć że dane już są ok
    validateResults();
}
```

#### Getter do wyników
```c++
TwójModułData TwójModułModule::getResults() {
    
    if (!resultsValid()) {
        runTwójModuł();
    }

    return results;
}
```

#### Opcjonalne printy
```c++
void TwójModułModule::notify() {
    log("Notifying"); // Zrób co chcesz

    ModuleBase::notify(); // Wywołaj właściwą metodę
}
```
Pamiętaj żeby w deklaracji klasy wskazać, które metody będziesz przesłaniać:
```c++
/* include/TwojModułModule.hpp */
...
    void notify() override;
...
```

### Już wkrótce
#### Dependency Injection, testy