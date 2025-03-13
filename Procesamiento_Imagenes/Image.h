#include <stdint.h>
#include <cstdio>

enum ImageType{  //Un enum de las dstintas extensiones de imágenes que se pueden abrir en el programa usando las librerías. 
    PNG, JPG, BMP, TGA
}; 

struct Image{
    uint8_t* data = NULL ;
    size_t size = 0;
    int w;
    int h;
    int channels; // los canales será cuántos valores de colo habrá por pixel, o sea RGB es 3
    Image(const char* filename); //constructor que solo tenga que recibir el nombre del archivo 
    Image(int w, int h, int channels); // crear imagen vacía para manipular
    Image(const Image& img); //constructor para poder copiar imágenes
    ~Image();  // destructor de Image

    bool read (const char* filename);  //El constructor llamará esta función
    bool write(const char* filename);

    ImageType getFileType(const char* filename);
    
    Image& grayscale_promedio(); // filtros para escala de grises
    Image& grayscale_lum();
    Image& convolution();

};

