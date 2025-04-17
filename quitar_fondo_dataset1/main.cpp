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
        //Preprocesado para aumentar la intensidad de los bordes (cambio imperceptible la verdad xd)
        cv::Mat blur;
        cv::GaussianBlur(imagenes[i], blur, cv::Size(0, 0), 3);
        cv::Mat detalle;
        cv::addWeighted(imagenes[i], 1.5, blur, -0.5, 0, detalle); //añade peso de 1.5 a la imagen original y -0.5 a la imagen detalle

        cv::Mat gris;
        cv::cvtColor(detalle, gris, cv::COLOR_BGR2GRAY);
        cv::Mat bordes;
        cv::Canny(gris, bordes, 50, 150);
        //intentaremos usar MORPH_CLOSE a aver si logra cerrar los bordes, lo hacemos 5 veces seguidas para intensificar el efecto.
        cv::morphologyEx(bordes, bordes, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), 5);
        std::vector<std::vector<cv::Point>> contornos;
        cv::findContours(bordes, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        cv::Mat mascara = cv::Mat::zeros(imagenes[i].size(), CV_8UC1); //creamos mascara de un canal de 8 bits (puesto que es binarizada)
        for(const auto& contorno : contornos){
            double area = cv::contourArea(contorno); //calcula el area de cada contorno que hay en la lista
            if(area> 500){ //este umbral no importa tanto (ver nota obsidian para ver el porqué)
                cv::drawContours(mascara, std::vector<std::vector<cv::Point>>{contorno}, -1, 255, cv::FILLED); //rellenamos lo que hay en los contornos que superan el umbral
            }
        }

        //podemos hacer un posprocesado similiar al preprocesado a las mascaras
        cv::morphologyEx(mascara, mascara, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), 5);
        cv::Mat planta_sin_fondo;
        cv::bitwise_and(imagenes[i],imagenes[i], planta_sin_fondo, mascara);

        char filename[200]; 
        sprintf(filename, "//192.168.1.210/papi/Fonsito/images_semillero/learn_output/%d.jpg",i);
        cv::imwrite(filename, planta_sin_fondo);
    }
    return 0;
}

//haacemos esta funcion para guardar varias imagenes, como el datast1 de la albahaca es de 40 imagenes
//podemos hacer esto, si fueran muchas mas imagenes seria mala idea que las guardemos en la RAM
std::vector<cv::Mat>load_images(int cantidad){
    char filename[200];
    std::vector<cv::Mat> imagenes;
    for(int i=0; i<cantidad; i++){
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