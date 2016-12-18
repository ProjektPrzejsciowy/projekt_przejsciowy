# Projekt przejściowy

## Najnowsze zmiany
Dodano wczytywanie sali z poziomu okna konfiguracji świata.

**UWAGA!** Zaktualizowano plik **l15.world**, który teraz nie ładuje domyślnie modeli, dlatego po uruchomieniu Gazebo świat jest pusty (tylko ground_plane i oświetlenie).

Konfiguracja wybranych pomieszczeń znajduje się tymczasowo w katalogu **world** i ma postać plików tekstowych, w których zapisane są nazwy modeli wraz z ich pozycją i orientacją.

## Jak zacząć
Aby zbudować projekt należy wykonać w folderze **catkin_ws**:
```
catkin_make
```
Ścieżkę folderu, w którym znajdują się pluginy z rozszerzeniem **.so** należy dodać do zmiennej środowiskowej **GAZEBO_PLUGIN_PATH**:
```
export GAZEBO_PLUGIN_PATH='/root/catkin_ws/devel/lib/'
```
Najlepiej jest dodać powyższą linię do pliku **.bashrc**.

Uruchamianie gazebo w połączeniu z rosem:
```
roslaunch projekt_przejsciowy l15.launch &
```

## Dodatkowe informacje
W przypadku dodania nowych zasobów lub modyfikacji istniejących (np. ikony przycisków) należy dodać je do katalogu:
```
/root/.gazebo/res/
```
Modele obiektów Gazebo znajdują się w katalogu:
```
/root/.gazebo/models/
```
