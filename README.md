# Projekt przejściowy

## Najnowsze zmiany
**UWAGA!** Zmiana nazwy katalogu ze źródłami na **src** oraz zmiana nazw kilku plików *.cc i *.hh oraz pluginów!

Plik **gui.ini** nie powinien być edytowany, ponieważ chcemy żeby nakładka uruchamiała sie tylko dla naszego pliku world. Dlatego plik usunięto z repozytorium, a jego zawartość w obrazie powinna pozostać domyślna, czyli:
```
[geometry]
x=0
y=0
```
W związku z powyższym zaktualizowano plik **laboratorium_L15.world**.

Dodano plugin world odpowiadający za zarządzanie obiektami. Zapewniono komunikację typu Publisher-Subscriber między pluginami.

Dodano okno konfiguracji świata i obsługę dodawania oraz usuwania modeli.

## Jak zacząć
Aby zbudować projekt należy wykonać w folderze **src**:
```
mkdir build
cd build
cmake ../
make
```
Zbudowane pluginy z rozszerzeniem **.so** należy umieścić w katalogu
```
/root/.gazebo/plugins/
```
W przypdaku dodania nowych zasobów lub modyfikacji (np. ikony przycisków) należy dodać je do katalogu
```
/root/.gazebo/res/
```
Modele obiektów Gazebo znajdują się w katalogu
```
/root/.gazebo/models/
```
