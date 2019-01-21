# Cardiorama

Inżynieria Biomedyczna - Dedykowane Algorytmy Diagnostyki Medycznej - Analiza EKG

## TODO
### Klasy bazowe modułów

- [x] EcgBaseline
- [ ] RPeaks
- [x] Waves
- [x] TWaves
- [x] Hrv1
- [x] Hrv2
- [ ] HrvDfa
- [ ] HeartClass

## Quick start

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
### Pobierz dane
```
$ sh -x download.sh
```
Jeżeli chcesz aby twoje dane zawsze się automatycznie pobierały (np. ktoś będzie ich potrzebować) w foldezrze data znajduje się plik files.txt, dodaj do niego w nowej linii link do pobrania danych. W pliku już są przykładowe linki.
##### !Wszystkie dane powinny znajdować się tylko i wyłącznie  w folderze data!

### Skonfiguruj i skompiluj
```
$ cd build
$ cmake ..
$ make
```

### Uruchom
 ```./cardiorama``` 
 lub
 ```/your/path/to/repo/build/cardiorama```


### Bonus
Wklej to do swojego ```.bashrc``` i zapomnij co tu widziałeś.
```
alias cardio="your/path/to/repo/cardio.sh"
```
