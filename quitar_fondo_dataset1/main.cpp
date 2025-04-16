#include <opencv2/opencv.hpp>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<sstream>
std::vector<cv::Mat>load_images(int cantidad);

int main(){
    int cantidad = 40; 
    std::vector<cv::Mat> imagenes = load_images(cantidad);
    printf("se cargaron %d imagenes correctamente", imagenes.size());
    for(int i=0; i<cantidad; i++){
        cv::Mat gris;
        cv::cvtColor(imagenes[i], gris, cv::COLOR_BGR2GRAY);
    
        cv::Mat bordes;
        cv::Canny(gris, bordes, 50, 150);

        char filename[200]; 
        sprintf(filename, "//192.168.1.210/papi/Fonsito/images_semillero/learn_output/%d.jpg",i);
        cv::imwrite(filename, bordes);
    }
    return 0;
}

//haacemos esta funcion para guardar varias imagenes, como el datast1 de la albahaca es de 40 imagenes
//podemos hacer esto, si fueran muchas mas imagenes seria mala idea que las guardemos en la RAM
std::vector<cv::Mat>load_images(int cantidad){
    char filename[200];
    std::vector<cv::Mat> imagenes;
    for(int i=0; i<=cantidad; i++){
        sprintf(filename, "//192.168.1.210/papi/Fonsito/images_semillero/dataset_Peronospora_belbahrii/%d.jpg",i);
        cv::Mat img =cv::imread(filename);
        if(img.empty()){
            std::cerr << "No se pudo cargar la imagen: "<< filename << std::endl; //forma para mostrar el error por consola
            continue;
        }

        imagenes.push_back(img); //ponemos img al final del vector imagenes
    }

    return imagenes;
}