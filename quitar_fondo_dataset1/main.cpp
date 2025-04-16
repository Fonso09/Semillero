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
    
    //probaremos normalizar la luz de todas las fotos

    for(int i=0; i<cantidad; i++){
        //PREPROCESAMIENTO:
        //primero es necesario pasar la imagen a espacio de color HSV
        //una vez ya en HSV separamos los canales H,S,V. Puesto que V es el que nos interesa al ser el brillo.
        //entonces ecualizamos el valor del brillo, haciendo que aumente el contraste viendo mucho mejor los detalles
        //por ultimo unimos los canales y los convertimos a BGR para guardar en una nueva carpeta
        cv::Mat hsv;
        cv::cvtColor(imagenes[i], hsv, cv::COLOR_BGR2HSV);

        std::vector<cv::Mat> canales;
        cv::split(hsv, canales); //se guarda en orden H->0, S->1 y V->2

        cv::equalizeHist(canales[2], canales[2]); //guardamos el V equializado en el mismo vector, sobreescribimos basicamente
        cv::merge(canales, hsv); //unimos los tres canales con V modificado

        //PROCESAMIENTO
        //elegimos valores de verdes bajos y verdes altos:
        cv::Scalar verde_bajo(35, 40, 40);   //esta en formato HSV
        cv::Scalar verde_alto(85, 255, 255);

        cv::Mat mascara;
        cv::inRange(hsv, verde_bajo, verde_alto, mascara); // hsv in, mascara=out, evalua si los pixeles en hsv estan dentro del rango, si si hace que sea blanco si no es negro
        //mascara es una imagen igual de tamaño que la anterior solo que es de un solo canal
        //por eso ser hara bitwise and posteriormente
        
        //como ya se tiene la mascara muy probablemente tiene ruido por el aumento de contraste en el preprocesamiento
        //y por obtener la mascara

        cv::morphologyEx(mascara, mascara, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1, -1), 1); //puntos blancos indeseables
        cv::morphologyEx(mascara, mascara, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1, -1), 1); //puntos negros indeseables (si elimina los colores que deseamos analizar modificar este filtro)

        //como mascara solo es una imagen de un canal (imagen binaria) tenemos que hacer bitwiseAND para que extraiga la planta del fondo

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