set -e

cd /c/Users/USUARIO/Desktop/Semillero/quitar_fondo_dataset1/build
/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
