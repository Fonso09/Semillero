#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"


Image::Image(const char* filename){
    if(read(filename)){
        printf("Leíste %s\n", filename);
        size = w*h*channels; // declaramos el tamaño de la imagen
    } else{
        printf("Falló leyendo %s\n", filename);
    }
} //constructor que solo tenga que recibir el nombre del archivo 


Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
    size = w*h*channels; // declaramos el tamaño de la imagen
    data = new uint8_t[size];

} // crear imagen vacía para manipular


Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
    memcpy(data, img.data, size);
} //constructor para poder copiar imágenes


Image::~Image(){
    stbi_image_free(data); // función de la librería de stb_image.h

}  // destructor de Imagen


bool Image:: write(const char* filename){
    //Primero vamos a verificar qué extensión es la imagen que vamos a utilizar
    ImageType type =getFileType(filename);
    int success; // los types regresan un entero
    switch (type)
    {
    case PNG:
        success = stbi_write_png(filename, w,  h, channels, data, w*channels); // todas estas funciones se pueden ver en la biblioteca stb_image_write.h, cada una de las estructuras de cada función se pueden ver en esa librería
        break;
    case JPG:
        success = stbi_write_jpg(filename, w,  h, channels, data, 100); // el 100 se refiere a la quiality
        break;
    case BMP:
        success = stbi_write_bmp(filename, w,  h, channels, data);
        break;
    case TGA:        
        success = stbi_write_tga(filename, w,  h, channels, data);
        break;
    }
    return success != 0 ; 

}


bool Image::  read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0); // puedes ver la documentación en stb_image pero lo que hace el último cero es que forza la cantidad de canales deseados, se deja en cero para que no fuerce nada
    return data != NULL;
}

ImageType Image:: getFileType(const char* filename){
    const char* ext = strrchr(filename, '.'); //cogemos la extensión del filename de la imagen
    if(ext != NULL){  //Solo si encuentra el . en el filename
       if(strcmp(ext, ".png")==0) { //strcmp es string compare si es 0 es que es png, es coincidente
            return PNG;
       }else if(strcmp(ext, ".jpg")==0){
            return JPG;
       }else if(strcmp(ext, ".bmp")==0){
            return BMP;
       }else if(strcmp(ext, ".tga")==0){
        return TGA;
        } 
    }
    return PNG; // retornamos png por si no llega a detectar ninguna de las anteriores en los if vistos
}

Image& Image::grayscale_promedio(){
    /*lo que se hace en este método es que suma todos los canales de color y los divide entre tres
    red + blue + green/3, hace un promedio y pone ese valor en cada pixel
    */
    if(channels < 3){
       printf("la imagen %p tiene menos de 3 canales, se asumen que ya está en escala de grises", this);    
    } else{
        for(int i=0; i<size; i+=channels){
            int gray = (data[i]+ data[i+1]+ data[i+2])/3; //suma los tres canales del pixel y lo divide por tres para poner el valor promediado
            memset(data+i, gray, 3); 
        }
    }
    return *this;
}
Image& Image::grayscale_lum(){
   /*
   */ 
}
