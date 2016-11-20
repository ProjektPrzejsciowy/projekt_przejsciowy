# Projekt przejsciowy

## Jak zacząć 
Plik gui.ini należy umieścić w folderze /root/.gazebo/
Aby zbudować projekt należy wykonać w folderze pp_gazebo_plugin:
'''bash
mkdir build
cd build
cmake ../
make
'''

oraz dodać folder build do zmiennej środowiskowej GAZEBO_PLUGIN_PATH, będąc w folderze build wykonaj:
'''
export GAZEBO_PLUGIN_PATH=`pwd`
'''
