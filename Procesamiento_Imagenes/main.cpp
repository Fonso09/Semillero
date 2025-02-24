#include "Image.h"



int main(){
    Image test("test.jpg"); //probamos constructor para ver si estamos leyendo bien la imagen
    test.write("new.png"); //escribimos (o sea creamos una nueva imagen) .png para ver si está funcionando bien la función de write
    Image copy = test; //vemos si estamos copiando bien las imágenes

    for (int i= 0; i< copy.w*copy.channels*90; ++i){  //vamos a poner la primera línea de pixeles de la imagen como en blanco, si multiplicamos por otro numero el w*channels será el número de filas que queremos pintar de blanco
        copy.data[i] = 255; // se pone la primera línea blanco porque hicimos w*channels y 255 es para color blanco, esto es a la imagen que copiamos
    }
    copy.write("copy.png"); //creamos la nueva imagen de la primera línea con los pixeles en blanco de la copia
    Image blank(100,100,3); //creamos imagen en blanco
    blank.write("blank.jpg"); //Escribimos la imagen en blanco en formato jpg
    return 0;
}