#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("//10.243.55.7/papi/Fonsito/images_semillero/learn/imagen_test1.jpg"); //Para leer una imagen se hace con cv::imread y eso lo guardamos en una variable tipo cv::Mat llamada img

    //vamos a depurar si podemos abrir la imagen, si no se puede se cierra el programa con este mensaje
    if(img.empty()){
        std::cerr <<"No se pudo abrir la imagen\n";
        return -1;
    }

    cv::imshow("Imagen prueba", img); //funcion para mostrar la imgen abierta
    cv::waitKey(0);


    return 0; 
}