set -e

cd /c/Users/USUARIO/Desktop/Semillero/learn_OpenCV/build
/usr/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
