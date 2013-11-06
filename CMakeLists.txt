# Der Projektname
project(TempSensor)

# Minimal benötigte CMake-Version wenn z.B. bestimmte CMake-Kommandos benutzt werden
cmake_minimum_required(VERSION 2.6)

# CMake soll auch in diesen Verzeichnissen weitersuchen
add_subdirectory(lib)
add_subdirectory(app)
