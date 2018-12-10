# Cardiorama

Inżynieria Biomedyczna - Dedykowane Algorytmy Diagnostyki Medycznej - Analiza EKG

## Na początek

Dzięki poniższym instrukcjom pobierzesz i uruchomisz projekt na swoim komputerze.

### Wymagania

Wszystko co znajdziesz poniżej zostało przetestowane na systemach Ubuntu 16.04 i Linux Mint 18 z CMake w wersji 3.5.1. i GCC w wersji 5.4.0

Projekt wykorzystuje następujące biblioteki zewnętrzne:
* CURL
* OpenBLAS
* LAPACK
* SuperLU
* ARPACK

Dodatkowo do każdej z bibliotek należy pobrać pliki deweloperskie. Na przykład instalując paczkę "lapack", zainstaluj również "lapack-dev" lub "lapack-development".

Dla przykładu, na Linux Mint 18 powinnno wystarczyć:
```
$ sudo apt-get install libcurl4-openssl-dev libopenblas-dev liblapack-dev libsuperlu-dev libarpack2-dev
```

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
