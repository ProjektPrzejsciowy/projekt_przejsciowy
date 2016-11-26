# Projekt przejściowy

## Najnowsze zmiany
Plik **gui.ini** nie powinien być edytowany, ponieważ chcemy żeby nakładka uruchamiała sie tylko dla naszego pliku world. Dlatego plik usunięto z repozytorium, a jego zawartość w obrazie powinna pozostać domyślna, czyli:
```
[geometry]
x=0
y=0
```
W związku z powyższym poprawiono plik **laboratorium_L15.world** między innymi dodając:
```
<gui>
  <plugin name="PluginGUI" filename="libpp_gazebo_plugin.so"/>
</gui>
```

## Jak zacząć
Aby zbudować projekt należy wykonać w folderze **pp_gazebo_plugin**:
```
mkdir build
cd build
cmake ../
make
```
oraz dodać utworzony folder **build** do zmiennej środowiskowej **GAZEBO_PLUGIN_PATH**. Tymczasowym rozwiązaniem jest wykonywanie w folderze:
```
export GAZEBO_PLUGIN_PATH=`pwd`
```
Lepszym rozwiązaniem jest dodanie powyższej linii do pliku **.bashrc** (zamiast `pwd` należy podać pełną ścieżkę).

Ponadto zawartość folderu **models** powinno się skopiować do folderu:
```
~/.gazebo/models
```

