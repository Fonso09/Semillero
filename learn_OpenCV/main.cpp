#include <opencv2/opencv.hpp>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    cv::Mat img = cv::imread("//192.168.1.210/papi/Fonsito/images_semillero/learn/imagen_test1.jpg"); //Para leer una imagen se hace con cv::imread y eso lo guardamos en una variable tipo cv::Mat llamada img

    //vamos a depurar si podemos abrir la imagen, si no se puede se cierra el programa con este mensaje
    if(img.empty()){
        std::cerr <<"No se pudo abrir la imagen\n";
        return -1;
    }
    cv::imshow("Imagen original", img);
    for(int j=0; j<img.rows; j++){
        for(int i=0; i<img.cols; i++){
            cv::Vec3b& pixel = img.at<cv::Vec3b>(j,i);
            pixel[0]= 255-pixel[0];
            pixel[1]= 255-pixel[1];
            pixel[2]= 255-pixel[2];
            

        }
    }

    cv::imshow("Resultado colores invertidos", img);
    cv::waitKey(0);


    return 0; 
}