# Schach-Spiel
Ich habe mithife der Qt-bibliothek in C++ ein Schach Spiel entwickelt. Das Spiel kann dabei mithilfe von Clicks bedient werden.

# Das Programm zum laufen bekommen

## Voraussetzungen
- Man benötigt Clion
- Qt(Bibliothek) 6 installieren
->Dabei ist darauf zu achten das auch der MSVC Compiler installliert wird.
- Die Cmake kann man automatisch generieren lassen durch clion indem man bei der Projekterstellung auf "Qt Widgets executable" drückt.
- Cmake Datei befindet sich auch in diesem Ordner

## Projekt in CLion einrichten

1. CMake konfigurieren
CLion erkennt das Projekt anhand der CMakeLists.txt. Man muss aber unter:

 File > Settings > Build, Execution, Deployment > CMake:

CMake-Profil auswählen oder erstellen

Falls Qt nicht erkannt wird: Setze CMAKE_PREFIX_PATH manuell auf den Qt-Installationspfad

z. B.:CMAKE_PREFIX_PATH=C:\Qt\6.6.2\MSVC_19

2. Qt in CLion erkennen lassen
Wenn Qt nicht automatisch gefunden wird:

 File > Settings > Kits oder Toolchains

Setze Umgebungsvariable CMAKE_PREFIX_PATH auf Qt-Installationsordner (...\Qt\6.6.2\MSVC_19)

3. Setzen des Arbeitsverzeichnises um die Bilder zu laden.
Run>edit Configurations>Working directory

Projektordner setzen als = \$PROJECT\_DIR\$




# Lizenshinweise
Dieses Projekt verwendet die Qt-Bibliothek (https://www.qt.io),
die unter der GNU Lesser General Public License (LGPL) Version 3 lizenziert ist.

Eine Kopie der LGPL v3 finden Sie hier:
https://www.gnu.org/licenses/lgpl-3.0.html
